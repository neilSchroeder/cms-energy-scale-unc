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
#include "boost/program_options.hpp"

std::string DIRECTORY_NAME = "fnuf_systematics";
int main( int argc, char **argv ){
    using namespace boost;
    namespace opts = boost::program_options;

    std::string eleInputFile;
    std::string phoInputFile;
    std::string rootFileOut = "fnuf_systematics_out";
    bool        boostedSystematics = 1;
    bool        usingPions = 0;
    bool        force = 0;

    opts::options_description desc("Main Options");
    
    desc.add_options()
        ("eleInputFile", opts::value<std::string>(&eleInputFile), "Electron Input File")
        ("phoInputFile", opts::value<std::string>(&phoInputFile), "Photon Input File")
        ("rootFileOut", opts::value<std::string>(&rootFileOut), "Output Root File Name (default is 'fnuf_systematics_out')")
        ("outDir", opts::value<std::string>(&DIRECTORY_NAME), "Output Directory (default is 'fnuf_systematics')")
        ("boostedSystematics", opts::value<bool>(&boostedSystematics), "Boost systematics to cover method uncertainties (default is 1)")
        ("usingPions", opts::value<bool>(&usingPions), "If you are using pions instead of photons for this production, enable this option (default is 0)");        
        ("force", opts::value<bool>(&force), "If you want to reproduce your root file, turn this option on (default is 0)");        
    ;

    if( usingPions ) std::cout << "You are using pions" << std::endl;

    opts::variables_map v_map;
    opts::store(opts::parse_command_line(argc, argv, desc), v_map);
    opts::notify(v_map);
    
    myHistogramProducer hist_producer;
    myLookUpTableProducer table_producer;
    mySystematicsPlotter syst_plotter;


    if( usingPions ) hist_producer.produce_PION_Histograms(eleInputFile, phoInputFile, rootFileOut, DIRECTORY_NAME);
    else{
        std::string temp_filename = DIRECTORY_NAME+rootFileOut+".root";
        std::cout << temp_filename << std::endl;
        TFile * file_exists = TFile::Open(temp_filename.c_str(),"READ");
        
        if(!file_exists || force) hist_producer.produce_FNUF_Histograms(eleInputFile, phoInputFile, rootFileOut, DIRECTORY_NAME);
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

    return 0;
}
