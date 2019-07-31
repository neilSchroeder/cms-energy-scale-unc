#ifndef FRAMEWORK
#define FRAMEWORK

/*
 *
 *
 *
 *
 * defines member functions for the FNUF framework
 * Most commonly used function is correctedEnergy
 *
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

#include "RecoCaloTools/Navigation/interface/CaloNavigator.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include "models.h"
#include "frameworkFunctions.h"
#include "math.h"
#include <utility>
#include <string>
#include <stdexcept>
#include <tuple>

//#define LinearEnergy

double RING_RESPONSE [100];
double RING_REWEIGHT_EB [100];
double RING_REWEIGHT_EE [100];
double RING_ETA [100];
double NUM_XTAL_BINS = 16383.;
std::map< std::pair<int, int>, double> ecal_map_barrel;
std::map< std::tuple<int, int, int>, double> ecal_map_endcap;
double MAX_DR = 0.8;

void framework::initializeGlobals(){
    double showerMax_EB = 0.26; //defines the location of the LCE normalization in EB
    double showerMax_EE = 0.27; //defines the location of the LCE normalization in EE

	for( int i = 0; i < 100; i++){
		RING_RESPONSE[i] = 1 - (double)i*0.01; 
		RING_ETA[i] = (i+1)*(2.4/100.0);
		RING_REWEIGHT_EB[i] = 1;
		RING_REWEIGHT_EE[i] = 1;
	}

    models myModels;
    for( int i = 0; i < 100; i++){
        RING_REWEIGHT_EB[i] = myModels.LightCollectionEfficiencyWeighted(showerMax_EB, 0, RING_RESPONSE[i], 1);
        RING_REWEIGHT_EE[i] = myModels.LightCollectionEfficiencyWeighted(showerMax_EE, 2, RING_RESPONSE[i], 1);
    }

    int id, ix, iy, ieta, iphi, iz;
    float eta;
    ifstream in;
    in.open("/home/schr1077/cms/fnuf_framework/CMSSW_8_0_26_patch1/src/lceFramework/ntuples/plugins/data/ecal_barrel_eta.dat");
    if(!in.good()) cout << "your file didn't open" << endl;
    while(in >> id >> ieta >> iphi >> iz >> eta){
        ecal_map_barrel.insert( std::pair< typename std::pair<int, int>, float>(std::pair<int, int>(ieta, iphi), eta));
    }
    in.close();
    in.open("/home/schr1077/cms/fnuf_framework/CMSSW_8_0_26_patch1/src/lceFramework/ntuples/plugins/data/ecal_endcap_eta.dat");
    while(in >> id >> ix >> iy >> iz >> eta){
        ecal_map_endcap.insert( std::pair<typename std::tuple<int, int, int>, float>(std::tuple<int, int, int>(ix, iy, iz), eta));
    }
    in.close();
};

void framework::correctedEnergy( reco::Photon e, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > recHits, edm::PCaloHitContainer pCaloHits, double (*weight)(double, double, double, double), double retLCE [100], double retLinear [8] , float * defaultEnergy, int * numSupClustCrystals){
	using namespace std;
    models myModels;
	//some variables
	double updatedSimE [100] = {0};
#ifdef LinearEnergy
	double linearSimE [8] = {0};
	int linearFcns = 8;
#endif
	double defaultSimE = 0;
	EcalRecHit crystalHere;
	double crystalEnergy;
	double depthHere;
	int apdBins = 100;
    double totalCrystalEnergy = 0;

	uint32_t currentId;

	edm::PCaloHitContainer::const_iterator caloHitsItr;
	edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >::const_iterator recHitsItr;

	//get the super cluster and its hits and fractions collection
	reco::SuperClusterRef eSupClust = e.superCluster();
	const std::vector< std::pair<DetId, float> > crystIDs = eSupClust->hitsAndFractions();


	//now we need to get the PCaloHitContainer by DetId
	//first we loop over the crystals.
	std::set<uint32_t> recIDs;
	for(int i = 0; i < fabs(crystIDs.size()); i++){

		//if we have seen this crystal already, do not process it
		if( recIDs.find(crystIDs[i].first.rawId()) == recIDs.end()){
			recIDs.insert(crystIDs[i].first.rawId());

			//dont run past the end of the collection
			if( recHits.find(crystIDs[i].first.rawId()) != recHits.end()){
				//define the current crystal ID and its energy;
				currentId     = std::get<0>(crystIDs[i]).rawId();
				crystalHere   = *(recHits.find(currentId));
				crystalEnergy = crystalHere.energy();

				//a correction must be applied crystal by crystal
				for( int jjj = 0; jjj< apdBins; jjj++){ updatedSimE[jjj] = 0.;}
#ifdef LinearEnergy
				for( int jjj = 0; jjj < linearFcns; jjj++){ linearSimE[jjj] = 0.;}
#endif
				defaultSimE = 0.;

				//Now we loop over the PCaloHits
				for(caloHitsItr = pCaloHits.begin(); caloHitsItr != pCaloHits.end(); caloHitsItr++){

					//We only want PCaloHits in this super cluster
					if(caloHitsItr->id() == currentId){

						//Get the Depth of the PCaloHit and its corresponding bin
						depthHere = (double)((caloHitsItr->depth())>>2)/NUM_XTAL_BINS; //16383 is 2^14 - 1
                        std::cout << caloHitsItr->depth() << " " << (caloHitsItr->depth()>>2) << " " << NUM_XTAL_BINS << " " << depthHere << std::endl;
						//sum up the weighted energy using functions
						if( depthHere == 0.) depthHere = 1./(NUM_XTAL_BINS);
						if( depthHere == 1.) depthHere = 1 - 1./(NUM_XTAL_BINS);
                        if(depthHere > 0. && depthHere < 1.){
						    //the following line calculates the energy with default LCE weights.
                            defaultSimE += caloHitsItr->energy();
                            for(int ggg = 0; ggg < apdBins; ggg++){
                                if( fabs(e.eta()) < 1.479) updatedSimE[ggg] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[ggg], ::RING_REWEIGHT_EB[ggg])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                                else if( fabs(e.eta()) >= 1.497) updatedSimE[ggg] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[ggg], ::RING_REWEIGHT_EE[ggg])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                            }//end for apd/pn bins
#ifdef LinearEnergy
                            linearSimE[0] += caloHitsItr->energy()*linear_A(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[1] += caloHitsItr->energy()*linear_B(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[2] += caloHitsItr->energy()*linear_C(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[3] += caloHitsItr->energy()*linear_D(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[4] += caloHitsItr->energy()*linear_E(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[5] += caloHitsItr->energy()*linear_F(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[6] += caloHitsItr->energy()*linear_G(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[7] += caloHitsItr->energy()*linear_H(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
#endif
                        }//end for broken energy
                    }//end if currentId
                }// end for caloHits
				if(crystalEnergy > 0.07 && defaultSimE != 0.){// cut on noisy crystals
					for(int zzz = 0; zzz < 100; zzz++){
						retLCE[zzz] += updatedSimE[zzz]*crystalEnergy/defaultSimE;
#ifdef LinearEnergy
						if(zzz < linearFcns) retLinear[zzz] += linearSimE[zzz]*crystalEnergy/defaultSimE;
#endif
					}
                        totalCrystalEnergy += crystalEnergy;
				}// end if defaultSimE != 0
			}// end if not end of recHits
		}//end if crystal already in set
	}//end for crystals in supercluster
	*numSupClustCrystals = recIDs.size();
    *defaultEnergy = (float)totalCrystalEnergy;
	return;
};


void framework::correctedEnergy( reco::GsfElectron e, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > recHits, edm::PCaloHitContainer pCaloHits, double  (*weight)(double, double, double, double) , double retLCE [100], double retLinear [8], float * defaultEnergy, int * numSupClustCrystals){
	using namespace std;
    models myModels;
	//some variables
	double updatedSimE [100] = {0.};
#ifdef LinearEnergy
	double linearSimE [8] = {0.};
    int linearFcns = 8;
#endif
	double defaultSimE = 0.;
	EcalRecHit crystalHere;
	double crystalEnergy;
	double depthHere;
	int apdBins = 100;
    double totalCrystalEnergy = 0.;

	uint32_t currentId;

	edm::PCaloHitContainer::const_iterator caloHitsItr;
	edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >::const_iterator recHitsItr;

	//get the super cluster and its hits and fractions collection
	reco::SuperClusterRef eSupClust = e.superCluster();
	const std::vector< std::pair<DetId, float> > crystIDs = eSupClust->hitsAndFractions();


	//now we need to get the PCaloHitContainer by DetId
	//first we loop over the crystals.
	std::set<uint32_t> recIDs;
	for(int i = 0; i < fabs(crystIDs.size()); i++){

		//if we have seen this crystal already, do not process it
		if( recIDs.find(crystIDs[i].first.rawId()) == recIDs.end()){
			recIDs.insert(crystIDs[i].first.rawId());

			//dont run past the end of the collection
			if( recHits.find(crystIDs[i].first.rawId()) != recHits.end()){
				//define the current crystal ID and its energy;
				currentId     = std::get<0>(crystIDs[i]).rawId();
				crystalHere   = *(recHits.find(currentId));
				crystalEnergy = crystalHere.energy();

				//a correction must be applied crystal by crystal
                for( int iii = 0; iii < apdBins; iii++){ updatedSimE[iii] = 0.;}
#ifdef LinearEnergy
                for( int iii = 0; iii < linearFcns; iii++){ linearSimE[iii] = 0.;}
#endif
                defaultSimE = 0.;

                //Now we loop over the PCaloHits
                for(caloHitsItr = pCaloHits.begin(); caloHitsItr != pCaloHits.end(); caloHitsItr++){

                    //We only want PCaloHits in this super cluster
                    if(caloHitsItr->id() == currentId){
                        //Get the Depth of the PCaloHit and its corresponding bin
                        depthHere = (double)((caloHitsItr->depth())>>2)/NUM_XTAL_BINS; //16383 is 2^14 - 1
                        //sum up the weighted energy using functions
                       	if( depthHere == 0.) depthHere = 1./NUM_XTAL_BINS;
                       	if( depthHere == 1.) depthHere = 1 - 1./NUM_XTAL_BINS;
                        if(depthHere > 0. && depthHere < 1.){
                            //the following line calculates the energy with default LCE weights.
                            defaultSimE += caloHitsItr->energy();
                            for(int jjj = 0; jjj < apdBins; jjj++){
                                if( fabs(e.eta()) < 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EB[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                                else if( fabs(e.eta()) >= 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EE[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                            }// end for apdBins
#ifdef LinearEnergy
                            linearSimE[0] += caloHitsItr->energy()*linear_A(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[1] += caloHitsItr->energy()*linear_B(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[2] += caloHitsItr->energy()*linear_C(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[3] += caloHitsItr->energy()*linear_D(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[4] += caloHitsItr->energy()*linear_E(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[5] += caloHitsItr->energy()*linear_F(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[6] += caloHitsItr->energy()*linear_G(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[7] += caloHitsItr->energy()*linear_H(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
#endif
                        }//end if energy is broken
                    }//end if currentId
                }// end for caloHits
				if(crystalEnergy > 0.07 && defaultSimE != 0.){// cut on noisy crystals
					for(int zzz = 0; zzz < apdBins; zzz++){
						retLCE[zzz] += updatedSimE[zzz]*crystalEnergy/defaultSimE;
#ifdef LinearEnergy
						if(zzz < linearFcns) retLinear[zzz] += linearSimE[zzz]*crystalEnergy/defaultSimE;
#endif
					}
                        totalCrystalEnergy += crystalEnergy;
				}// end if defaultSimE != 0
			}// end if not end of recHits
		}//end if crystal already in set
	}//end for crystals in supercluster
	*numSupClustCrystals = recIDs.size();
    *defaultEnergy = (float)totalCrystalEnergy;

	return;
};

void framework::correctedEnergy( reco::GenParticle e, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > recHits, edm::PCaloHitContainer pCaloHits, double  (*weight)(double, double, double, double) , double retLCE [100], double retLinear [8], float * defaultEnergy, int * numSupClustCrystals){
	using namespace std;
    models myModels;
    double gen_eta = e.eta();
    double gen_phi = e.phi();
	//some variables
	double updatedSimE [100] = {0.};
#ifdef LinearEnergy
	double linearSimE [8] = {0.};
    int linearFcns = 8;
#endif
	double defaultSimE = 0.;
	EcalRecHit crystalHere;
	double crystalEnergy;
	double depthHere;
	int apdBins = 100;
    double totalCrystalEnergy = 0.;

	uint32_t currentId;

	edm::PCaloHitContainer::const_iterator caloHitsItr;
	edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >::const_iterator recHitsItr;

	//get a list of the crystals within a dr cone of 0.8 of the initial pion
    //
    //to do this I will loop over all possible crystals in the Barrel and Endcap
    //    -> This will entail creating all possible DetIds for the two regions
    //    -> Check if the DetId is valid
    //    -> Get the eta and phi of the DetId
    //    -> Compare the eta and phi of the crystal to the genParticle
    //    -> Add to list of crystals associated with the genParticle

	std::vector< std::pair<DetId, float> > crystIDs;

    //first loop is over ieta, iphi
    for(int ieta = -85; ieta < 86; ieta++){
        for(int iphi = 1; iphi < 101; iphi++){
            if( ieta != 0 ){
                EBDetId * thisDetId = new EBDetId(ieta, iphi);
                if( EBDetId::validDetId(thisDetId->ieta(), thisDetId->iphi()) ){
                    float randFloat = 0.1;
                    std::pair<int, int> my_loc = std::pair<int, int>(ieta, iphi);
                    double thisEta = ecal_map_barrel.find(my_loc)->second; 
                    double thisPhi = 3.1415926536*iphi/180.; //get phi from EBdetId
                    double dR = sqrt( pow(gen_eta-thisEta, 2) + pow(gen_phi-thisPhi, 2));
                    if( dR < MAX_DR ){
                        crystIDs.push_back(std::pair<DetId, float>(DetId((EBDetId(ieta,iphi)).rawId()), randFloat));
                    }
                }
            }
        }
    }

    for(int ix = 1; ix < 101; ix++){
        for(int iy = 1; iy < 101; iy++){
            if( ix != 0 ){
                int iz = 1;
                if(gen_eta < -1.479) iz = -1;
                EEDetId * thisDetId = new EEDetId(ix, iy, iz);
                if( EEDetId::validDetId(thisDetId->ix(), thisDetId->iy(), thisDetId->zside())){
                    float randFloat = 0.1;
                    double thisEta = ecal_map_endcap.find(std::tuple<int,int,int>(ix, iy, iz))->second; //get eta from EEDetId
                    double thisPhi = atan2((iy-50),(ix-50)); //get phi from EEDetId
                    double dR = sqrt( pow(gen_eta-thisEta, 2) + pow(gen_phi-thisPhi, 2));
                    if( dR < 0.8 ){
                        crystIDs.push_back(std::pair<DetId, float>(DetId((EEDetId(ix,iy,iz)).rawId()), randFloat));
                    }
                }
            }
        }
    }

	//now we need to get the PCaloHitContainer by DetId
	//first we loop over the crystals.
	std::set<uint32_t> recIDs;
	for(int i = 0; i < fabs(crystIDs.size()); i++){

		//if we have seen this crystal already, do not process it
		if( recIDs.find(crystIDs[i].first.rawId()) == recIDs.end()){
			recIDs.insert(crystIDs[i].first.rawId());

			//dont run past the end of the collection
			if( recHits.find(crystIDs[i].first.rawId()) != recHits.end()){
				//define the current crystal ID and its energy;
				currentId     = std::get<0>(crystIDs[i]).rawId();
				crystalHere   = *(recHits.find(currentId));
				crystalEnergy = crystalHere.energy();

				//a correction must be applied crystal by crystal
                for( int iii = 0; iii < apdBins; iii++){ updatedSimE[iii] = 0.;}
#ifdef LinearEnergy
                for( int iii = 0; iii < linearFcns; iii++){ linearSimE[iii] = 0.;}
#endif
                defaultSimE = 0.;

                //Now we loop over the PCaloHits
                int pcalo_count = 0;
                for(caloHitsItr = pCaloHits.begin(); caloHitsItr != pCaloHits.end(); caloHitsItr++){
                    //We only want PCaloHits in this super cluster
                    if(caloHitsItr->id() == currentId){
                        //Get the Depth of the PCaloHit and its corresponding bin
                        depthHere = (double)((caloHitsItr->depth())>>2)/NUM_XTAL_BINS; //16383 is 2^14 - 1
                        //sum up the weighted energy using functions
                       	if( depthHere == 0.) depthHere = 1./NUM_XTAL_BINS;
                       	if( depthHere == 1.) depthHere = 1 - 1./NUM_XTAL_BINS;
                        if(depthHere > 0. && depthHere < 1.){
                            //the following line calculates the energy with default LCE weights.
                            defaultSimE += caloHitsItr->energy();
                            for(int jjj = 0; jjj < apdBins; jjj++){
                                if( fabs(e.eta()) < 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EB[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                                else if( fabs(e.eta()) >= 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EE[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                            }// end for apdBins
                            pcalo_count++;
#ifdef LinearEnergy
                            linearSimE[0] += caloHitsItr->energy()*linear_A(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[1] += caloHitsItr->energy()*linear_B(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[2] += caloHitsItr->energy()*linear_C(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[3] += caloHitsItr->energy()*linear_D(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[4] += caloHitsItr->energy()*linear_E(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[5] += caloHitsItr->energy()*linear_F(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[6] += caloHitsItr->energy()*linear_G(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
                            linearSimE[7] += caloHitsItr->energy()*linear_H(depthHere)/myModels.LightCollectionEfficiencyDefault(depthHere);
#endif
                        }//end if energy is broken
                    }//end if currentId
                }// end for caloHits
				if(crystalEnergy > 0.07 && defaultSimE != 0. && pcalo_count > 50 ){// cut on noisy crystals
					for(int zzz = 0; zzz < apdBins; zzz++){
						retLCE[zzz] += updatedSimE[zzz]*crystalEnergy/defaultSimE;
#ifdef LinearEnergy
						if(zzz < linearFcns) retLinear[zzz] += linearSimE[zzz]*crystalEnergy/defaultSimE;
#endif
					}
                        totalCrystalEnergy += crystalEnergy;
				}// end if defaultSimE != 0
			}// end if not end of recHits
		}//end if crystal already in set
	}//end for crystals in supercluster
	*numSupClustCrystals = recIDs.size();
    *defaultEnergy = (float)totalCrystalEnergy;

	return;
};

void framework::corrected3x3Energy( reco::Photon e, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > recHits, const CaloTopology* topology, edm::PCaloHitContainer pCaloHits, double  (*weight)(double, double, double, double) , double ret3x3LCE [50], float * defaultEnergy, int * numSupClustCrystals){
	using namespace std;
    models myModels;
	//some variables
	double updatedSimE [50] = {0.};

	double defaultSimE = 0.;
	EcalRecHit crystalHere;
	double crystalEnergy;
	double depthHere;
	int apdBins = 50;
        double totalCrystalEnergy = 0.;

	uint32_t currentId;

	edm::PCaloHitContainer::const_iterator caloHitsItr;
	edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >::const_iterator recHitsItr;

	//get the super cluster and its hits and fractions collection
	reco::SuperClusterRef eSupClust = e.superCluster();
//	const std::vector< std::pair<DetId, float> > crystIDs = eSupClust->hitsAndFractions();

	std::vector<DetId> v_id = noZS::EcalClusterTools::matrixDetId(topology, e.superCluster()->seed()->seed().rawId(), -1, 1, -1, 1);
	//now we need to get the PCaloHitContainer by DetId
	//first we loop over the crystals.
	std::set<uint32_t> recIDs;
	for(int i = 0; i < fabs(v_id.size()); i++){

		//if we have seen this crystal already, do not process it
		if( recIDs.find(v_id[i].rawId()) == recIDs.end()){
			recIDs.insert(v_id[i].rawId());

			//dont run past the end of the collection
			if( recHits.find(v_id[i].rawId()) != recHits.end()){
				//define the current crystal ID and its energy;
				currentId     = v_id[i].rawId();
				crystalHere   = *(recHits.find(currentId));
				crystalEnergy = crystalHere.energy();

				//a correction must be applied crystal by crystal
                for( int iii = 0; iii < apdBins; iii++){ updatedSimE[iii] = 0.;}
                
		defaultSimE = 0.;

                //Now we loop over the PCaloHits
                for(caloHitsItr = pCaloHits.begin(); caloHitsItr != pCaloHits.end(); caloHitsItr++){

                    //We only want PCaloHits in this super cluster
                    if(caloHitsItr->id() == currentId){
                        //Get the Depth of the PCaloHit and its corresponding bin
                        depthHere = (double)((caloHitsItr->depth())>>2)/16383.; //16383 is 2^14 - 1
                        //sum up the weighted energy using functions
                       	if( depthHere == 0.) depthHere = 1./16384.;
                       	if( depthHere == 1.) depthHere = 1 - 1./16384.;
                        if(depthHere > 0. && depthHere < 1.){
                            //the following line calculates the energy with default LCE weights.
                            defaultSimE += caloHitsItr->energy();
                            for(int jjj = 0; jjj < apdBins; jjj++){
                                if( fabs(e.eta()) < 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EB[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                                else if( fabs(e.eta()) >= 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EE[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                            }// end for apdBins

                        }//end if energy is broken
                    }//end if currentId
                }// end for caloHits
				if(crystalEnergy > 0.07 && defaultSimE != 0.){// cut on noisy crystals
					for(int zzz = 0; zzz < apdBins; zzz++){
						ret3x3LCE[zzz] += updatedSimE[zzz]*crystalEnergy/defaultSimE;
					}
                        totalCrystalEnergy += crystalEnergy;
				}// end if defaultSimE != 0
			}// end if not end of recHits
		}//end if crystal already in set
	}//end for crystals in 3*3
	*numSupClustCrystals = recIDs.size();
        *defaultEnergy = (float)totalCrystalEnergy;

	return;
};

void framework::corrected3x3Energy( reco::GsfElectron e, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > recHits, const CaloTopology* topology, edm::PCaloHitContainer pCaloHits, double  (*weight)(double, double, double, double) , double ret3x3LCE [50], float * defaultEnergy, int * numSupClustCrystals){
	using namespace std;
    models myModels;
	//some variables
	double updatedSimE [50] = {0.};

	double defaultSimE = 0.;
	EcalRecHit crystalHere;
	double crystalEnergy;
	double depthHere;
	int apdBins = 50;
        double totalCrystalEnergy = 0.;

	uint32_t currentId;

	edm::PCaloHitContainer::const_iterator caloHitsItr;
	edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >::const_iterator recHitsItr;

	//get the super cluster and its hits and fractions collection
	reco::SuperClusterRef eSupClust = e.superCluster();
//	const std::vector< std::pair<DetId, float> > crystIDs = eSupClust->hitsAndFractions();

	std::vector<DetId> v_id = noZS::EcalClusterTools::matrixDetId(topology, e.superCluster()->seed()->seed().rawId(), -1, 1, -1, 1);
	//now we need to get the PCaloHitContainer by DetId
	//first we loop over the crystals.
	std::set<uint32_t> recIDs;
	for(int i = 0; i < fabs(v_id.size()); i++){

		//if we have seen this crystal already, do not process it
		if( recIDs.find(v_id[i].rawId()) == recIDs.end()){
			recIDs.insert(v_id[i].rawId());

			//dont run past the end of the collection
			if( recHits.find(v_id[i].rawId()) != recHits.end()){
				//define the current crystal ID and its energy;
				currentId     = v_id[i].rawId();
				crystalHere   = *(recHits.find(currentId));
				crystalEnergy = crystalHere.energy();

				//a correction must be applied crystal by crystal
                for( int iii = 0; iii < apdBins; iii++){ updatedSimE[iii] = 0.;}
                
		defaultSimE = 0.;

                //Now we loop over the PCaloHits
                for(caloHitsItr = pCaloHits.begin(); caloHitsItr != pCaloHits.end(); caloHitsItr++){

                    //We only want PCaloHits in this super cluster
                    if(caloHitsItr->id() == currentId){
                        //Get the Depth of the PCaloHit and its corresponding bin
                        depthHere = (double)((caloHitsItr->depth())>>2)/16383.; //16383 is 2^14 - 1
                        //sum up the weighted energy using functions
                       	if( depthHere == 0.) depthHere = 1./16384.;
                       	if( depthHere == 1.) depthHere = 1 - 1./16384.;
                        if(depthHere > 0. && depthHere < 1.){
                            //the following line calculates the energy with default LCE weights.
                            defaultSimE += caloHitsItr->energy();
                            for(int jjj = 0; jjj < apdBins; jjj++){
                                if( fabs(e.eta()) < 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EB[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                                else if( fabs(e.eta()) >= 1.497) updatedSimE[jjj] += caloHitsItr->energy()*weight(depthHere, e.eta(), ::RING_RESPONSE[jjj], ::RING_REWEIGHT_EE[jjj])/(myModels.LightCollectionEfficiencyDefault(depthHere));
                            }// end for apdBins

                        }//end if energy is broken
                    }//end if currentId
                }// end for caloHits
				if(crystalEnergy > 0.07 && defaultSimE != 0.){// cut on noisy crystals
					for(int zzz = 0; zzz < apdBins; zzz++){
						ret3x3LCE[zzz] += updatedSimE[zzz]*crystalEnergy/defaultSimE;
					}
                        totalCrystalEnergy += crystalEnergy;
				}// end if defaultSimE != 0
			}// end if not end of recHits
		}//end if crystal already in set
	}//end for crystals in 3*3
	*numSupClustCrystals = recIDs.size();
        *defaultEnergy = (float)totalCrystalEnergy;

	return;
};


int framework::getShowerMax( reco::Photon thisPhoton, edm::PCaloHitContainer pCaloHits){
	int ret = -999;
	edm::PCaloHitContainer::const_iterator hit;
	TH1D* showerShape = new TH1D("showerShape", "showerShape", 100, 0, 1);
	double energy;
	double depth;
	for(hit = pCaloHits.begin(); hit != pCaloHits.end(); hit++){
		if( hit->id() == thisPhoton.superCluster()->seed()->seed().rawId()){
			energy = hit->energy();
			depth = (double)((hit->depth())>>2)/NUM_XTAL_BINS;
			showerShape->Fill(depth, energy);
		}
	}
	ret = showerShape->GetMaximumBin();
	return ret;
};
int framework::getShowerMax( reco::GsfElectron thisElectron, edm::PCaloHitContainer pCaloHits){
	int ret = -999;
	edm::PCaloHitContainer::const_iterator hit;
	TH1D* showerShape = new TH1D("showerShape", "showerShape", 100, 0, 1);
	double energy;
	double depth;
	for(hit = pCaloHits.begin(); hit != pCaloHits.end(); hit++){
		if( hit->id() == thisElectron.superCluster()->seed()->seed().rawId()){
			energy = hit->energy();
			depth = (double)((hit->depth())>>2)/NUM_XTAL_BINS;
			showerShape->Fill(depth, energy);
		}
	}
	ret = showerShape->GetMaximumBin();
	return ret;
};
#endif
