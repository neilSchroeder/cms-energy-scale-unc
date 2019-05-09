#ifndef utilityhistograms
#define utilityhistograms

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
#include "../interface/frameworkHistogramProducer.h"

//#define ETA_VETO

std::string DIRECTORY_NAME = "photonSystematics";

/// Produce FNUF Histograms only analyzes two files at a time
void myHistogramProducer::produce_FNUF_Histograms( std::string ele_file, std::string pho_file, std::string outputFileName, std::string outputDirectoryName){
    std::string ret = "";

    std::cout << "Electron File: " << ele_file << "\nPhoton File: " << pho_file << std::endl;

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
		double etaMax = etaBins[iii+1];
		double etaMin = etaBins[iii];
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
	in.open( ele_file.c_str() );

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
                            for(int i = 0; i < numEtaBins - 1 ; i++){
                                if( fabs(etaSC[0]) > etaBins[i] && fabs(etaSC[0]) < etaBins[i+1]){
                                    etaIndex1 = i;
                                }
                                if( fabs(etaSC[1]) > etaBins[i] && fabs(etaSC[1]) < etaBins[i+1]){
                                    etaIndex2 = i;
                                }
                            }
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
            std::cout << "The file " << ele_file << " did not open properly" << std::endl;
            std::cout << "... continuing without this file." << std::endl;
        }
        myFile->Close();
    }//end while files in
	
	in.close();
	in.open( pho_file.c_str() );

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
            std::cout << "The file " << pho_file << " did not open correctly" << std::endl;
            std::cout << "... continuing without this file." << std::endl;
        }
        myFile->Close();
    }//end while files in
	
	in.close();

    // manage output directory
    //
    DIRECTORY_NAME = outputDirectoryName;
    
    
    system(std::string("source ./clean_up_directories.sh "+DIRECTORY_NAME).c_str());
    std::cout << "source ./clean_up_directories.sh "+DIRECTORY_NAME << std::endl;
    //////////////////////////////////////////////////////
    
    std::string fileOut = DIRECTORY_NAME+outputFileName;
    if(fileOut.find(".root") == std::string::npos) fileOut = fileOut+".root";


    std::cout<< "files successfully analyzed... " << std::endl;
    std::cout<< "begin writing to file `"<< fileOut << "' ..." << std::endl;

	//////////////////////////////////////////////////////

	TFile * out = new TFile(fileOut.c_str(), "RECREATE");
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
	return;
};

