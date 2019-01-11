# CMS: Systematic Uncertainty on the Photon Energy Scale

 This documentation contains the following:

    1) An analyzer containing a framework which will produce the ntuples required to produce the systematic uncertainty on the photon energy scale.
    2) A set of files which will produce the relevant plots and text files containing the systematic uncertainties on the photon energy scale.

 This documentation does not contain:

    1) The edits to the CMSSW code which will store the energy deposits at every depth location within a crystal
    2) The particle gun code which describes the fixed pt particle gun specifications

## Geting Started

### Prerequisites

    This study is done on CMSSW_8_0_26_patch1.

    You will also need a set of root files which contain the folowing features:
        1) Produced in the range of 0 < |eta| < 2.5, flat probability
        2) Stored information of PCaloHit depths
        3) (optional, but necessary to reproduce results from AN-18-079) Electron and photon particle gun samples with fixed Pt at 60 GeV. With optional productions at 30, 45, and 120 GeV.

### Installing

## Running the Ntuplizer
    
    Condor was used as the batch submission program. The file condor_filelist.perl was used to submit the particle gun samples to condor for analysis. Please refer to condor_filelist_instructions.txt for how to use it, or if you're comfortable reading perl go explore it yourself. 
    
## Running the Producer

## Adding New Models
