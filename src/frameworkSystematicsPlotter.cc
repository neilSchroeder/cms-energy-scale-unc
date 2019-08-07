#ifndef utilityplotter
#define utilityplotter

/*
 *
 *
 *
 * This is where the functions used to produce the plots for the systematic 
 *      uncertainty on the photon energy scale are defined.
 *
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TLegend.h>
#include <TCollection.h>
#include <TKey.h>
#include <TPave.h>
#include <TLatex.h>
#include <TPaletteAxis.h>
#include <TStyle.h>
#include <TTree.h>
#include "../interface/frameworkSystematicsPlotter.h"

//#define ETA_VETO
//#define ALT_R9

extern std::string DIRECTORY_NAME;
extern bool _flag_crossChecks;
extern bool _flag_truncate;
extern bool _flag_median;

double laser_response_2016 [7] = {0.93, 0.93, 0.92, 0.91, 0.82, 0.72, 0.56};
double laser_response_2017 [7] = {0.91, 0.90, 0.89, 0.88, 0.77, 0.65, 0.45};
double laser_response_2018 [7] = {0.90, 0.90, 0.88, 0.86, 0.75, 0.61, 0.40};

int laserResponseBins_2016 [7] = {92, 92, 91, 90, 81, 71, 55};
int laserResponseBins_2017 [7] = {90, 89, 88, 87, 76, 64, 44};
int laserResponseBins_2018 [7] = {89, 89, 87, 86, 74, 60, 39};

/// Produce FNUF Histograms only analyzes two files at a time
double etaBins_center[7] = {0.15, 0.5, 0.9, 1.2721, 1.687, 1.95, 2.3};

void mySystematicsPlotter::produce_2016_2017_Plots(std::string fileName, bool corrections){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};

    std::string energy = "";
    float _fEnergy = 0.;
    if(fileName.find("030") != std::string::npos){
        energy = "_30GeV";
        _fEnergy = 30;
    }
    if(fileName.find("045") != std::string::npos){
        energy = "_45GeV";
        _fEnergy = 45;
    }
    if(fileName.find("060") != std::string::npos){
        energy = "_60GeV";
        _fEnergy = 60;
    }
    if(fileName.find("120") != std::string::npos){
        energy = "_120GeV";
        _fEnergy = 120;
    }

    //begin making the necessary histograms
    std::vector< std::vector<TH1F*> > systematics;
    std::vector< std::vector<TH1F*> > energy_pho;
    std::vector< std::vector<TH1F*> > energy_ele;
    std::vector< std::vector<TH1F*> > events_pho;
    std::vector< std::vector<TH1F*> > events_ele;
    std::vector< std::vector<TH1F*> > rms_pho;
    std::vector< std::vector<TH1F*> > rms_ele;
    std::vector< TH1F* > temp_;
    std::vector< TH1F* > temp1_;
    std::vector< TH1F* > temp2_;
    std::vector< TH1F* > temp3_;
    std::vector< TH1F* > temp4_;
    std::vector< TH1F* > temp5_;
    std::vector< TH1F* > temp6_;
    char title [50];
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < numEtaBins; j++){
            sprintf(title, "Systematics_%i_%i", i, j);
            temp_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "Energy_Pho_%i_%i", i, j);
            temp1_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "Energy_Ele_%i_%i", i, j);
            temp2_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "Events_Pho_%i_%i", i, j);
            temp3_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "Events_Ele_%i_%i", i, j);
            temp4_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "rms_Pho_%i_%i", i, j);
            temp5_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "rms_Ele_%i_%i", i, j);
            temp6_.push_back(new TH1F(title, title, numEtaBins, etaBins));
        }
        systematics.push_back(temp_);
        energy_pho.push_back(temp1_);
        energy_ele.push_back(temp2_);
        events_pho.push_back(temp3_);
        events_ele.push_back(temp4_);
        rms_pho.push_back(temp5_);
        rms_ele.push_back(temp6_);
        temp_.clear();
        temp1_.clear();
        temp2_.clear();
        temp3_.clear();
        temp4_.clear();
        temp5_.clear();
        temp6_.clear();
    }

    std::vector< std::vector<TH1F*> > e_0_hists;
    std::vector< std::vector<TH1F*> > e_1_hists;
    std::vector< std::vector<TH1F*> > e_2_hists;
    std::vector< std::vector<TH1F*> > e_3_hists;
    std::vector< std::vector<TH1F*> > e_4_hists;
    std::vector< std::vector<TH1F*> > g_0_hists;
    std::vector< std::vector<TH1F*> > g_1_hists;
    std::vector< std::vector<TH1F*> > g_2_hists;
    std::vector< std::vector<TH1F*> > g_3_hists;
    std::vector< std::vector<TH1F*> > g_4_hists;
#ifdef ALT_R9
    std::vector< std::vector<TH1F*> > e_5_hists;
    std::vector< std::vector<TH1F*> > g_5_hists;
#endif


    const char * fileChar = fileName.c_str();
    TFile* myHistograms = new TFile(fileChar, "READ");

    std::vector<TH1F*> e_0;
    std::vector<TH1F*> e_1;
    std::vector<TH1F*> e_2;
    std::vector<TH1F*> e_3;
    std::vector<TH1F*> e_4;
    std::vector<TH1F*> g_0;
    std::vector<TH1F*> g_1;
    std::vector<TH1F*> g_2;
    std::vector<TH1F*> g_3;
    std::vector<TH1F*> g_4;
#ifdef ALT_R9
    std::vector<TH1F*> e_5;
    std::vector<TH1F*> g_5;
#endif

    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < 100; j++){
            sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
            e_0.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "e_1_%i_%i_%i", i, i+1, j);
            e_1.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "e_2_%i_%i_%i", i, i+1, j);
            e_2.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "e_3_%i_%i_%i", i, i+1, j);
            e_3.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "e_4_%i_%i_%i", i, i+1, j);
            e_4.push_back((TH1F*)myHistograms->Get(title));

            sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
            g_0.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "g_1_%i_%i_%i", i, i+1, j);
            g_1.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "g_2_%i_%i_%i", i, i+1, j);
            g_2.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "g_3_%i_%i_%i", i, i+1, j);
            g_3.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "g_4_%i_%i_%i", i, i+1, j);
            g_4.push_back((TH1F*)myHistograms->Get(title));
#ifdef ALT_R9
            sprintf( title, "e_5_%i_%i_%i", i, i+1, j);
            e_5.push_back((TH1F*)myHistograms->Get(title));
            sprintf( title, "g_5_%i_%i_%i", i, i+1, j);
            g_5.push_back((TH1F*)myHistograms->Get(title));
#endif

        }
        e_0_hists.push_back(e_0);
        e_1_hists.push_back(e_1);
        e_2_hists.push_back(e_2);
        e_3_hists.push_back(e_3);
        e_4_hists.push_back(e_4);
        g_0_hists.push_back(g_0);
        g_1_hists.push_back(g_1);
        g_2_hists.push_back(g_2);
        g_3_hists.push_back(g_3);
        g_4_hists.push_back(g_4);
#ifdef ALT_R9
        e_5_hists.push_back(e_5);
        g_5_hists.push_back(g_5);
        e_5.clear();
        g_5.clear();
#endif
        e_0.clear();
        e_1.clear();
        e_2.clear();
        e_3.clear();
        e_4.clear();
        g_0.clear();
        g_1.clear();
        g_2.clear();
        g_3.clear();
        g_4.clear();
    }

#ifndef ALT_R9
    std::string uncertainty_low = "rootFiles/uncertainty_hists_low_060.root";
    std::string uncertainty_high = "rootFiles/uncertainty_hists_high_060.root";
    std::string uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_060.root";

    if(fileName.find("030") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_030.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_030.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_030.root";
    }
    if(fileName.find("045") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_045.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_045.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_045.root";
    }
    if(fileName.find("120") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_120.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_120.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_120.root";
    }
#else
    std::string uncertainty_low = "rootFiles/uncertainty_hists_low_060_altR9.root";
    std::string uncertainty_high = "rootFiles/uncertainty_hists_high_060_altR9.root";
    std::string uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_060_altR9.root";

    if(fileName.find("030") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_030_altR9.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_030_altR9.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_030_altR9.root";
    }
    if(fileName.find("045") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_045_altR9.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_045_altR9.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_045_altR9.root";
    }
    if(fileName.find("120") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_120_altR9.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_120_altR9.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_120_altR9.root";
    }
#endif

    TFile * correction_low = new TFile(uncertainty_low.c_str(), "READ");
    TFile * correction_high = new TFile(uncertainty_high.c_str(), "READ");
    TFile * correction_front = new TFile(uncertainty_frontDown.c_str(), "READ");

    TH2F * low_ratio_0 = (TH2F*)correction_low->Get("ratio_0");
    TH2F * low_ratio_1 = (TH2F*)correction_low->Get("ratio_1");
    TH2F * low_ratio_2 = (TH2F*)correction_low->Get("ratio_2");
    TH2F * low_ratio_3 = (TH2F*)correction_low->Get("ratio_3");
    TH2F * low_ratio_4 = (TH2F*)correction_low->Get("ratio_4");

    TH2F * high_ratio_0 = (TH2F*)correction_high->Get("ratio_0");
    TH2F * high_ratio_1 = (TH2F*)correction_high->Get("ratio_1");
    TH2F * high_ratio_2 = (TH2F*)correction_high->Get("ratio_2");
    TH2F * high_ratio_3 = (TH2F*)correction_high->Get("ratio_3");
    TH2F * high_ratio_4 = (TH2F*)correction_high->Get("ratio_4");

    TH2F * front_ratio_0 = (TH2F*)correction_front->Get("ratio_0");
    TH2F * front_ratio_1 = (TH2F*)correction_front->Get("ratio_1");
    TH2F * front_ratio_2 = (TH2F*)correction_front->Get("ratio_2");
    TH2F * front_ratio_3 = (TH2F*)correction_front->Get("ratio_3");
    TH2F * front_ratio_4 = (TH2F*)correction_front->Get("ratio_4");

#ifdef ALT_R9
    TH2F * low_ratio_5 = (TH2F*)correction_low->Get("ratio_5");
    TH2F * high_ratio_5 = (TH2F*)correction_high->Get("ratio_5");
    TH2F * front_ratio_5 = (TH2F*)correction_front->Get("ratio_5");
#endif

    double mean1, mean2;
    double error1, error2;
    double quantile;
    double statError;
    double muNatError;
    double finalVal;
    double correction;
    double median = 0.5;
    for(int eta = 0; eta < numEtaBins; eta++){
        if(eta != 4){
            for(int apd = 35; apd < 99; apd++){
                if(_flag_crossChecks){
                    for(int i = 0; i < 7; i++){
                        if(laserResponseBins_2016[i] == apd){
                            mySystematicsPlotter::plot_pair(g_0_hists[eta][99-apd], e_0_hists[eta][99-apd], "0", energy, "", 0, -999);
                            mySystematicsPlotter::plot_pair(g_1_hists[eta][99-apd], e_1_hists[eta][99-apd], "1", energy, "", 0, -999);
                            mySystematicsPlotter::plot_pair(g_2_hists[eta][99-apd], e_2_hists[eta][99-apd], "2", energy, "", 0, -999);
                            mySystematicsPlotter::plot_pair(g_3_hists[eta][99-apd], e_3_hists[eta][99-apd], "3", energy, "", 0, -999);
                            mySystematicsPlotter::plot_pair(g_4_hists[eta][99-apd], e_4_hists[eta][99-apd], "4", energy, "", 0, -999);
#ifdef ALT_R9
                            mySystematicsPlotter::plot_pair(g_5_hists[eta][99-apd], e_5_hists[eta][99-apd], "5", energy, "", 0, -999);
#endif
                        }
                    }
                }
                if(_flag_truncate){
                    e_0_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    g_0_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    e_1_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    g_1_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    e_2_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    g_2_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    e_3_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    g_3_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    e_4_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    g_4_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                }

                double correction_norm = std::max( fabs(low_ratio_0->GetBinContent(eta+1, apd+1)), fabs(high_ratio_0->GetBinContent(eta+1, apd+1)));
                double correction_front = fabs(front_ratio_0->GetBinContent(eta+1, apd+1));
                if(_flag_median){
                    e_0_hists[eta][99-apd]->GetQuantiles(1, &mean1, &median); 
                    g_0_hists[eta][99-apd]->GetQuantiles(1, &mean2, &median); 
                }
                else{
                    mean1 = e_0_hists[eta][99-apd]->GetMean();
                    mean2 = g_0_hists[eta][99-apd]->GetMean();
                }
                error1 = e_0_hists[eta][99-apd]->GetRMS()/sqrt(e_0_hists[eta][99-apd]->GetEntries());
                error2 = g_0_hists[eta][99-apd]->GetRMS()/sqrt(g_0_hists[eta][99-apd]->GetEntries());
                correction = (1 + (correction_front/100.) + (correction_norm/100.));
                if(corrections){
                    systematics[apd][0]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*correction);
                    systematics[apd][0]->SetBinError(eta + 1, 100*(mean2/mean1)*correction*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                else{
                    systematics[apd][0]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1));
                    systematics[apd][0]->SetBinError(eta + 1, 100*(mean2/mean1)*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));\
                }
                energy_pho[apd][0]->SetBinContent(eta+1, mean2);
                energy_pho[apd][0]->SetBinError(eta+1, error2);
                energy_ele[apd][0]->SetBinContent(eta+1, mean1);
                energy_ele[apd][0]->SetBinError(eta+1, error1);
                events_pho[apd][0]->SetBinContent(eta+1,g_0_hists[eta][99-apd]->GetEntries()); 
                events_ele[apd][0]->SetBinContent(eta+1,e_0_hists[eta][99-apd]->GetEntries()); 
                rms_pho[apd][0]->SetBinContent(eta+1, g_0_hists[eta][99-apd]->GetRMS());
                rms_ele[apd][0]->SetBinContent(eta+1, e_0_hists[eta][99-apd]->GetRMS());

                correction_norm = std::max( fabs(low_ratio_1->GetBinContent(eta+1, apd+1)), fabs(high_ratio_1->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_1->GetBinContent(eta+1, apd+1));
                if(_flag_median){
                    e_1_hists[eta][99-apd]->GetQuantiles(1, &mean1, &median); 
                    g_1_hists[eta][99-apd]->GetQuantiles(1, &mean2, &median); 
                }
                else{
                    mean1 = e_1_hists[eta][99-apd]->GetMean();
                    mean2 = g_1_hists[eta][99-apd]->GetMean();
                }
                mean1 = e_1_hists[eta][99-apd]->GetMean();
                mean2 = g_1_hists[eta][99-apd]->GetMean();
                error1 = e_1_hists[eta][99-apd]->GetRMS()/sqrt(e_1_hists[eta][99-apd]->GetEntries());
                error2 = g_1_hists[eta][99-apd]->GetRMS()/sqrt(g_1_hists[eta][99-apd]->GetEntries());
                correction = (1 + (correction_front/100.) + (correction_norm/100.));
                if(corrections){
                    systematics[apd][1]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*correction);
                    systematics[apd][1]->SetBinError(eta + 1, 100*(mean2/mean1)*correction*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                else{
                    systematics[apd][1]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1));
                    systematics[apd][1]->SetBinError(eta + 1, 100*(mean2/mean1)*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                energy_pho[apd][1]->SetBinContent(eta+1, mean2);
                energy_pho[apd][1]->SetBinError(eta+1, error2);
                energy_ele[apd][1]->SetBinContent(eta+1, mean1);
                energy_ele[apd][1]->SetBinError(eta+1, error1);
                events_pho[apd][1]->SetBinContent(eta+1,g_1_hists[eta][99-apd]->GetEntries()); 
                events_ele[apd][1]->SetBinContent(eta+1,e_1_hists[eta][99-apd]->GetEntries()); 
                rms_pho[apd][1]->SetBinContent(eta+1, g_1_hists[eta][99-apd]->GetRMS());
                rms_ele[apd][1]->SetBinContent(eta+1, e_1_hists[eta][99-apd]->GetRMS());

                correction_norm = std::max( fabs(low_ratio_2->GetBinContent(eta+1, apd+1)), fabs(high_ratio_2->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_2->GetBinContent(eta+1, apd+1));
                if(_flag_median){
                    e_2_hists[eta][99-apd]->GetQuantiles(1, &mean1, &median); 
                    g_2_hists[eta][99-apd]->GetQuantiles(1, &mean2, &median); 
                }
                else{
                    mean1 = e_2_hists[eta][99-apd]->GetMean();
                    mean2 = g_2_hists[eta][99-apd]->GetMean();
                }
                mean1 = e_2_hists[eta][99-apd]->GetMean();
                mean2 = g_2_hists[eta][99-apd]->GetMean();
                error1 = e_2_hists[eta][99-apd]->GetRMS()/sqrt(e_2_hists[eta][99-apd]->GetEntries());
                error2 = g_2_hists[eta][99-apd]->GetRMS()/sqrt(g_2_hists[eta][99-apd]->GetEntries());
                correction = (1 + (correction_front/100.) + (correction_norm/100.));
                if(corrections){
                    systematics[apd][2]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*correction);
                    systematics[apd][2]->SetBinError(eta + 1, 100*(mean2/mean1)*correction*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                else{
                    systematics[apd][2]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1));
                    systematics[apd][2]->SetBinError(eta + 1, 100*(mean2/mean1)*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                energy_pho[apd][2]->SetBinContent(eta+1, mean2);
                energy_pho[apd][2]->SetBinError(eta+1, error2);
                energy_ele[apd][2]->SetBinContent(eta+1, mean1);
                energy_ele[apd][2]->SetBinError(eta+1, error1);
                events_pho[apd][2]->SetBinContent(eta+1,g_2_hists[eta][99-apd]->GetEntries()); 
                events_ele[apd][2]->SetBinContent(eta+1,e_2_hists[eta][99-apd]->GetEntries()); 
                rms_pho[apd][2]->SetBinContent(eta+1, g_2_hists[eta][99-apd]->GetRMS());
                rms_ele[apd][2]->SetBinContent(eta+1, e_2_hists[eta][99-apd]->GetRMS());

                correction_norm = std::max( fabs(low_ratio_3->GetBinContent(eta+1, apd+1)), fabs(high_ratio_3->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_3->GetBinContent(eta+1, apd+1));
                if(_flag_median){
                    e_3_hists[eta][99-apd]->GetQuantiles(1, &mean1, &median); 
                    g_3_hists[eta][99-apd]->GetQuantiles(1, &mean2, &median); 
                }
                else{
                    mean1 = e_3_hists[eta][99-apd]->GetMean();
                    mean2 = g_3_hists[eta][99-apd]->GetMean();
                }
                mean1 = e_3_hists[eta][99-apd]->GetMean();
                mean2 = g_3_hists[eta][99-apd]->GetMean();
                error1 = e_3_hists[eta][99-apd]->GetRMS()/sqrt(e_3_hists[eta][99-apd]->GetEntries());
                error2 = g_3_hists[eta][99-apd]->GetRMS()/sqrt(g_3_hists[eta][99-apd]->GetEntries());
                correction = (1 + (correction_front/100.) + (correction_norm/100.));
                if(corrections){
                    systematics[apd][3]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*correction);
                    systematics[apd][3]->SetBinError(eta + 1, 100*(mean2/mean1)*correction*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                else{
                    systematics[apd][3]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1));
                    systematics[apd][3]->SetBinError(eta + 1, 100*(mean2/mean1)*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                energy_pho[apd][3]->SetBinContent(eta+1, mean2);
                energy_pho[apd][3]->SetBinError(eta+1, error2);
                energy_ele[apd][3]->SetBinContent(eta+1, mean1);
                energy_ele[apd][3]->SetBinError(eta+1, error1);
                events_pho[apd][3]->SetBinContent(eta+1,g_3_hists[eta][99-apd]->GetEntries()); 
                events_ele[apd][3]->SetBinContent(eta+1,e_3_hists[eta][99-apd]->GetEntries()); 
                rms_pho[apd][3]->SetBinContent(eta+1, g_3_hists[eta][99-apd]->GetRMS());
                rms_ele[apd][3]->SetBinContent(eta+1, e_3_hists[eta][99-apd]->GetRMS());

                correction_norm = std::max( fabs(low_ratio_4->GetBinContent(eta+1, apd+1)), fabs(high_ratio_4->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_4->GetBinContent(eta+1, apd+1));
                if(_flag_median){
                    e_4_hists[eta][99-apd]->GetQuantiles(1, &mean1, &median); 
                    g_4_hists[eta][99-apd]->GetQuantiles(1, &mean2, &median); 
                }
                else{
                    mean1 = e_4_hists[eta][99-apd]->GetMean();
                    mean2 = g_4_hists[eta][99-apd]->GetMean();
                }
                error1 = e_4_hists[eta][99-apd]->GetRMS()/sqrt(e_4_hists[eta][99-apd]->GetEntries());
                error2 = g_4_hists[eta][99-apd]->GetRMS()/sqrt(g_4_hists[eta][99-apd]->GetEntries());
                correction = (1 + (correction_front/100.) + (correction_norm/100.));
                if(corrections){
                    systematics[apd][4]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*correction);
                    systematics[apd][4]->SetBinError(eta + 1, 100*(mean2/mean1)*correction*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                else{
                    systematics[apd][4]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1));
                    systematics[apd][4]->SetBinError(eta + 1, 100*(mean2/mean1)*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                energy_pho[apd][4]->SetBinContent(eta+1, mean2);
                energy_pho[apd][4]->SetBinError(eta+1, error2);
                energy_ele[apd][4]->SetBinContent(eta+1, mean1);
                energy_ele[apd][4]->SetBinError(eta+1, error1);
                events_pho[apd][4]->SetBinContent(eta+1,g_4_hists[eta][99-apd]->GetEntries()); 
                events_ele[apd][4]->SetBinContent(eta+1,e_4_hists[eta][99-apd]->GetEntries()); 
                rms_pho[apd][4]->SetBinContent(eta+1, g_4_hists[eta][99-apd]->GetRMS());
                rms_ele[apd][4]->SetBinContent(eta+1, e_4_hists[eta][99-apd]->GetRMS());
#ifdef ALT_R9
                correction_norm = std::max( fabs(low_ratio_5->GetBinContent(eta+1, apd+1)), fabs(high_ratio_5->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_5->GetBinContent(eta+1, apd+1));
                if(_flag_truncate){
                    e_5_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                    g_5_hists[eta][99-apd]->GetXaxis()->SetRangeUser(1, 1.05);
                }
                mean1 = e_5_hists[eta][99-apd]->GetMean();
                mean2 = g_5_hists[eta][99-apd]->GetMean();
                error1 = e_5_hists[eta][99-apd]->GetRMS()/sqrt(e_5_hists[eta][99-apd]->GetEntries());
                error2 = g_5_hists[eta][99-apd]->GetRMS()/sqrt(g_5_hists[eta][99-apd]->GetEntries());
                correction = (1 + (correction_front/100.) + (correction_norm/100.));
                if(corrections){
                    systematics[apd][5]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*correction);
                    systematics[apd][5]->SetBinError(eta + 1, 100*(mean2/mean1)*correction*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                else{
                    systematics[apd][5]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1));
                    systematics[apd][5]->SetBinError(eta + 1, 100*(mean2/mean1)*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));
                }
                energy_pho[apd][5]->SetBinContent(eta+1, mean2);
                energy_pho[apd][5]->SetBinError(eta+1, error2);
                energy_ele[apd][5]->SetBinContent(eta+1, mean1);
                energy_ele[apd][5]->SetBinError(eta+1, error1);
                events_pho[apd][5]->SetBinContent(eta+1,g_5_hists[eta][99-apd]->GetEntries()); 
                events_ele[apd][5]->SetBinContent(eta+1,e_5_hists[eta][99-apd]->GetEntries()); 
                rms_pho[apd][5]->SetBinContent(eta+1, g_5_hists[eta][99-apd]->GetRMS());
                rms_ele[apd][5]->SetBinContent(eta+1, e_5_hists[eta][99-apd]->GetRMS());
#endif
            }
        }
    }

    TH1F * systematics2016_0 = new TH1F("systematics2016_0", "systematics2016_0", 8, etaBins);
    TH1F * systematics2016_1 = new TH1F("systematics2016_1", "systematics2016_1", 8, etaBins);
    TH1F * systematics2016_2 = new TH1F("systematics2016_2", "systematics2016_2", 8, etaBins);
    TH1F * systematics2016_3 = new TH1F("systematics2016_3", "systematics2016_3", 8, etaBins);
    TH1F * systematics2016_4 = new TH1F("systematics2016_4", "systematics2016_4", 8, etaBins);

    TH1F * systematics2017_0 = new TH1F("systematics2017_0", "systematics2017_0", 8, etaBins);
    TH1F * systematics2017_1 = new TH1F("systematics2017_1", "systematics2017_1", 8, etaBins);
    TH1F * systematics2017_2 = new TH1F("systematics2017_2", "systematics2017_2", 8, etaBins);
    TH1F * systematics2017_3 = new TH1F("systematics2017_3", "systematics2017_3", 8, etaBins);
    TH1F * systematics2017_4 = new TH1F("systematics2017_4", "systematics2017_4", 8, etaBins);

    TH1F * systematics2018_0 = new TH1F("systematics2018_0", "systematics2018_0", 8, etaBins);
    TH1F * systematics2018_1 = new TH1F("systematics2018_1", "systematics2018_1", 8, etaBins);
    TH1F * systematics2018_2 = new TH1F("systematics2018_2", "systematics2018_2", 8, etaBins);
    TH1F * systematics2018_3 = new TH1F("systematics2018_3", "systematics2018_3", 8, etaBins);
    TH1F * systematics2018_4 = new TH1F("systematics2018_4", "systematics2018_4", 8, etaBins);

    TH1F * energy_pho2016_0 = new TH1F("energy_pho2016_0", "energy_pho2016_0", 8, etaBins);
    TH1F * energy_pho2016_1 = new TH1F("energy_pho2016_1", "energy_pho2016_1", 8, etaBins);
    TH1F * energy_pho2016_2 = new TH1F("energy_pho2016_2", "energy_pho2016_2", 8, etaBins);
    TH1F * energy_pho2016_3 = new TH1F("energy_pho2016_3", "energy_pho2016_3", 8, etaBins);
    TH1F * energy_pho2016_4 = new TH1F("energy_pho2016_4", "energy_pho2016_4", 8, etaBins);

    TH1F * energy_pho2017_0 = new TH1F("energy_pho2017_0", "energy_pho2017_0", 8, etaBins);
    TH1F * energy_pho2017_1 = new TH1F("energy_pho2017_1", "energy_pho2017_1", 8, etaBins);
    TH1F * energy_pho2017_2 = new TH1F("energy_pho2017_2", "energy_pho2017_2", 8, etaBins);
    TH1F * energy_pho2017_3 = new TH1F("energy_pho2017_3", "energy_pho2017_3", 8, etaBins);
    TH1F * energy_pho2017_4 = new TH1F("energy_pho2017_4", "energy_pho2017_4", 8, etaBins);

    TH1F * energy_pho2018_0 = new TH1F("energy_pho2018_0", "energy_pho2018_0", 8, etaBins);
    TH1F * energy_pho2018_1 = new TH1F("energy_pho2018_1", "energy_pho2018_1", 8, etaBins);
    TH1F * energy_pho2018_2 = new TH1F("energy_pho2018_2", "energy_pho2018_2", 8, etaBins);
    TH1F * energy_pho2018_3 = new TH1F("energy_pho2018_3", "energy_pho2018_3", 8, etaBins);
    TH1F * energy_pho2018_4 = new TH1F("energy_pho2018_4", "energy_pho2018_4", 8, etaBins);

    TH1F * energy_ele2016_0 = new TH1F("energy_ele2016_0", "energy_ele2016_0", 8, etaBins);
    TH1F * energy_ele2016_1 = new TH1F("energy_ele2016_1", "energy_ele2016_1", 8, etaBins);
    TH1F * energy_ele2016_2 = new TH1F("energy_ele2016_2", "energy_ele2016_2", 8, etaBins);
    TH1F * energy_ele2016_3 = new TH1F("energy_ele2016_3", "energy_ele2016_3", 8, etaBins);
    TH1F * energy_ele2016_4 = new TH1F("energy_ele2016_4", "energy_ele2016_4", 8, etaBins);

    TH1F * energy_ele2017_0 = new TH1F("energy_ele2017_0", "energy_ele2017_0", 8, etaBins);
    TH1F * energy_ele2017_1 = new TH1F("energy_ele2017_1", "energy_ele2017_1", 8, etaBins);
    TH1F * energy_ele2017_2 = new TH1F("energy_ele2017_2", "energy_ele2017_2", 8, etaBins);
    TH1F * energy_ele2017_3 = new TH1F("energy_ele2017_3", "energy_ele2017_3", 8, etaBins);
    TH1F * energy_ele2017_4 = new TH1F("energy_ele2017_4", "energy_ele2017_4", 8, etaBins);

    TH1F * energy_ele2018_0 = new TH1F("energy_ele2018_0", "energy_ele2018_0", 8, etaBins);
    TH1F * energy_ele2018_1 = new TH1F("energy_ele2018_1", "energy_ele2018_1", 8, etaBins);
    TH1F * energy_ele2018_2 = new TH1F("energy_ele2018_2", "energy_ele2018_2", 8, etaBins);
    TH1F * energy_ele2018_3 = new TH1F("energy_ele2018_3", "energy_ele2018_3", 8, etaBins);
    TH1F * energy_ele2018_4 = new TH1F("energy_ele2018_4", "energy_ele2018_4", 8, etaBins);

    TH1F * events_pho2016_0 = new TH1F("events_pho2016_0", "events_pho2016_0", 8, etaBins);
    TH1F * events_pho2016_1 = new TH1F("events_pho2016_1", "events_pho2016_1", 8, etaBins);
    TH1F * events_pho2016_2 = new TH1F("events_pho2016_2", "events_pho2016_2", 8, etaBins);
    TH1F * events_pho2016_3 = new TH1F("events_pho2016_3", "events_pho2016_3", 8, etaBins);
    TH1F * events_pho2016_4 = new TH1F("events_pho2016_4", "events_pho2016_4", 8, etaBins);

    TH1F * events_ele2016_0 = new TH1F("events_ele2016_0", "events_ele2016_0", 8, etaBins);
    TH1F * events_ele2016_1 = new TH1F("events_ele2016_1", "events_ele2016_1", 8, etaBins);
    TH1F * events_ele2016_2 = new TH1F("events_ele2016_2", "events_ele2016_2", 8, etaBins);
    TH1F * events_ele2016_3 = new TH1F("events_ele2016_3", "events_ele2016_3", 8, etaBins);
    TH1F * events_ele2016_4 = new TH1F("events_ele2016_4", "events_ele2016_4", 8, etaBins);

    TH1F * rms_pho2016_0 = new TH1F("rms_pho2016_0", "rms_pho2016_0", 8, etaBins);
    TH1F * rms_pho2016_1 = new TH1F("rms_pho2016_1", "rms_pho2016_1", 8, etaBins);
    TH1F * rms_pho2016_2 = new TH1F("rms_pho2016_2", "rms_pho2016_2", 8, etaBins);
    TH1F * rms_pho2016_3 = new TH1F("rms_pho2016_3", "rms_pho2016_3", 8, etaBins);
    TH1F * rms_pho2016_4 = new TH1F("rms_pho2016_4", "rms_pho2016_4", 8, etaBins);

    TH1F * rms_ele2016_0 = new TH1F("rms_ele2016_0", "rms_ele2016_0", 8, etaBins);
    TH1F * rms_ele2016_1 = new TH1F("rms_ele2016_1", "rms_ele2016_1", 8, etaBins);
    TH1F * rms_ele2016_2 = new TH1F("rms_ele2016_2", "rms_ele2016_2", 8, etaBins);
    TH1F * rms_ele2016_3 = new TH1F("rms_ele2016_3", "rms_ele2016_3", 8, etaBins);
    TH1F * rms_ele2016_4 = new TH1F("rms_ele2016_4", "rms_ele2016_4", 8, etaBins);

    TH1F * rms_pho2017_0 = new TH1F("rms_pho2017_0", "rms_pho2017_0", 8, etaBins);
    TH1F * rms_pho2017_1 = new TH1F("rms_pho2017_1", "rms_pho2017_1", 8, etaBins);
    TH1F * rms_pho2017_2 = new TH1F("rms_pho2017_2", "rms_pho2017_2", 8, etaBins);
    TH1F * rms_pho2017_3 = new TH1F("rms_pho2017_3", "rms_pho2017_3", 8, etaBins);
    TH1F * rms_pho2017_4 = new TH1F("rms_pho2017_4", "rms_pho2017_4", 8, etaBins);

    TH1F * rms_ele2017_0 = new TH1F("rms_ele2017_0", "rms_ele2017_0", 8, etaBins);
    TH1F * rms_ele2017_1 = new TH1F("rms_ele2017_1", "rms_ele2017_1", 8, etaBins);
    TH1F * rms_ele2017_2 = new TH1F("rms_ele2017_2", "rms_ele2017_2", 8, etaBins);
    TH1F * rms_ele2017_3 = new TH1F("rms_ele2017_3", "rms_ele2017_3", 8, etaBins);
    TH1F * rms_ele2017_4 = new TH1F("rms_ele2017_4", "rms_ele2017_4", 8, etaBins);

    TH1F * rms_pho2018_0 = new TH1F("rms_pho2018_0", "rms_pho2018_0", 8, etaBins);
    TH1F * rms_pho2018_1 = new TH1F("rms_pho2018_1", "rms_pho2018_1", 8, etaBins);
    TH1F * rms_pho2018_2 = new TH1F("rms_pho2018_2", "rms_pho2018_2", 8, etaBins);
    TH1F * rms_pho2018_3 = new TH1F("rms_pho2018_3", "rms_pho2018_3", 8, etaBins);
    TH1F * rms_pho2018_4 = new TH1F("rms_pho2018_4", "rms_pho2018_4", 8, etaBins);

    TH1F * rms_ele2018_0 = new TH1F("rms_ele2018_0", "rms_ele2018_0", 8, etaBins);
    TH1F * rms_ele2018_1 = new TH1F("rms_ele2018_1", "rms_ele2018_1", 8, etaBins);
    TH1F * rms_ele2018_2 = new TH1F("rms_ele2018_2", "rms_ele2018_2", 8, etaBins);
    TH1F * rms_ele2018_3 = new TH1F("rms_ele2018_3", "rms_ele2018_3", 8, etaBins);
    TH1F * rms_ele2018_4 = new TH1F("rms_ele2018_4", "rms_ele2018_4", 8, etaBins);
#ifdef ALT_R9
    TH1F * systematics2016_5 = new TH1F("systematics2016_5", "systematics2016_5", 8, etaBins);
    TH1F * systematics2017_5 = new TH1F("systematics2017_5", "systematics2017_5", 8, etaBins);
    TH1F * systematics2018_5 = new TH1F("systematics2018_5", "systematics2018_5", 8, etaBins);
    TH1F * energy_ele2016_5 = new TH1F("energy_ele2016_5", "energy_ele2016_5", 8, etaBins);
    TH1F * energy_ele2017_5 = new TH1F("energy_ele2017_5", "energy_ele2017_5", 8, etaBins);
    TH1F * energy_ele2018_5 = new TH1F("energy_ele2018_5", "energy_ele2018_5", 8, etaBins);
    TH1F * energy_pho2016_5 = new TH1F("energy_pho2016_5", "energy_pho2016_5", 8, etaBins);
    TH1F * energy_pho2017_5 = new TH1F("energy_pho2017_5", "energy_pho2017_5", 8, etaBins);
    TH1F * energy_pho2018_5 = new TH1F("energy_pho2018_5", "energy_pho2018_5", 8, etaBins);
    TH1F * events_ele2016_5 = new TH1F("events_ele2016_5", "events_ele2016_5", 8, etaBins);
    TH1F * events_pho2016_5 = new TH1F("events_pho2016_5", "events_pho2016_5", 8, etaBins);
    TH1F * rms_ele2016_5 = new TH1F("rms_ele2016_5", "rms_ele2016_5", 8, etaBins);
    TH1F * rms_ele2017_5 = new TH1F("rms_ele2017_5", "rms_ele2017_5", 8, etaBins);
    TH1F * rms_ele2018_5 = new TH1F("rms_ele2018_5", "rms_ele2018_5", 8, etaBins);
    TH1F * rms_pho2016_5 = new TH1F("rms_pho2016_5", "rms_pho2016_5", 8, etaBins);
    TH1F * rms_pho2017_5 = new TH1F("rms_pho2017_5", "rms_pho2017_5", 8, etaBins);
    TH1F * rms_pho2018_5 = new TH1F("rms_pho2018_5", "rms_pho2018_5", 8, etaBins);
#endif

    for(int i = 0; i < numR9bins; i++){
        for(int j = 0; j < numEtaBins; j++){
            int bin = j;
            if(j != 4){
                if(j > 4) bin = j-1;
                switch( i ){
                    case 0:
                        systematics2016_0->SetBinContent(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        systematics2017_0->SetBinContent(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        systematics2018_0->SetBinContent(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        systematics2016_0->SetBinError(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        systematics2017_0->SetBinError(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        systematics2018_0->SetBinError(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_pho2016_0->SetBinContent(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_pho2017_0->SetBinContent(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_pho2018_0->SetBinContent(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_pho2016_0->SetBinError(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_pho2017_0->SetBinError(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_pho2018_0->SetBinError(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_ele2016_0->SetBinContent(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_ele2017_0->SetBinContent(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_ele2018_0->SetBinContent(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_ele2016_0->SetBinError(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_ele2017_0->SetBinError(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_ele2018_0->SetBinError(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        events_pho2016_0->SetBinContent(j+1, events_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        events_ele2016_0->SetBinContent(j+1, events_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2016_0->SetBinContent(j+1, rms_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_ele2016_0->SetBinContent(j+1, rms_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2017_0->SetBinContent(j+1, rms_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_ele2017_0->SetBinContent(j+1, rms_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_pho2018_0->SetBinContent(j+1, rms_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        rms_ele2018_0->SetBinContent(j+1, rms_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                    case 1:
                        systematics2016_1->SetBinContent(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        systematics2017_1->SetBinContent(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        systematics2018_1->SetBinContent(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        systematics2016_1->SetBinError(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        systematics2017_1->SetBinError(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        systematics2018_1->SetBinError(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_pho2016_1->SetBinContent(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_pho2017_1->SetBinContent(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_pho2018_1->SetBinContent(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_pho2016_1->SetBinError(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_pho2017_1->SetBinError(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_pho2018_1->SetBinError(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_ele2016_1->SetBinContent(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_ele2017_1->SetBinContent(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_ele2018_1->SetBinContent(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_ele2016_1->SetBinError(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_ele2017_1->SetBinError(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_ele2018_1->SetBinError(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        events_pho2016_1->SetBinContent(j+1, events_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        events_ele2016_1->SetBinContent(j+1, events_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2016_1->SetBinContent(j+1, rms_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_ele2016_1->SetBinContent(j+1, rms_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2017_1->SetBinContent(j+1, rms_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_ele2017_1->SetBinContent(j+1, rms_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_pho2018_1->SetBinContent(j+1, rms_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        rms_ele2018_1->SetBinContent(j+1, rms_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                    case 2:
                        systematics2016_2->SetBinContent(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        systematics2017_2->SetBinContent(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        systematics2018_2->SetBinContent(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        systematics2016_2->SetBinError(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        systematics2017_2->SetBinError(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        systematics2018_2->SetBinError(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_pho2016_2->SetBinContent(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_pho2017_2->SetBinContent(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_pho2018_2->SetBinContent(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_pho2016_2->SetBinError(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_pho2017_2->SetBinError(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_pho2018_2->SetBinError(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_ele2016_2->SetBinContent(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_ele2017_2->SetBinContent(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_ele2018_2->SetBinContent(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_ele2016_2->SetBinError(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_ele2017_2->SetBinError(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_ele2018_2->SetBinError(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        events_pho2016_2->SetBinContent(j+1, events_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        events_ele2016_2->SetBinContent(j+1, events_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2016_2->SetBinContent(j+1, rms_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_ele2016_2->SetBinContent(j+1, rms_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2017_2->SetBinContent(j+1, rms_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_ele2017_2->SetBinContent(j+1, rms_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_pho2018_2->SetBinContent(j+1, rms_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        rms_ele2018_2->SetBinContent(j+1, rms_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                    case 3:
                        systematics2016_3->SetBinContent(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        systematics2017_3->SetBinContent(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        systematics2018_3->SetBinContent(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        systematics2016_3->SetBinError(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        systematics2017_3->SetBinError(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        systematics2018_3->SetBinError(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_pho2016_3->SetBinContent(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_pho2017_3->SetBinContent(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_pho2018_3->SetBinContent(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_pho2016_3->SetBinError(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_pho2017_3->SetBinError(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_pho2018_3->SetBinError(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_ele2016_3->SetBinContent(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_ele2017_3->SetBinContent(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_ele2018_3->SetBinContent(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_ele2016_3->SetBinError(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_ele2017_3->SetBinError(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_ele2018_3->SetBinError(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        events_pho2016_3->SetBinContent(j+1, events_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        events_ele2016_3->SetBinContent(j+1, events_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2016_3->SetBinContent(j+1, rms_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_ele2016_3->SetBinContent(j+1, rms_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2017_3->SetBinContent(j+1, rms_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_ele2017_3->SetBinContent(j+1, rms_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_pho2018_3->SetBinContent(j+1, rms_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        rms_ele2018_3->SetBinContent(j+1, rms_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                    case 4:
                        systematics2016_4->SetBinContent(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        systematics2017_4->SetBinContent(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        systematics2018_4->SetBinContent(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        systematics2016_4->SetBinError(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        systematics2017_4->SetBinError(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        systematics2018_4->SetBinError(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_pho2016_4->SetBinContent(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_pho2017_4->SetBinContent(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_pho2018_4->SetBinContent(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_pho2016_4->SetBinError(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_pho2017_4->SetBinError(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_pho2018_4->SetBinError(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_ele2016_4->SetBinContent(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_ele2017_4->SetBinContent(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_ele2018_4->SetBinContent(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_ele2016_4->SetBinError(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_ele2017_4->SetBinError(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_ele2018_4->SetBinError(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        events_pho2016_4->SetBinContent(j+1, events_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        events_ele2016_4->SetBinContent(j+1, events_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2016_4->SetBinContent(j+1, rms_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_ele2016_4->SetBinContent(j+1, rms_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2017_4->SetBinContent(j+1, rms_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_ele2017_4->SetBinContent(j+1, rms_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_pho2018_4->SetBinContent(j+1, rms_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        rms_ele2018_4->SetBinContent(j+1, rms_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
#ifdef ALT_R9
                    case 5:
                        systematics2016_5->SetBinContent(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        systematics2017_5->SetBinContent(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        systematics2018_5->SetBinContent(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        systematics2016_5->SetBinError(j+1, systematics[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        systematics2017_5->SetBinError(j+1, systematics[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        systematics2018_5->SetBinError(j+1, systematics[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_pho2016_5->SetBinContent(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_pho2017_5->SetBinContent(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_pho2018_5->SetBinContent(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_pho2016_5->SetBinError(j+1, energy_pho[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_pho2017_5->SetBinError(j+1, energy_pho[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_pho2018_5->SetBinError(j+1, energy_pho[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        energy_ele2016_5->SetBinContent(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        energy_ele2017_5->SetBinContent(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        energy_ele2018_5->SetBinContent(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        energy_ele2016_5->SetBinError(j+1, energy_ele[laserResponseBins_2016[bin]][i]->GetBinError(j+1));
                        energy_ele2017_5->SetBinError(j+1, energy_ele[laserResponseBins_2017[bin]][i]->GetBinError(j+1));
                        energy_ele2018_5->SetBinError(j+1, energy_ele[laserResponseBins_2018[bin]][i]->GetBinError(j+1));
                        events_pho2016_5->SetBinContent(j+1, events_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        events_ele2016_5->SetBinContent(j+1, events_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2016_5->SetBinContent(j+1, rms_pho[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_ele2016_5->SetBinContent(j+1, rms_ele[laserResponseBins_2016[bin]][i]->GetBinContent(j+1));
                        rms_pho2017_5->SetBinContent(j+1, rms_pho[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_ele2017_5->SetBinContent(j+1, rms_ele[laserResponseBins_2017[bin]][i]->GetBinContent(j+1));
                        rms_pho2018_5->SetBinContent(j+1, rms_pho[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
                        rms_ele2018_5->SetBinContent(j+1, rms_ele[laserResponseBins_2018[bin]][i]->GetBinContent(j+1));
#endif
                }
            }
        }
    }

    std::cout << "[STATUS] writing systematics to text file ... " << std::endl;

    std::ofstream out;
    std::string fileOutPre = DIRECTORY_NAME+"/fnuf_systematics_2016";
    std::string textFileName = fileOutPre+energy+".dat";
    out.open(textFileName.c_str(), std::ofstream::out | std::ofstream::trunc);
    //the first printed line in the text file follows and describes the binning of scheme
    out << "#eta_center eta_low_edge eta_high_edge r9_low_edge r9_high_edge Et laser_response E_gamma_mean Pho_Events Pho_rms E_ele_mean Ele_Events ele_rms systematic uncertainty" << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < numR9bins; j++){
            if(j == 0) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_0->GetBinContent(i+1) << " " << events_pho2016_0->GetBinContent(i+1) << " " << rms_pho2016_0->GetBinContent(i+1) << " " << energy_ele2016_0->GetBinContent(i+1) << " " << events_ele2016_0->GetBinContent(i+1) << " " << rms_ele2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinError(i+1) << std::endl;
            if(j == 1) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_1->GetBinContent(i+1) << " " << events_pho2016_1->GetBinContent(i+1) << " " << rms_pho2016_1->GetBinContent(i+1) << " " << energy_ele2016_1->GetBinContent(i+1) << " " << events_ele2016_1->GetBinContent(i+1) << " " << rms_ele2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinError(i+1) << std::endl;
            if(j == 2) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_2->GetBinContent(i+1) << " " << events_pho2016_2->GetBinContent(i+1) << " " << rms_pho2016_2->GetBinContent(i+1) << " " << energy_ele2016_2->GetBinContent(i+1) << " " << events_ele2016_2->GetBinContent(i+1) << " " << rms_ele2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinError(i+1) << std::endl;
            if(j == 3) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_3->GetBinContent(i+1) << " " << events_pho2016_3->GetBinContent(i+1) << " " << rms_pho2016_3->GetBinContent(i+1) << " " << energy_ele2016_3->GetBinContent(i+1) << " " << events_ele2016_3->GetBinContent(i+1) << " " << rms_ele2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinError(i+1) << std::endl;
            if(j == 4) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_4->GetBinContent(i+1) << " " << events_pho2016_4->GetBinContent(i+1) << " " << rms_pho2016_4->GetBinContent(i+1) << " " << energy_ele2016_4->GetBinContent(i+1) << " " << events_ele2016_4->GetBinContent(i+1) << " " << rms_ele2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinError(i+1) << std::endl;
#ifdef ALT_R9
            if(j == 5) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_5->GetBinContent(i+1) << " " << events_pho2016_5->GetBinContent(i+1) << " " << rms_pho2016_5->GetBinContent(i+1) << " " << energy_ele2016_5->GetBinContent(i+1) << " " << events_ele2016_5->GetBinContent(i+1) << " " << rms_ele2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinError(i+1) << std::endl;
#endif
        }
    }
    for(int i = 5; i < 8; i++){
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[0] << " " << r9Bins[0+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_0->GetBinContent(i+1) << " " << events_pho2016_0->GetBinContent(i+1) << " " << rms_pho2016_0->GetBinContent(i+1) << " " << energy_ele2016_0->GetBinContent(i+1) << " " << events_ele2016_0->GetBinContent(i+1) << " " << rms_ele2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[1] << " " << r9Bins[1+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_1->GetBinContent(i+1) << " " << events_pho2016_1->GetBinContent(i+1) << " " << rms_pho2016_1->GetBinContent(i+1) << " " << energy_ele2016_1->GetBinContent(i+1) << " " << events_ele2016_1->GetBinContent(i+1) << " " << rms_ele2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[2] << " " << r9Bins[2+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_2->GetBinContent(i+1) << " " << events_pho2016_2->GetBinContent(i+1) << " " << rms_pho2016_2->GetBinContent(i+1) << " " << energy_ele2016_2->GetBinContent(i+1) << " " << events_ele2016_2->GetBinContent(i+1) << " " << rms_ele2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[3] << " " << r9Bins[3+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_3->GetBinContent(i+1) << " " << events_pho2016_3->GetBinContent(i+1) << " " << rms_pho2016_3->GetBinContent(i+1) << " " << energy_ele2016_3->GetBinContent(i+1) << " " << events_ele2016_3->GetBinContent(i+1) << " " << rms_ele2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[4] << " " << r9Bins[4+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_4->GetBinContent(i+1) << " " << events_pho2016_4->GetBinContent(i+1) << " " << rms_pho2016_4->GetBinContent(i+1) << " " << energy_ele2016_4->GetBinContent(i+1) << " " << events_ele2016_4->GetBinContent(i+1) << " " << rms_ele2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinError(i+1) << std::endl;
#ifdef ALT_R9
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[5] << " " << r9Bins[5+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_5->GetBinContent(i+1) << " " << events_pho2016_5->GetBinContent(i+1) << " " << rms_pho2016_5->GetBinContent(i+1) << " " << energy_ele2016_5->GetBinContent(i+1) << " " << events_ele2016_5->GetBinContent(i+1) << " " << rms_ele2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinError(i+1) << std::endl;
#endif
    }
    out.close();
    fileOutPre = DIRECTORY_NAME+"/fnuf_systematics_2017";
    textFileName = fileOutPre+energy+".dat";
    out.open(textFileName.c_str(), std::ofstream::out | std::ofstream::trunc);
    out << "#eta_center eta_low_edge eta_high_edge r9_low_edge r9_high_edge Et laser_response E_gamma_mean Pho_Events Pho_rms E_ele_mean Ele_Events ele_rms systematic uncertainty" << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < numR9bins; j++){
            if(j == 0) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_0->GetBinContent(i+1) << " " << events_pho2016_0->GetBinContent(i+1) << " " << rms_pho2016_0->GetBinContent(i+1) << " " << energy_ele2016_0->GetBinContent(i+1) << " " << events_ele2016_0->GetBinContent(i+1) << " " << rms_ele2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinError(i+1) << std::endl;
            if(j == 1) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_1->GetBinContent(i+1) << " " << events_pho2016_1->GetBinContent(i+1) << " " << rms_pho2016_1->GetBinContent(i+1) << " " << energy_ele2016_1->GetBinContent(i+1) << " " << events_ele2016_1->GetBinContent(i+1) << " " << rms_ele2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinError(i+1) << std::endl;
            if(j == 2) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_2->GetBinContent(i+1) << " " << events_pho2016_2->GetBinContent(i+1) << " " << rms_pho2016_2->GetBinContent(i+1) << " " << energy_ele2016_2->GetBinContent(i+1) << " " << events_ele2016_2->GetBinContent(i+1) << " " << rms_ele2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinError(i+1) << std::endl;
            if(j == 3) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_3->GetBinContent(i+1) << " " << events_pho2016_3->GetBinContent(i+1) << " " << rms_pho2016_3->GetBinContent(i+1) << " " << energy_ele2016_3->GetBinContent(i+1) << " " << events_ele2016_3->GetBinContent(i+1) << " " << rms_ele2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinError(i+1) << std::endl;
            if(j == 4) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_4->GetBinContent(i+1) << " " << events_pho2016_4->GetBinContent(i+1) << " " << rms_pho2016_4->GetBinContent(i+1) << " " << energy_ele2016_4->GetBinContent(i+1) << " " << events_ele2016_4->GetBinContent(i+1) << " " << rms_ele2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinError(i+1) << std::endl;
#ifdef ALT_R9
            if(j == 5) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_5->GetBinContent(i+1) << " " << events_pho2016_5->GetBinContent(i+1) << " " << rms_pho2016_5->GetBinContent(i+1) << " " << energy_ele2016_5->GetBinContent(i+1) << " " << events_ele2016_5->GetBinContent(i+1) << " " << rms_ele2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinError(i+1) << std::endl;
#endif
        }
    }
    for(int i = 5; i < 8; i++){
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[0] << " " << r9Bins[0+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_0->GetBinContent(i+1) << " " << events_pho2016_0->GetBinContent(i+1) << " " << rms_pho2016_0->GetBinContent(i+1) << " " << energy_ele2016_0->GetBinContent(i+1) << " " << events_ele2016_0->GetBinContent(i+1) << " " << rms_ele2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[1] << " " << r9Bins[1+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_1->GetBinContent(i+1) << " " << events_pho2016_1->GetBinContent(i+1) << " " << rms_pho2016_1->GetBinContent(i+1) << " " << energy_ele2016_1->GetBinContent(i+1) << " " << events_ele2016_1->GetBinContent(i+1) << " " << rms_ele2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[2] << " " << r9Bins[2+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_2->GetBinContent(i+1) << " " << events_pho2016_2->GetBinContent(i+1) << " " << rms_pho2016_2->GetBinContent(i+1) << " " << energy_ele2016_2->GetBinContent(i+1) << " " << events_ele2016_2->GetBinContent(i+1) << " " << rms_ele2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[3] << " " << r9Bins[3+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_3->GetBinContent(i+1) << " " << events_pho2016_3->GetBinContent(i+1) << " " << rms_pho2016_3->GetBinContent(i+1) << " " << energy_ele2016_3->GetBinContent(i+1) << " " << events_ele2016_3->GetBinContent(i+1) << " " << rms_ele2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[4] << " " << r9Bins[4+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_4->GetBinContent(i+1) << " " << events_pho2016_4->GetBinContent(i+1) << " " << rms_pho2016_4->GetBinContent(i+1) << " " << energy_ele2016_4->GetBinContent(i+1) << " " << events_ele2016_4->GetBinContent(i+1) << " " << rms_ele2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinError(i+1) << std::endl;
#ifdef ALT_R9
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[5] << " " << r9Bins[5+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_5->GetBinContent(i+1) << " " << events_pho2016_5->GetBinContent(i+1) << " " << rms_pho2016_5->GetBinContent(i+1) << " " << energy_ele2016_5->GetBinContent(i+1) << " " << events_ele2016_5->GetBinContent(i+1) << " " << rms_ele2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinError(i+1) << std::endl;
#endif
    }
    out.close();
    fileOutPre = DIRECTORY_NAME+"/fnuf_systematics_2018";
    textFileName = fileOutPre+energy+".dat";
    out.open(textFileName.c_str(), std::ofstream::out | std::ofstream::trunc);
    out << "#eta_center eta_low_edge eta_high_edge r9_low_edge r9_high_edge Et laser_response E_gamma_mean Pho_Events Pho_rms E_ele_mean Ele_Events ele_rms systematic uncertainty" << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < numR9bins; j++){
            if(j == 0) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_0->GetBinContent(i+1) << " " << events_pho2016_0->GetBinContent(i+1) << " " << rms_pho2016_0->GetBinContent(i+1) << " " << energy_ele2016_0->GetBinContent(i+1) << " " << events_ele2016_0->GetBinContent(i+1) << " " << rms_ele2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinError(i+1) << std::endl;
            if(j == 1) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_1->GetBinContent(i+1) << " " << events_pho2016_1->GetBinContent(i+1) << " " << rms_pho2016_1->GetBinContent(i+1) << " " << energy_ele2016_1->GetBinContent(i+1) << " " << events_ele2016_1->GetBinContent(i+1) << " " << rms_ele2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinError(i+1) << std::endl;
            if(j == 2) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_2->GetBinContent(i+1) << " " << events_pho2016_2->GetBinContent(i+1) << " " << rms_pho2016_2->GetBinContent(i+1) << " " << energy_ele2016_2->GetBinContent(i+1) << " " << events_ele2016_2->GetBinContent(i+1) << " " << rms_ele2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinError(i+1) << std::endl;
            if(j == 3) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_3->GetBinContent(i+1) << " " << events_pho2016_3->GetBinContent(i+1) << " " << rms_pho2016_3->GetBinContent(i+1) << " " << energy_ele2016_3->GetBinContent(i+1) << " " << events_ele2016_3->GetBinContent(i+1) << " " << rms_ele2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinError(i+1) << std::endl;
            if(j == 4) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_4->GetBinContent(i+1) << " " << events_pho2016_4->GetBinContent(i+1) << " " << rms_pho2016_4->GetBinContent(i+1) << " " << energy_ele2016_4->GetBinContent(i+1) << " " << events_ele2016_4->GetBinContent(i+1) << " " << rms_ele2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinError(i+1) << std::endl;
#ifdef ALT_R9
            if(j == 5) out << etaBins_center[i] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " " << _fEnergy << " " << laser_response_2016[i] << " "  << energy_pho2016_5->GetBinContent(i+1) << " " << events_pho2016_5->GetBinContent(i+1) << " " << rms_pho2016_5->GetBinContent(i+1) << " " << energy_ele2016_5->GetBinContent(i+1) << " " << events_ele2016_5->GetBinContent(i+1) << " " << rms_ele2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinError(i+1) << std::endl;
#endif
        }
    }
    for(int i = 5; i < 8; i++){
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[0] << " " << r9Bins[0+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_0->GetBinContent(i+1) << " " << events_pho2016_0->GetBinContent(i+1) << " " << rms_pho2016_0->GetBinContent(i+1) << " " << energy_ele2016_0->GetBinContent(i+1) << " " << events_ele2016_0->GetBinContent(i+1) << " " << rms_ele2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinContent(i+1) << " " << systematics2016_0->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[1] << " " << r9Bins[1+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_1->GetBinContent(i+1) << " " << events_pho2016_1->GetBinContent(i+1) << " " << rms_pho2016_1->GetBinContent(i+1) << " " << energy_ele2016_1->GetBinContent(i+1) << " " << events_ele2016_1->GetBinContent(i+1) << " " << rms_ele2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinContent(i+1) << " " << systematics2016_1->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[2] << " " << r9Bins[2+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_2->GetBinContent(i+1) << " " << events_pho2016_2->GetBinContent(i+1) << " " << rms_pho2016_2->GetBinContent(i+1) << " " << energy_ele2016_2->GetBinContent(i+1) << " " << events_ele2016_2->GetBinContent(i+1) << " " << rms_ele2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinContent(i+1) << " " << systematics2016_2->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[3] << " " << r9Bins[3+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_3->GetBinContent(i+1) << " " << events_pho2016_3->GetBinContent(i+1) << " " << rms_pho2016_3->GetBinContent(i+1) << " " << energy_ele2016_3->GetBinContent(i+1) << " " << events_ele2016_3->GetBinContent(i+1) << " " << rms_ele2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinContent(i+1) << " " << systematics2016_3->GetBinError(i+1) << std::endl;
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[4] << " " << r9Bins[4+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_4->GetBinContent(i+1) << " " << events_pho2016_4->GetBinContent(i+1) << " " << rms_pho2016_4->GetBinContent(i+1) << " " << energy_ele2016_4->GetBinContent(i+1) << " " << events_ele2016_4->GetBinContent(i+1) << " " << rms_ele2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinContent(i+1) << " " << systematics2016_4->GetBinError(i+1) << std::endl;
#ifdef ALT_R9
        out << etaBins_center[i-1] << " " << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[5] << " " << r9Bins[5+1] << " " << _fEnergy << " " << laser_response_2016[i-1] << " " << energy_pho2016_5->GetBinContent(i+1) << " " << events_pho2016_5->GetBinContent(i+1) << " " << rms_pho2016_5->GetBinContent(i+1) << " " << energy_ele2016_5->GetBinContent(i+1) << " " << events_ele2016_5->GetBinContent(i+1) << " " << rms_ele2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinContent(i+1) << " " << systematics2016_5->GetBinError(i+1) << std::endl;
#endif
    }
    out.close();

    std::cout << "[STATUS] plotting the systematics for 2016, 2017, and 2018 ... " << std::endl;

    if(fileName.find("030") != std::string::npos) energy = "30 GeV";
    if(fileName.find("045") != std::string::npos) energy = "45 GeV";
    if(fileName.find("060") != std::string::npos) energy = "60 GeV";
    if(fileName.find("120") != std::string::npos) energy = "120 GeV";

#ifndef ALT_R9
    std::string region = "EB";
    mySystematicsPlotter::plot_year(systematics2016_0, systematics2016_1, systematics2016_2, systematics2016_3, systematics2016_4, "2016", energy, region, -999, -999);
    mySystematicsPlotter::plot_year(systematics2017_0, systematics2017_1, systematics2017_2, systematics2017_3, systematics2017_4, "2017", energy, region, -999, -999);
    mySystematicsPlotter::plot_year(systematics2018_0, systematics2018_1, systematics2018_2, systematics2018_3, systematics2018_4, "2018", energy, region, -999, -999);


    region = "EE";
    mySystematicsPlotter::plot_year(systematics2016_0, systematics2016_1, systematics2016_2, systematics2016_3, systematics2016_4, "2016", energy, region, -0.02, -999);
    mySystematicsPlotter::plot_year(systematics2017_0, systematics2017_1, systematics2017_2, systematics2017_3, systematics2017_4, "2017", energy, region, -0.02, -999);
    mySystematicsPlotter::plot_year(systematics2018_0, systematics2018_1, systematics2018_2, systematics2018_3, systematics2018_4, "2018", energy, region, -0.02, -999);

    region = "combined";
    mySystematicsPlotter::plot_year(systematics2016_0, systematics2016_1, systematics2016_2, systematics2016_3, systematics2016_4, "2016", energy, region, -0.10, 1);
    mySystematicsPlotter::plot_year(systematics2017_0, systematics2017_1, systematics2017_2, systematics2017_3, systematics2017_4, "2017", energy, region, -999, -999);
    mySystematicsPlotter::plot_year(systematics2018_0, systematics2018_1, systematics2018_2, systematics2018_3, systematics2018_4, "2018", energy, region, -999, -999);

    if(_flag_crossChecks){
        mySystematicsPlotter::plot_yearEnergy(energy_pho2016_0, energy_pho2016_1, energy_pho2016_2, energy_pho2016_3, energy_pho2016_4, "2016", energy, region, "pho", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergy(energy_pho2017_0, energy_pho2017_1, energy_pho2017_2, energy_pho2017_3, energy_pho2017_4, "2017", energy, region, "pho", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergy(energy_pho2018_0, energy_pho2018_1, energy_pho2018_2, energy_pho2018_3, energy_pho2018_4, "2018", energy, region, "pho", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergy(energy_ele2016_0, energy_ele2016_1, energy_ele2016_2, energy_ele2016_3, energy_ele2016_4, "2016", energy, region, "ele", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergy(energy_ele2017_0, energy_ele2017_1, energy_ele2017_2, energy_ele2017_3, energy_ele2017_4, "2017", energy, region, "ele", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergy(energy_ele2018_0, energy_ele2018_1, energy_ele2018_2, energy_ele2018_3, energy_ele2018_4, "2018", energy, region, "ele", 1.0025, 1.04);
    }
#else
    std::string region = "EB";
    mySystematicsPlotter::plot_yearAltR9(systematics2016_0, systematics2016_1, systematics2016_2, systematics2016_3, systematics2016_4, systematics2016_5, "2016", energy, region, -999, -999);
    mySystematicsPlotter::plot_yearAltR9(systematics2017_0, systematics2017_1, systematics2017_2, systematics2017_3, systematics2017_4, systematics2017_5, "2017", energy, region, -999, -999);
    mySystematicsPlotter::plot_yearAltR9(systematics2018_0, systematics2018_1, systematics2018_2, systematics2018_3, systematics2018_4, systematics2018_5, "2018", energy, region, -999, -999);
    region = "EE";
    mySystematicsPlotter::plot_yearAltR9(systematics2016_0, systematics2016_1, systematics2016_2, systematics2016_3, systematics2016_4, systematics2016_5, "2016", energy, region, -999, -999);
    mySystematicsPlotter::plot_yearAltR9(systematics2017_0, systematics2017_1, systematics2017_2, systematics2017_3, systematics2017_4, systematics2017_5, "2017", energy, region, -999, -999);
    mySystematicsPlotter::plot_yearAltR9(systematics2018_0, systematics2018_1, systematics2018_2, systematics2018_3, systematics2018_4, systematics2018_5, "2018", energy, region, -999, -999);
    region = "combined";
    mySystematicsPlotter::plot_yearAltR9(systematics2016_0, systematics2016_1, systematics2016_2, systematics2016_3, systematics2016_4, systematics2016_5, "2016", energy, region, -999, -999);
    mySystematicsPlotter::plot_yearAltR9(systematics2017_0, systematics2017_1, systematics2017_2, systematics2017_3, systematics2017_4, systematics2017_5, "2017", energy, region, -999, -999);
    mySystematicsPlotter::plot_yearAltR9(systematics2018_0, systematics2018_1, systematics2018_2, systematics2018_3, systematics2018_4, systematics2018_5, "2018", energy, region, -999, -999);
    if(_flag_crossChecks){
        mySystematicsPlotter::plot_yearEnergyAltR9(energy_pho2016_0, energy_pho2016_1, energy_pho2016_2, energy_pho2016_3, energy_pho2016_4, energy_pho2016_5, "2016", energy, region, "pho", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergyAltR9(energy_pho2017_0, energy_pho2017_1, energy_pho2017_2, energy_pho2017_3, energy_pho2017_4, energy_pho2017_5, "2017", energy, region, "pho", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergyAltR9(energy_pho2018_0, energy_pho2018_1, energy_pho2018_2, energy_pho2018_3, energy_pho2018_4, energy_pho2018_5, "2018", energy, region, "pho", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergyAltR9(energy_ele2016_0, energy_ele2016_1, energy_ele2016_2, energy_ele2016_3, energy_ele2016_4, energy_ele2016_5, "2016", energy, region, "ele", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergyAltR9(energy_ele2017_0, energy_ele2017_1, energy_ele2017_2, energy_ele2017_3, energy_ele2017_4, energy_ele2017_5, "2017", energy, region, "ele", 1.0025, 1.04);
        mySystematicsPlotter::plot_yearEnergyAltR9(energy_ele2018_0, energy_ele2018_1, energy_ele2018_2, energy_ele2018_3, energy_ele2018_4, energy_ele2018_5, "2018", energy, region, "ele", 1.0025, 1.04);
    }
#endif
        return;
};


void mySystematicsPlotter::plot_year( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, std::string year, std::string energy, std::string region, double yMin, double yMax){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};
    double xmin = 0;
    double xmax = 2.4999999;
    if( region.find("EB") != std::string::npos ) xmax = 1.4;
    if( region.find("EE") != std::string::npos ) xmin = 1.57;

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

    if(yMax == -999){
        std::vector<double> myMax;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
            }

        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
            }
        }
        yMax = *std::max_element(myMax.begin(), myMax.end());
        yMax *= 1.5;
    }
    if(yMin == -999){
        std::vector<double> myMin;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
            }
        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
            }
        }
        yMin = *std::min_element(myMin.begin(), myMin.end());
        yMin *= 1.3;
    }

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    if(region.compare("EB") == 0 || region.compare("EE") == 0) a_0 = new TCanvas("a0", "", 1200, 1200);
    else a_0 = new TCanvas("a_0", "", 1600, 1200);
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
    std::string temp = year+" Conditions";
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    temp = "E_{T}(#gamma/e): " + energy;
    legend->AddEntry((TObject*)0, temp.c_str(), "");


    hist0->SetYTitle("#bf{#gamma/e Energy Scale Relative Difference (%)}");
    hist0->SetXTitle("#bf{|#eta|}");
    hist0->SetAxisRange(yMin, yMax, "Y");

    if( region.find("EB") != std::string::npos ) hist0->GetXaxis()->SetRangeUser(0., 1.4);
    if( region.find("EE") != std::string::npos ) hist0->GetXaxis()->SetRange(6, 8);
    if( region.find("combined") != std::string::npos){ hist0->GetXaxis()->SetRange(1, 8);}

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
    TLine * line = new TLine(xmin, 0.07, xmax, 0.07);
    line->SetLineWidth(5);
    line->SetLineStyle(9);
    TBox * excludeTransition = new TBox(1.4442, yMin, 1.57, yMax);
    excludeTransition->SetFillStyle(3002);
    excludeTransition->SetFillColor(kBlack);
    excludeTransition->SetLineColor(kBlack);
    if(region.compare("combined") == 0) excludeTransition->Draw("same");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    if(energy.find("30") != std::string::npos) energy = "_030GeV";
    if(energy.find("45") != std::string::npos) energy = "_045GeV";
    if(energy.find("60") != std::string::npos) energy = "_060GeV";
    if(energy.find("120") != std::string::npos) energy = "_120GeV";

    std::string name = DIRECTORY_NAME+"/systematics_"+year+"_"+region+energy+".pdf";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_"+year+"_"+region+energy+".C";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_"+year+"_"+region+energy+".png";
    a_0->SaveAs(name.c_str());
    delete line;
    delete a_0;
    return;
};

void mySystematicsPlotter::plot_yearAltR9( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, TH1F * hist5, std::string year, std::string energy, std::string region, double yMin, double yMax){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};
    double xmin = 0;
    double xmax = 2.4999999;
    if( region.find("EB") != std::string::npos ) xmax = 1.4;
    if( region.find("EE") != std::string::npos ) xmin = 1.57;

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

    if(yMax == -999){
        std::vector<double> myMax;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
                myMax.push_back((double)hist5->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
                myMax.push_back((double)hist5->GetBinContent(i));
            }

        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
                myMax.push_back((double)hist5->GetBinContent(i));
            }
        }
        yMax = *std::max_element(myMax.begin(), myMax.end());
        yMax *= 1.5;
    }
    if(yMin == -999){
        std::vector<double> myMin;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
                myMin.push_back((double)hist5->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
                myMin.push_back((double)hist5->GetBinContent(i));
            }
        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
                myMin.push_back((double)hist5->GetBinContent(i));
            }
        }
        yMin = *std::min_element(myMin.begin(), myMin.end());
        yMin *= 1.3;
    }

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    if(region.compare("EB") == 0 || region.compare("EE") == 0) a_0 = new TCanvas("a0", "", 1200, 1200);
    else a_0 = new TCanvas("a_0", "", 1600, 1200);
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
    std::string temp = year+" Conditions";
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    temp = "E_{T}(#gamma/e): " + energy;
    legend->AddEntry((TObject*)0, temp.c_str(), "");


    hist0->SetYTitle("#bf{#gamma/e Energy Scale Relative Difference (%)}");
    hist0->SetXTitle("#bf{|#eta|}");
    hist0->SetAxisRange(yMin, yMax, "Y");

    if( region.find("EB") != std::string::npos ) hist0->GetXaxis()->SetRangeUser(0., 1.4);
    if( region.find("EE") != std::string::npos ) hist0->GetXaxis()->SetRange(6, 8);
    if( region.find("combined") != std::string::npos){ hist0->GetXaxis()->SetRange(1, 8);}

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
    TLine * line = new TLine(xmin, 0.07, xmax, 0.07);
    line->SetLineWidth(5);
    line->SetLineStyle(9);
    TBox * excludeTransition = new TBox(1.4442, yMin, 1.57, yMax);
    excludeTransition->SetFillStyle(3002);
    excludeTransition->SetFillColor(kBlack);
    excludeTransition->SetLineColor(kBlack);
    if(region.compare("combined") == 0) excludeTransition->Draw("same");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    if(energy.find("30") != std::string::npos) energy = "_030GeV";
    if(energy.find("45") != std::string::npos) energy = "_045GeV";
    if(energy.find("60") != std::string::npos) energy = "_060GeV";
    if(energy.find("120") != std::string::npos) energy = "_120GeV";

    std::string name = DIRECTORY_NAME+"/systematics_"+year+"_"+region+energy+"_altR9.pdf";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_"+year+"_"+region+energy+"_altR9.C";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_"+year+"_"+region+energy+"_altR9.png";
    a_0->SaveAs(name.c_str());
    delete line;
    delete a_0;
    return;
};

void mySystematicsPlotter::plot_yearEnergy( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, std::string year, std::string energy, std::string region, std::string elePho, double yMin, double yMax){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};
    double xmin = 0;
    double xmax = 2.4999999;
    if( region.find("EB") != std::string::npos ) xmax = 1.4;
    if( region.find("EE") != std::string::npos ) xmin = 1.57;

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

    if(yMax == -999){
        std::vector<double> myMax;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
            }

        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
            }
        }
        yMax = *std::max_element(myMax.begin(), myMax.end());
        yMax *= 1.5;
    }
    if(yMin == -999){
        std::vector<double> myMin;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
            }
        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
            }
        }
        yMin = *std::min_element(myMin.begin(), myMin.end());
        yMin *= 1.3;
    }

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    if(region.compare("EB") == 0 || region.compare("EE") == 0) a_0 = new TCanvas("a0", "", 1200, 1200);
    else a_0 = new TCanvas("a_0", "", 1600, 1200);
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
    std::string temp = year+" Conditions";
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    if(elePho.compare("pho") == 0) temp = "E_{T}(#gamma): " + energy;
    else temp = "E_{T}(e): "+energy;
    legend->AddEntry((TObject*)0, temp.c_str(), "");


    std::string elePho_title = "";
    if(elePho.compare("ele") == 0) elePho_title = "#LT E'^{e}_{SC}/E^{e}_{SC} #GT (A.U.)";
    if(elePho.compare("pho") == 0) elePho_title = "#LT E'^{#gamma}_{SC}/E^{#gamma}_{SC} #GT (A.U.)";
    hist0->SetYTitle(elePho_title.c_str());
    hist0->SetXTitle("#bf{|#eta|}");
    hist0->SetAxisRange(yMin, yMax, "Y");

    if( region.find("EB") != std::string::npos ) hist0->GetXaxis()->SetRangeUser(0., 1.4);
    if( region.find("EE") != std::string::npos ) hist0->GetXaxis()->SetRange(6, 8);
    if( region.find("combined") != std::string::npos){ hist0->GetXaxis()->SetRange(1, 8);}

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
    TLine * line = new TLine(xmin, 0.07, xmax, 0.07);
    line->SetLineWidth(5);
    line->SetLineStyle(9);
    TBox * excludeTransition = new TBox(1.4442, yMin, 1.57, yMax);
    excludeTransition->SetFillStyle(3002);
    excludeTransition->SetFillColor(kBlack);
    excludeTransition->SetLineColor(kBlack);
    if(region.compare("combined") == 0) excludeTransition->Draw("same");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    if(energy.find("30") != std::string::npos) energy = "_030GeV";
    if(energy.find("45") != std::string::npos) energy = "_045GeV";
    if(energy.find("60") != std::string::npos) energy = "_060GeV";
    if(energy.find("120") != std::string::npos) energy = "_120GeV";

    std::string name = DIRECTORY_NAME+"/energy_"+elePho+"_"+year+"_"+region+energy+".pdf";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/energy_"+elePho+"_"+year+"_"+region+energy+".C";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/energy_"+elePho+"_"+year+"_"+region+energy+".png";
    a_0->SaveAs(name.c_str());
    delete line;
    delete a_0;
    return;
};

void mySystematicsPlotter::plot_yearEnergyAltR9( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, TH1F * hist5, std::string year, std::string energy, std::string region, std::string elePho, double yMin, double yMax){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};
    double xmin = 0;
    double xmax = 2.4999999;
    if( region.find("EB") != std::string::npos ) xmax = 1.4;
    if( region.find("EE") != std::string::npos ) xmin = 1.57;

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

    if(yMax == -999){
        std::vector<double> myMax;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
                myMax.push_back((double)hist5->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
                myMax.push_back((double)hist5->GetBinContent(i));
            }

        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMax.push_back((double)hist0->GetBinContent(i));
                myMax.push_back((double)hist1->GetBinContent(i));
                myMax.push_back((double)hist2->GetBinContent(i));
                myMax.push_back((double)hist3->GetBinContent(i));
                myMax.push_back((double)hist4->GetBinContent(i));
                myMax.push_back((double)hist5->GetBinContent(i));
            }
        }
        yMax = *std::max_element(myMax.begin(), myMax.end());
        yMax *= 1.5;
    }
    if(yMin == -999){
        std::vector<double> myMin;
        if(region.find("EE") != std::string::npos){
            for(int i = 5; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
                myMin.push_back((double)hist5->GetBinContent(i));
            }
        }
        if(region.find("EB") != std::string::npos){
            for(int i = 0; i < 4; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
                myMin.push_back((double)hist5->GetBinContent(i));
            }
        }
        if(region.find("combined") != std::string::npos){
            for(int i = 0; i < 9; i++){
                myMin.push_back((double)hist0->GetBinContent(i));
                myMin.push_back((double)hist1->GetBinContent(i));
                myMin.push_back((double)hist2->GetBinContent(i));
                myMin.push_back((double)hist3->GetBinContent(i));
                myMin.push_back((double)hist4->GetBinContent(i));
                myMin.push_back((double)hist5->GetBinContent(i));
            }
        }
        yMin = *std::min_element(myMin.begin(), myMin.end());
        yMin *= 1.3;
    }

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    if(region.compare("EB") == 0 || region.compare("EE") == 0) a_0 = new TCanvas("a0", "", 1200, 1200);
    else a_0 = new TCanvas("a_0", "", 1600, 1200);
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
    std::string temp = year+" Conditions";
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    if(elePho.compare("pho") == 0) temp = "E_{T}(#gamma): " + energy;
    else temp = "E_{T}(e): "+energy;
    legend->AddEntry((TObject*)0, temp.c_str(), "");


    std::string elePho_title = "";
    if(elePho.compare("ele") == 0) elePho_title = "#LT E'^{e}_{SC}/E^{e}_{SC} #GT (A.U.)";
    if(elePho.compare("pho") == 0) elePho_title = "#LT E'^{#gamma}_{SC}/E^{#gamma}_{SC} #GT (A.U.)";
    hist0->SetYTitle(elePho_title.c_str());
    hist0->SetXTitle("#bf{|#eta|}");
    hist0->SetAxisRange(yMin, yMax, "Y");

    if( region.find("EB") != std::string::npos ) hist0->GetXaxis()->SetRangeUser(0., 1.4);
    if( region.find("EE") != std::string::npos ) hist0->GetXaxis()->SetRange(6, 8);
    if( region.find("combined") != std::string::npos){ hist0->GetXaxis()->SetRange(1, 8);}

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
    TLine * line = new TLine(xmin, 0.07, xmax, 0.07);
    line->SetLineWidth(5);
    line->SetLineStyle(9);
    TBox * excludeTransition = new TBox(1.4442, yMin, 1.57, yMax);
    excludeTransition->SetFillStyle(3002);
    excludeTransition->SetFillColor(kBlack);
    excludeTransition->SetLineColor(kBlack);
    if(region.compare("combined") == 0) excludeTransition->Draw("same");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    if(energy.find("30") != std::string::npos) energy = "_030GeV";
    if(energy.find("45") != std::string::npos) energy = "_045GeV";
    if(energy.find("60") != std::string::npos) energy = "_060GeV";
    if(energy.find("120") != std::string::npos) energy = "_120GeV";

    std::string name = DIRECTORY_NAME+"/energy_"+elePho+"_"+year+"_"+region+energy+"_altR9.pdf";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/energy_"+elePho+"_"+year+"_"+region+energy+"_altR9.C";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/energy_"+elePho+"_"+year+"_"+region+energy+"_altR9.png";
    a_0->SaveAs(name.c_str());
    delete line;
    delete a_0;
    return;
};

void mySystematicsPlotter::plot_pair( TH1F * hist0, TH1F * hist1, std::string year, std::string energy, std::string region, double yMin, double yMax){

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

    double xmin = 0;
    double xmax = 999;
    for(int i = 1; i <= hist0->GetNbinsX();i++){
        if(hist0->GetBinContent(i) > 0 || hist1->GetBinContent(i) > 0){
            xmin = hist0->GetBinLowEdge(i);
            break;
        }
    }
    for(int i = hist0->GetNbinsX(); i > 0; i--){
        if(hist0->GetBinContent(i) > 0 || hist1->GetBinContent(i) > 0){
            xmax = hist0->GetBinLowEdge(i+1);
            break;
        }
    }
    
    hist0->Scale(1/hist0->Integral());
    hist1->Scale(1/hist1->Integral());

    hist0->Rebin(10,"",0);
    hist1->Rebin(10, "", 0);

    if(yMax == -999){
        std::vector<double> myMax;
        myMax.push_back(hist0->GetMaximum());
        myMax.push_back(hist1->GetMaximum());
        yMax = *std::max_element(myMax.begin(), myMax.end());
        yMax *= 1.5;
    }
    if(yMin == -999){
        std::vector<double> myMin;
        myMin.push_back(hist0->GetMinimum());
        myMin.push_back(hist1->GetMinimum());
        yMin = *std::min_element(myMin.begin(), myMin.end());
        yMin *= 1.3;
    }

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.97, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    TCanvas * a_0;
    a_0 = new TCanvas("a0", "", 1200, 1200);
    a_0->cd();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.125);
    gPad->SetGridy(1);
    gPad->SetGridx(1);

    hist0->SetLineColor(kRed);
    hist0->SetLineWidth(3);
    hist0->SetFillColor(kRed);
    hist0->SetFillStyle(3001);
    hist1->SetLineColor(kBlack);
    hist1->SetLineWidth(3);
    hist1->SetMarkerSize(1.2);
    hist1->SetMarkerStyle(kFullCircle);

    TLegend * legend = new TLegend(0.125,0.7,0.97,0.9);
    legend->SetNColumns(2);
    legend->AddEntry(hist0, "photons", "lf");
    std::string temp = "E_{T}(#gamma/e): " + energy;
    legend->AddEntry(hist1, "electrons", "lp");
    legend->AddEntry((TObject*)0, "2016 conditions", "");


    hist0->SetYTitle("Events");
    hist0->SetXTitle("E'_{SC}/E_{SC}");
    hist0->SetAxisRange(yMin, yMax, "Y");
    hist0->SetAxisRange(xmin, xmax, "X");

    hist0->SetLabelSize(0.035, "Y");
    hist0->SetTitleOffset(1.40, "Y");
    hist0->SetTitleOffset(0.76, "X");
    hist0->SetTitleFont(42, "Y");
    hist0->SetTitleFont(42, "X");
    hist0->SetTitleSize(0.04, "Y");
    hist0->SetTitleSize(0.05, "X");
    hist0->Draw("hist");
    hist1->Draw("SAME P");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    std::string name = DIRECTORY_NAME+"/ratioDistribution_"+hist0->GetName()+"-"+hist1->GetName()+".pdf";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/ratioDistribution_"+hist0->GetName()+"-"+hist1->GetName()+".C";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/ratioDistribution_"+hist0->GetName()+"-"+hist1->GetName()+".png";
    a_0->SaveAs(name.c_str());
    delete a_0;
    return;
};

void mySystematicsPlotter::produce_2016_2017_PionPlots(std::string fileName, bool corrections){

    int numEtaBins = 8;
    double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};

    //begin making the necessary histograms
    std::vector< std::vector<TH1F*> > systematics;
    std::vector< TH1F* > temp_;
    char title [50];
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < numEtaBins; j++){
            sprintf(title, "Systematics_%i_%i", i, j);
            temp_.push_back(new TH1F(title, title, numEtaBins, etaBins));
        }
        systematics.push_back(temp_);
        temp_.clear();
    }

    std::vector< std::vector<TH1F*> > e_0_hists;
    std::vector< std::vector<TH1F*> > g_0_hists;

    const char * fileChar = fileName.c_str();
    TFile* myHistograms = new TFile(fileChar, "READ");

    std::vector<TH1F*> e_0;
    std::vector<TH1F*> g_0;

    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < 100; j++){
            sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
            e_0.push_back((TH1F*)myHistograms->Get(title));

            sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
            g_0.push_back((TH1F*)myHistograms->Get(title));
        }
        e_0_hists.push_back(e_0);
        g_0_hists.push_back(g_0);
        e_0.clear();
        g_0.clear();
    }

    double mean1, mean2;
    double error1, error2;
    double quantile;
    double statError;
    double muNatError;
    double finalVal;
    for(int eta = 0; eta < numEtaBins; eta++){
        if(eta != 4){
            for(int apd = 45; apd < 95; apd++){
                mean1 = e_0_hists[eta][99-apd]->GetMean();
                mean2 = g_0_hists[eta][99-apd]->GetMean();
                error1 = e_0_hists[eta][99-apd]->GetRMS()/sqrt(e_0_hists[eta][99-apd]->GetEntries());
                error2 = g_0_hists[eta][99-apd]->GetRMS()/sqrt(g_0_hists[eta][99-apd]->GetEntries());
                systematics[apd][0]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1));
                systematics[apd][0]->SetBinError(eta + 1, systematics[apd][0]->GetBinContent(eta+1)*sqrt(pow(error1/mean1, 2) + pow(error2/mean2, 2)));

            }
        }
    }

    TH1F * endcap2016_0 = new TH1F("endcap2016_0", "endcap2016_0", 8, etaBins);
    TH1F * endcap2017_0 = new TH1F("endcap2017_0", "endcap2017_0", 8, etaBins);

    endcap2016_0->SetBinContent(6, systematics[93][0]->GetBinContent(6));
    endcap2016_0->SetBinContent(7, systematics[73][0]->GetBinContent(7));
    endcap2016_0->SetBinContent(8, systematics[59][0]->GetBinContent(8));
    endcap2016_0->SetBinError(6, systematics[93][0]->GetBinError(6));
    endcap2016_0->SetBinError(7, systematics[73][0]->GetBinError(7));
    endcap2016_0->SetBinError(8, systematics[59][0]->GetBinError(8));

    endcap2017_0->SetBinContent(6, systematics[79][0]->GetBinContent(6));
    endcap2017_0->SetBinContent(7, systematics[65][0]->GetBinContent(7));
    endcap2017_0->SetBinContent(8, systematics[49][0]->GetBinContent(8));
    endcap2017_0->SetBinError(6, systematics[79][0]->GetBinError(6));
    endcap2017_0->SetBinError(7, systematics[65][0]->GetBinError(7));
    endcap2017_0->SetBinError(8, systematics[49][0]->GetBinError(8));

    std::cout << "[STATUS] writing systematics to text file ... " << std::endl;

    std::ofstream out;
    std::string fileOutPre = DIRECTORY_NAME+"/fnuf_systematics_2016";
    std::string energy = "";
    if(fileName.find("030") != std::string::npos) energy = "_30GeV";
    if(fileName.find("045") != std::string::npos) energy = "_45GeV";
    if(fileName.find("060") != std::string::npos) energy = "_60GeV";
    if(fileName.find("120") != std::string::npos) energy = "_120GeV";

    std::cout << "[STATUS] plotting the systematics for 2016 and 2017 ... " << std::endl;

    if(fileName.find("030") != std::string::npos) energy = "30 GeV";
    if(fileName.find("045") != std::string::npos) energy = "45 GeV";
    if(fileName.find("060") != std::string::npos) energy = "60 GeV";
    if(fileName.find("120") != std::string::npos) energy = "120 GeV";

    std::string region = "EB";
    mySystematicsPlotter::plot_Pion2016(systematics[93][0], energy, region, -0.1, 0.2);
    mySystematicsPlotter::plot_Pion2017(systematics[91][0], energy, region, -0.1, 0.2);
    region = "EE";
    mySystematicsPlotter::plot_Pion2016(endcap2016_0, energy, region, -0.1, 0.7);
    mySystematicsPlotter::plot_Pion2017(endcap2017_0, energy, region, -0.1, 0.7);
    return;
};

void mySystematicsPlotter::plot_Pion2016( TH1F * hist0, std::string energy, std::string region, double yMin, double yMax){
    double xmin = 0;
    double xmax = 2.4999999;
    if( region.find("EB") != std::string::npos ) xmax = 1.4;
    if( region.find("EE") != std::string::npos ) xmin = 1.57;

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.822, 0.91, "#font[42]{13 TeV}");
    TCanvas * a_0 = new TCanvas("a0", "", 900, 900);
    a_0->cd();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.125);
    gPad->SetGridy(1);
    gPad->SetGridx(1);
    hist0->SetLineColor(kBlack);
    hist0->SetLineWidth(3);
    hist0->SetMarkerStyle(kFullCircle);
    hist0->SetMarkerColor(kBlack);
    hist0->SetMarkerSize(3);
    TLegend * legend = new TLegend(0.125,0.7,0.97,0.9);
    legend->AddEntry(hist0, "Pion Systematics", "lp");
    legend->AddEntry((TObject*)0, "2016 Conditions", "");
    std::string temp = "E_{T}(#gamma/e): " + energy;
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    hist0->SetYTitle("#bf{Systematics [%]}");
    hist0->SetXTitle("#bf{|#eta|}");
    hist0->SetAxisRange(yMin, yMax, "Y");
    if( region.find("EB") != std::string::npos ) hist0->GetXaxis()->SetRangeUser(0., 1.4);
    if( region.find("EE") != std::string::npos ) hist0->GetXaxis()->SetRange(6, 8);
    if( region.find("combined") != std::string::npos){ hist0->GetXaxis()->SetRange(0, 8);}
    hist0->SetLabelSize(0.035, "Y");
    hist0->SetTitleOffset(1.10, "Y");
    hist0->SetTitleOffset(0.66, "X");
    hist0->SetTitleFont(42, "Y");
    hist0->SetTitleFont(42, "X");
    hist0->SetTitleSize(0.05, "Y");
    hist0->SetTitleSize(0.06, "X");
    hist0->Draw("E");
    TLine * line = new TLine(xmin, 0.07, xmax, 0.07);
    line->SetLineWidth(5);
    line->SetLineStyle(9);
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    if(energy.find("30") != std::string::npos) energy = "_030GeV";
    if(energy.find("45") != std::string::npos) energy = "_045GeV";
    if(energy.find("60") != std::string::npos) energy = "_060GeV";
    if(energy.find("120") != std::string::npos) energy = "_120GeV";

    std::string name = DIRECTORY_NAME+"/systematics_2016_"+region+energy+".pdf";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_2016_"+region+energy+".C";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_2016_"+region+energy+".png";
    a_0->SaveAs(name.c_str());
    delete line;
    delete a_0;
    return;
};

void mySystematicsPlotter::plot_Pion2017( TH1F * hist0, std::string energy, std::string region, double yMin, double yMax){
    double xmin = 0;
    double xmax = 2.4999999;
    if( region.find("EB") != std::string::npos ) xmax = 1.4;
    if( region.find("EE") != std::string::npos ) xmin = 1.57;

    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaintTextFormat("0.2f");

    TLatex* pave = new TLatex(0.125, 0.91, "#font[42]{#bf{CMS} Simulation #it{Preliminary}}");
    TLatex* lumi_label = new TLatex(0.822, 0.91, "#font[42]{13 TeV}");
    TCanvas * a_0 = new TCanvas("a0", "", 900, 900);
    a_0->cd();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.125);
    gPad->SetGridy(1);
    gPad->SetGridx(1);
    hist0->SetLineColor(kBlack);
    hist0->SetLineWidth(3);
    hist0->SetMarkerStyle(kFullCircle);
    hist0->SetMarkerColor(kBlack);
    hist0->SetMarkerSize(3);
    TLegend * legend = new TLegend(0.125,0.7,0.97,0.9);
    legend->AddEntry(hist0, "Pion Systematics", "lp");
    legend->AddEntry((TObject*)0, "2017 Conditions", "");
    std::string temp = "E_{T}(#gamma/e): "+energy;
    legend->AddEntry((TObject*)0, temp.c_str(), "");
    hist0->SetYTitle("#bf{Systematics [%]}");
    hist0->SetXTitle("#bf{|#eta|}");
    hist0->SetAxisRange(xmin, xmax-0.0001,"X");
    hist0->SetAxisRange(yMin, yMax, "Y");
    hist0->SetLabelSize(0.035, "Y");
    hist0->SetTitleOffset(1.10, "Y");
    hist0->SetTitleOffset(0.66, "X");
    hist0->SetTitleFont(42, "Y");
    hist0->SetTitleFont(42, "X");
    hist0->SetTitleSize(0.05, "Y");
    hist0->SetTitleSize(0.06, "X");
    hist0->Draw("E");
    TLine * line = new TLine(xmin, 0.07, xmax, 0.07);
    line->SetLineWidth(5);
    line->SetLineStyle(9);
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    legend->SetNColumns(2);
    legend->SetTextSize(0.04);
    legend->SetTextFont(62);
    legend->Draw();

    if(energy.find("30") != std::string::npos) energy = "_030GeV";
    if(energy.find("45") != std::string::npos) energy = "_045GeV";
    if(energy.find("60") != std::string::npos) energy = "_060GeV";
    if(energy.find("120") != std::string::npos) energy = "_120GeV";

    std::string name = DIRECTORY_NAME+"/systematics_2017_"+region+energy+".pdf";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_2017_"+region+energy+".C";
    a_0->SaveAs(name.c_str());
    name = DIRECTORY_NAME+"/systematics_2017_"+region+energy+".png";
    a_0->SaveAs(name.c_str());
    delete line;
    delete a_0;
    return;
};

/*
   void mySystematicsPlotter::print_yearHistsToFile(TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, std::string year, std::string energy){

   std::string outFileName = "year_systematics_"+year+".dat"
   ofstream out;


   return;
   }
   */
#endif
