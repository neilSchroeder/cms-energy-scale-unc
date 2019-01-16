// -*- C++ -*-
//
// Package:    ntupleGenerator/ntuples
// Class:      ntuples
// 
/**\class ntuples ntuples.cc ntupleGenerator/ntuples/plugins/ntuples.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Neil Schroeder
//         Created:  Thu, 06 Apr 2017 20:13:06 GMT
//
//


// system include files
#include <memory>

// user include files
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

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

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

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

//#define Debug

auto thisModel = models::LightCollectionEfficiencyWeighted;

class ntuples : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
    public:
        explicit ntuples(const edm::ParameterSet&);
        ~ntuples();

        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


    private:
        virtual void beginJob() override;
        virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
        virtual void endJob() override;

        // ----------member data ---------------------------

        //Ttree data members
        float_t R9 [2];
        float_t full5x5_R9 [2];
        float_t energyR [2];
        float_t eta [2];
        float_t etaSC [2];
        float_t phi [2];
        float_t energyG [2];
        float_t etaS [2];
        float_t phiS [2];
        float_t rawSuperClusterEnergy [2];
        float_t def_nomiRecHitSum [2];
        double apd_lce_RecHitSums1 [100];
        double apd_lce_RecHitSums2 [100];
        double linearEnergies1 [8];
        double linearEnergies2 [8];
        float_t dr [2];
        float_t seedCrystalRatio [2];
        int showerMaxBin [2];
        int supClustCrystals [2];
        Long64_t run, event, lum;

        //TTree
        TTree* data;

        //particle IDs
        int motherID;
        int daughterID;
        bool photons;

        //Handles and tokens
        edm::Handle<edm::View<reco::GenParticle> > particle;
        edm::EDGetTokenT<edm::View< reco::GenParticle > > particleToken;
        edm::Handle<edm::View<PileupSummaryInfo> > PupInfo;
        edm::EDGetTokenT<edm::View<PileupSummaryInfo> > PupInfoToken;
        edm::Handle<edm::View<reco::Photon> > photonHandle;
        edm::EDGetTokenT<edm::View<reco::Photon> > photonToken;
        edm::Handle<edm::View<reco::GsfElectron> > electronHandle;
        edm::EDGetTokenT<edm::View<reco::GsfElectron> > electronToken;
        edm::Handle<edm::PCaloHitContainer> pCaloHits_EB_Handle;
        edm::EDGetTokenT<edm::PCaloHitContainer> pCaloHits_EB_Token;
        edm::Handle<edm::PCaloHitContainer> pCaloHits_EE_Handle;
        edm::EDGetTokenT<edm::PCaloHitContainer> pCaloHits_EE_Token;
        //		edm::EDGetTokenT<edm::ValueMap<bool> > eleTightIdMapToken_;
        edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHit_EB_Handle;
        edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHit_EB_Token;
        edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHit_EE_Handle;
        edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHit_EE_Token;
};

//
// constants, enums and typedefs
//TH1D* runSumEnergies[10];
//
// static data member definitions
//
//std::vector<uint32_t> detIds;
//
// constructors and destructor
//
ntuples::ntuples(const edm::ParameterSet& iConfig):
    motherID(iConfig.getParameter<int>("motherID")),
    daughterID(iConfig.getParameter<int>("daughterID")),
    photons(iConfig.getParameter<bool>("photons"))
{
    //now do what ever initialization is needed

    usesResource("TFileService");
    edm::Service<TFileService> fs;

    data = fs->make<TTree>("data", "Matched Pair Data");
    data->Branch("RECO_Energy", energyR, "energyR[2]/F");
    data->Branch("Super_Cluster_Raw_Energy", rawSuperClusterEnergy, "rawSuperClusterEnergy[2]/F");
    data->Branch("Rechit_Energy_Sum_1", def_nomiRecHitSum, "def_nomiRecHitSum[2]/F");
    data->Branch("apd_lce_RecHitSums1", apd_lce_RecHitSums1, "apd_lce_RecHitSums1[100]/D");
    data->Branch("apd_lce_RecHitSums2", apd_lce_RecHitSums2, "apd_lce_RecHitSums2[100]/D");
#ifdef LinearEnergy
    data->Branch("Linear_Energies_1", linearEnergies1, "linearEnergies1[8]/D");
    data->Branch("Linear_Energies_2", linearEnergies2, "linearEnergies2[8]/D");
#endif
    data->Branch("Gen_Energy", energyG, "energyG[2]/F");
    data->Branch("R9", R9, "R9[2]/F");
    data->Branch("Full_5x5_R9", full5x5_R9, "full5x5_R9[2]/F");
    data->Branch("Reco_Eta", eta, "eta[2]/F");
    data->Branch("Super_Cluster_Eta", etaSC, "etaSC[2]/F");
    data->Branch("Gen_Eta", etaS, "etaS[2]/F");
    data->Branch("Reco_Phi", phi, "phi[2]/F");
    data->Branch("Gen_Phi", phiS, "phiS[2]/F");
    data->Branch("dR", dr, "dr[2]/F");
    data->Branch("Super_Cluster_Crystals", supClustCrystals, "supClustCrystals[2]/F");
    data->Branch("Shower_Max_Bin", showerMaxBin, "showerMaxBin[2]/I");
    data->Branch("run", &run);
    data->Branch("event", &event);
    data->Branch("lum", &lum);

    particleToken = consumes< edm::View < reco::GenParticle> >(edm::InputTag("genParticles"));
    photonToken   = consumes< edm::View < reco::Photon> >(edm::InputTag("gedPhotons"));
    electronToken = consumes< edm::View < reco::GsfElectron> >(edm::InputTag("gedGsfElectrons"));
    pCaloHits_EB_Token = consumes<edm::PCaloHitContainer>(edm::InputTag("g4SimHits", "EcalHitsEB", "HLT"));
    pCaloHits_EE_Token = consumes<edm::PCaloHitContainer>(edm::InputTag("g4SimHits", "EcalHitsEE", "HLT"));
    recHit_EB_Token   = consumes<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > >(edm::InputTag("reducedEcalRecHitsEB"));
    recHit_EE_Token   = consumes<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > >(edm::InputTag("reducedEcalRecHitsEE"));

    framework myFramework;
    myFramework.initializeGlobals();
}


ntuples::~ntuples()
{
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
    void
ntuples::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    run = iEvent.id().run();
    event = iEvent.id().event();
    lum = iEvent.id().luminosityBlock();

    iEvent.getByToken(particleToken, particle);         //GenParticles
    iEvent.getByToken(electronToken, electronHandle);   //GsfElectron
    iEvent.getByToken(photonToken, photonHandle);       //Photon
    iEvent.getByToken(pCaloHits_EB_Token, pCaloHits_EB_Handle); //PCaloHits EB
    iEvent.getByToken(pCaloHits_EE_Token, pCaloHits_EE_Handle); //PCaloHits EE
    iEvent.getByToken(recHit_EB_Token, recHit_EB_Handle);       //EcalRecHits EB
    iEvent.getByToken(recHit_EE_Token, recHit_EE_Handle);       //EcalRecHits EE



#ifdef CrossCheck
    edm::PCaloHitContainer::const_iterator caloHitsItr;
    for(caloHitsItr = pCaloHits_EB_Handle->begin(); caloHitsItr != pCaloHits_EB_Handle->end(); caloHitsItr++){
        int temp = caloHitsItr->depth();
        temp &= 0x0003;
        double depth = (double)(caloHitsItr->depth()>>2)/16383.;
        cout << "EB ==> temp flag: " << temp << " || depth: " << depth << " || energy: " << caloHitsItr->energy() << endl << endl;
    }	
    for(caloHitsItr = pCaloHits_EE_Handle->begin(); caloHitsItr != pCaloHits_EE_Handle->end(); caloHitsItr++){
        int temp = caloHitsItr->depth();
        temp &= 0x0003;
        double depth = (double)(caloHitsItr->depth()>>2)/16383.;
        cout << "EE ==> temp flag: " << temp << " || depth: " << depth << " || energy: " << caloHitsItr->energy() << endl << endl;
    }	
#endif


    //index of objects in GenParticles which correspond to the 2 daughter particles
    int lengthGenPair = 2;

    //set all of the tree variables to nonsense values in case they don't get assigned in this event
    for(int i = 0; i<2; i++){
        R9[i]          = -999;
        full5x5_R9[i]  = -999;
        energyG[i]     = -999;
        energyR[i]     = -999;
        rawSuperClusterEnergy[i] = -999;
        def_nomiRecHitSum[i]   = -999;
        eta[i]         = -999;
        etaSC[i]       = -999;
        phi[i]         = -999;
        etaS[i]        = -999;
        phiS[i]        = -999;
        dr[i]          = -999;
        supClustCrystals[i] = -999;
        showerMaxBin[i]= -999;
    }
    for( int i = 0; i < 100; i++){
        apd_lce_RecHitSums1[i] = 0;
        apd_lce_RecHitSums2[i] = 0;
#ifdef LinearEnergy
        if( i < 8){
            linearEnergies1[i] = 0;
            linearEnergies2[i] = 0;
        }
#endif
    }

    models myModels;
    framework myFramework;
    //for each of the GenParticle objects, find the first two which are daughter of higgs or Z
    //this nonsense needs to be redone
    std::vector<reco::GenParticle> genPair;
    for (auto &p : *particle){
        if( abs(p.pdgId()) == daughterID ){ 
            //			if( p.mother(0)->pdgId() == motherID ){ // this line makes sure the GenParticles are not the same
            const reco::GenParticle* p_temp = dynamic_cast<const reco::GenParticle*>(&p);
            while(p_temp->status() != 1){
                p_temp = dynamic_cast<const reco::GenParticle*>(p_temp->daughter(0));
            }
            genPair.push_back(*p_temp); 
            //			}// end mother ID check
        }// end daughter ID check
    }//end for particle

    //fill some quantities for the GenParticle
    for(int i = 0; i < 2; i++){
        energyG[i]  = genPair[i].energy();
        etaS[i]     = genPair[i].eta();
        phiS[i]     = genPair[i].phi();
    }

    //dr of closest RecoCandidate to GenParticle
    float mindr [2] = {999, 999}; 

    //this is the index of the RecoCandidates to be used with recoPairPointer
    int index [2] = {-1, -1}; 

    //for each of the GenParticle objects, find the closest RecoCandidate.
    float tempDr;
    for(int i = 0; i < lengthGenPair; i++){
        int count = 0;
        if(photons){
            for (auto &g : *photonHandle){
                tempDr = deltaR(g, genPair[i]);
                if( tempDr < mindr[i] ){
                    index[i] = count;
                    mindr[i] = tempDr;
                }//end if smaller dr
                count++;
            }//end for 
        }
        else{
            for (auto &g : *electronHandle){
                tempDr = deltaR(g, genPair[i]);
                if( tempDr < mindr[i] && index[0] != count ){
                    index[i] = count;
                    mindr[i] = tempDr;
                }//end if smaller dr
                count++;
            }//end for 
        }
    }//end for each GenParticle of pair

    //if the above loop returns both of the particles look for a different one
    if( index[0] == index[1]){
        int redo;
        int noredo;
        if( mindr[0] < mindr[1]){ redo = 1; noredo = 0;	}//end if mindr
        else{ redo = 0; noredo = 1; }

        mindr[redo] = 999;
        index[redo] = -1;

        int count = 0;
        if(photons && fabs(photonHandle->size()) > 1){
            for (auto &g : *photonHandle){
                tempDr = deltaR(g, genPair[redo]);
                if( tempDr < mindr[redo] && index[noredo] != count ){
                    index[redo] = count;
                    mindr[redo] = tempDr;
                }//end if smaller dr
                count++;
            }//end for 
        }//end if photon
        else if (!photons && fabs(electronHandle->size()) > 1){
            for (auto &g : *electronHandle){
                tempDr = deltaR(g, genPair[redo]);
                if( tempDr < mindr[redo] && index[noredo] != count ){
                    index[redo] = count;
                    mindr[redo] = tempDr;
                }//end if smaller dr
                count++;
            }//end for 
        }//else
    }//end if index

    for(int i = 0; i < 2; i++){dr[i] = mindr[i];}

    //fill quantities
    edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > >  thisRecHitHandle = recHit_EB_Handle;
    edm::Handle<edm::PCaloHitContainer>  thisPCaloHitsHandle = pCaloHits_EB_Handle;
    if(photons){
        for(int i = 0; i < 2; i++){
            if( index[i] != -1){ 
                if( fabs((*photonHandle)[index[i]].eta()) > 1.479){
                    thisRecHitHandle = recHit_EE_Handle;
                    thisPCaloHitsHandle = pCaloHits_EE_Handle;
                }
                //Set the various tree quantities for the RECO object
                if(i == 0)myFramework.correctedEnergy((*photonHandle)[index[i]], *thisRecHitHandle, *thisPCaloHitsHandle, thisModel, apd_lce_RecHitSums1, linearEnergies1, &(def_nomiRecHitSum[i]), &(supClustCrystals[i]));
                if(i == 1)myFramework.correctedEnergy((*photonHandle)[index[i]], *thisRecHitHandle, *thisPCaloHitsHandle, thisModel, apd_lce_RecHitSums2, linearEnergies2, &(def_nomiRecHitSum[i]), &(supClustCrystals[i]));
                rawSuperClusterEnergy[i]      = (*photonHandle)[index[i]].superCluster()->rawEnergy();
                energyR[i]                    = (*photonHandle)[index[i]].energy();
                eta[i]                        = (*photonHandle)[index[i]].eta();
                etaSC[i]                      = (*photonHandle)[index[i]].superCluster()->eta();
                phi[i]                        = (*photonHandle)[index[i]].phi();
                R9[i]                         = (*photonHandle)[index[i]].r9();
                full5x5_R9[i]                 = (*photonHandle)[index[i]].full5x5_r9();
                showerMaxBin[i]               = myFramework.getShowerMax((*photonHandle)[index[i]], *thisPCaloHitsHandle);
            }// end if index[0]
        }//end for photons
    }//end if photons
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else{
        //ELECTRON 1
        for(int i = 0; i < 2; i++){

            if( index[i] != -1){ 
                if( fabs((*electronHandle)[index[i]].eta()) > 1.479){
                    thisRecHitHandle = recHit_EE_Handle;
                    thisPCaloHitsHandle = pCaloHits_EE_Handle;
                }
                //Set the various tree quantities for the RECO object
                if(i == 0) myFramework.correctedEnergy((*electronHandle)[index[i]], *thisRecHitHandle, *thisPCaloHitsHandle, thisModel, apd_lce_RecHitSums1, linearEnergies1, &(def_nomiRecHitSum[i]), &(supClustCrystals[i]));
                if(i == 1) myFramework.correctedEnergy((*electronHandle)[index[i]], *thisRecHitHandle, *thisPCaloHitsHandle, thisModel, apd_lce_RecHitSums2, linearEnergies2, &(def_nomiRecHitSum[i]), &(supClustCrystals[i]));
                energyR[i]                    = (*electronHandle)[index[i]].correctedEcalEnergy();
                rawSuperClusterEnergy[i]      = (*electronHandle)[index[i]].superCluster()->rawEnergy();
                eta[i]                        = (*electronHandle)[index[i]].eta();
                etaSC[i]                      = (*electronHandle)[index[i]].superCluster()->eta();
                phi[i]                        = (*electronHandle)[index[i]].phi();
                R9[i]                         = (*electronHandle)[index[i]].r9();
                full5x5_R9[i]                 = (*electronHandle)[index[i]].full5x5_r9();
                showerMaxBin[i]               = myFramework.getShowerMax((*electronHandle)[index[i]], *thisPCaloHitsHandle);
            }// end if index[0]
        }//end for electrons
    }//end if electrons

    //fill the tree
    data->Fill();


#ifdef THIS_IS_AN_EVENT_EXAMPLE
    Handle<ExampleData> pIn;
    iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
    ESHandle<SetupData> pSetup;
    iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
    void 
ntuples::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
    void 
ntuples::endJob() 
{
    //things to do at endtime go here
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ntuples::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ntuples);
