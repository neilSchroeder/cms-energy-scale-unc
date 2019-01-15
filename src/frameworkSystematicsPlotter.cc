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

extern std::string DIRECTORY_NAME;

/// Produce FNUF Histograms only analyzes two files at a time

void mySystematicsPlotter::produce_2016_2017_Plots(std::string fileName){
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00}; 

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
    std::vector< std::vector<TH1F*> > e_1_hists;
    std::vector< std::vector<TH1F*> > e_2_hists;
    std::vector< std::vector<TH1F*> > e_3_hists;
    std::vector< std::vector<TH1F*> > e_4_hists;
    std::vector< std::vector<TH1F*> > g_0_hists;
    std::vector< std::vector<TH1F*> > g_1_hists;
    std::vector< std::vector<TH1F*> > g_2_hists;
    std::vector< std::vector<TH1F*> > g_3_hists;
    std::vector< std::vector<TH1F*> > g_4_hists;

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

    std::string uncertainty_low = "rootFiles/uncertainty_hists_low.root";
    std::string uncertainty_high = "rootFiles/uncertainty_hists_high.root";
    std::string uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown.root";

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

    double mean1, mean2;
    double error1, error2;
    double quantile;
    double statError;
    double muNatError;
    double finalVal;
    for(int eta = 0; eta < numEtaBins; eta++){
        if(eta != 4){
            for(int apd = 45; apd < 95; apd++){
                double correction_norm = std::max( fabs(low_ratio_0->GetBinContent(eta+1, apd+1)), fabs(high_ratio_0->GetBinContent(eta+1, apd+1)));
                double correction_front = fabs(front_ratio_0->GetBinContent(eta+1, apd+1));
                mean1 = e_0_hists[eta][99-apd]->GetMean();
                mean2 = g_0_hists[eta][99-apd]->GetMean();
                error1 = e_0_hists[eta][99-apd]->GetRMS()/sqrt(e_0_hists[eta][99-apd]->GetEntries());
                error2 = g_0_hists[eta][99-apd]->GetRMS()/sqrt(g_0_hists[eta][99-apd]->GetEntries());
                systematics[apd][0]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*(1 + (correction_front/100.) + (correction_norm/100.)));
                systematics[apd][0]->SetBinError(eta + 1, 0.00001);

                correction_norm = std::max( fabs(low_ratio_1->GetBinContent(eta+1, apd+1)), fabs(high_ratio_1->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_1->GetBinContent(eta+1, apd+1));
                mean1 = e_1_hists[eta][99-apd]->GetMean();
                mean2 = g_1_hists[eta][99-apd]->GetMean();
                error1 = e_1_hists[eta][99-apd]->GetRMS()/sqrt(e_1_hists[eta][99-apd]->GetEntries());
                error2 = g_1_hists[eta][99-apd]->GetRMS()/sqrt(g_1_hists[eta][99-apd]->GetEntries());
                systematics[apd][1]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*(1 + (correction_front/100.) + (correction_norm/100.)));
                systematics[apd][1]->SetBinError(eta + 1, 0.00001);

                correction_norm = std::max( fabs(low_ratio_2->GetBinContent(eta+1, apd+1)), fabs(high_ratio_2->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_2->GetBinContent(eta+1, apd+1));
                mean1 = e_2_hists[eta][99-apd]->GetMean();
                mean2 = g_2_hists[eta][99-apd]->GetMean();
                error1 = e_2_hists[eta][99-apd]->GetRMS()/sqrt(e_2_hists[eta][99-apd]->GetEntries());
                error2 = g_2_hists[eta][99-apd]->GetRMS()/sqrt(g_2_hists[eta][99-apd]->GetEntries());
                systematics[apd][2]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*(1 + (correction_front/100.) + (correction_norm/100.)));
                systematics[apd][2]->SetBinError(eta + 1, 0.00001);

                correction_norm = std::max( fabs(low_ratio_3->GetBinContent(eta+1, apd+1)), fabs(high_ratio_3->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_3->GetBinContent(eta+1, apd+1));
                mean1 = e_3_hists[eta][99-apd]->GetMean();
                mean2 = g_3_hists[eta][99-apd]->GetMean();
                error1 = e_3_hists[eta][99-apd]->GetRMS()/sqrt(e_3_hists[eta][99-apd]->GetEntries());
                error2 = g_3_hists[eta][99-apd]->GetRMS()/sqrt(g_3_hists[eta][99-apd]->GetEntries());
                systematics[apd][3]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*(1 + (correction_front/100.) + (correction_norm/100.)));
                systematics[apd][3]->SetBinError(eta + 1, 0.00001);

                correction_norm = std::max( fabs(low_ratio_4->GetBinContent(eta+1, apd+1)), fabs(high_ratio_4->GetBinContent(eta+1, apd+1)));
                correction_front = fabs(front_ratio_4->GetBinContent(eta+1, apd+1));
                mean1 = e_4_hists[eta][99-apd]->GetMean();
                mean2 = g_4_hists[eta][99-apd]->GetMean();
                error1 = e_4_hists[eta][99-apd]->GetRMS()/sqrt(e_4_hists[eta][99-apd]->GetEntries());
                error2 = g_4_hists[eta][99-apd]->GetRMS()/sqrt(g_4_hists[eta][99-apd]->GetEntries());
                systematics[apd][4]->SetBinContent(eta + 1, 100*((mean2/mean1) - 1)*(1 + (correction_front/100.) + (correction_norm/100.)));
                systematics[apd][4]->SetBinError(eta + 1, 0.00001);

            }
        }
    }

    TH1F * endcap2016_0 = new TH1F("endcap2016_0", "endcap2016_0", 8, etaBins);
    TH1F * endcap2016_1 = new TH1F("endcap2016_1", "endcap2016_1", 8, etaBins);
    TH1F * endcap2016_2 = new TH1F("endcap2016_2", "endcap2016_2", 8, etaBins);
    TH1F * endcap2016_3 = new TH1F("endcap2016_3", "endcap2016_3", 8, etaBins);
    TH1F * endcap2016_4 = new TH1F("endcap2016_4", "endcap2016_4", 8, etaBins);

    TH1F * endcap2017_0 = new TH1F("endcap2017_0", "endcap2017_0", 8, etaBins);
    TH1F * endcap2017_1 = new TH1F("endcap2017_1", "endcap2017_1", 8, etaBins);
    TH1F * endcap2017_2 = new TH1F("endcap2017_2", "endcap2017_2", 8, etaBins);
    TH1F * endcap2017_3 = new TH1F("endcap2017_3", "endcap2017_3", 8, etaBins);
    TH1F * endcap2017_4 = new TH1F("endcap2017_4", "endcap2017_4", 8, etaBins);

    endcap2016_0->SetBinContent(6, systematics[93][0]->GetBinContent(6));
    endcap2016_0->SetBinContent(7, systematics[73][0]->GetBinContent(7));
    endcap2016_0->SetBinContent(8, systematics[59][0]->GetBinContent(8));
    endcap2016_1->SetBinContent(6, systematics[93][1]->GetBinContent(6));
    endcap2016_1->SetBinContent(7, systematics[73][1]->GetBinContent(7));
    endcap2016_1->SetBinContent(8, systematics[59][1]->GetBinContent(8));
    endcap2016_2->SetBinContent(6, systematics[93][2]->GetBinContent(6));
    endcap2016_2->SetBinContent(7, systematics[73][2]->GetBinContent(7));
    endcap2016_2->SetBinContent(8, systematics[59][2]->GetBinContent(8));
    endcap2016_3->SetBinContent(6, systematics[93][3]->GetBinContent(6));
    endcap2016_3->SetBinContent(7, systematics[73][3]->GetBinContent(7));
    endcap2016_3->SetBinContent(8, systematics[59][3]->GetBinContent(8));
    endcap2016_4->SetBinContent(6, systematics[93][4]->GetBinContent(6));
    endcap2016_4->SetBinContent(7, systematics[73][4]->GetBinContent(7));
    endcap2016_4->SetBinContent(8, systematics[59][4]->GetBinContent(8));
    endcap2016_0->SetBinError(6, systematics[93][0]->GetBinError(6));
    endcap2016_0->SetBinError(7, systematics[73][0]->GetBinError(7));
    endcap2016_0->SetBinError(8, systematics[59][0]->GetBinError(8));
    endcap2016_1->SetBinError(6, systematics[93][1]->GetBinError(6));
    endcap2016_1->SetBinError(7, systematics[73][1]->GetBinError(7));
    endcap2016_1->SetBinError(8, systematics[59][1]->GetBinError(8));
    endcap2016_2->SetBinError(6, systematics[93][2]->GetBinError(6));
    endcap2016_2->SetBinError(7, systematics[73][2]->GetBinError(7));
    endcap2016_2->SetBinError(8, systematics[59][2]->GetBinError(8));
    endcap2016_3->SetBinError(6, systematics[93][3]->GetBinError(6));
    endcap2016_3->SetBinError(7, systematics[73][3]->GetBinError(7));
    endcap2016_3->SetBinError(8, systematics[59][3]->GetBinError(8));
    endcap2016_4->SetBinError(6, systematics[93][4]->GetBinError(6));
    endcap2016_4->SetBinError(7, systematics[73][4]->GetBinError(7));
    endcap2016_4->SetBinError(8, systematics[59][4]->GetBinError(8));

    endcap2017_0->SetBinContent(6, systematics[79][0]->GetBinContent(6));
    endcap2017_0->SetBinContent(7, systematics[65][0]->GetBinContent(7));
    endcap2017_0->SetBinContent(8, systematics[49][0]->GetBinContent(8));
    endcap2017_1->SetBinContent(6, systematics[79][1]->GetBinContent(6));
    endcap2017_1->SetBinContent(7, systematics[65][1]->GetBinContent(7));
    endcap2017_1->SetBinContent(8, systematics[49][1]->GetBinContent(8));
    endcap2017_2->SetBinContent(6, systematics[79][2]->GetBinContent(6));
    endcap2017_2->SetBinContent(7, systematics[65][2]->GetBinContent(7));
    endcap2017_2->SetBinContent(8, systematics[49][2]->GetBinContent(8));
    endcap2017_3->SetBinContent(6, systematics[79][3]->GetBinContent(6));
    endcap2017_3->SetBinContent(7, systematics[65][3]->GetBinContent(7));
    endcap2017_3->SetBinContent(8, systematics[49][3]->GetBinContent(8));
    endcap2017_4->SetBinContent(6, systematics[79][4]->GetBinContent(6));
    endcap2017_4->SetBinContent(7, systematics[65][4]->GetBinContent(7));
    endcap2017_4->SetBinContent(8, systematics[49][4]->GetBinContent(8));
    endcap2017_0->SetBinError(6, systematics[79][0]->GetBinError(6));
    endcap2017_0->SetBinError(7, systematics[65][0]->GetBinError(7));
    endcap2017_0->SetBinError(8, systematics[49][0]->GetBinError(8));
    endcap2017_1->SetBinError(6, systematics[79][1]->GetBinError(6));
    endcap2017_1->SetBinError(7, systematics[65][1]->GetBinError(7));
    endcap2017_1->SetBinError(8, systematics[49][1]->GetBinError(8));
    endcap2017_2->SetBinError(6, systematics[79][2]->GetBinError(6));
    endcap2017_2->SetBinError(7, systematics[65][2]->GetBinError(7));
    endcap2017_2->SetBinError(8, systematics[49][2]->GetBinError(8));
    endcap2017_3->SetBinError(6, systematics[79][3]->GetBinError(6));
    endcap2017_3->SetBinError(7, systematics[65][3]->GetBinError(7));
    endcap2017_3->SetBinError(8, systematics[49][3]->GetBinError(8));
    endcap2017_4->SetBinError(6, systematics[79][4]->GetBinError(6));
    endcap2017_4->SetBinError(7, systematics[65][4]->GetBinError(7));
    endcap2017_4->SetBinError(8, systematics[49][4]->GetBinError(8));

    std::cout << "writing systematics to text file ... " << std::endl;

    std::ofstream out;
    std::string fileOutPre = DIRECTORY_NAME+"/fnuf_systematics_2016";
    std::string energy = "";
    if(fileName.find("030") != std::string::npos) energy = "_30GeV";
    if(fileName.find("045") != std::string::npos) energy = "_45GeV";
    if(fileName.find("060") != std::string::npos) energy = "_60GeV";
    if(fileName.find("120") != std::string::npos) energy = "_120GeV";
    std::string textFileName = fileOutPre+energy+".txt";
    out.open(textFileName.c_str(), std::ofstream::out | std::ofstream::trunc);
    //the first printed line in the text file follows and describes the binning of scheme
    out << "eta_low_edge eta_high_edge r9_low_edge r9_high_edge laser_response systematic statUnc" << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < numR9bins; j++){
            out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " 0.94 " << systematics[93][j]->GetBinContent(i+1) << std::endl;
        }
    }
    for(int i = 5; i < 8; i++){
        std::string laserResponse = "";
        if( i == 5 ) laserResponse = 0.94;
        if( i == 6 ) laserResponse = 0.74;
        if( i == 7 ) laserResponse = 0.60;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[0] << " " << r9Bins[0+1] << " " << laserResponse << " " << endcap2016_0->GetBinContent(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[1] << " " << r9Bins[1+1] << " " << laserResponse << " " << endcap2016_1->GetBinContent(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[2] << " " << r9Bins[2+1] << " " << laserResponse << " " << endcap2016_2->GetBinContent(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[3] << " " << r9Bins[3+1] << " " << laserResponse << " " << endcap2016_3->GetBinContent(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[4] << " " << r9Bins[4+1] << " " << laserResponse << " " << endcap2016_4->GetBinContent(i+1) << std::endl;
    }
    out.close();
    fileOutPre = DIRECTORY_NAME+"/fnuf_systematics_2017";
    textFileName = fileOutPre+energy+".txt";
    out.open(textFileName.c_str(), std::ofstream::out | std::ofstream::trunc);
    out << "eta_low_edge eta_high_edge r9_low_edge r9_high_edge systematic" << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < numR9bins; j++){
            out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[j] << " " << r9Bins[j+1] << " 0.92 " << systematics[91][j]->GetBinContent(i+1) << " " << systematics[91][j]->GetBinContent(i+1) << std::endl;
        }
    }
    for(int i = 5; i < 8; i++){
        std::string laserResponse = "";
        if( i == 5) laserResponse = 0.80;
        if( i == 6) laserResponse = 0.66;
        if( i == 7) laserResponse = 0.50;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[0] << " " << r9Bins[0+1] << " " << endcap2017_0->GetBinContent(i+1) << " " << endcap2017_0->GetBinError(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[1] << " " << r9Bins[1+1] << " " << endcap2017_1->GetBinContent(i+1) << " " << endcap2017_1->GetBinError(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[2] << " " << r9Bins[2+1] << " " << endcap2017_2->GetBinContent(i+1) << " " << endcap2017_2->GetBinError(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[3] << " " << r9Bins[3+1] << " " << endcap2017_3->GetBinContent(i+1) << " " << endcap2017_3->GetBinError(i+1) << std::endl;
        out << etaBins[i] << " " << etaBins[i+1] << " " << r9Bins[4] << " " << r9Bins[4+1] << " " << endcap2017_4->GetBinContent(i+1) << " " << endcap2017_4->GetBinError(i+1) << std::endl;
    }
    out.close();

    std::cout << "plotting the systematics for 2016 and 2017 ... " << std::endl;

    if(fileName.find("030") != std::string::npos) energy = "30 GeV";
    if(fileName.find("045") != std::string::npos) energy = "45 GeV";
    if(fileName.find("060") != std::string::npos) energy = "60 GeV";
    if(fileName.find("120") != std::string::npos) energy = "120 GeV";

    std::string region = "EB";
    mySystematicsPlotter::plot_2016(systematics[93][0], systematics[93][1], systematics[93][2], systematics[93][3], systematics[93][4], energy, region, -0.05, 0.25);
    mySystematicsPlotter::plot_2017(systematics[91][0], systematics[91][1], systematics[91][2], systematics[91][3], systematics[91][4], energy, region, -0.10, 0.35);
    region = "EE";
    mySystematicsPlotter::plot_2016(endcap2016_0, endcap2016_1, endcap2016_2, endcap2016_3, endcap2016_4, energy, region, -0.05, 0.6 );
    mySystematicsPlotter::plot_2017(endcap2017_0, endcap2017_1, endcap2017_2, endcap2017_3, endcap2017_4, energy, region, -0.05, 0.9);
    return;
};

void mySystematicsPlotter::plot_2016( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, std::string energy, std::string region, double yMin, double yMax){
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
	legend->AddEntry((TObject*)0, "2016 Conditions", "");
    std::string temp = "#gamma/e gun: " + energy;
    std::cout << temp << " " << energy << std::endl;
	legend->AddEntry((TObject*)0, temp.c_str(), "");
	hist0->SetYTitle("#bf{Systematics [%]}");
	hist0->SetXTitle("#bf{|#eta|}");
	hist0->SetAxisRange(yMin, yMax, "Y");
	if( region.find("EB") != std::string::npos ) hist0->GetXaxis()->SetRangeUser(0., 1.4);
	if( region.find("EE") != std::string::npos ) hist0->GetXaxis()->SetRange(6, 8);
	hist0->SetLabelSize(0.035, "Y");
	hist0->SetTitleOffset(1.10, "Y");
	hist0->SetTitleOffset(0.66, "X");
	hist0->SetTitleFont(42, "Y");
	hist0->SetTitleFont(42, "X");
	hist0->SetTitleSize(0.05, "Y");
	hist0->SetTitleSize(0.06, "X");
	hist0->GetXaxis()->CenterTitle();
	hist0->Draw("E");
	hist1->Draw("SAME E");
	hist2->Draw("SAME E");
	hist3->Draw("SAME E");
	hist4->Draw("SAME E");
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

void mySystematicsPlotter::plot_2017( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, std::string energy, std::string region, double yMin, double yMax){
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
	hist2->SetLineWidth(3);hist2->SetMarkerStyle(kFullTriangleUp);
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
	legend->AddEntry((TObject*)0, "2017 Conditions", "");
    std::string temp = "#gamma/e gun: "+energy;
	legend->AddEntry((TObject*)0, temp.c_str(), "");
	hist0->SetYTitle("#bf{Systematics [%]}");
	hist0->SetXTitle("#bf{|#eta|}");
	hist0->SetAxisRange(xmin, xmax-0.000001 ,"X");
	hist0->SetAxisRange(yMin, yMax, "Y");
	hist0->SetLabelSize(0.035, "Y");
	hist0->SetTitleOffset(1.10, "Y");
	hist0->SetTitleOffset(0.66, "X");
	hist0->SetTitleFont(42, "Y");
	hist0->SetTitleFont(42, "X");
	hist0->SetTitleSize(0.05, "Y");
	hist0->SetTitleSize(0.06, "X");
	hist0->GetXaxis()->CenterTitle();
	hist0->Draw("E");
	hist1->Draw("SAME E");
	hist2->Draw("SAME E");
	hist3->Draw("SAME E");
	hist4->Draw("SAME E");
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

#endif
