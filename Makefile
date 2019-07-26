CFLAGS = -pthread -m64 -Wno-deprecated -lboost_program_options
CFLAGS += $(shell root-config --cflags --libs)
HERE = $(shell pwd)

all: Check1

Check1: src/producer_PhotonSystematics.cc
	g++ -o src/producer_PhotonSystematics ./src/producer_PhotonSystematics.cc ${HERE}/src/frameworkHistogramProducer.cc ${HERE}/src/frameworkLUTproducer.cc ${HERE}/src/frameworkSystematicsPlotter.cc ${CFLAGS} 
Check2: src/plot_RatioVsEt.cc
	g++ -o src/plot_RatioVsEt ./src/plot_RatioVsEt.cc ${CFLAGS} 
