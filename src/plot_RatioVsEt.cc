

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <TH1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TPad.h>

void plotForEta(TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, std::string type, int eta);
void plotForEta(TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, std::string type, int eta);
void plotForR9(TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, std::string type, int eta);

bool _flag_altR9 = false;

int main(int argc, char ** argv){

    using namespace boost;
    namespace opts = boost::program_options;

    std::string inputFile;
    std::string outputFile;

    opts::options_description desc("Main Options");

    desc.add_options()
        ("help", "print help message")
        ("inputFile,i", opts::value<std::string>(&inputFile), "Input .dat File")
        ("outputFile,o", opts::value<std::string>(&outputFile), "Output string")
        ("altR9", opts::bool_switch(&_flag_altR9), "alt r9 options")
    ;

    opts::variables_map v_map;
    opts::store(opts::parse_command_line(argc, argv, desc), v_map);
    opts::notify(v_map);

    if(v_map.count("help")){
        std::cout << desc << std::endl;
        return 1;
    }

    std::ifstream in(inputFile.c_str());
    if(in.peek() == std::ifstream::traits_type::eof()){
        std::cout << "[ERROR] the intput file is empty or does not exist" << std::endl; return 2;
    }

    double etBins [5] = {22.5, 37.5, 52.5, 67.5, 172.5};
    TH1F * absEta_0_1_r9_0_1 = new TH1F("absEta_0_1_r9_0_1", "", 4, etBins);
    TH1F * absEta_0_1_r9_1_2 = new TH1F("absEta_0_1_r9_1_2", "", 4, etBins);
    TH1F * absEta_0_1_r9_2_3 = new TH1F("absEta_0_1_r9_2_3", "", 4, etBins);
    TH1F * absEta_0_1_r9_3_4 = new TH1F("absEta_0_1_r9_3_4", "", 4, etBins);
    TH1F * absEta_0_1_r9_4_5 = new TH1F("absEta_0_1_r9_4_5", "", 4, etBins);
    TH1F * absEta_0_1_r9_5_6 = new TH1F("absEta_0_1_r9_5_6", "", 4, etBins);

    TH1F * absEta_1_2_r9_0_1 = new TH1F("absEta_1_2_r9_0_1", "", 4, etBins);
    TH1F * absEta_1_2_r9_1_2 = new TH1F("absEta_1_2_r9_1_2", "", 4, etBins);
    TH1F * absEta_1_2_r9_2_3 = new TH1F("absEta_1_2_r9_2_3", "", 4, etBins);
    TH1F * absEta_1_2_r9_3_4 = new TH1F("absEta_1_2_r9_3_4", "", 4, etBins);
    TH1F * absEta_1_2_r9_4_5 = new TH1F("absEta_1_2_r9_4_5", "", 4, etBins);
    TH1F * absEta_1_2_r9_5_6 = new TH1F("absEta_1_2_r9_5_6", "", 4, etBins);

    TH1F * absEta_2_3_r9_0_1 = new TH1F("absEta_2_3_r9_0_1", "", 4, etBins);
    TH1F * absEta_2_3_r9_1_2 = new TH1F("absEta_2_3_r9_1_2", "", 4, etBins);
    TH1F * absEta_2_3_r9_2_3 = new TH1F("absEta_2_3_r9_2_3", "", 4, etBins);
    TH1F * absEta_2_3_r9_3_4 = new TH1F("absEta_2_3_r9_3_4", "", 4, etBins);
    TH1F * absEta_2_3_r9_4_5 = new TH1F("absEta_2_3_r9_4_5", "", 4, etBins);
    TH1F * absEta_2_3_r9_5_6 = new TH1F("absEta_2_3_r9_5_6", "", 4, etBins);

    TH1F * absEta_3_4_r9_0_1 = new TH1F("absEta_3_4_r9_0_1", "", 4, etBins);
    TH1F * absEta_3_4_r9_1_2 = new TH1F("absEta_3_4_r9_1_2", "", 4, etBins);
    TH1F * absEta_3_4_r9_2_3 = new TH1F("absEta_3_4_r9_2_3", "", 4, etBins);
    TH1F * absEta_3_4_r9_3_4 = new TH1F("absEta_3_4_r9_3_4", "", 4, etBins);
    TH1F * absEta_3_4_r9_4_5 = new TH1F("absEta_3_4_r9_4_5", "", 4, etBins);
    TH1F * absEta_3_4_r9_5_6 = new TH1F("absEta_3_4_r9_5_6", "", 4, etBins);

    TH1F * absEta_4_5_r9_0_1 = new TH1F("absEta_4_5_r9_0_1", "", 4, etBins);
    TH1F * absEta_4_5_r9_1_2 = new TH1F("absEta_4_5_r9_1_2", "", 4, etBins);
    TH1F * absEta_4_5_r9_2_3 = new TH1F("absEta_4_5_r9_2_3", "", 4, etBins);
    TH1F * absEta_4_5_r9_3_4 = new TH1F("absEta_4_5_r9_3_4", "", 4, etBins);
    TH1F * absEta_4_5_r9_4_5 = new TH1F("absEta_4_5_r9_4_5", "", 4, etBins);
    TH1F * absEta_4_5_r9_5_6 = new TH1F("absEta_4_5_r9_5_6", "", 4, etBins);

    TH1F * absEta_5_6_r9_0_1 = new TH1F("absEta_5_6_r9_0_1", "", 4, etBins);
    TH1F * absEta_5_6_r9_1_2 = new TH1F("absEta_5_6_r9_1_2", "", 4, etBins);
    TH1F * absEta_5_6_r9_2_3 = new TH1F("absEta_5_6_r9_2_3", "", 4, etBins);
    TH1F * absEta_5_6_r9_3_4 = new TH1F("absEta_5_6_r9_3_4", "", 4, etBins);
    TH1F * absEta_5_6_r9_4_5 = new TH1F("absEta_5_6_r9_4_5", "", 4, etBins);
    TH1F * absEta_5_6_r9_5_6 = new TH1F("absEta_5_6_r9_5_6", "", 4, etBins);

    TH1F * absEta_6_7_r9_0_1 = new TH1F("absEta_6_7_r9_0_1", "", 4, etBins);
    TH1F * absEta_6_7_r9_1_2 = new TH1F("absEta_6_7_r9_1_2", "", 4, etBins);
    TH1F * absEta_6_7_r9_2_3 = new TH1F("absEta_6_7_r9_2_3", "", 4, etBins);
    TH1F * absEta_6_7_r9_3_4 = new TH1F("absEta_6_7_r9_3_4", "", 4, etBins);
    TH1F * absEta_6_7_r9_4_5 = new TH1F("absEta_6_7_r9_4_5", "", 4, etBins);
    TH1F * absEta_6_7_r9_5_6 = new TH1F("absEta_6_7_r9_5_6", "", 4, etBins);

    TH1F * phoAbsEta_0_1_r9_0_1 = new TH1F("phoAbsEta_0_1_r9_0_1", "", 4, etBins);
    TH1F * phoAbsEta_0_1_r9_1_2 = new TH1F("phoAbsEta_0_1_r9_1_2", "", 4, etBins);
    TH1F * phoAbsEta_0_1_r9_2_3 = new TH1F("phoAbsEta_0_1_r9_2_3", "", 4, etBins);
    TH1F * phoAbsEta_0_1_r9_3_4 = new TH1F("phoAbsEta_0_1_r9_3_4", "", 4, etBins);
    TH1F * phoAbsEta_0_1_r9_4_5 = new TH1F("phoAbsEta_0_1_r9_4_5", "", 4, etBins);
    TH1F * phoAbsEta_0_1_r9_5_6 = new TH1F("phoAbsEta_0_1_r9_5_6", "", 4, etBins);

    TH1F * phoAbsEta_1_2_r9_0_1 = new TH1F("phoAbsEta_1_2_r9_0_1", "", 4, etBins);
    TH1F * phoAbsEta_1_2_r9_1_2 = new TH1F("phoAbsEta_1_2_r9_1_2", "", 4, etBins);
    TH1F * phoAbsEta_1_2_r9_2_3 = new TH1F("phoAbsEta_1_2_r9_2_3", "", 4, etBins);
    TH1F * phoAbsEta_1_2_r9_3_4 = new TH1F("phoAbsEta_1_2_r9_3_4", "", 4, etBins);
    TH1F * phoAbsEta_1_2_r9_4_5 = new TH1F("phoAbsEta_1_2_r9_4_5", "", 4, etBins);
    TH1F * phoAbsEta_1_2_r9_5_6 = new TH1F("phoAbsEta_1_2_r9_5_6", "", 4, etBins);

    TH1F * phoAbsEta_2_3_r9_0_1 = new TH1F("phoAbsEta_2_3_r9_0_1", "", 4, etBins);
    TH1F * phoAbsEta_2_3_r9_1_2 = new TH1F("phoAbsEta_2_3_r9_1_2", "", 4, etBins);
    TH1F * phoAbsEta_2_3_r9_2_3 = new TH1F("phoAbsEta_2_3_r9_2_3", "", 4, etBins);
    TH1F * phoAbsEta_2_3_r9_3_4 = new TH1F("phoAbsEta_2_3_r9_3_4", "", 4, etBins);
    TH1F * phoAbsEta_2_3_r9_4_5 = new TH1F("phoAbsEta_2_3_r9_4_5", "", 4, etBins);
    TH1F * phoAbsEta_2_3_r9_5_6 = new TH1F("phoAbsEta_2_3_r9_5_6", "", 4, etBins);

    TH1F * phoAbsEta_3_4_r9_0_1 = new TH1F("phoAbsEta_3_4_r9_0_1", "", 4, etBins);
    TH1F * phoAbsEta_3_4_r9_1_2 = new TH1F("phoAbsEta_3_4_r9_1_2", "", 4, etBins);
    TH1F * phoAbsEta_3_4_r9_2_3 = new TH1F("phoAbsEta_3_4_r9_2_3", "", 4, etBins);
    TH1F * phoAbsEta_3_4_r9_3_4 = new TH1F("phoAbsEta_3_4_r9_3_4", "", 4, etBins);
    TH1F * phoAbsEta_3_4_r9_4_5 = new TH1F("phoAbsEta_3_4_r9_4_5", "", 4, etBins);
    TH1F * phoAbsEta_3_4_r9_5_6 = new TH1F("phoAbsEta_3_4_r9_5_6", "", 4, etBins);

    TH1F * phoAbsEta_4_5_r9_0_1 = new TH1F("phoAbsEta_4_5_r9_0_1", "", 4, etBins);
    TH1F * phoAbsEta_4_5_r9_1_2 = new TH1F("phoAbsEta_4_5_r9_1_2", "", 4, etBins);
    TH1F * phoAbsEta_4_5_r9_2_3 = new TH1F("phoAbsEta_4_5_r9_2_3", "", 4, etBins);
    TH1F * phoAbsEta_4_5_r9_3_4 = new TH1F("phoAbsEta_4_5_r9_3_4", "", 4, etBins);
    TH1F * phoAbsEta_4_5_r9_4_5 = new TH1F("phoAbsEta_4_5_r9_4_5", "", 4, etBins);
    TH1F * phoAbsEta_4_5_r9_5_6 = new TH1F("phoAbsEta_4_5_r9_5_6", "", 4, etBins);

    TH1F * phoAbsEta_5_6_r9_0_1 = new TH1F("phoAbsEta_5_6_r9_0_1", "", 4, etBins);
    TH1F * phoAbsEta_5_6_r9_1_2 = new TH1F("phoAbsEta_5_6_r9_1_2", "", 4, etBins);
    TH1F * phoAbsEta_5_6_r9_2_3 = new TH1F("phoAbsEta_5_6_r9_2_3", "", 4, etBins);
    TH1F * phoAbsEta_5_6_r9_3_4 = new TH1F("phoAbsEta_5_6_r9_3_4", "", 4, etBins);
    TH1F * phoAbsEta_5_6_r9_4_5 = new TH1F("phoAbsEta_5_6_r9_4_5", "", 4, etBins);
    TH1F * phoAbsEta_5_6_r9_5_6 = new TH1F("phoAbsEta_5_6_r9_5_6", "", 4, etBins);

    TH1F * phoAbsEta_6_7_r9_0_1 = new TH1F("phoAbsEta_6_7_r9_0_1", "", 4, etBins);
    TH1F * phoAbsEta_6_7_r9_1_2 = new TH1F("phoAbsEta_6_7_r9_1_2", "", 4, etBins);
    TH1F * phoAbsEta_6_7_r9_2_3 = new TH1F("phoAbsEta_6_7_r9_2_3", "", 4, etBins);
    TH1F * phoAbsEta_6_7_r9_3_4 = new TH1F("phoAbsEta_6_7_r9_3_4", "", 4, etBins);
    TH1F * phoAbsEta_6_7_r9_4_5 = new TH1F("phoAbsEta_6_7_r9_4_5", "", 4, etBins);
    TH1F * phoAbsEta_6_7_r9_5_6 = new TH1F("phoAbsEta_6_7_r9_5_6", "", 4, etBins);

    TH1F * eleAbsEta_0_1_r9_0_1 = new TH1F("eleAbsEta_0_1_r9_0_1", "", 4, etBins);
    TH1F * eleAbsEta_0_1_r9_1_2 = new TH1F("eleAbsEta_0_1_r9_1_2", "", 4, etBins);
    TH1F * eleAbsEta_0_1_r9_2_3 = new TH1F("eleAbsEta_0_1_r9_2_3", "", 4, etBins);
    TH1F * eleAbsEta_0_1_r9_3_4 = new TH1F("eleAbsEta_0_1_r9_3_4", "", 4, etBins);
    TH1F * eleAbsEta_0_1_r9_4_5 = new TH1F("eleAbsEta_0_1_r9_4_5", "", 4, etBins);
    TH1F * eleAbsEta_0_1_r9_5_6 = new TH1F("eleAbsEta_0_1_r9_5_6", "", 4, etBins);

    TH1F * eleAbsEta_1_2_r9_0_1 = new TH1F("eleAbsEta_1_2_r9_0_1", "", 4, etBins);
    TH1F * eleAbsEta_1_2_r9_1_2 = new TH1F("eleAbsEta_1_2_r9_1_2", "", 4, etBins);
    TH1F * eleAbsEta_1_2_r9_2_3 = new TH1F("eleAbsEta_1_2_r9_2_3", "", 4, etBins);
    TH1F * eleAbsEta_1_2_r9_3_4 = new TH1F("eleAbsEta_1_2_r9_3_4", "", 4, etBins);
    TH1F * eleAbsEta_1_2_r9_4_5 = new TH1F("eleAbsEta_1_2_r9_4_5", "", 4, etBins);
    TH1F * eleAbsEta_1_2_r9_5_6 = new TH1F("eleAbsEta_1_2_r9_5_6", "", 4, etBins);

    TH1F * eleAbsEta_2_3_r9_0_1 = new TH1F("eleAbsEta_2_3_r9_0_1", "", 4, etBins);
    TH1F * eleAbsEta_2_3_r9_1_2 = new TH1F("eleAbsEta_2_3_r9_1_2", "", 4, etBins);
    TH1F * eleAbsEta_2_3_r9_2_3 = new TH1F("eleAbsEta_2_3_r9_2_3", "", 4, etBins);
    TH1F * eleAbsEta_2_3_r9_3_4 = new TH1F("eleAbsEta_2_3_r9_3_4", "", 4, etBins);
    TH1F * eleAbsEta_2_3_r9_4_5 = new TH1F("eleAbsEta_2_3_r9_4_5", "", 4, etBins);
    TH1F * eleAbsEta_2_3_r9_5_6 = new TH1F("eleAbsEta_2_3_r9_5_6", "", 4, etBins);

    TH1F * eleAbsEta_3_4_r9_0_1 = new TH1F("eleAbsEta_3_4_r9_0_1", "", 4, etBins);
    TH1F * eleAbsEta_3_4_r9_1_2 = new TH1F("eleAbsEta_3_4_r9_1_2", "", 4, etBins);
    TH1F * eleAbsEta_3_4_r9_2_3 = new TH1F("eleAbsEta_3_4_r9_2_3", "", 4, etBins);
    TH1F * eleAbsEta_3_4_r9_3_4 = new TH1F("eleAbsEta_3_4_r9_3_4", "", 4, etBins);
    TH1F * eleAbsEta_3_4_r9_4_5 = new TH1F("eleAbsEta_3_4_r9_4_5", "", 4, etBins);
    TH1F * eleAbsEta_3_4_r9_5_6 = new TH1F("eleAbsEta_3_4_r9_5_6", "", 4, etBins);

    TH1F * eleAbsEta_4_5_r9_0_1 = new TH1F("eleAbsEta_4_5_r9_0_1", "", 4, etBins);
    TH1F * eleAbsEta_4_5_r9_1_2 = new TH1F("eleAbsEta_4_5_r9_1_2", "", 4, etBins);
    TH1F * eleAbsEta_4_5_r9_2_3 = new TH1F("eleAbsEta_4_5_r9_2_3", "", 4, etBins);
    TH1F * eleAbsEta_4_5_r9_3_4 = new TH1F("eleAbsEta_4_5_r9_3_4", "", 4, etBins);
    TH1F * eleAbsEta_4_5_r9_4_5 = new TH1F("eleAbsEta_4_5_r9_4_5", "", 4, etBins);
    TH1F * eleAbsEta_4_5_r9_5_6 = new TH1F("eleAbsEta_4_5_r9_5_6", "", 4, etBins);

    TH1F * eleAbsEta_5_6_r9_0_1 = new TH1F("eleAbsEta_5_6_r9_0_1", "", 4, etBins);
    TH1F * eleAbsEta_5_6_r9_1_2 = new TH1F("eleAbsEta_5_6_r9_1_2", "", 4, etBins);
    TH1F * eleAbsEta_5_6_r9_2_3 = new TH1F("eleAbsEta_5_6_r9_2_3", "", 4, etBins);
    TH1F * eleAbsEta_5_6_r9_3_4 = new TH1F("eleAbsEta_5_6_r9_3_4", "", 4, etBins);
    TH1F * eleAbsEta_5_6_r9_4_5 = new TH1F("eleAbsEta_5_6_r9_4_5", "", 4, etBins);
    TH1F * eleAbsEta_5_6_r9_5_6 = new TH1F("eleAbsEta_5_6_r9_5_6", "", 4, etBins);

    TH1F * eleAbsEta_6_7_r9_0_1 = new TH1F("eleAbsEta_6_7_r9_0_1", "", 4, etBins);
    TH1F * eleAbsEta_6_7_r9_1_2 = new TH1F("eleAbsEta_6_7_r9_1_2", "", 4, etBins);
    TH1F * eleAbsEta_6_7_r9_2_3 = new TH1F("eleAbsEta_6_7_r9_2_3", "", 4, etBins);
    TH1F * eleAbsEta_6_7_r9_3_4 = new TH1F("eleAbsEta_6_7_r9_3_4", "", 4, etBins);
    TH1F * eleAbsEta_6_7_r9_4_5 = new TH1F("eleAbsEta_6_7_r9_4_5", "", 4, etBins);
    TH1F * eleAbsEta_6_7_r9_5_6 = new TH1F("eleAbsEta_6_7_r9_5_6", "", 4, etBins);
    
    double eta_center, eta_low, eta_high, r9_low, r9_high, Et, lr, phoE, eleE, phoN, eleN, syst, unc, eleRMS, phoRMS;

    while( in >> eta_center >> eta_low >> eta_high >> r9_low >> r9_high >> Et >> lr >> phoE >> phoN >> phoRMS >> eleE >> eleN >> eleRMS >> syst >> unc){
        int etBin = 0;
        if( Et == 30) etBin = 1;
        else if( Et == 45) etBin = 2;
        else if( Et == 60) etBin = 3;
        else if( Et == 120) etBin = 4;
        else{
            std::cout << "[ERROR] came across an unexpected value" << std::endl;
            return 2;
        }
        bool eta0 = eta_low == 0.;
        bool eta1 = eta_low == 0.3;
        bool eta2 = eta_low == 0.7;
        bool eta3 = eta_low == 1.1;
        bool eta4 = eta_low == 1.57;
        bool eta5 = eta_low == 1.8;
        bool eta6 = eta_low == 2.1;
        bool r90 = r9_low == 0.;
        bool r91 = r9_low == 0.8;
        bool r92 = r9_low == 0.9;
        bool r93 = r9_low == 0.92;
        bool r94 = r9_low == 0.96;
        bool r95 = r9_low == 0.96;
        if(_flag_altR9) r94 = r9_low == 0.94;


        if(eta0 && r90){
               absEta_0_1_r9_0_1->SetBinContent(etBin, syst);
               absEta_0_1_r9_0_1->SetBinError(etBin, unc);
               phoAbsEta_0_1_r9_0_1->SetBinContent(etBin, phoE);
               phoAbsEta_0_1_r9_0_1->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_0_1_r9_0_1->SetBinContent(etBin, eleE);
               eleAbsEta_0_1_r9_0_1->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta0 && r91){
               absEta_0_1_r9_1_2->SetBinContent(etBin, syst);
               absEta_0_1_r9_1_2->SetBinError(etBin, unc);
               phoAbsEta_0_1_r9_1_2->SetBinContent(etBin, phoE);
               phoAbsEta_0_1_r9_1_2->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_0_1_r9_1_2->SetBinContent(etBin, eleE);
               eleAbsEta_0_1_r9_1_2->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta0 && r92){
               absEta_0_1_r9_2_3->SetBinContent(etBin, syst);
               absEta_0_1_r9_2_3->SetBinError(etBin, unc);
               phoAbsEta_0_1_r9_2_3->SetBinContent(etBin, phoE);
               phoAbsEta_0_1_r9_2_3->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_0_1_r9_2_3->SetBinContent(etBin, eleE);
               eleAbsEta_0_1_r9_2_3->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta0 && r93){
               absEta_0_1_r9_3_4->SetBinContent(etBin, syst);
               absEta_0_1_r9_3_4->SetBinError(etBin, unc);
               phoAbsEta_0_1_r9_3_4->SetBinContent(etBin, phoE);
               phoAbsEta_0_1_r9_3_4->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_0_1_r9_3_4->SetBinContent(etBin, eleE);
               eleAbsEta_0_1_r9_3_4->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta0 && r94){
               absEta_0_1_r9_4_5->SetBinContent(etBin, syst);
               absEta_0_1_r9_4_5->SetBinError(etBin, unc);
               phoAbsEta_0_1_r9_4_5->SetBinContent(etBin, phoE);
               phoAbsEta_0_1_r9_4_5->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_0_1_r9_4_5->SetBinContent(etBin, eleE);
               eleAbsEta_0_1_r9_4_5->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta0 && r95 && _flag_altR9){
               absEta_0_1_r9_5_6->SetBinContent(etBin, syst);
               absEta_0_1_r9_5_6->SetBinError(etBin, unc);
               phoAbsEta_0_1_r9_5_6->SetBinContent(etBin, phoE);
               phoAbsEta_0_1_r9_5_6->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_0_1_r9_5_6->SetBinContent(etBin, eleE);
               eleAbsEta_0_1_r9_5_6->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta1 && r90){
               absEta_1_2_r9_0_1->SetBinContent(etBin, syst);
               absEta_1_2_r9_0_1->SetBinError(etBin, unc);
               phoAbsEta_1_2_r9_0_1->SetBinContent(etBin, phoE);
               phoAbsEta_1_2_r9_0_1->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_1_2_r9_0_1->SetBinContent(etBin, eleE);
               eleAbsEta_1_2_r9_0_1->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta1 && r91){
               absEta_1_2_r9_1_2->SetBinContent(etBin, syst);
               absEta_1_2_r9_1_2->SetBinError(etBin, unc);
               phoAbsEta_1_2_r9_1_2->SetBinContent(etBin, phoE);
               phoAbsEta_1_2_r9_1_2->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_1_2_r9_1_2->SetBinContent(etBin, eleE);
               eleAbsEta_1_2_r9_1_2->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta1 && r92){
               absEta_1_2_r9_2_3->SetBinContent(etBin, syst);
               absEta_1_2_r9_2_3->SetBinError(etBin, unc);
               phoAbsEta_1_2_r9_2_3->SetBinContent(etBin, phoE);
               phoAbsEta_1_2_r9_2_3->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_1_2_r9_2_3->SetBinContent(etBin, eleE);
               eleAbsEta_1_2_r9_2_3->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta1 && r93){
               absEta_1_2_r9_3_4->SetBinContent(etBin, syst);
               absEta_1_2_r9_3_4->SetBinError(etBin, unc);
               phoAbsEta_1_2_r9_3_4->SetBinContent(etBin, phoE);
               phoAbsEta_1_2_r9_3_4->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_1_2_r9_3_4->SetBinContent(etBin, eleE);
               eleAbsEta_1_2_r9_3_4->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta1 && r94){
               absEta_1_2_r9_4_5->SetBinContent(etBin, syst);
               absEta_1_2_r9_4_5->SetBinError(etBin, unc);
               phoAbsEta_1_2_r9_4_5->SetBinContent(etBin, phoE);
               phoAbsEta_1_2_r9_4_5->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_1_2_r9_4_5->SetBinContent(etBin, eleE);
               eleAbsEta_1_2_r9_4_5->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta1 && r95 && _flag_altR9){
               absEta_1_2_r9_5_6->SetBinContent(etBin, syst);
               absEta_1_2_r9_5_6->SetBinError(etBin, unc);
               phoAbsEta_1_2_r9_5_6->SetBinContent(etBin, phoE);
               phoAbsEta_1_2_r9_5_6->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_1_2_r9_5_6->SetBinContent(etBin, eleE);
               eleAbsEta_1_2_r9_5_6->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta2 && r90){
               absEta_2_3_r9_0_1->SetBinContent(etBin, syst);
               absEta_2_3_r9_0_1->SetBinError(etBin, unc);
               phoAbsEta_2_3_r9_0_1->SetBinContent(etBin, phoE);
               phoAbsEta_2_3_r9_0_1->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_2_3_r9_0_1->SetBinContent(etBin, eleE);
               eleAbsEta_2_3_r9_0_1->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta2 && r91){
               absEta_2_3_r9_1_2->SetBinContent(etBin, syst);
               absEta_2_3_r9_1_2->SetBinError(etBin, unc);
               phoAbsEta_2_3_r9_1_2->SetBinContent(etBin, phoE);
               phoAbsEta_2_3_r9_1_2->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_2_3_r9_1_2->SetBinContent(etBin, eleE);
               eleAbsEta_2_3_r9_1_2->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta2 && r92){
               absEta_2_3_r9_2_3->SetBinContent(etBin, syst);
               absEta_2_3_r9_2_3->SetBinError(etBin, unc);
               phoAbsEta_2_3_r9_2_3->SetBinContent(etBin, phoE);
               phoAbsEta_2_3_r9_2_3->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_2_3_r9_2_3->SetBinContent(etBin, eleE);
               eleAbsEta_2_3_r9_2_3->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta2 && r93){
               absEta_2_3_r9_3_4->SetBinContent(etBin, syst);
               absEta_2_3_r9_3_4->SetBinError(etBin, unc);
               phoAbsEta_2_3_r9_3_4->SetBinContent(etBin, phoE);
               phoAbsEta_2_3_r9_3_4->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_2_3_r9_3_4->SetBinContent(etBin, eleE);
               eleAbsEta_2_3_r9_3_4->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta2 && r94){
               absEta_2_3_r9_4_5->SetBinContent(etBin, syst);
               absEta_2_3_r9_4_5->SetBinError(etBin, unc);
               phoAbsEta_2_3_r9_4_5->SetBinContent(etBin, phoE);
               phoAbsEta_2_3_r9_4_5->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_2_3_r9_4_5->SetBinContent(etBin, eleE);
               eleAbsEta_2_3_r9_4_5->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta2 && r95 && _flag_altR9){
               absEta_2_3_r9_5_6->SetBinContent(etBin, syst);
               absEta_2_3_r9_5_6->SetBinError(etBin, unc);
               phoAbsEta_2_3_r9_5_6->SetBinContent(etBin, phoE);
               phoAbsEta_2_3_r9_5_6->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_2_3_r9_5_6->SetBinContent(etBin, eleE);
               eleAbsEta_2_3_r9_5_6->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta3 && r90){
               absEta_3_4_r9_0_1->SetBinContent(etBin, syst);
               absEta_3_4_r9_0_1->SetBinError(etBin, unc);
               phoAbsEta_3_4_r9_0_1->SetBinContent(etBin, phoE);
               phoAbsEta_3_4_r9_0_1->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_3_4_r9_0_1->SetBinContent(etBin, eleE);
               eleAbsEta_3_4_r9_0_1->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta3 && r91){
               absEta_3_4_r9_1_2->SetBinContent(etBin, syst);
               absEta_3_4_r9_1_2->SetBinError(etBin, unc);
               phoAbsEta_3_4_r9_1_2->SetBinContent(etBin, phoE);
               phoAbsEta_3_4_r9_1_2->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_3_4_r9_1_2->SetBinContent(etBin, eleE);
               eleAbsEta_3_4_r9_1_2->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta3 && r92){
               absEta_3_4_r9_2_3->SetBinContent(etBin, syst);
               absEta_3_4_r9_2_3->SetBinError(etBin, unc);
               phoAbsEta_3_4_r9_2_3->SetBinContent(etBin, phoE);
               phoAbsEta_3_4_r9_2_3->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_3_4_r9_2_3->SetBinContent(etBin, eleE);
               eleAbsEta_3_4_r9_2_3->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta3 && r93){
               absEta_3_4_r9_3_4->SetBinContent(etBin, syst);
               absEta_3_4_r9_3_4->SetBinError(etBin, unc);
               phoAbsEta_3_4_r9_3_4->SetBinContent(etBin, phoE);
               phoAbsEta_3_4_r9_3_4->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_3_4_r9_3_4->SetBinContent(etBin, eleE);
               eleAbsEta_3_4_r9_3_4->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta3 && r94){
               absEta_3_4_r9_4_5->SetBinContent(etBin, syst);
               absEta_3_4_r9_4_5->SetBinError(etBin, unc);
               phoAbsEta_3_4_r9_4_5->SetBinContent(etBin, phoE);
               phoAbsEta_3_4_r9_4_5->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_3_4_r9_4_5->SetBinContent(etBin, eleE);
               eleAbsEta_3_4_r9_4_5->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta3 && r95 && _flag_altR9){
               absEta_3_4_r9_5_6->SetBinContent(etBin, syst);
               absEta_3_4_r9_5_6->SetBinError(etBin, unc);
               phoAbsEta_3_4_r9_5_6->SetBinContent(etBin, phoE);
               phoAbsEta_3_4_r9_5_6->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_3_4_r9_5_6->SetBinContent(etBin, eleE);
               eleAbsEta_3_4_r9_5_6->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta4 && r90){
               absEta_4_5_r9_0_1->SetBinContent(etBin, syst);
               absEta_4_5_r9_0_1->SetBinError(etBin, unc);
               phoAbsEta_4_5_r9_0_1->SetBinContent(etBin, phoE);
               phoAbsEta_4_5_r9_0_1->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_4_5_r9_0_1->SetBinContent(etBin, eleE);
               eleAbsEta_4_5_r9_0_1->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta4 && r91){
               absEta_4_5_r9_1_2->SetBinContent(etBin, syst);
               absEta_4_5_r9_1_2->SetBinError(etBin, unc);
               phoAbsEta_4_5_r9_1_2->SetBinContent(etBin, phoE);
               phoAbsEta_4_5_r9_1_2->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_4_5_r9_1_2->SetBinContent(etBin, eleE);
               eleAbsEta_4_5_r9_1_2->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta4 && r92){
               absEta_4_5_r9_2_3->SetBinContent(etBin, syst);
               absEta_4_5_r9_2_3->SetBinError(etBin, unc);
               phoAbsEta_4_5_r9_2_3->SetBinContent(etBin, phoE);
               phoAbsEta_4_5_r9_2_3->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_4_5_r9_2_3->SetBinContent(etBin, eleE);
               eleAbsEta_4_5_r9_2_3->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta4 && r93){
               absEta_4_5_r9_3_4->SetBinContent(etBin, syst);
               absEta_4_5_r9_3_4->SetBinError(etBin, unc);
               phoAbsEta_4_5_r9_3_4->SetBinContent(etBin, phoE);
               phoAbsEta_4_5_r9_3_4->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_4_5_r9_3_4->SetBinContent(etBin, eleE);
               eleAbsEta_4_5_r9_3_4->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta4 && r94){
               absEta_4_5_r9_4_5->SetBinContent(etBin, syst);
               absEta_4_5_r9_4_5->SetBinError(etBin, unc);
               phoAbsEta_4_5_r9_4_5->SetBinContent(etBin, phoE);
               phoAbsEta_4_5_r9_4_5->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_4_5_r9_4_5->SetBinContent(etBin, eleE);
               eleAbsEta_4_5_r9_4_5->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta4 && r95 && _flag_altR9){
               absEta_4_5_r9_5_6->SetBinContent(etBin, syst);
               absEta_4_5_r9_5_6->SetBinError(etBin, unc);
               phoAbsEta_4_5_r9_5_6->SetBinContent(etBin, phoE);
               phoAbsEta_4_5_r9_5_6->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_4_5_r9_5_6->SetBinContent(etBin, eleE);
               eleAbsEta_4_5_r9_5_6->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta5 && r90){
               absEta_5_6_r9_0_1->SetBinContent(etBin, syst);
               absEta_5_6_r9_0_1->SetBinError(etBin, unc);
               phoAbsEta_5_6_r9_0_1->SetBinContent(etBin, phoE);
               phoAbsEta_5_6_r9_0_1->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_5_6_r9_0_1->SetBinContent(etBin, eleE);
               eleAbsEta_5_6_r9_0_1->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta5 && r91){
               absEta_5_6_r9_1_2->SetBinContent(etBin, syst);
               absEta_5_6_r9_1_2->SetBinError(etBin, unc);
               phoAbsEta_5_6_r9_1_2->SetBinContent(etBin, phoE);
               phoAbsEta_5_6_r9_1_2->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_5_6_r9_1_2->SetBinContent(etBin, eleE);
               eleAbsEta_5_6_r9_1_2->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta5 && r92){
               absEta_5_6_r9_2_3->SetBinContent(etBin, syst);
               absEta_5_6_r9_2_3->SetBinError(etBin, unc);
               phoAbsEta_5_6_r9_2_3->SetBinContent(etBin, phoE);
               phoAbsEta_5_6_r9_2_3->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_5_6_r9_2_3->SetBinContent(etBin, eleE);
               eleAbsEta_5_6_r9_2_3->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta5 && r93){
               absEta_5_6_r9_3_4->SetBinContent(etBin, syst);
               absEta_5_6_r9_3_4->SetBinError(etBin, unc);
               phoAbsEta_5_6_r9_3_4->SetBinContent(etBin, phoE);
               phoAbsEta_5_6_r9_3_4->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_5_6_r9_3_4->SetBinContent(etBin, eleE);
               eleAbsEta_5_6_r9_3_4->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta5 && r94){
               absEta_5_6_r9_4_5->SetBinContent(etBin, syst);
               absEta_5_6_r9_4_5->SetBinError(etBin, unc);
               phoAbsEta_5_6_r9_4_5->SetBinContent(etBin, phoE);
               phoAbsEta_5_6_r9_4_5->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_5_6_r9_4_5->SetBinContent(etBin, eleE);
               eleAbsEta_5_6_r9_4_5->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta5 && r95 && _flag_altR9){
               absEta_5_6_r9_5_6->SetBinContent(etBin, syst);
               absEta_5_6_r9_5_6->SetBinError(etBin, unc);
               phoAbsEta_5_6_r9_5_6->SetBinContent(etBin, phoE);
               phoAbsEta_5_6_r9_5_6->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_5_6_r9_5_6->SetBinContent(etBin, eleE);
               eleAbsEta_5_6_r9_5_6->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta6 && r90){
               absEta_6_7_r9_0_1->SetBinContent(etBin, syst);
               absEta_6_7_r9_0_1->SetBinError(etBin, unc);
               phoAbsEta_6_7_r9_0_1->SetBinContent(etBin, phoE);
               phoAbsEta_6_7_r9_0_1->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_6_7_r9_0_1->SetBinContent(etBin, eleE);
               eleAbsEta_6_7_r9_0_1->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta6 && r91){
               absEta_6_7_r9_1_2->SetBinContent(etBin, syst);
               absEta_6_7_r9_1_2->SetBinError(etBin, unc);
               phoAbsEta_6_7_r9_1_2->SetBinContent(etBin, phoE);
               phoAbsEta_6_7_r9_1_2->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_6_7_r9_1_2->SetBinContent(etBin, eleE);
               eleAbsEta_6_7_r9_1_2->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta6 && r92){
               absEta_6_7_r9_2_3->SetBinContent(etBin, syst);
               absEta_6_7_r9_2_3->SetBinError(etBin, unc);
               phoAbsEta_6_7_r9_2_3->SetBinContent(etBin, phoE);
               phoAbsEta_6_7_r9_2_3->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_6_7_r9_2_3->SetBinContent(etBin, eleE);
               eleAbsEta_6_7_r9_2_3->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta6 && r93){
               absEta_6_7_r9_3_4->SetBinContent(etBin, syst);
               absEta_6_7_r9_3_4->SetBinError(etBin, unc);
               phoAbsEta_6_7_r9_3_4->SetBinContent(etBin, phoE);
               phoAbsEta_6_7_r9_3_4->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_6_7_r9_3_4->SetBinContent(etBin, eleE);
               eleAbsEta_6_7_r9_3_4->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta6 && r94){
               absEta_6_7_r9_4_5->SetBinContent(etBin, syst);
               absEta_6_7_r9_4_5->SetBinError(etBin, unc);
               phoAbsEta_6_7_r9_4_5->SetBinContent(etBin, phoE);
               phoAbsEta_6_7_r9_4_5->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_6_7_r9_4_5->SetBinContent(etBin, eleE);
               eleAbsEta_6_7_r9_4_5->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
        if(eta6 && r95 && _flag_altR9){
               absEta_6_7_r9_5_6->SetBinContent(etBin, syst);
               absEta_6_7_r9_5_6->SetBinError(etBin, unc);
               phoAbsEta_6_7_r9_5_6->SetBinContent(etBin, phoE);
               phoAbsEta_6_7_r9_5_6->SetBinError(etBin, phoRMS/sqrt(phoN));
               eleAbsEta_6_7_r9_5_6->SetBinContent(etBin, eleE);
               eleAbsEta_6_7_r9_5_6->SetBinError(etBin, eleRMS/sqrt(eleN));
        }
    }

    if(!_flag_altR9){
    plotForEta(absEta_0_1_r9_0_1, absEta_0_1_r9_1_2, absEta_0_1_r9_2_3, absEta_0_1_r9_3_4, absEta_0_1_r9_4_5, "syst", 0);
    plotForEta(absEta_1_2_r9_0_1, absEta_1_2_r9_1_2, absEta_1_2_r9_2_3, absEta_1_2_r9_3_4, absEta_1_2_r9_4_5, "syst", 1);
    plotForEta(absEta_2_3_r9_0_1, absEta_2_3_r9_1_2, absEta_2_3_r9_2_3, absEta_2_3_r9_3_4, absEta_2_3_r9_4_5, "syst", 2);
    plotForEta(absEta_3_4_r9_0_1, absEta_3_4_r9_1_2, absEta_3_4_r9_2_3, absEta_3_4_r9_3_4, absEta_3_4_r9_4_5, "syst", 3);
    plotForEta(absEta_4_5_r9_0_1, absEta_4_5_r9_1_2, absEta_4_5_r9_2_3, absEta_4_5_r9_3_4, absEta_4_5_r9_4_5, "syst", 4);
    plotForEta(absEta_5_6_r9_0_1, absEta_5_6_r9_1_2, absEta_5_6_r9_2_3, absEta_5_6_r9_3_4, absEta_5_6_r9_4_5, "syst", 5);
    plotForEta(absEta_6_7_r9_0_1, absEta_6_7_r9_1_2, absEta_6_7_r9_2_3, absEta_6_7_r9_3_4, absEta_6_7_r9_4_5, "syst", 6);

    plotForEta(phoAbsEta_0_1_r9_0_1, phoAbsEta_0_1_r9_1_2, phoAbsEta_0_1_r9_2_3, phoAbsEta_0_1_r9_3_4, phoAbsEta_0_1_r9_4_5, "pho", 0);
    plotForEta(phoAbsEta_1_2_r9_0_1, phoAbsEta_1_2_r9_1_2, phoAbsEta_1_2_r9_2_3, phoAbsEta_1_2_r9_3_4, phoAbsEta_1_2_r9_4_5, "pho", 1);
    plotForEta(phoAbsEta_2_3_r9_0_1, phoAbsEta_2_3_r9_1_2, phoAbsEta_2_3_r9_2_3, phoAbsEta_2_3_r9_3_4, phoAbsEta_2_3_r9_4_5, "pho", 2);
    plotForEta(phoAbsEta_3_4_r9_0_1, phoAbsEta_3_4_r9_1_2, phoAbsEta_3_4_r9_2_3, phoAbsEta_3_4_r9_3_4, phoAbsEta_3_4_r9_4_5, "pho", 3);
    plotForEta(phoAbsEta_4_5_r9_0_1, phoAbsEta_4_5_r9_1_2, phoAbsEta_4_5_r9_2_3, phoAbsEta_4_5_r9_3_4, phoAbsEta_4_5_r9_4_5, "pho", 4);
    plotForEta(phoAbsEta_5_6_r9_0_1, phoAbsEta_5_6_r9_1_2, phoAbsEta_5_6_r9_2_3, phoAbsEta_5_6_r9_3_4, phoAbsEta_5_6_r9_4_5, "pho", 5);
    plotForEta(phoAbsEta_6_7_r9_0_1, phoAbsEta_6_7_r9_1_2, phoAbsEta_6_7_r9_2_3, phoAbsEta_6_7_r9_3_4, phoAbsEta_6_7_r9_4_5, "pho", 6);

    plotForEta(eleAbsEta_0_1_r9_0_1, eleAbsEta_0_1_r9_1_2, eleAbsEta_0_1_r9_2_3, eleAbsEta_0_1_r9_3_4, eleAbsEta_0_1_r9_4_5, "ele", 0);
    plotForEta(eleAbsEta_1_2_r9_0_1, eleAbsEta_1_2_r9_1_2, eleAbsEta_1_2_r9_2_3, eleAbsEta_1_2_r9_3_4, eleAbsEta_1_2_r9_4_5, "ele", 1);
    plotForEta(eleAbsEta_2_3_r9_0_1, eleAbsEta_2_3_r9_1_2, eleAbsEta_2_3_r9_2_3, eleAbsEta_2_3_r9_3_4, eleAbsEta_2_3_r9_4_5, "ele", 2);
    plotForEta(eleAbsEta_3_4_r9_0_1, eleAbsEta_3_4_r9_1_2, eleAbsEta_3_4_r9_2_3, eleAbsEta_3_4_r9_3_4, eleAbsEta_3_4_r9_4_5, "ele", 3);
    plotForEta(eleAbsEta_4_5_r9_0_1, eleAbsEta_4_5_r9_1_2, eleAbsEta_4_5_r9_2_3, eleAbsEta_4_5_r9_3_4, eleAbsEta_4_5_r9_4_5, "ele", 4);
    plotForEta(eleAbsEta_5_6_r9_0_1, eleAbsEta_5_6_r9_1_2, eleAbsEta_5_6_r9_2_3, eleAbsEta_5_6_r9_3_4, eleAbsEta_5_6_r9_4_5, "ele", 5);
    plotForEta(eleAbsEta_6_7_r9_0_1, eleAbsEta_6_7_r9_1_2, eleAbsEta_6_7_r9_2_3, eleAbsEta_6_7_r9_3_4, eleAbsEta_6_7_r9_4_5, "ele", 6);
    }
    else{
    plotForEta(absEta_0_1_r9_0_1, absEta_0_1_r9_1_2, absEta_0_1_r9_2_3, absEta_0_1_r9_3_4, absEta_0_1_r9_4_5, absEta_0_1_r9_5_6, "syst", 0);
    plotForEta(absEta_1_2_r9_0_1, absEta_1_2_r9_1_2, absEta_1_2_r9_2_3, absEta_1_2_r9_3_4, absEta_1_2_r9_4_5, absEta_1_2_r9_5_6, "syst", 1);
    plotForEta(absEta_2_3_r9_0_1, absEta_2_3_r9_1_2, absEta_2_3_r9_2_3, absEta_2_3_r9_3_4, absEta_2_3_r9_4_5, absEta_2_3_r9_5_6, "syst", 2);
    plotForEta(absEta_3_4_r9_0_1, absEta_3_4_r9_1_2, absEta_3_4_r9_2_3, absEta_3_4_r9_3_4, absEta_3_4_r9_4_5, absEta_3_4_r9_5_6, "syst", 3);
    plotForEta(absEta_4_5_r9_0_1, absEta_4_5_r9_1_2, absEta_4_5_r9_2_3, absEta_4_5_r9_3_4, absEta_4_5_r9_4_5, absEta_4_5_r9_5_6, "syst", 4);
    plotForEta(absEta_5_6_r9_0_1, absEta_5_6_r9_1_2, absEta_5_6_r9_2_3, absEta_5_6_r9_3_4, absEta_5_6_r9_4_5, absEta_5_6_r9_5_6, "syst", 5);
    plotForEta(absEta_6_7_r9_0_1, absEta_6_7_r9_1_2, absEta_6_7_r9_2_3, absEta_6_7_r9_3_4, absEta_6_7_r9_4_5, absEta_6_7_r9_5_6, "syst", 6);

    plotForEta(phoAbsEta_0_1_r9_0_1, phoAbsEta_0_1_r9_1_2, phoAbsEta_0_1_r9_2_3, phoAbsEta_0_1_r9_3_4, phoAbsEta_0_1_r9_4_5, phoAbsEta_0_1_r9_5_6, "pho", 0);
    plotForEta(phoAbsEta_1_2_r9_0_1, phoAbsEta_1_2_r9_1_2, phoAbsEta_1_2_r9_2_3, phoAbsEta_1_2_r9_3_4, phoAbsEta_1_2_r9_4_5, phoAbsEta_1_2_r9_5_6, "pho", 1);
    plotForEta(phoAbsEta_2_3_r9_0_1, phoAbsEta_2_3_r9_1_2, phoAbsEta_2_3_r9_2_3, phoAbsEta_2_3_r9_3_4, phoAbsEta_2_3_r9_4_5, phoAbsEta_2_3_r9_5_6, "pho", 2);
    plotForEta(phoAbsEta_3_4_r9_0_1, phoAbsEta_3_4_r9_1_2, phoAbsEta_3_4_r9_2_3, phoAbsEta_3_4_r9_3_4, phoAbsEta_3_4_r9_4_5, phoAbsEta_3_4_r9_5_6, "pho", 3);
    plotForEta(phoAbsEta_4_5_r9_0_1, phoAbsEta_4_5_r9_1_2, phoAbsEta_4_5_r9_2_3, phoAbsEta_4_5_r9_3_4, phoAbsEta_4_5_r9_4_5, phoAbsEta_4_5_r9_5_6, "pho", 4);
    plotForEta(phoAbsEta_5_6_r9_0_1, phoAbsEta_5_6_r9_1_2, phoAbsEta_5_6_r9_2_3, phoAbsEta_5_6_r9_3_4, phoAbsEta_5_6_r9_4_5, phoAbsEta_5_6_r9_5_6, "pho", 5);
    plotForEta(phoAbsEta_6_7_r9_0_1, phoAbsEta_6_7_r9_1_2, phoAbsEta_6_7_r9_2_3, phoAbsEta_6_7_r9_3_4, phoAbsEta_6_7_r9_4_5, phoAbsEta_6_7_r9_5_6, "pho", 6);

    plotForEta(eleAbsEta_0_1_r9_0_1, eleAbsEta_0_1_r9_1_2, eleAbsEta_0_1_r9_2_3, eleAbsEta_0_1_r9_3_4, eleAbsEta_0_1_r9_4_5, eleAbsEta_0_1_r9_4_5, "ele", 0);
    plotForEta(eleAbsEta_1_2_r9_0_1, eleAbsEta_1_2_r9_1_2, eleAbsEta_1_2_r9_2_3, eleAbsEta_1_2_r9_3_4, eleAbsEta_1_2_r9_4_5, eleAbsEta_1_2_r9_4_5, "ele", 1);
    plotForEta(eleAbsEta_2_3_r9_0_1, eleAbsEta_2_3_r9_1_2, eleAbsEta_2_3_r9_2_3, eleAbsEta_2_3_r9_3_4, eleAbsEta_2_3_r9_4_5, eleAbsEta_2_3_r9_4_5, "ele", 2);
    plotForEta(eleAbsEta_3_4_r9_0_1, eleAbsEta_3_4_r9_1_2, eleAbsEta_3_4_r9_2_3, eleAbsEta_3_4_r9_3_4, eleAbsEta_3_4_r9_4_5, eleAbsEta_3_4_r9_4_5, "ele", 3);
    plotForEta(eleAbsEta_4_5_r9_0_1, eleAbsEta_4_5_r9_1_2, eleAbsEta_4_5_r9_2_3, eleAbsEta_4_5_r9_3_4, eleAbsEta_4_5_r9_4_5, eleAbsEta_4_5_r9_4_5, "ele", 4);
    plotForEta(eleAbsEta_5_6_r9_0_1, eleAbsEta_5_6_r9_1_2, eleAbsEta_5_6_r9_2_3, eleAbsEta_5_6_r9_3_4, eleAbsEta_5_6_r9_4_5, eleAbsEta_5_6_r9_4_5, "ele", 5);
    plotForEta(eleAbsEta_6_7_r9_0_1, eleAbsEta_6_7_r9_1_2, eleAbsEta_6_7_r9_2_3, eleAbsEta_6_7_r9_3_4, eleAbsEta_6_7_r9_4_5, eleAbsEta_6_7_r9_4_5, "ele", 6);
    }

    plotForR9(absEta_0_1_r9_0_1, absEta_1_2_r9_0_1, absEta_2_3_r9_0_1, absEta_3_4_r9_0_1, absEta_4_5_r9_0_1, absEta_5_6_r9_0_1, absEta_6_7_r9_0_1, "syst", 0);
    plotForR9(absEta_0_1_r9_1_2, absEta_1_2_r9_1_2, absEta_2_3_r9_1_2, absEta_3_4_r9_1_2, absEta_4_5_r9_1_2, absEta_5_6_r9_1_2, absEta_6_7_r9_1_2, "syst", 1);
    plotForR9(absEta_0_1_r9_2_3, absEta_1_2_r9_2_3, absEta_2_3_r9_2_3, absEta_3_4_r9_2_3, absEta_4_5_r9_2_3, absEta_5_6_r9_2_3, absEta_6_7_r9_2_3, "syst", 2);
    plotForR9(absEta_0_1_r9_3_4, absEta_1_2_r9_3_4, absEta_2_3_r9_3_4, absEta_3_4_r9_3_4, absEta_4_5_r9_3_4, absEta_5_6_r9_3_4, absEta_6_7_r9_3_4, "syst", 3);
    plotForR9(absEta_0_1_r9_4_5, absEta_1_2_r9_4_5, absEta_2_3_r9_4_5, absEta_3_4_r9_4_5, absEta_4_5_r9_4_5, absEta_5_6_r9_4_5, absEta_6_7_r9_4_5, "syst", 4);
    if(_flag_altR9 )    plotForR9(absEta_0_1_r9_5_6, absEta_1_2_r9_5_6, absEta_2_3_r9_5_6, absEta_3_4_r9_5_6, absEta_4_5_r9_5_6, absEta_5_6_r9_5_6, absEta_6_7_r9_5_6, "syst", 5);

    plotForR9(phoAbsEta_0_1_r9_0_1, phoAbsEta_1_2_r9_0_1, phoAbsEta_2_3_r9_0_1, phoAbsEta_3_4_r9_0_1, phoAbsEta_4_5_r9_0_1, phoAbsEta_5_6_r9_0_1, phoAbsEta_6_7_r9_0_1, "pho", 0);
    plotForR9(phoAbsEta_0_1_r9_1_2, phoAbsEta_1_2_r9_1_2, phoAbsEta_2_3_r9_1_2, phoAbsEta_3_4_r9_1_2, phoAbsEta_4_5_r9_1_2, phoAbsEta_5_6_r9_1_2, phoAbsEta_6_7_r9_1_2, "pho", 1);
    plotForR9(phoAbsEta_0_1_r9_2_3, phoAbsEta_1_2_r9_2_3, phoAbsEta_2_3_r9_2_3, phoAbsEta_3_4_r9_2_3, phoAbsEta_4_5_r9_2_3, phoAbsEta_5_6_r9_2_3, phoAbsEta_6_7_r9_2_3, "pho", 2);
    plotForR9(phoAbsEta_0_1_r9_3_4, phoAbsEta_1_2_r9_3_4, phoAbsEta_2_3_r9_3_4, phoAbsEta_3_4_r9_3_4, phoAbsEta_4_5_r9_3_4, phoAbsEta_5_6_r9_3_4, phoAbsEta_6_7_r9_3_4, "pho", 3);
    plotForR9(phoAbsEta_0_1_r9_4_5, phoAbsEta_1_2_r9_4_5, phoAbsEta_2_3_r9_4_5, phoAbsEta_3_4_r9_4_5, phoAbsEta_4_5_r9_4_5, phoAbsEta_5_6_r9_4_5, phoAbsEta_6_7_r9_4_5, "pho", 4);
    if(_flag_altR9 )    plotForR9(phoAbsEta_0_1_r9_5_6, phoAbsEta_1_2_r9_5_6, phoAbsEta_2_3_r9_5_6, phoAbsEta_3_4_r9_5_6, phoAbsEta_4_5_r9_5_6, phoAbsEta_5_6_r9_5_6, phoAbsEta_6_7_r9_5_6, "pho", 5);
    

    plotForR9(eleAbsEta_0_1_r9_0_1, eleAbsEta_1_2_r9_0_1, eleAbsEta_2_3_r9_0_1, eleAbsEta_3_4_r9_0_1, eleAbsEta_4_5_r9_0_1, eleAbsEta_5_6_r9_0_1, eleAbsEta_6_7_r9_0_1, "ele", 0);
    plotForR9(eleAbsEta_0_1_r9_1_2, eleAbsEta_1_2_r9_1_2, eleAbsEta_2_3_r9_1_2, eleAbsEta_3_4_r9_1_2, eleAbsEta_4_5_r9_1_2, eleAbsEta_5_6_r9_1_2, eleAbsEta_6_7_r9_1_2, "ele", 1);
    plotForR9(eleAbsEta_0_1_r9_2_3, eleAbsEta_1_2_r9_2_3, eleAbsEta_2_3_r9_2_3, eleAbsEta_3_4_r9_2_3, eleAbsEta_4_5_r9_2_3, eleAbsEta_5_6_r9_2_3, eleAbsEta_6_7_r9_2_3, "ele", 2);
    plotForR9(eleAbsEta_0_1_r9_3_4, eleAbsEta_1_2_r9_3_4, eleAbsEta_2_3_r9_3_4, eleAbsEta_3_4_r9_3_4, eleAbsEta_4_5_r9_3_4, eleAbsEta_5_6_r9_3_4, eleAbsEta_6_7_r9_3_4, "ele", 3);
    plotForR9(eleAbsEta_0_1_r9_4_5, eleAbsEta_1_2_r9_4_5, eleAbsEta_2_3_r9_4_5, eleAbsEta_3_4_r9_4_5, eleAbsEta_4_5_r9_4_5, eleAbsEta_5_6_r9_4_5, eleAbsEta_6_7_r9_4_5, "ele", 4);
    if(_flag_altR9 )    plotForR9(eleAbsEta_0_1_r9_5_6, eleAbsEta_1_2_r9_5_6, eleAbsEta_2_3_r9_5_6, eleAbsEta_3_4_r9_5_6, eleAbsEta_4_5_r9_5_6, eleAbsEta_5_6_r9_5_6, eleAbsEta_6_7_r9_5_6, "ele", 5);


    return 0;
}

void plotForEta(TH1F * hist0, TH1F * hist1, TH1F* hist2, TH1F * hist3, TH1F * hist4, std::string type, int eta){

    if(!hist0){
        std::cout << "[ERROR] the histogram named " << hist0->GetName() << " was provided as hist0, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist1){
        std::cout << "[ERROR] the histogram named " << hist1->GetName() << " was provided as hist1, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist2){
        std::cout << "[ERROR] the histogram named " << hist2->GetName() << " was provided as hist2, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist3){
        std::cout << "[ERROR] the histogram named " << hist3->GetName() << " was provided as hist3, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist4){
        std::cout << "[ERROR] the histogram named " << hist4->GetName() << " was provided as hist4, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }

    std::vector<double> myMax;
        for(int i = 1; i < 5; i++){
            myMax.push_back((double)hist0->GetBinContent(i));
            myMax.push_back((double)hist1->GetBinContent(i));
            myMax.push_back((double)hist2->GetBinContent(i));
            myMax.push_back((double)hist3->GetBinContent(i));
            myMax.push_back((double)hist4->GetBinContent(i));
        }
    double yMax = *std::max_element(myMax.begin(), myMax.end());
    if(type.compare("stat") == 0) yMax *= 1.7;
    else yMax = 1.04;

    std::vector<double> myMin;
        for(int i = 1; i < 5; i++){
            myMin.push_back((double)hist0->GetBinContent(i));
            myMin.push_back((double)hist1->GetBinContent(i));
            myMin.push_back((double)hist2->GetBinContent(i));
            myMin.push_back((double)hist3->GetBinContent(i));
            myMin.push_back((double)hist4->GetBinContent(i));
        }
    double yMin = *std::min_element(myMin.begin(), myMin.end());
    if(type.compare("syst") == 0) yMin -= 0.3*fabs(yMin);
    else yMin = 1.0025;

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    a_0 = new TCanvas("a_0", "", 1200, 1200);
    a_0->cd();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.125);
    gPad->SetGridy(1);
    gPad->SetGridx(1);

    hist0->SetLineColor(kRed);
    hist0->SetLineWidth(3);
    hist0->SetMarkerStyle(kFullCircle);
    hist0->SetMarkerColor(kRed);
    hist0->SetMarkerSize(3);
    hist1->SetLineColor(kOrange+7);
    hist1->SetLineWidth(3);
    hist1->SetMarkerStyle(kFullSquare);
    hist1->SetMarkerColor(kOrange+7);
    hist1->SetMarkerSize(3);
    hist2->SetLineColor(kGreen+2);
    hist2->SetLineWidth(3);
    hist2->SetMarkerStyle(kFullTriangleUp);
    hist2->SetMarkerColor(kGreen+2);
    hist2->SetMarkerSize(3);
    hist3->SetLineColor(kBlue+1);
    hist3->SetLineWidth(3);
    hist3->SetMarkerStyle(kFullTriangleDown);
    hist3->SetMarkerColor(kBlue+1);
    hist3->SetMarkerSize(3);
    hist4->SetLineColor(kMagenta+2);
    hist4->SetLineWidth(3);
    hist4->SetMarkerStyle(kFullDiamond);
    hist4->SetMarkerColor(kMagenta+2);
    hist4->SetMarkerSize(3);

    TLegend * legend = new TLegend(0.125,0.7,0.97,0.9);
    legend->AddEntry(hist0, "0.00 < R_{9} < 0.80", "lp");
    legend->AddEntry(hist1, "0.80 < R_{9} < 0.90", "lp");
    legend->AddEntry(hist2, "0.90 < R_{9} < 0.92", "lp");
    legend->AddEntry(hist3, "0.92 < R_{9} < 0.96", "lp");
    legend->AddEntry(hist4, "0.96 < R_{9} < 1.00", "lp");
    std::string temp = "2016 Conditions";
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    std::string post = "";
    switch(eta){
        case 0: 
            temp = "0.0 < |#eta| < 0.3";
            post = "absEta_0_0.3";
            break;
        case 1:
            temp = "0.3 < |#eta| < 0.7";
            post = "absEta_0.3_0.7";
            break;
        case 2:
            temp = "0.7 < |#eta| < 1.1";
            post = "absEta_0.7_1.1";
            break;
        case 3:
            temp = "1.1 < |#eta| < 1.4442";
            post = "absEta_1.1_1.4442";
            break;
        case 4:
            temp = "1.566 < |#eta| < 1.8";
            post = "absEta_1.566_1.8";
            break;
        case 5:
            temp = "1.8 < |#eta| < 2.1";
            post = "absEta_1.8_2.1";
            break;
        case 6:
            temp = "2.1 < |#eta| < 2.5";
            post = "absEta_2.1_2.5";
            break;
    }
    legend->AddEntry((TObject*)0, temp.c_str(), "");

    std::string type_title;
    if(type.compare("syst") == 0) type_title = "Systematics (%)";
    if(type.compare("ele") == 0) type_title = "#LT E'^{e}_{SC}/E^{e}_{SC} #GT (A.U.)";
    if(type.compare("pho") == 0) type_title = "#LT E'^{#gamma}_{SC}/E^{#gamma}_{SC} #GT (A.U.)";
    hist0->SetYTitle(type_title.c_str());
    hist0->SetXTitle("#bf{E_{T}}");
    hist0->SetAxisRange(yMin, yMax, "Y");

    hist0->SetLabelSize(0.035, "Y");
    hist0->SetTitleOffset(1.40, "Y");
    hist0->SetTitleOffset(0.76, "X");
    hist0->SetTitleFont(42, "Y");
    hist0->SetTitleFont(42, "X");
    hist0->SetTitleSize(0.04, "Y");
    hist0->SetTitleSize(0.05, "X");
    hist0->Draw("E");
    hist1->Draw("SAME E");
    hist2->Draw("SAME E");
    hist3->Draw("SAME E");
    hist4->Draw("SAME E");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();


    std::string name = "./plots/etaVsEt_"+type+"_"+post+".pdf";
    a_0->SaveAs(name.c_str());
    name = "./plots/etaVsEt_"+type+"_"+post+".C";
    a_0->SaveAs(name.c_str());
    name = "./plots/etaVsEt_"+type+"_"+post+".png";
    a_0->SaveAs(name.c_str());
    delete a_0;
    return;
}

void plotForEta(TH1F * hist0, TH1F * hist1, TH1F* hist2, TH1F * hist3, TH1F * hist4, TH1F * hist5, std::string type, int eta){

    if(!hist0){
        std::cout << "[ERROR] the histogram named " << hist0->GetName() << " was provided as hist0, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist1){
        std::cout << "[ERROR] the histogram named " << hist1->GetName() << " was provided as hist1, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist2){
        std::cout << "[ERROR] the histogram named " << hist2->GetName() << " was provided as hist2, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist3){
        std::cout << "[ERROR] the histogram named " << hist3->GetName() << " was provided as hist3, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist4){
        std::cout << "[ERROR] the histogram named " << hist4->GetName() << " was provided as hist4, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }

    std::vector<double> myMax;
        for(int i = 1; i < 5; i++){
            myMax.push_back((double)hist0->GetBinContent(i));
            myMax.push_back((double)hist1->GetBinContent(i));
            myMax.push_back((double)hist2->GetBinContent(i));
            myMax.push_back((double)hist3->GetBinContent(i));
            myMax.push_back((double)hist4->GetBinContent(i));
            myMax.push_back((double)hist5->GetBinContent(i));
        }
    double yMax = *std::max_element(myMax.begin(), myMax.end());
    if(type.compare("stat") == 0) yMax *= 1.7;
    else yMax = 1.04;

    std::vector<double> myMin;
        for(int i = 1; i < 5; i++){
            myMin.push_back((double)hist0->GetBinContent(i));
            myMin.push_back((double)hist1->GetBinContent(i));
            myMin.push_back((double)hist2->GetBinContent(i));
            myMin.push_back((double)hist3->GetBinContent(i));
            myMin.push_back((double)hist4->GetBinContent(i));
            myMin.push_back((double)hist5->GetBinContent(i));
        }
    double yMin = *std::min_element(myMin.begin(), myMin.end());
    if(type.compare("syst") == 0) yMin -= 0.3*fabs(yMin);
    else yMin = 1.0025;

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    a_0 = new TCanvas("a_0", "", 1200, 1200);
    a_0->cd();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.125);
    gPad->SetGridy(1);
    gPad->SetGridx(1);

    hist0->SetLineColor(kRed);
    hist0->SetLineWidth(3);
    hist0->SetMarkerStyle(kFullCircle);
    hist0->SetMarkerColor(kRed);
    hist0->SetMarkerSize(3);
    hist1->SetLineColor(kOrange+7);
    hist1->SetLineWidth(3);
    hist1->SetMarkerStyle(kFullSquare);
    hist1->SetMarkerColor(kOrange+7);
    hist1->SetMarkerSize(3);
    hist2->SetLineColor(kGreen+2);
    hist2->SetLineWidth(3);
    hist2->SetMarkerStyle(kFullTriangleUp);
    hist2->SetMarkerColor(kGreen+2);
    hist2->SetMarkerSize(3);
    hist3->SetLineColor(kBlue+1);
    hist3->SetLineWidth(3);
    hist3->SetMarkerStyle(kFullTriangleDown);
    hist3->SetMarkerColor(kBlue+1);
    hist3->SetMarkerSize(3);
    hist4->SetLineColor(kMagenta+2);
    hist4->SetLineWidth(3);
    hist4->SetMarkerStyle(kFullDiamond);
    hist4->SetMarkerColor(kMagenta+2);
    hist4->SetMarkerSize(3);
    hist5->SetLineColor(kBlack);
    hist5->SetLineWidth(3);
    hist5->SetMarkerStyle(kFullCross);
    hist5->SetMarkerColor(kBlack);
    hist5->SetMarkerSize(3);

    TLegend * legend = new TLegend(0.125,0.7,0.97,0.9);
    legend->AddEntry(hist0, "0.00 < R_{9} < 0.80", "lp");
    legend->AddEntry(hist1, "0.80 < R_{9} < 0.90", "lp");
    legend->AddEntry(hist2, "0.90 < R_{9} < 0.92", "lp");
    legend->AddEntry(hist3, "0.92 < R_{9} < 0.94", "lp");
    legend->AddEntry(hist4, "0.94 < R_{9} < 0.96", "lp");
    legend->AddEntry(hist5, "0.96 < R_{9} < 1.00", "lp");
    std::string temp = "2016 Conditions";
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    std::string post = "";
    switch(eta){
        case 0: 
            temp = "0.0 < |#eta| < 0.3";
            post = "absEta_0_0.3";
            break;
        case 1:
            temp = "0.3 < |#eta| < 0.7";
            post = "absEta_0.3_0.7";
            break;
        case 2:
            temp = "0.7 < |#eta| < 1.1";
            post = "absEta_0.7_1.1";
            break;
        case 3:
            temp = "1.1 < |#eta| < 1.4442";
            post = "absEta_1.1_1.4442";
            break;
        case 4:
            temp = "1.566 < |#eta| < 1.8";
            post = "absEta_1.566_1.8";
            break;
        case 5:
            temp = "1.8 < |#eta| < 2.1";
            post = "absEta_1.8_2.1";
            break;
        case 6:
            temp = "2.1 < |#eta| < 2.5";
            post = "absEta_2.1_2.5";
            break;
    }
    legend->AddEntry((TObject*)0, temp.c_str(), "");

    std::string type_title;
    if(type.compare("syst") == 0) type_title = "Systematics (%)";
    if(type.compare("ele") == 0) type_title = "#LT E'^{e}_{SC}/E^{e}_{SC} #GT (A.U.)";
    if(type.compare("pho") == 0) type_title = "#LT E'^{#gamma}_{SC}/E^{#gamma}_{SC} #GT (A.U.)";
    hist0->SetYTitle(type_title.c_str());
    hist0->SetXTitle("#bf{E_{T}}");
    hist0->SetAxisRange(yMin, yMax, "Y");

    hist0->SetLabelSize(0.035, "Y");
    hist0->SetTitleOffset(1.40, "Y");
    hist0->SetTitleOffset(0.76, "X");
    hist0->SetTitleFont(42, "Y");
    hist0->SetTitleFont(42, "X");
    hist0->SetTitleSize(0.04, "Y");
    hist0->SetTitleSize(0.05, "X");
    hist0->Draw("E");
    hist1->Draw("SAME E");
    hist2->Draw("SAME E");
    hist3->Draw("SAME E");
    hist4->Draw("SAME E");
    hist5->Draw("SAME E");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    std::string name = "./plots/etaVsEt_"+type+"_"+post+"_altR9.pdf";
    a_0->SaveAs(name.c_str());
    name = "./plots/etaVsEt_"+type+"_"+post+"_altR9.C";
    a_0->SaveAs(name.c_str());
    name = "./plots/etaVsEt_"+type+"_"+post+"_altR9.png";
    a_0->SaveAs(name.c_str());
    delete a_0;
    return;
}

void plotForR9(TH1F * hist0, TH1F * hist1, TH1F* hist2, TH1F * hist3, TH1F * hist4, TH1F* hist5, TH1F * hist6, std::string type, int eta){

    if(!hist0){
        std::cout << "[ERROR] the histogram named " << hist0->GetName() << " was provided as hist0, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist1){
        std::cout << "[ERROR] the histogram named " << hist1->GetName() << " was provided as hist1, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist2){
        std::cout << "[ERROR] the histogram named " << hist2->GetName() << " was provided as hist2, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist3){
        std::cout << "[ERROR] the histogram named " << hist3->GetName() << " was provided as hist3, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist4){
        std::cout << "[ERROR] the histogram named " << hist4->GetName() << " was provided as hist4, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist5){
        std::cout << "[ERROR] the histogram named " << hist5->GetName() << " was provided as hist5, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }
    if(!hist6){
        std::cout << "[ERROR] the histogram named " << hist6->GetName() << " was provided as hist6, but is not a valid pointer" << std::endl;
        std::cout << "[ERROR] cannot recover, moving past this... " << std::endl;
        return;
    }

    std::vector<double> myMax;
    for(int i = 1; i < 5; i++){
        myMax.push_back((double)hist0->GetBinContent(i));
        myMax.push_back((double)hist1->GetBinContent(i));
        myMax.push_back((double)hist2->GetBinContent(i));
        myMax.push_back((double)hist3->GetBinContent(i));
        myMax.push_back((double)hist4->GetBinContent(i));
        myMax.push_back((double)hist5->GetBinContent(i));
        myMax.push_back((double)hist6->GetBinContent(i));
    }
    double yMax = *std::max_element(myMax.begin(), myMax.end());
    if(type.compare("syst") == 0 ) yMax *= 1.7;
    else yMax = 1.04;

    std::vector<double> myMin;
    for(int i = 1; i < 5; i++){
        myMin.push_back((double)hist0->GetBinContent(i));
        myMin.push_back((double)hist1->GetBinContent(i));
        myMin.push_back((double)hist2->GetBinContent(i));
        myMin.push_back((double)hist3->GetBinContent(i));
        myMin.push_back((double)hist4->GetBinContent(i));
        myMin.push_back((double)hist5->GetBinContent(i));
        myMin.push_back((double)hist6->GetBinContent(i));
    }
    double yMin = *std::min_element(myMin.begin(), myMin.end());
    if(type.compare("syst") == 0) yMin -= 0.3*fabs(yMin);
    else yMin = 1.0025;

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    a_0 = new TCanvas("a_0", "", 1200, 1200);
    a_0->cd();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.125);
    gPad->SetGridy(1);
    gPad->SetGridx(1);


    hist0->SetLineColor(kRed+3);
    hist0->SetLineWidth(3);
    hist0->SetMarkerStyle(45);
    hist0->SetMarkerColor(kRed+3);
    hist0->SetMarkerSize(3);
    hist1->SetLineColor(kRed);
    hist1->SetLineWidth(3);
    hist1->SetMarkerStyle(kFullCircle);
    hist1->SetMarkerColor(kRed);
    hist1->SetMarkerSize(3);
    hist2->SetLineColor(kOrange+7);
    hist2->SetLineWidth(3);
    hist2->SetMarkerStyle(kFullSquare);
    hist2->SetMarkerColor(kOrange+7);
    hist2->SetMarkerSize(3);
    hist3->SetLineColor(kGreen+2);
    hist3->SetLineWidth(3);
    hist3->SetMarkerStyle(kFullTriangleUp);
    hist3->SetMarkerColor(kGreen+2);
    hist3->SetMarkerSize(3);
    hist4->SetLineColor(kBlue+1);
    hist4->SetLineWidth(3);
    hist4->SetMarkerStyle(kFullTriangleDown);
    hist4->SetMarkerColor(kBlue+1);
    hist4->SetMarkerSize(3);
    hist5->SetLineColor(kMagenta+2);
    hist5->SetLineWidth(3);
    hist5->SetMarkerStyle(kFullDiamond);
    hist5->SetMarkerColor(kMagenta+2);
    hist5->SetMarkerSize(3);
    hist6->SetLineColor(kBlack);
    hist6->SetLineWidth(3);
    hist6->SetMarkerStyle(kFullCross);
    hist6->SetMarkerColor(kBlack);
    hist6->SetMarkerSize(3);

    TLegend * legend = new TLegend(0.125,0.7,0.97,0.9);
    legend->AddEntry(hist0, "0.0 < |#eta| < 0.3", "lp");
    legend->AddEntry(hist1, "0.3 < |#eta| < 0.7", "lp");
    legend->AddEntry(hist2, "0.7 < |#eta| < 1.1", "lp");
    legend->AddEntry(hist3, "1.1 < |#eta| < 1.4442", "lp");
    legend->AddEntry(hist4, "1.566 < |#eta| < 1.8", "lp");
    legend->AddEntry(hist5, "1.8 < |#eta| < 2.1", "lp");
    legend->AddEntry(hist6, "2.1 < |#eta| < 2.5", "lp");
    std::string temp = "2016 Conditions";
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    std::string post = "";
    switch(eta){
        case 0: 
            temp = "0.0 < R_{9} < 0.8";
            post = "r9_0_0.8";
            break;
        case 1:
            temp = "0.8 < R_{9} < 0.9";
            post = "r9_0.8_0.9";
            break;
        case 2:
            temp = "0.9 < R_{9} < 0.92";
            post = "r9_0.9_0.92";
            break;
        case 3:
            if(!_flag_altR9){
                temp = "0.92 < R_{9} < 0.96";
                post = "r9_0.92_0.96";
            }
            else{
                temp = "0.92 < R_{9} < 0.94";
                post = "r9_0.92_0.94";
            }
            break;
        case 4:
            if(!_flag_altR9){
                temp = "0.96 < R_{9} < 1";
                post = "r9_0.96_1";
            }
            else{
                temp = "0.94 < R_{9} < 0.96";
                post = "R9_0.94_0.96";
            }
            break;
        case 5:
            temp = "0.96 < R_{9} < 1";
            post = "r9_0.96_1";
            break;
    }
    legend->AddEntry((TObject*)0, temp.c_str(), "");

    std::string type_title;
    if(type.compare("syst") == 0) type_title = "Systematics (%)";
    if(type.compare("ele") == 0) type_title = "#LT E'^{e}_{SC}/E^{e}_{SC} #GT (A.U.)";
    if(type.compare("pho") == 0) type_title = "#LT E'^{#gamma}_{SC}/E^{#gamma}_{SC} #GT (A.U.)";
    hist0->SetYTitle(type_title.c_str());
    hist0->SetXTitle("#bf{E_{T}}");
    hist0->SetAxisRange(yMin, yMax, "Y");

    hist0->SetLabelSize(0.035, "Y");
    hist0->SetTitleOffset(1.40, "Y");
    hist0->SetTitleOffset(0.76, "X");
    hist0->SetTitleFont(42, "Y");
    hist0->SetTitleFont(42, "X");
    hist0->SetTitleSize(0.04, "Y");
    hist0->SetTitleSize(0.05, "X");
    hist0->Draw("E");
    hist1->Draw("SAME E");
    hist2->Draw("SAME E");
    hist3->Draw("SAME E");
    hist4->Draw("SAME E");
    hist5->Draw("SAME E");
    hist6->Draw("SAME E");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(3);
    legend->SetTextSize(0.03);
    legend->SetTextFont(62);
    legend->Draw();

    std::string last = "";
    if(_flag_altR9) last = "_altR9";

    std::string name = "./plots/r9VsEt_"+type+"_"+post+last+".pdf";
    a_0->SaveAs(name.c_str());
    name = "./plots/r9VsEt_"+type+"_"+post+last+".C";
    a_0->SaveAs(name.c_str());
    name = "./plots/r9VsEt_"+type+"_"+post+last+".png";
    a_0->SaveAs(name.c_str());
    delete a_0;
    return;
}
