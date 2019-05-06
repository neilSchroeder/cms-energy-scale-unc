import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

#set up process
process = cms.Process("ntuples")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

options = VarParsing.VarParsing('standard')


#print only every 10000th event
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#define variables
#options.register('InputFile', "", VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "File containing a list of the EXACT location of the AODs, AODSIMs, MINIAODs, MINIAODSIMs (no default provided)")
options.register('OutputFile', 
		"~/", #default value
		VarParsing.VarParsing.multiplicity.singleton, #single object or list
		VarParsing.VarParsing.varType.string, #variable type
		"File containing a list of the EXACT location of the output file  (default = ~/)")

options.register('MotherID',
		-1, #default value
		VarParsing.VarParsing.multiplicity.singleton, #single object or list
		VarParsing.VarParsing.varType.int, #variable type
		"PDG ID of the mother partice (default = -1)")

options.register('DaughterID',
		-1, #default value
		VarParsing.VarParsing.multiplicity.singleton, #single object or list
		VarParsing.VarParsing.varType.int, #variable type
		"PDG ID of the daughter partice (default = -1)")

options.register('recoPhotons',
		False, #default value
		VarParsing.VarParsing.multiplicity.singleton, #single object or list
		VarParsing.VarParsing.varType.int, #variable type
		"Your RECO objects are photons: True(1) or False(0)? (default 0)")

options.parseArguments()
print options

if options.recoPhotons == 1:
	photon = True
else:
	photon = False

#prepare input files
#with open(options.InputFile) as f:
 #       content = f.readlines()
#content = [x.strip() for x in content]
	
#content = ['file:' + item for item in content]

#feed in input files
process.source = cms.Source("PoolSource",
	    fileNames = cms.untracked.vstring(options.files)
	    )
# turn on VID producer, indicate data format  to be
#from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
#dataFormat = DataFormat.AOD
#switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
#my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff']

#add them to the VID producer
#for idmod in my_id_modules:
#    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#tell the process what variables and plug-in to use
process.ntuples = cms.EDAnalyzer('ntuples',
				 motherID = cms.int32(23), #cms.int32(options.MotherID),
				 daughterID = cms.int32(11), #cms.int32(options.DaughterID),
		#		 eleTightIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp80"),
				 photons = cms.bool(False),
                 pions = cms.bool(False))

#prepare the output file
options.OutputFile = 'file:' + options.OutputFile

#provide output file
process.TFileService = cms.Service("TFileService",
	            fileName = cms.string('file:myFile.root')
	    )


process.p = cms.Path(process.ntuples)

