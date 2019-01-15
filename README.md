# CMS: Systematic Uncertainty on the Photon Energy Scale

Code for obtaining the systematic uncertainty on the photon energy scale using the method outlined in AN-18-079.

 This documentation contains the following:

 1) An analyzer containing a framework which will produce the ntuples required to produce the systematic uncertainty on the photon energy scale.
 2) A set of files which will produce the relevant plots and text files containing the systematic uncertainties on the photon energy scale from the root files produced by the analyzer mentioned in 1.

 This documentation does not contain:
 1) The edits to the CMSSW code which will store the energy deposits at every depth location within a crystal, although this should now be an option that can just be turned on.
 2) The particle gun code which describes the fixed pt particle gun specifications


## Getting Started


### Prerequisites

You will also need a set of root files which contain the folowing features:
 1) Electron and photon particle gun samples. To reproduce results from AN-18-079 the particle gun samples should be produced with fixed Pt at 60 GeV.
 2) Produced in the range of 0 < |eta| < 2.5, flat probability
 3) Stored information of PCaloHit depths


### Installing


From your preference of work area, run the following commands:

    cmsrel CMSSW_8_0_26_patch1
    cd CMSSW_8_0_26_patch1/src/
    cmsenv
    git cms-init
    git clone git@github.com:neilSchroeder/cms-photon-energy-scale-unc.git photonEnScaleUnc
    cd photonEnScaleUnc
    scram b -j 4
    make

## Running the Ntuplizer

The ntuplizer used to produce the necessary trees is included in this repository. Simply submit your particle gun samples, with PCaloHit depth information stored, to be analyzed using the edmAnalyzer provided. It is suggested to use some kind of batch submission as the analyzer can take some time to sort through all the sim hits.

## Running the Producer

Once the ntuples have been produced run the follwing command to generate a text file with a list of all the root files with their full path names, replacing myDirectory with the path to the directory where the root files are stored:

    ls -1 myElectronDirectory/*.root >> rootFilesElectronList.txt
    ls -1 myPhotonDirectory/*.root >> rootFilesPhotonList.txt

These text files will be supplied to the producer in order to make the histograms and plots of the systematic uncertainty on the photon energy scale.

### Arguments for src/producer_photonSystematics

When it comes time to run the producer there will be 4 arguments passed to the producer:
 1) --eleInputFile: this will be the file rootFilesElectronList.txt which you created earlier.
 2) --phoInputFile: this will be the file rootFilesPhotonList.txt which you created earlier.
 3) --rootFileOut: this is the name of the root file containing all the intermediary histograms. You may choose the name for this file. There is protection built into the framework on the off chance you do not include the ".root" at the end of the file name. If you forget to include it, do not interrupt the program as it will be able to handle this.
 4) --outDir: this is the name of the directory you wish to have everything written to. The name should be unique as it will be created along-side the folders in this repository.

You should now be ready to run the producer. It should be run from the photonEnScaleUnc/ folder and an example is given below:

```
   src/producer_PhotonSystematics --eleInputFile="rootFilesElectronList.txt" --phoInputFile="rootFilesPhotonList.txt" --rootFileOut="myOutputRootFile" --outDir="./my_results/" 
```

This will take on the order of 5 minutes to run depending mostly on how many root files you have chosen to loop over.

## Adding New Models

The instructions for this are in progress.
