/*
 *
 *
 *
 * This is the macro that does all the plotting for the FNUF Framework.
 * It takes in a file with a list of root files containing the tree "data" in a directory
 *      titled "fnufTree"
 * 
 * From this list of root files it will do 3 things:
 *      1) make a root file containing histograms in the categories described in AN-18-079
 *          whose name is based on the name of the file passed to this function.
 *      2) use the root file it has just created to make two sets of plots:
 *          a) 2D Photon Systematic Uncertainty plots
 *          b) Photon Systematic Uncertainty plots showing the systematics for ECAL's 
 *              EE and EB under conditions corresponding to the radiation damage for 
 *              2016 and 2017.
 *      3) simultaneously a text file containing the systematic uncertainties on the 
 *          photon energy scale (in %) corresponding the the entries in the plots for 2b.
 *
 *
 *
 *
 *
 */

#include "../interface/frameworkHistogramProducer.h"
#include "../interface/frameworkLUTproducer.h"
#include "../interface/frameworkSystematicsPlotter.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
#include "boost/program_options.hpp"

//#define ALT_R9

std::string DIRECTORY_NAME = "fnuf_systematics";
std::string info = "[INFO] ";
std::string error = "[ERROR] ";

#ifndef ALT_R9
	int numR9bins = 5;
	double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00}; 
#else
    int numR9bins = 6;
    double r9Bins [7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00};
#endif

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.566, 1.8, 2.1, 2.5};

bool _flag_crossChecks = false;
bool _flag_truncate = false;
bool _flag_tex = true;
bool _flag_ratio = false;
bool _flag_median = false;

