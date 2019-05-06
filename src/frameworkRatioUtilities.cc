#ifndef utilities
#define utilities

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
#include "frameworkUtilities.h"

//#define ETA_VETO

std::string DIRECTORY_NAME = "photonSystematics";

/// Produce FNUF Histograms only analyzes two files at a time
std::string myUtilities::produce_FNUF_Histograms( char ** cLineArgs, int i ){
    std::string ret = "";

    std::cout << "File to analyze: " << cLineArgs[i] << " and " << cLineArgs[i+1] << std::endl;

	//declare some constants
	int numR9bins = 5;
	double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00}; 

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};

    int apdBins = 100;
    double apdMin = 0;
    double apdMax = 1;

	//make the histograms
	//note: plotting using this code has been temporarily disabled

	//declare std::vectors for an iterative TH1 creation method

	std::vector< std::vector<TH1F*> > Histogramse_0;
	std::vector< std::vector<TH1F*> > Histogramsg_0;
	std::vector< std::vector<TH1F*> > Histogramse_1;
	std::vector< std::vector<TH1F*> > Histogramsg_1;
	std::vector< std::vector<TH1F*> > Histogramse_2;
	std::vector< std::vector<TH1F*> > Histogramsg_2;
	std::vector< std::vector<TH1F*> > Histogramse_3;
	std::vector< std::vector<TH1F*> > Histogramsg_3;
	std::vector< std::vector<TH1F*> > Histogramse_4;
	std::vector< std::vector<TH1F*> > Histogramsg_4;

	char titleLow [50];
	char titleHigh [50];
	char tagLow [50];
	char tagHigh [50];
	std::vector<TH1F*> Histse_0;
	std::vector<TH1F*> Histsg_0;
	std::vector<TH1F*> Histse_1;
	std::vector<TH1F*> Histsg_1;
	std::vector<TH1F*> Histse_2;
	std::vector<TH1F*> Histsg_2;
	std::vector<TH1F*> Histse_3;
	std::vector<TH1F*> Histsg_3;
	std::vector<TH1F*> Histse_4;
	std::vector<TH1F*> Histsg_4;

	int count = 1;
	int bins = 125600;
	//create the necessary histograms
	for(int iii = 0; iii < numEtaBins; iii++){
		double etaMax = ((double)iii+1)*(2.5/(double)numEtaBins);
		double etaMin = (double)iii * 2.5/(double)numEtaBins;
		double apd = 1;
		for(int jjj = 0; jjj < 100; jjj++){
			if( jjj > 0 ) apd -= 0.01;
			sprintf( titleLow, "e R9_0, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( titleHigh, "g R9_0, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( tagLow, "e_0_%i_%i_%i", iii, iii+1, jjj);
			sprintf( tagHigh, "g_0_%i_%i_%i", iii, iii+1, jjj);
			TH1F * eHist_0 = new TH1F( tagLow, titleLow, bins, 0, 5);
			TH1F * gHist_0 = new TH1F( tagHigh, titleHigh, bins, 0, 5);
			sprintf( titleLow, "e R9_1, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( titleHigh, "g R9_1, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( tagLow, "e_1_%i_%i_%i", iii, iii+1, jjj);
			sprintf( tagHigh, "g_1_%i_%i_%i", iii, iii+1, jjj);
			TH1F * eHist_1 = new TH1F( tagLow, titleLow, bins, 0, 5);
			TH1F * gHist_1 = new TH1F( tagHigh, titleHigh, bins, 0, 5);
			sprintf( titleLow, "e R9_2, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( titleHigh, "g R9_2, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( tagLow, "e_2_%i_%i_%i", iii, iii+1, jjj);
			sprintf( tagHigh, "g_2_%i_%i_%i", iii, iii+1, jjj);
			TH1F * eHist_2 = new TH1F( tagLow, titleLow, bins, 0, 5);
			TH1F * gHist_2 = new TH1F( tagHigh, titleHigh, bins, 0, 5);
			sprintf( titleLow, "e R9_3, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( titleHigh, "g R9_3, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( tagLow, "e_3_%i_%i_%i", iii, iii+1, jjj);
			sprintf( tagHigh, "g_3_%i_%i_%i", iii, iii+1, jjj);
			TH1F * eHist_3 = new TH1F( tagLow, titleLow, bins, 0, 5);
			TH1F * gHist_3 = new TH1F( tagHigh, titleHigh, bins, 0, 5);
			sprintf( titleLow, "e R9_4, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( titleHigh, "g R9_4, %lf < |#eta| < %lf, APD/PN = %lf", etaMin, etaMax, apd);
			sprintf( tagLow, "e_4_%i_%i_%i", iii, iii+1, jjj);
			sprintf( tagHigh, "g_4_%i_%i_%i", iii, iii+1, jjj);
			TH1F * eHist_4 = new TH1F( tagLow, titleLow, bins, 0, 5);
			TH1F * gHist_4 = new TH1F( tagHigh, titleHigh, bins, 0, 5);
			Histse_0.push_back(eHist_0);
			Histsg_0.push_back(gHist_0);
            Histse_1.push_back(eHist_1);
            Histsg_1.push_back(gHist_1);
            Histse_2.push_back(eHist_2);
            Histsg_2.push_back(gHist_2);
            Histse_3.push_back(eHist_3);
            Histsg_3.push_back(gHist_3);
            Histse_4.push_back(eHist_4);
            Histsg_4.push_back(gHist_4);
			if(iii != 4) count++;
		}//end for jjj
		Histogramse_0.push_back(Histse_0);
		Histogramsg_0.push_back(Histsg_0);
		Histogramse_1.push_back(Histse_1);
		Histogramsg_1.push_back(Histsg_1);
		Histogramse_2.push_back(Histse_2);
		Histogramsg_2.push_back(Histsg_2);
		Histogramse_3.push_back(Histse_3);
		Histogramsg_3.push_back(Histsg_3);
		Histogramse_4.push_back(Histse_4);
		Histogramsg_4.push_back(Histsg_4);
		Histse_0.clear();
		Histsg_0.clear();
        Histse_1.clear();
        Histsg_1.clear();
        Histse_2.clear();
        Histsg_2.clear();
        Histse_3.clear();
        Histsg_3.clear();
        Histse_4.clear();
        Histsg_4.clear();
	}//end for iii

	//tree members
	float R9 [2];
	float full5x5_R9 [2];
	float energyR [2];
	float eta [2];
	float etaSC [2];
	float phi [2];
	float energyG [2];
	float etaS [2];
	float phiS [2];
	float rawSuperClusterEnergy [2];
	float def_nomiRecHitSum [2];
	double apd_lce_RecHitSums1 [100];
	double apd_lce_RecHitSums2 [100];
	double linearEnergies1 [8];
	double linearEnergies2 [8];
	float dr [2];
	float seedCrystalRatio [2];
	int showerMaxBin [2];
	float supClustCrystals [2];
	Long64_t run, event, lum;

	//File stuffs
    std::ifstream in;
	const char * thisFile = cLineArgs[i];
	in.open( thisFile );

    std::string rootFile;
	bool noVeto = true;
	// by my own convention this loop will be the electron loop
    while( in >> rootFile){
        TFile * myFile = TFile::Open(rootFile.c_str());
        if(!(myFile->IsZombie())){
            TIter next(myFile->GetListOfKeys());
            TKey *key;
            while( (key = (TKey*)next()) ){
                std::string ntuples = "ntuples";
                if(rootFile.find("High") != std::string::npos) ntuples = "ntuplesHigh";
                if(rootFile.find("Low") != std::string::npos) ntuples = "ntuplesLow";
                if( ntuples.compare(key->GetName()) == 0 ){
                    std::string folder = "ntuples/data";
                    if(rootFile.find("High") != std::string::npos) folder = "ntuplesHigh/data";
                    if(rootFile.find("Low") != std::string::npos) folder = "ntuplesLow/data";
                    TTree * thisTTree = (TTree*)myFile->Get(folder.c_str());
                    thisTTree->SetBranchAddress("RECO_Energy", energyR);
                    thisTTree->SetBranchAddress("Super_Cluster_Raw_Energy", rawSuperClusterEnergy);
                    thisTTree->SetBranchAddress("Rechit_Energy_Sum_1", def_nomiRecHitSum);
                    thisTTree->SetBranchAddress("apd_lce_RecHitSums1", apd_lce_RecHitSums1);
                    thisTTree->SetBranchAddress("apd_lce_RecHitSums2", apd_lce_RecHitSums2);
                    thisTTree->SetBranchAddress("Gen_Energy", energyG);
                    thisTTree->SetBranchAddress("R9", R9);
                    thisTTree->SetBranchAddress("Full_5x5_R9", full5x5_R9);
                    thisTTree->SetBranchAddress("Reco_Eta", eta);
                    thisTTree->SetBranchAddress("Super_Cluster_Eta", etaSC);
                    thisTTree->SetBranchAddress("Gen_Eta", etaS);
                    thisTTree->SetBranchAddress("Reco_Phi", phi);
                    thisTTree->SetBranchAddress("Gen_Phi", phiS);
                    thisTTree->SetBranchAddress("dR", dr);
                    //thisTTree->SetBranchAddress("Super_Cluster_Crystals", supClustCrystals);
                    //thisTTree->SetBranchAddress("Shower_Max_Bin", showerMaxBin);
                    thisTTree->SetBranchAddress("run", &run);
                    thisTTree->SetBranchAddress("event", &event);
                    thisTTree->SetBranchAddress("lum", &lum);

                    /////////////////////////////////////////////////////////////////////////////////////////////
                    //this part of the code fills the histograms
                    for(Long64_t treeIndex = 0; treeIndex < thisTTree->GetEntries(); treeIndex++){
                        thisTTree->GetEntry(treeIndex);
                        if( dr[0] != 999 && dr[1] != 999){
                            //determine which eta bin the first electron falls into
                            int etaIndex1 = fabs(etaSC[0])/(2.5/(double)numEtaBins);
                            int etaIndex2 = fabs(etaSC[1])/(2.5/(double)numEtaBins);;
#ifdef Bins9
                            for(int i = 0; i < numEtaBins - 1 ; i++){
                                if( fabs(etaSC[0]) > etaBins[i] && fabs(etaSC[0]) < etaBins[i+1]){
                                    etaIndex1 = i;
                                }
                                if( fabs(etaSC[1]) > etaBins[i] && fabs(etaSC[1]) < etaBins[i+1]){
                                    etaIndex2 = i;
                                }
                            }
#endif
#ifdef Bins12
                            if(etaIndex1 == 7){
                                if(fabs(etaSC[0]) < 1.442) etaIndex1 = 6;
                                if(fabs(etaSC[0]) > 1.5) etaIndex1 = 8;
                            }
                            //electron 2 eta bin
                            if(etaIndex2 == 7){
                                if(fabs(etaSC[1]) < 1.442) etaIndex2 = 6;
                                if(fabs(etaSC[1]) > 1.5) etaIndex2 = 8;
                            }
#endif
#ifdef Bins24
                            if(etaIndex1 == 14){
                                if(fabs(etaSC[0]) < 1.442) etaIndex1 = 13;
                                if(fabs(etaSC[0]) > 1.5) etaIndex1 = 15;
                            }
                            //electron 2 eta bin
                            if(etaIndex2 == 14){
                                if(fabs(etaSC[1]) < 1.442) etaIndex2 = 12;
                                if(fabs(etaSC[1]) > 1.5) etaIndex2 = 14;
                            }
#endif
                            //the following if statement is just a catch for particles
                            //     with an eta more than 2.5


                            if( etaIndex1 < numEtaBins && etaIndex2 < numEtaBins){
                                noVeto = true;
#ifdef ETA_VETO
                                if(fabs(etaSC[0]) < 0.024) noVeto = false;
                                if(fabs(etaSC[0]) > 0.432 && fabs(etaSC[0]) < 0.456) noVeto = false;
                                if(fabs(etaSC[0]) > 0.768 && fabs(etaSC[0]) < 0.816) noVeto = false;
                                if(fabs(etaSC[0]) > 1.128 && fabs(etaSC[0]) < 1.152) noVeto = false;
#endif
#ifdef ETA_VETO
                                noVeto = true;
                                if(fabs(etaSC[0]) < 0.024 ) noVeto = false;
                                if(fabs(etaSC[0]) > 0.432 && fabs(etaSC[0]) < 0.456) noVeto = false;
                                if(fabs(etaSC[0]) > 0.768 && fabs(etaSC[0]) < 0.816) noVeto = false;
                                if(fabs(etaSC[0]) > 1.128 && fabs(etaSC[0]) < 1.152) noVeto = false;
#endif
                                if(noVeto){
                                //make 2D plots for R9 bins:::
                                if(full5x5_R9[0] > r9Bins[0] && full5x5_R9[0] < r9Bins[1]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_0[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[0] > r9Bins[1] && full5x5_R9[0] < r9Bins[2]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_1[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[0] > r9Bins[2] && full5x5_R9[0] < r9Bins[3]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_2[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[0] > r9Bins[3] && full5x5_R9[0] < r9Bins[4]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_3[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[0] > r9Bins[4] && full5x5_R9[0] < r9Bins[5]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_4[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                    }//end for apd bins
                                }
                                }
#ifdef ETA_VETO
                                noVeto = true;
                                if(fabs(etaSC[1]) < 0.024 ) noVeto = false;
                                if(fabs(etaSC[1]) > 0.432 && fabs(etaSC[1]) < 0.456) noVeto = false;
                                if(fabs(etaSC[1]) > 0.768 && fabs(etaSC[1]) < 0.816) noVeto = false;
                                if(fabs(etaSC[1]) > 1.128 && fabs(etaSC[1]) < 1.152) noVeto = false;
#endif
                                if(noVeto){
                                if(full5x5_R9[1] > r9Bins[0] && full5x5_R9[1] < r9Bins[1]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_0[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[1] > r9Bins[1] && full5x5_R9[1] < r9Bins[2]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_1[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[1] > r9Bins[2] && full5x5_R9[1] < r9Bins[3]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_2[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[1] > r9Bins[3] && full5x5_R9[1] < r9Bins[4]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_3[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                    }//end for apd bins
                                }
                                if(full5x5_R9[1] > r9Bins[4] && full5x5_R9[1] < r9Bins[5]){
                                    for(int i = 0; i < 100; i++){
                                        Histogramse_4[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                    }//end for apd bins
                                }
                                }
#endif
                            }
                        }//end if both particles are reconstructed
                    }//end for tree index
                }// end if found key named ntuples
                else{
                    std::cout << "Did not find directory 'ntuples' for file " << rootFile << std::endl;
                    std::cout << "... continuing without this file." << std::endl;
                }
            }//end while keys
        }//end if not zombie
        else{
            std::cout << "The file " << thisFile << " did not open properly" << std::endl;
            std::cout << "... continuing without this file." << std::endl;
        }
        myFile->Close();
    }//end while files in
	
	in.close();
	thisFile = cLineArgs[i+1];
	in.open( thisFile );

	// this loop will be the photon loop
    while( in >> rootFile){
        TFile * myFile = TFile::Open(rootFile.c_str());
        if(!(myFile->IsZombie())){
            TIter next(myFile->GetListOfKeys());
            TKey *key;
            while( (key = (TKey*)next()) ){
                std::string ntuples = "ntuples";
                if(rootFile.find("High") != std::string::npos) ntuples = "ntuplesHigh";
                if(rootFile.find("Low") != std::string::npos) ntuples = "ntuplesLow";
                if( ntuples.compare(key->GetName()) == 0 ){
                    std::string folder = "ntuples/data";
                    if(ntuples.find("High") != std::string::npos) folder = "ntuplesHigh/data";
                    if(ntuples.find("Low") != std::string::npos) folder = "ntuplesLow/data";
                    TTree * thisTTree = (TTree*)myFile->Get(folder.c_str());
                    thisTTree->SetBranchAddress("RECO_Energy", energyR);
                    thisTTree->SetBranchAddress("Super_Cluster_Raw_Energy", rawSuperClusterEnergy);
                    thisTTree->SetBranchAddress("Rechit_Energy_Sum_1", def_nomiRecHitSum);
                    thisTTree->SetBranchAddress("apd_lce_RecHitSums1", apd_lce_RecHitSums1);
                    thisTTree->SetBranchAddress("apd_lce_RecHitSums2", apd_lce_RecHitSums2);
                    thisTTree->SetBranchAddress("Gen_Energy", energyG);
                    thisTTree->SetBranchAddress("R9", R9);
                    thisTTree->SetBranchAddress("Full_5x5_R9", full5x5_R9);
                    thisTTree->SetBranchAddress("Reco_Eta", eta);
                    thisTTree->SetBranchAddress("Super_Cluster_Eta", etaSC);
                    thisTTree->SetBranchAddress("Gen_Eta", etaS);
                    thisTTree->SetBranchAddress("Reco_Phi", phi);
                    thisTTree->SetBranchAddress("Gen_Phi", phiS);
                    thisTTree->SetBranchAddress("dR", dr);
                    //thisTTree->SetBranchAddress("Super_Cluster_Crystals", supClustCrystals);
                    //thisTTree->SetBranchAddress("Shower_Max_Bin", showerMaxBin);
                    thisTTree->SetBranchAddress("run", &run);
                    thisTTree->SetBranchAddress("event", &event);
                    thisTTree->SetBranchAddress("lum", &lum);

                    for(Long64_t treeIndex = 0; treeIndex < thisTTree->GetEntries(); treeIndex++){
                        thisTTree->GetEntry(treeIndex);
                        if( dr[0] != 999 && dr[1] != 999){
                            int etaIndex1 = fabs(etaSC[0])/(2.5/(double)numEtaBins);
                            int etaIndex2 = fabs(etaSC[1])/(2.5/(double)numEtaBins);
                            for(int i = 0; i < numEtaBins - 1 ; i++){
                                if( fabs(etaSC[0]) > etaBins[i] && fabs(etaSC[0]) < etaBins[i+1]){
                                    etaIndex1 = i;
                                }
                                if( fabs(etaSC[1]) > etaBins[i] && fabs(etaSC[1]) < etaBins[i+1]){
                                    etaIndex2 = i;
                                }
                            }
                            if(etaIndex1 < numEtaBins && etaIndex2 < numEtaBins){
#ifdef ETA_VETO
                                noVeto = true;
                                if(fabs(etaSC[0]) < 0.024) noVeto = false;
                                if(fabs(etaSC[0]) > 0.432 && fabs(etaSC[0]) < 0.456) noVeto = false;
                                if(fabs(etaSC[0]) > 0.768 && fabs(etaSC[0]) < 0.816) noVeto = false;
                                if(fabs(etaSC[0]) > 1.128 && fabs(etaSC[0]) < 1.152) noVeto = false;
#endif
                                if(noVeto){

                                    //make 2D plots for R9 bins:::
                                    if(full5x5_R9[0] > r9Bins[0] && full5x5_R9[0] < r9Bins[1]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_0[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[0] > r9Bins[1] && full5x5_R9[0] < r9Bins[2]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_1[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[0] > r9Bins[2] && full5x5_R9[0] < r9Bins[3]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_2[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[0] > r9Bins[3] && full5x5_R9[0] < r9Bins[4]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_3[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[0] > r9Bins[4] && full5x5_R9[0] < r9Bins[5]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_4[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                        }//end for apd bins
                                    }
                                }//end if veto
#ifdef ETA_VETO
                                noVeto = true;
                                if(fabs(etaSC[1]) < 0.024) noVeto = false;
                                if(fabs(etaSC[1]) > 0.432 && fabs(etaSC[1]) < 0.456) noVeto = false;
                                if(fabs(etaSC[1]) > 0.768 && fabs(etaSC[1]) < 0.816) noVeto = false;
                                if(fabs(etaSC[1]) > 1.128 && fabs(etaSC[1]) < 1.152) noVeto = false;
#endif
                                if(noVeto){
                                    if(full5x5_R9[1] > r9Bins[0] && full5x5_R9[1] < r9Bins[1]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_0[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[1] > r9Bins[1] && full5x5_R9[1] < r9Bins[2]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_1[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[1] > r9Bins[2] && full5x5_R9[1] < r9Bins[3]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_2[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[1] > r9Bins[3] && full5x5_R9[1] < r9Bins[4]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_3[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                        }//end for apd bins
                                    }
                                    if(full5x5_R9[1] > r9Bins[4] && full5x5_R9[1] < r9Bins[5]){
                                        for(int i = 0; i < 100; i++){
                                            Histogramsg_4[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                        }//end for apd bins
                                    }
                                }
                            }//end if the particles are inside 2.5
                        }//end if both particles are reconstructed
                    }//end for tree index
                }//end if key == ntuples
                else{
                    std::cout << "Did not find directory 'ntuples' for file " << rootFile << std::endl;
                    std::cout << "... continuing without this file." << std::endl;
                }
            }//end while keys
        }//end if is zombie
        else{
            std::cout << "The file " << thisFile << " did not open correctly" << std::endl;
            std::cout << "... continuing without this file." << std::endl;
        }
        myFile->Close();
    }//end while files in
	
	in.close();
    std::string inputFileName = std::string(cLineArgs[i]);
    std::size_t extension_location = inputFileName.find(".");
    inputFileName = inputFileName.substr(1, extension_location-1);

    // manage output directory
    //
    DIRECTORY_NAME = "photonSystematics_"+inputFileName;
    
    system(std::string("source clean_up_directories.sh "+DIRECTORY_NAME).c_str());
    //////////////////////////////////////////////////////
    
    std::string fileOut = DIRECTORY_NAME+"/photonSystematics_Histograms_"+inputFileName+".root";


    std::cout<< "files successfully analyzed... " << std::endl;
    std::cout<< "begin writing to file `"<< fileOut << "' ..." << std::endl;

	//////////////////////////////////////////////////////

	thisFile = fileOut.c_str();
	
	TFile * out = new TFile(thisFile, "RECREATE");
	out->cd();
    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < apdBins; j++){
            Histogramse_0[i][j]->Write();
            Histogramse_1[i][j]->Write();
            Histogramse_2[i][j]->Write();
            Histogramse_3[i][j]->Write();
            Histogramse_4[i][j]->Write();
            Histogramsg_0[i][j]->Write();
            Histogramsg_1[i][j]->Write();
            Histogramsg_2[i][j]->Write();
            Histogramsg_3[i][j]->Write();
            Histogramsg_4[i][j]->Write();
        }
    }

    out->Close();
    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < apdBins; j++){
            delete Histogramse_0[i][j];
            delete Histogramse_1[i][j];
            delete Histogramse_2[i][j];
            delete Histogramse_3[i][j];
            delete Histogramse_4[i][j];
            delete Histogramsg_0[i][j];
            delete Histogramsg_1[i][j];
            delete Histogramsg_2[i][j];
            delete Histogramsg_3[i][j];
            delete Histogramsg_4[i][j];
        }
    }
    std::cout << "finished writing to file... " << std::endl;
    ret = fileOut;
	return ret;
};

void myUtilities::produce_FNUF_Plots(std::string fileName){
    myUtilities::produce_LookUpTables( fileName);
    myUtilities::produce_2016_2017_Plots(fileName);
    return;
};

void myUtilities::produce_Ratio_Plots(std::string fileName1, std::string fileName2){
    myUtilities::produce_RatioLookUpTables( fileName1, fileName2);
//    myUtilities::produce_2016_2017_Ratio_Plots( fileName1, fileName2 );
    return;
};

void myUtilities::produce_LookUpTables(std::string fileName){

    std::cout << "begin producing look-up tables... " << std::endl;

	int numR9bins = 5;
	double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00}; 

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.566, 1.8, 2.1, 2.5};
	TFile* myHistograms = new TFile(fileName.c_str(), "READ");

    std::cout << "initializing histograms ... " << std::endl;
    
	TH2F * mean_0 = new TH2F("mean_0", "Photon Systematics [%], 0 < R9 < 0.8", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_1 = new TH2F("mean_1", "Photon Systematics [%], 0.8 < R9 < 0.9", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_2 = new TH2F("mean_2", "Photon Systematics [%], 0.9 < R9 < 0.92", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_3 = new TH2F("mean_3", "Photon Systematics [%], 0.92 < R9 < 0.96", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_4 = new TH2F("mean_4", "Photon Systematics [%], 0.96 < R9 < 1.0", numEtaBins, etaBins, 100, 0.005, 1.005);

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

	char title [50];
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

    std::cout << "evaluating systematics ... " << std::endl;

    TFile * correction_low = new TFile("uncertainty_hists_low.root", "READ");
    TFile * correction_high = new TFile("uncertainty_hists_high.root", "READ");
    TFile * correction_front = new TFile("uncertainty_hists_frontDown.root", "READ");

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
	double err1, err2;
	double ratio;
	double quantile;
	for(int eta = 0; eta < numEtaBins; eta++){
        if(etaBins[eta] != 1.4442 && etaBins[eta+1] != 1.566){
            for(int apd = 0; apd < 100; apd++){
                double correction_0 = 1 + std::max(fabs(high_ratio_0->GetBinContent(eta+1, apd+1)), fabs(low_ratio_0->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_0->GetBinContent(eta+1,apd+1)/100.);
                double correction_1 = 1 + std::max(fabs(high_ratio_1->GetBinContent(eta+1, apd+1)), fabs(low_ratio_1->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_1->GetBinContent(eta+1,apd+1)/100.);
                double correction_2 = 1 + std::max(fabs(high_ratio_2->GetBinContent(eta+1, apd+1)), fabs(low_ratio_2->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_2->GetBinContent(eta+1,apd+1)/100.);
                double correction_3 = 1 + std::max(fabs(high_ratio_3->GetBinContent(eta+1, apd+1)), fabs(low_ratio_3->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_3->GetBinContent(eta+1,apd+1)/100.);
                double correction_4 = 1 + std::max(fabs(high_ratio_4->GetBinContent(eta+1, apd+1)), fabs(low_ratio_4->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_4->GetBinContent(eta+1,apd+1)/100.);
                
                mean1 = e_0_hists[eta][99-apd]->GetMean();
                mean2 = g_0_hists[eta][99-apd]->GetMean();
                mean_0->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_0);

                mean1 = e_1_hists[eta][99-apd]->GetMean();
                mean2 = g_1_hists[eta][99-apd]->GetMean();
                mean_1->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_1);

                mean1 = e_2_hists[eta][99-apd]->GetMean();
                mean2 = g_2_hists[eta][99-apd]->GetMean();
                mean_2->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_2);

                mean1 = e_3_hists[eta][99-apd]->GetMean();
                mean2 = g_3_hists[eta][99-apd]->GetMean();
                mean_3->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_3);

                mean1 = e_4_hists[eta][99-apd]->GetMean();
                mean2 = g_4_hists[eta][99-apd]->GetMean();
                mean_4->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_4);

                delete e_0_hists[eta][99-apd];
                delete g_0_hists[eta][99-apd];
                delete e_1_hists[eta][99-apd];
                delete g_1_hists[eta][99-apd];
                delete e_2_hists[eta][99-apd];
                delete g_2_hists[eta][99-apd];
                delete e_3_hists[eta][99-apd];
                delete g_3_hists[eta][99-apd];
                delete e_4_hists[eta][99-apd];
                delete g_4_hists[eta][99-apd];
            }
        }
    }

    TH2F * mean_EE_0 = (TH2F*)mean_0->Clone();
    TH2F * mean_EE_1 = (TH2F*)mean_1->Clone();
    TH2F * mean_EE_2 = (TH2F*)mean_2->Clone();
    TH2F * mean_EE_3 = (TH2F*)mean_3->Clone();
    TH2F * mean_EE_4 = (TH2F*)mean_4->Clone();

    myUtilities::plot_LookUpTable( mean_0, "lookUpTable_EB_R9_0", 0., 1.44419, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_1, "lookUpTable_EB_R9_1", 0., 1.44419, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_2, "lookUpTable_EB_R9_2", 0., 1.44419, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_3, "lookUpTable_EB_R9_3", 0., 1.44419, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_4, "lookUpTable_EB_R9_4", 0., 1.44419, -0.7, 0.7);

    myUtilities::plot_LookUpTable( mean_EE_0, "lookUpTable_EE_R9_0", 1.566, 2.499, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_EE_1, "lookUpTable_EE_R9_1", 1.566, 2.499, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_EE_2, "lookUpTable_EE_R9_2", 1.566, 2.499, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_EE_3, "lookUpTable_EE_R9_3", 1.566, 2.499, -0.7, 0.7);
    myUtilities::plot_LookUpTable( mean_EE_4, "lookUpTable_EE_R9_4", 1.566, 2.499, -0.7, 0.7);

    std::cout << std::endl << "look-up tables have been produced ... " << std::endl;

    return;
};

void myUtilities::produce_RatioLookUpTables(std::string fileName1, std::string fileName2){

    std::cout << "begin producing ratio look-up tables... " << std::endl;

	int numR9bins = 5;
	double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00}; 

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.566, 1.8, 2.1, 2.5};

    std::cout << "initializing histograms ... " << std::endl;

    std::vector< std::vector<TH1F*> > ratio;
    std::vector< std::vector<TH1F*> > systematics1;
    std::vector< std::vector<TH1F*> > systematics2;
    std::vector< TH1F* > temp1_;
    std::vector< TH1F* > temp2_;
    std::vector< TH1F* > temp3_;
    char title [50];
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < numEtaBins; j++){
            sprintf(title, "ratio_%i_%i", i, j);
            temp3_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "systematics1_%i_%i", i, j);
            temp1_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "systematics2_%i_%i", i, j);
            temp2_.push_back(new TH1F(title, title, numEtaBins, etaBins));
        }
        ratio.push_back(temp3_);
        systematics1.push_back(temp1_);
        systematics2.push_back(temp2_);
        temp1_.clear();
        temp2_.clear();
        temp3_.clear();
    }
    
	TH2F * mean1_0 = new TH2F("mean1_0", "Photon Systematics [%], 0 < R9 < 0.8", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_1 = new TH2F("mean1_1", "Photon Systematics [%], 0.8 < R9 < 0.9", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_2 = new TH2F("mean1_2", "Photon Systematics [%], 0.9 < R9 < 0.92", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_3 = new TH2F("mean1_3", "Photon Systematics [%], 0.92 < R9 < 0.96", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_4 = new TH2F("mean1_4", "Photon Systematics [%], 0.96 < R9 < 1.0", numEtaBins, etaBins, 100, 0.005, 1.005);

	TH2F * mean2_0 = new TH2F("mean2_0", "Photon Systematics [%], 0 < R9 < 0.8", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_1 = new TH2F("mean2_1", "Photon Systematics [%], 0.8 < R9 < 0.9", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_2 = new TH2F("mean2_2", "Photon Systematics [%], 0.9 < R9 < 0.92", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_3 = new TH2F("mean2_3", "Photon Systematics [%], 0.92 < R9 < 0.96", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_4 = new TH2F("mean2_4", "Photon Systematics [%], 0.96 < R9 < 1.0", numEtaBins, etaBins, 100, 0.005, 1.005);

    TH2F * ratio_0 = new TH2F("ratio_0", "Ratio of Systematics [%], 0 < R9 < 0.8", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_1 = new TH2F("ratio_1", "Ratio of Systematics [%], 0.8 < R9 < 0.9", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_2 = new TH2F("ratio_2", "Ratio of Systematics [%], 0.9 < R9 < 0.92", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_3 = new TH2F("ratio_3", "Ratio of Systematics [%], 0.92 < R9 < 0.96", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_4 = new TH2F("ratio_4", "Ratio of Systematics [%], 0.96 < R9 < 1.0", numEtaBins, etaBins, 100, 0.005, 1.005);

    std::vector< std::vector<TH1F*> > e1_0_hists;
	std::vector< std::vector<TH1F*> > e1_1_hists;
	std::vector< std::vector<TH1F*> > e1_2_hists;
	std::vector< std::vector<TH1F*> > e1_3_hists;
	std::vector< std::vector<TH1F*> > e1_4_hists;
	std::vector< std::vector<TH1F*> > g1_0_hists;
	std::vector< std::vector<TH1F*> > g1_1_hists;
	std::vector< std::vector<TH1F*> > g1_2_hists;
	std::vector< std::vector<TH1F*> > g1_3_hists;
	std::vector< std::vector<TH1F*> > g1_4_hists;

	std::vector< std::vector<TH1F*> > e2_0_hists;
	std::vector< std::vector<TH1F*> > e2_1_hists;
	std::vector< std::vector<TH1F*> > e2_2_hists;
	std::vector< std::vector<TH1F*> > e2_3_hists;
	std::vector< std::vector<TH1F*> > e2_4_hists;
	std::vector< std::vector<TH1F*> > g2_0_hists;
	std::vector< std::vector<TH1F*> > g2_1_hists;
	std::vector< std::vector<TH1F*> > g2_2_hists;
	std::vector< std::vector<TH1F*> > g2_3_hists;
	std::vector< std::vector<TH1F*> > g2_4_hists;

    std::vector<TH1F*> e1_0;
	std::vector<TH1F*> e1_1;
	std::vector<TH1F*> e1_2;
	std::vector<TH1F*> e1_3;
	std::vector<TH1F*> e1_4;
	std::vector<TH1F*> g1_0;
	std::vector<TH1F*> g1_1;
	std::vector<TH1F*> g1_2;
	std::vector<TH1F*> g1_3;
	std::vector<TH1F*> g1_4;

	std::vector<TH1F*> e2_0;
	std::vector<TH1F*> e2_1;
	std::vector<TH1F*> e2_2;
	std::vector<TH1F*> e2_3;
	std::vector<TH1F*> e2_4;
	std::vector<TH1F*> g2_0;
	std::vector<TH1F*> g2_1;
	std::vector<TH1F*> g2_2;
	std::vector<TH1F*> g2_3;
	std::vector<TH1F*> g2_4;

    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < 100; j++){
            e1_0.push_back(new TH1F());
            e1_1.push_back(new TH1F());
            e1_2.push_back(new TH1F());
            e1_3.push_back(new TH1F());
            e1_4.push_back(new TH1F());
            g1_0.push_back(new TH1F());
            g1_1.push_back(new TH1F());
            g1_2.push_back(new TH1F());
            g1_3.push_back(new TH1F());
            g1_4.push_back(new TH1F());
            e2_0.push_back(new TH1F());
            e2_1.push_back(new TH1F());
            e2_2.push_back(new TH1F());
            e2_3.push_back(new TH1F());
            e2_4.push_back(new TH1F());
            g2_0.push_back(new TH1F());
            g2_1.push_back(new TH1F());
            g2_2.push_back(new TH1F());
            g2_3.push_back(new TH1F());
            g2_4.push_back(new TH1F());
        }
		e1_0_hists.push_back(e1_0);
		e1_1_hists.push_back(e1_1);
		e1_2_hists.push_back(e1_2);
		e1_3_hists.push_back(e1_3);
		e1_4_hists.push_back(e1_4);
		g1_0_hists.push_back(g1_0);
		g1_1_hists.push_back(g1_1);
		g1_2_hists.push_back(g1_2);
		g1_3_hists.push_back(g1_3);
		g1_4_hists.push_back(g1_4);
		e2_0_hists.push_back(e2_0);
		e2_1_hists.push_back(e2_1);
		e2_2_hists.push_back(e2_2);
		e2_3_hists.push_back(e2_3);
		e2_4_hists.push_back(e2_4);
		g2_0_hists.push_back(g2_0);
		g2_1_hists.push_back(g2_1);
		g2_2_hists.push_back(g2_2);
		g2_3_hists.push_back(g2_3);
		g2_4_hists.push_back(g2_4);
		e1_0.clear();
		e1_1.clear();
		e1_2.clear();
		e1_3.clear();
		e1_4.clear();
		g1_0.clear();
		g1_1.clear();
		g1_2.clear();
		g1_3.clear();
		g1_4.clear();
		e2_0.clear();
		e2_1.clear();
		e2_2.clear();
		e2_3.clear();
		e2_4.clear();
		g2_0.clear();
		g2_1.clear();
		g2_2.clear();
		g2_3.clear();
		g2_4.clear();
    }

	TFile* myHistograms1 = new TFile(fileName1.c_str(), "READ");
    if(!myHistograms1 || myHistograms1->IsZombie()){
        std::cout << "The file '" << fileName1 <<"` did not successfully open." << std::endl;
        return;
    }
    TFile* myHistograms2 = new TFile(fileName2.c_str(), "READ");
    if(!myHistograms2 || myHistograms2->IsZombie()){
        std::cout << "The file '" << fileName1 <<"` did not successfully open." << std::endl;
        return;
    }

    myHistograms1->cd();
	for(int i = 0; i < numEtaBins; i++){
		for(int j = 0; j < 100; j++){
			sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
			e1_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
            e1_0_hists[i][j]->GetMean();
			sprintf( title, "e_1_%i_%i_%i", i, i+1, j);
			e1_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_2_%i_%i_%i", i, i+1, j);
			e1_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_3_%i_%i_%i", i, i+1, j);
			e1_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_4_%i_%i_%i", i, i+1, j);
			e1_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
			g1_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_1_%i_%i_%i", i, i+1, j);
			g1_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_2_%i_%i_%i", i, i+1, j);
			g1_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_3_%i_%i_%i", i, i+1, j);
			g1_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_4_%i_%i_%i", i, i+1, j);
			g1_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
      	}
	}

    myHistograms2->cd();
	for(int i = 0; i < numEtaBins; i++){
		for(int j = 0; j < 100; j++){
			sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
			e2_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_1_%i_%i_%i", i, i+1, j);
			e2_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_2_%i_%i_%i", i, i+1, j);
			e2_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_3_%i_%i_%i", i, i+1, j);
			e2_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_4_%i_%i_%i", i, i+1, j);
			e2_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
			g2_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_1_%i_%i_%i", i, i+1, j);
			g2_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_2_%i_%i_%i", i, i+1, j);
			g2_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_3_%i_%i_%i", i, i+1, j);
			g2_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_4_%i_%i_%i", i, i+1, j);
			g2_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
      	}
	}

    std::cout << "evaluating systematics ... " << std::endl;

	double mean11, mean12, mean21, mean22;
	double err11, err12, err21, err22;
	double ratio1, ratio2;
    double err1, err2;
	double quantile;

	for(int eta = 0; eta < numEtaBins; eta++){
        if(etaBins[eta] != 1.4442 && etaBins[eta+1] != 1.566){
            for(int apd = 0; apd < 100; apd++){
                
                mean11 = e1_0_hists[eta][99-apd]->GetMean();
                mean12 = g1_0_hists[eta][99-apd]->GetMean();
                mean1_0->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][0]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_1_hists[eta][99-apd]->GetMean();
                mean12 = g1_1_hists[eta][99-apd]->GetMean();
                mean1_1->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][1]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_2_hists[eta][99-apd]->GetMean();
                mean12 = g1_2_hists[eta][99-apd]->GetMean();
                mean1_2->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][2]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_3_hists[eta][99-apd]->GetMean();
                mean12 = g1_3_hists[eta][99-apd]->GetMean();
                mean1_3->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][3]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_4_hists[eta][99-apd]->GetMean();
                mean12 = g1_4_hists[eta][99-apd]->GetMean();
                mean1_4->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][4]->SetBinContent(eta+1, mean12/mean11);

                mean21 = e2_0_hists[eta][99-apd]->GetMean();
                mean22 = g2_0_hists[eta][99-apd]->GetMean();
                mean2_0->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][0]->SetBinContent(eta+1, mean22/mean21);

                mean21 = e2_1_hists[eta][99-apd]->GetMean();
                mean22 = g2_1_hists[eta][99-apd]->GetMean();
                mean2_1->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][1]->SetBinContent(eta+1, mean22/mean21);

                mean21 = e2_2_hists[eta][99-apd]->GetMean();
                mean22 = g2_2_hists[eta][99-apd]->GetMean();
                mean2_2->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][2]->SetBinContent(eta+1, mean22/mean21);

                mean21 = e2_3_hists[eta][99-apd]->GetMean();
                mean22 = g2_3_hists[eta][99-apd]->GetMean();
                mean2_3->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][3]->SetBinContent(eta+1, mean22/mean21);

                mean21 = e2_4_hists[eta][99-apd]->GetMean();
                mean22 = g2_4_hists[eta][99-apd]->GetMean();
                mean2_4->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][4]->SetBinContent(eta+1, mean22/mean21);


                ratio[apd][0]->SetBinContent(eta+1, 100*((systematics1[apd][0]->GetBinContent(eta+1)/systematics2[apd][0]->GetBinContent(eta+1))- 1));
                ratio[apd][1]->SetBinContent(eta+1, 100*((systematics1[apd][1]->GetBinContent(eta+1)/systematics2[apd][1]->GetBinContent(eta+1))- 1));
                ratio[apd][2]->SetBinContent(eta+1, 100*((systematics1[apd][2]->GetBinContent(eta+1)/systematics2[apd][2]->GetBinContent(eta+1))- 1));
                ratio[apd][3]->SetBinContent(eta+1, 100*((systematics1[apd][3]->GetBinContent(eta+1)/systematics2[apd][3]->GetBinContent(eta+1))- 1));
                ratio[apd][4]->SetBinContent(eta+1, 100*((systematics1[apd][4]->GetBinContent(eta+1)/systematics2[apd][4]->GetBinContent(eta+1))- 1));

                ratio_0->SetBinContent(eta + 1, apd + 1, 100*(mean1_0->GetBinContent(eta+1, apd+1) / mean2_0->GetBinContent(eta+1, eta+2) - 1));
                ratio_1->SetBinContent(eta + 1, apd + 1, 100*(mean1_1->GetBinContent(eta+1, apd+1) / mean2_1->GetBinContent(eta+1, eta+2) - 1));
                ratio_2->SetBinContent(eta + 1, apd + 1, 100*(mean1_2->GetBinContent(eta+1, apd+1) / mean2_2->GetBinContent(eta+1, eta+2) - 1));
                ratio_3->SetBinContent(eta + 1, apd + 1, 100*(mean1_3->GetBinContent(eta+1, apd+1) / mean2_3->GetBinContent(eta+1, eta+2) - 1));
                ratio_4->SetBinContent(eta + 1, apd + 1, 100*(mean1_4->GetBinContent(eta+1, apd+1) / mean2_4->GetBinContent(eta+1, eta+2) - 1));
            }
        }
    }

    TH2F * ratio_EE_0 = (TH2F*)ratio_0->Clone();
    TH2F * ratio_EE_1 = (TH2F*)ratio_1->Clone();
    TH2F * ratio_EE_2 = (TH2F*)ratio_2->Clone();
    TH2F * ratio_EE_3 = (TH2F*)ratio_3->Clone();
    TH2F * ratio_EE_4 = (TH2F*)ratio_4->Clone();

    // these ratios will be saved to a root file for later use
    TFile * outputRatioHists = new TFile("uncertainty_hists_high_120.root", "RECREATE");
    outputRatioHists->cd();
    ratio_0->Write();
    ratio_1->Write();
    ratio_2->Write();
    ratio_3->Write();
    ratio_4->Write();
    outputRatioHists->Close();

    myUtilities::plot_LookUpTable( ratio_0, "ratioLookUpTable_EB_R9_0", 0., 1.44419, -15, 15);
    myUtilities::plot_LookUpTable( ratio_1, "ratioLookUpTable_EB_R9_1", 0., 1.44419, -15, 15);
    myUtilities::plot_LookUpTable( ratio_2, "ratioLookUpTable_EB_R9_2", 0., 1.44419, -15, 15);
    myUtilities::plot_LookUpTable( ratio_3, "ratioLookUpTable_EB_R9_3", 0., 1.44419, -15, 15);
    myUtilities::plot_LookUpTable( ratio_4, "ratioLookUpTable_EB_R9_4", 0., 1.44419, -15, 15);

    myUtilities::plot_LookUpTable( ratio_EE_0, "ratioLookUpTable_EE_R9_0", 1.566, 2.499, -15, 15);
    myUtilities::plot_LookUpTable( ratio_EE_1, "ratioLookUpTable_EE_R9_1", 1.566, 2.499, -15, 15);
    myUtilities::plot_LookUpTable( ratio_EE_2, "ratioLookUpTable_EE_R9_2", 1.566, 2.499, -15, 15);
    myUtilities::plot_LookUpTable( ratio_EE_3, "ratioLookUpTable_EE_R9_3", 1.566, 2.499, -15, 15);
    myUtilities::plot_LookUpTable( ratio_EE_4, "ratioLookUpTable_EE_R9_4", 1.566, 2.499, -15, 15);

    std::cout << std::endl << "ratio look-up tables have been produced ... " << std::endl;
    delete myHistograms1;
    delete myHistograms2;
    return;
};

void myUtilities::plot_LookUpTable( TH2F* thisHist, std::string title, double xMin, double xMax, double zMin, double zMax){
    TCanvas * a = new TCanvas("a", "", 900, 900);
    a->cd();
    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat("0.2f");
    gStyle->SetOptTitle(0);

    TLatex* pave = new TLatex(0.100, 0.91, "#font[42]{#bf{CMS} #it{Simulation Preliminary}}");
    TLatex* lumi_label = new TLatex(0.75, 0.91, "#font[42]{13 TeV}");
    thisHist->SetXTitle("|#eta|");
    thisHist->SetYTitle("Laser Response");
    thisHist->SetZTitle("Systematics [%]");
    thisHist->Draw("colztext");
    thisHist->SetContour(99);
    thisHist->SetAxisRange(xMin, xMax, "X");
    if(title.find("EB") != std::string::npos) thisHist->SetAxisRange(0.8, 0.9999999, "Y");
    if(title.find("EE") != std::string::npos) thisHist->SetAxisRange(0.6, 0.8999999, "Y");
    thisHist->SetAxisRange(zMin, zMax, "Z");
    thisHist->SetLabelSize(0.03, "Y");
    thisHist->SetLabelSize(0.02, "Z");
    thisHist->SetTitleSize(0.03, "Z");
    thisHist->SetTitleOffset(1.25, "Y");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    gPad->Update();	
    TPaletteAxis * palette =(TPaletteAxis*)thisHist->GetListOfFunctions()->FindObject("palette");
    palette->SetX2NDC(0.92);
    a->Modified();
    std::string saveName = DIRECTORY_NAME+"/"+title+".pdf";
    a->SaveAs(saveName.c_str());
    saveName = DIRECTORY_NAME+"/"+title+".C";
    a->SaveAs(saveName.c_str());
    saveName = DIRECTORY_NAME+"/"+title+".png";
    a->SaveAs(saveName.c_str());
    delete a;
    return;
};


void myUtilities::produce_2016_2017_Plots(std::string fileName){
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

    std::string uncertainty_low = "uncertainty_hists_low.root";
    std::string uncertainty_high = "uncertainty_hists_high.root";
    std::string uncertainty_frontDown = "uncertainty_hists_frontFlat.root";

    if(fileName.find("030") != std::string::npos){
        uncertainty_low = "uncertainty_hists_low_030.root";
        uncertainty_high = "uncertainty_hists_high_030.root";
        uncertainty_frontDown = "uncertainty_hists_frontFlat_030.root";
    }
    if(fileName.find("045") != std::string::npos){
        uncertainty_low = "uncertainty_hists_low_045.root";
        uncertainty_high = "uncertainty_hists_high_045.root";
        uncertainty_frontDown = "uncertainty_hists_frontFlat_045.root";
    }
    if(fileName.find("120") != std::string::npos){
        uncertainty_low = "uncertainty_hists_low_120.root";
        uncertainty_high = "uncertainty_hists_high_120.root";
        uncertainty_frontDown = "uncertainty_hists_frontFlat_120.root";
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
    myUtilities::plot_2016(systematics[93][0], systematics[93][1], systematics[93][2], systematics[93][3], systematics[93][4], energy, region, -0.05, 0.25);
    myUtilities::plot_2017(systematics[91][0], systematics[91][1], systematics[91][2], systematics[91][3], systematics[91][4], energy, region, -0.10, 0.35);
    region = "EE";
    myUtilities::plot_2016(endcap2016_0, endcap2016_1, endcap2016_2, endcap2016_3, endcap2016_4, energy, region, -0.05, 0.6 );
    myUtilities::plot_2017(endcap2017_0, endcap2017_1, endcap2017_2, endcap2017_3, endcap2017_4, energy, region, -0.05, 0.9);
    return;
};

void myUtilities::plot_2016( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, std::string energy, std::string region, double yMin, double yMax){
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

void myUtilities::plot_2017( TH1F * hist0, TH1F * hist1, TH1F * hist2, TH1F * hist3, TH1F * hist4, std::string energy, std::string region, double yMin, double yMax){
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