void myHistogramProducer::produce_PION_Histograms( std::string ele_file, std::string pi_file, std::string outputFileName, std::string outputDirectoryName){
    std::string ret = "";

    std::cout << "You are working with Pions" << std::endl;
    std::cout << "Electron File: " << ele_file << "\nPhoton File: " << pi_file << std::endl;

	//declare some constants

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

	char titleLow [50];
	char titleHigh [50];
	char tagLow [50];
	char tagHigh [50];
	std::vector<TH1F*> Histse_0;
	std::vector<TH1F*> Histsg_0;

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
			Histse_0.push_back(eHist_0);
			Histsg_0.push_back(gHist_0);
			if(iii != 4) count++;
		}//end for jjj
		Histogramse_0.push_back(Histse_0);
		Histogramsg_0.push_back(Histsg_0);
		Histse_0.clear();
		Histsg_0.clear();
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
	in.open( ele_file.c_str() );

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
                    thisTTree->SetBranchAddress("Reco_Phi", phi);
                    thisTTree->SetBranchAddress("Gen_Phi", phiS);
                    thisTTree->SetBranchAddress("dR", dr);
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
                        for(int i = 0; i < numEtaBins - 1 ; i++){
                            if( fabs(etaSC[0]) > etaBins[i] && fabs(etaSC[0]) < etaBins[i+1]){
                                etaIndex1 = i;
                            }
                            if( fabs(etaSC[1]) > etaBins[i] && fabs(etaSC[1]) < etaBins[i+1]){
                                etaIndex2 = i;
                            }
                        }
                            if( etaIndex1 < numEtaBins && full5x5_R9[0] > 0.94){
                                //make 2D plots for R9 bins:::
                                for(int i = 0; i < 100; i++){
                                    Histogramse_0[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                                }//end for apd bins
                            }
                                if( etaIndex2 < numEtaBins && full5x5_R9[1] > 0.94){
                                for(int i = 0; i < 100; i++){
                                    Histogramse_0[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                                }//end for apd bins
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
            std::cout << "The file " << ele_file << " did not open properly" << std::endl;
            std::cout << "... continuing without this file." << std::endl;
        }
        myFile->Close();
    }//end while files in
	
	in.close();
	in.open( pi_file.c_str() );

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
                    thisTTree->SetBranchAddress("Reco_Phi", phi);
                    thisTTree->SetBranchAddress("Gen_Phi", phiS);
                    thisTTree->SetBranchAddress("dR", dr);
                    thisTTree->SetBranchAddress("run", &run);
                    thisTTree->SetBranchAddress("event", &event);
                    thisTTree->SetBranchAddress("lum", &lum);

                    for(Long64_t treeIndex = 0; treeIndex < thisTTree->GetEntries(); treeIndex++){
                        thisTTree->GetEntry(treeIndex);
                        int etaIndex1 = fabs(eta[0])/(2.5/(double)numEtaBins);
                        int etaIndex2 = fabs(eta[1])/(2.5/(double)numEtaBins);
                        for(int i = 0; i < numEtaBins - 1 ; i++){
                            if( fabs(eta[0]) > etaBins[i] && fabs(eta[0]) < etaBins[i+1]){
                                etaIndex1 = i;
                            }
                            if( fabs(eta[1]) > etaBins[i] && fabs(eta[1]) < etaBins[i+1]){
                                etaIndex2 = i;
                            }
                        }
                        if(etaIndex1 < numEtaBins){
                            for(int i = 0; i < 100; i++){
                                Histogramsg_0[etaIndex1][i]->Fill(apd_lce_RecHitSums1[i]/def_nomiRecHitSum[0]);
                            }//end for apd bins
                        }
                        if(etaIndex2 < numEtaBins){
                            for(int i = 0; i < 100; i++){
                                Histogramsg_0[etaIndex2][i]->Fill(apd_lce_RecHitSums2[i]/def_nomiRecHitSum[1]);
                            }//end for apd bins
                        }//end if the particles are inside 2.5
                    }//end for tree index
                }//end if key == ntuples
                else{
                    std::cout << "Did not find directory 'ntuples' for file " << rootFile << std::endl;
                    std::cout << "... continuing without this file." << std::endl;
                }
            }//end while keys
        }//end if is zombie
        else{
            std::cout << "The file " << pi_file << " did not open correctly" << std::endl;
            std::cout << "... continuing without this file." << std::endl;
        }
        myFile->Close();
    }//end while files in
	
	in.close();

    // manage output directory
    //
    DIRECTORY_NAME = outputDirectoryName;
    
    
    system(std::string("source ./clean_up_directories.sh "+DIRECTORY_NAME).c_str());
    std::cout << "source ./clean_up_directories.sh "+DIRECTORY_NAME << std::endl;
    //////////////////////////////////////////////////////
    
    std::string fileOut = DIRECTORY_NAME+outputFileName;
    if(fileOut.find(".root") == std::string::npos) fileOut = fileOut+".root";


    std::cout<< "files successfully analyzed... " << std::endl;
    std::cout<< "begin writing to file `"<< fileOut << "' ..." << std::endl;

	//////////////////////////////////////////////////////

	TFile * out = new TFile(fileOut.c_str(), "RECREATE");
	out->cd();
    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < apdBins; j++){
            Histogramse_0[i][j]->Write();
            Histogramsg_0[i][j]->Write();
        }
    }

    out->Close();
    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < apdBins; j++){
            delete Histogramse_0[i][j];
            delete Histogramsg_0[i][j];
        }
    }
    std::cout << "finished writing to file... " << std::endl;
	return;
};

#endif