int main( int argc, char **argv ){
    using namespace boost;
    namespace opts = boost::program_options;

    std::string eleInputFile;
    std::string phoInputFile;
    std::string eleInputFile2;
    std::string phoInputFile2;
    std::string rootFileOut = "fnuf_systematics_out";
    std::string rootFileOut2 = "fnuf_systematics_out2";
    bool        boostedSystematics = 1;
    bool        usingPions = 0;
    bool        force = 0;

    opts::options_description desc("Main Options");
    
    desc.add_options()
        ("help", "print help message")
        ("eleInputFile", opts::value<std::string>(&eleInputFile), "Electron input file")
        ("phoInputFile", opts::value<std::string>(&phoInputFile), "Photon input file")
        ("eleInputFile2", opts::value<std::string>(&eleInputFile2), "Second electron input file (to be used with --ratio)")
        ("phoInputFile2", opts::value<std::string>(&phoInputFile2), "Second photon input file (to be used with --ratio)")
        ("rootFileOut", opts::value<std::string>(&rootFileOut), "Output root file name, default is 'fnuf_systematics_out'")
        ("rootFileOut2", opts::value<std::string>(&rootFileOut2), "Second output root file name, default is 'fnuf_systematics_out2'")
        ("outDir", opts::value<std::string>(&DIRECTORY_NAME), "Output Directory (default is 'fnuf_systematics')")
        ("boost", opts::bool_switch(&boostedSystematics), "Boost systematics to cover method uncertainties (enabled by default)")
        ("tex", opts::bool_switch(&_flag_tex), "Use this option to turn off producing .tex tables")
        ("usingPions", opts::bool_switch(&usingPions), "If you are using pions instead of photons for this production, enable this option (disabled by default)")        
        ("crossCheck", opts::bool_switch(&_flag_crossChecks), "Produce crossCheck plots")
        ("trunc", opts::bool_switch(&_flag_truncate), "Activating this option will truncate plots before obtaining the mean")
        ("median", opts::bool_switch(&_flag_median), "Use the median instead of the mean to evaluate systematics")
        ("ratio", opts::bool_switch(&_flag_ratio), "DEVELOPER OPTION, USE WITH CAUTION \nwill produce the ratio files used for the corrections")
        ("force", opts::bool_switch(&force), "If you want to reproduce your root file, turn this option on (disabled by default)")        
    ;


    opts::variables_map v_map;
    opts::store(opts::parse_command_line(argc, argv, desc), v_map);
    opts::notify(v_map);

    if(v_map.count("help")){
        std::cout << desc << std::endl;
        return 0;
    }

    ////////////////////////
    // handle some errors //
    ////////////////////////

    if(!v_map.count("eleInputFile")){
        std::cout << error << "you MUST provide an input file using eleInputFile" << std::endl;
        return 1;
    }
    else{
        std::ifstream in(eleInputFile.c_str());
        if(in.peek() == std::ifstream::traits_type::eof()){
            std::cout << error << "eleInputFile: " << eleInputFile << " is empty or does not exist" << std::endl;
            return 1;
        }
    }

    if(!v_map.count("phoInputFile")){
        std::cout << error << "you MUST provide an input file using phoInputFile" << std::endl;
        return 1;
    }
    else{
        std::ifstream in(phoInputFile.c_str());
        if(in.peek() == std::ifstream::traits_type::eof()){
            std::cout << error << "phoInputFile: " << phoInputFile << " is empty or does not exist" << std::endl;
            return 1;
        }
    }

    if(!v_map.count("eleInputFile2") && _flag_ratio){
        std::cout << error << "you MUST provide an input file using eleInputFile2" << std::endl;
        return 1;
    }
    else if(v_map.count("eleInputFile2")){
        std::ifstream in(eleInputFile2.c_str());
        if(in.peek() == std::ifstream::traits_type::eof()){
            std::cout << error << "eleInputFile2: " << eleInputFile2 << " is empty or does not exist" << std::endl;
            return 1;
        }
    }

    if(!v_map.count("phoInputFile2") && _flag_ratio){
        std::cout << error << "you MUST provide an input file using phoInputFile2" << std::endl;
        return 1;
    }
    else if(v_map.count("phoInputFile2")){
        std::ifstream in(phoInputFile2.c_str());
        if(in.peek() == std::ifstream::traits_type::eof()){
            std::cout << error << "phoInputFile2: " << phoInputFile2 << " is empty or does not exist" << std::endl;
            return 1;
        }
    }


    /////////////////////
    // declare classes //
    /////////////////////

    myHistogramProducer hist_producer;
    myLookUpTableProducer table_producer;
    mySystematicsPlotter syst_plotter;

    if(_flag_ratio){
        std::cout << info << "[OPTION --ratio] was provided" << std::endl;
        std::cout << info << "producing ratio systematics using " << std::endl;
        std::cout << info << "[OPTION --eleInputFile] " << eleInputFile << std::endl;
        std::cout << info << "[OPTION --phoInputFile] " << phoInputFile << std::endl;
        std::cout << info << "[OPTION --eleInputFile2] " << eleInputFile2 << std::endl;
        std::cout << info << "[OPTION --phoInputFile2] " << phoInputFile2 << std::endl;

        hist_producer.produce_FNUF_Histograms(eleInputFile, phoInputFile, rootFileOut, DIRECTORY_NAME);
        hist_producer.produce_FNUF_Histograms(eleInputFile2, phoInputFile2, rootFileOut2, DIRECTORY_NAME);

        rootFileOut = DIRECTORY_NAME+rootFileOut;
        rootFileOut2 = DIRECTORY_NAME+rootFileOut2;
        if(rootFileOut.find(".root") == std::string::npos) rootFileOut = rootFileOut+".root";
        if(rootFileOut2.find(".root") == std::string::npos) rootFileOut2 = rootFileOut2+".root";

        table_producer.produce_RatioLookUpTables(rootFileOut2, rootFileOut);
        return 0;
    }

    if( usingPions ){
        std::cout << info << "You are using pions" << std::endl;
        hist_producer.produce_PION_Histograms(eleInputFile, phoInputFile, rootFileOut, DIRECTORY_NAME);
    }
    else{
        std::string temp_filename = DIRECTORY_NAME+"/"+rootFileOut+".root";
        std::cout << info << "Looking for a root file called: " << temp_filename << std::endl;
        if(force) hist_producer.produce_FNUF_Histograms(eleInputFile, phoInputFile, rootFileOut, DIRECTORY_NAME);
        else{
            if( !TFile::Open(temp_filename.c_str(),"READ")) hist_producer.produce_FNUF_Histograms(eleInputFile, phoInputFile, rootFileOut, DIRECTORY_NAME);
            else{
            std::cout << info << "[OPTION --force] not provided \n[INFO] found file: " << temp_filename << std::endl;
            std::cout << info << "Continuing without reproducing root file... " << std::endl;
            }
        }
    }

    rootFileOut = DIRECTORY_NAME+rootFileOut;
    if(rootFileOut.find(".root") == std::string::npos) rootFileOut = rootFileOut+".root";


    if( usingPions ){
        table_producer.produce_PionLookUpTables(rootFileOut, boostedSystematics);
        syst_plotter.produce_2016_2017_PionPlots(rootFileOut, boostedSystematics);
    }
    else{
        table_producer.produce_LookUpTables(rootFileOut, boostedSystematics);
        syst_plotter.produce_2016_2017_Plots(rootFileOut, boostedSystematics);
    }

    if(!_flag_tex){

    /////////////////////////////////////////
    // turn the .dat files into tex tables //
    /////////////////////////////////////////

        std::string energy;
        if(eleInputFile.find("30") != std::string::npos) energy = "30GeV";
        if(eleInputFile.find("45") != std::string::npos) energy = "45GeV";
        if(eleInputFile.find("60") != std::string::npos) energy = "60GeV";
        if(eleInputFile.find("120") != std::string::npos) energy = "120GeV";

        system(std::string("python ./python/createTexTables.py -i './"+DIRECTORY_NAME+"/fnuf_systematics_2016_"+energy+".dat' -o './"+DIRECTORY_NAME+"/tex/fnuf_systematics_2016_"+energy+"'").c_str()); 
        system(std::string("python ./python/createTexTables.py -i './"+DIRECTORY_NAME+"/fnuf_systematics_2017_"+energy+".dat' -o './"+DIRECTORY_NAME+"/tex/fnuf_systematics_2017_"+energy+"'").c_str()); 
        system(std::string("python ./python/createTexTables.py -i './"+DIRECTORY_NAME+"/fnuf_systematics_2018_"+energy+".dat' -o './"+DIRECTORY_NAME+"/tex/fnuf_systematics_2018_"+energy+"'").c_str()); 

    }

    return 0;
}
