CFLAGS = -pthread -m64 -lstdc++fs -Wno-deprecated -lboost_program_options
CFLAGS += $(shell root-config --cflags --libs)

all: Check 

Check: src/producer_PhotonSystematics.cc
	g++ ${CFLAGS} -o src/producer_PhotonSystematics ./src/producer_PhotonSystematics.cc /home/schr1077/CMSSW_Sim/CMSSW_8_0_26_patch1/src/analyzer/src/frameworkHistogramProducer.cc /home/schr1077/CMSSW_Sim/CMSSW_8_0_26_patch1/src/analyzer/src/frameworkLUTproducer.cc /home/schr1077/CMSSW_Sim/CMSSW_8_0_26_patch1/src/analyzer/src/frameworkSystematicsPlotter.cc
