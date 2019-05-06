/*
 *
 *
 *
 * Header file for the functions available in the FNUF framework
 *
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

class framework{
    public:

        void initializeGlobals();
        void correctedEnergy( reco::Photon, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >, edm::PCaloHitContainer, double (*weight)(double, double, double, double), double [], double [], float *, int *);
        void correctedEnergy( reco::GsfElectron, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >, edm::PCaloHitContainer, double (*weight)(double, double, double, double), double [], double [], float *, int *);
        void correctedEnergy( reco::GenParticle, edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >, edm::PCaloHitContainer, double (*weight)(double, double, double, double), double [], double [], float *, int *);
        int getShowerMax( reco::Photon, edm::PCaloHitContainer);
        int getShowerMax( reco::GsfElectron, edm::PCaloHitContainer);
};
