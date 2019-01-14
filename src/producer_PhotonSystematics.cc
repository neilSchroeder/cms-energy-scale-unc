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
#include "../interface/frameworkSystematicsProducer.h"
#include "../interface/frameworkSystematicsPlotter.h"

int main( int argc, char **argv ){
    
    myHistogramProducer hist_producer;
    mySystematicsProducer syst_producer;
    mySystematicsPlotter syst_plotter;

    std::string thisRootFile = hist_producer.produce_FNUF_Histograms(argv, 1);

    syst_producer.produce_LookUpTables(thisRootFile);
    syst_plotter.produce_2016_2017_Plots(thisRootFile);

    return 0;
}
