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
#include <iostream>
#include "boost/program_options.hpp"

int main( int argc, char **argv ){
    using namespace boost;
    namespace opts = boost::program_options;

    std::string eleInputFile;
    std::string phoInputFile;
    std::string rootFileOut;
    std::string outDir;
    bool        boostedSystematics;
    bool        usingPions;

    opts::options_description desc("Main Options");
    
    desc.add_options()
        ("eleInputFile", opts::value<std::string>(&eleInputFile), "Electron Input File")
        ("phoInputFile", opts::value<std::string>(&phoInputFile), "Photon Input File")
        ("rootFileOut", opts::value<std::string>(&rootFileOut), "Output Root File Name")
        ("outDir", opts::value<std::string>(&outDir), "Output Directory")
        ("boostedSystematics", opts::value<bool>(&boostedSystematics), "Boost systematics to cover method uncertainties")
        ("usingPions", opts::value<bool>(&usingPions), "If you are using pions instead of photons for this production, enable this option");        
    ;

    if( usingPions ) std::cout << "You are using pions" << std::endl;

    opts::variables_map v_map;
    opts::store(opts::parse_command_line(argc, argv, desc), v_map);
    opts::notify(v_map);
    
    myHistogramProducer hist_producer;
    myLookUpTableProducer table_producer;
    mySystematicsPlotter syst_plotter;

    if( usingPions ) hist_producer.produce_PION_Histograms(eleInputFile, phoInputFile, rootFileOut, outDir);
    else hist_producer.produce_FNUF_Histograms(eleInputFile, phoInputFile, rootFileOut, outDir);

    rootFileOut = outDir+rootFileOut;
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
