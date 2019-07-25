CFLAGS = -pthread -m64 -Wno-deprecated -lboost_program_options
CFLAGS += $(shell root-config --cflags --libs)
HERE = $(shell pwd)

all: Check3

Check1: src/producer_PhotonSystematics.cc
	g++ ${CFLAGS} -o src/producer_PhotonSystematics ./src/producer_PhotonSystematics.cc ${HERE}/src/frameworkHistogramProducer.cc ${HERE}/src/frameworkLUTproducer.cc ${HERE}/src/frameworkSystematicsPlotter.cc
Check2: src/plot_RatioVsEt.cc
	g++ ${CFLAGS} -o src/plot_RatioVsEt ./src/plot_RatioVsEt.cc
Check3: src/producer_RatioSystematics.cc
	g++ ${CFLAGS} -o src/producer_RatioSystematics ./src/producer_RatioSystematics.cc ${HERE}/src/frameworkHistogramProducer.cc ${HERE}/src/frameworkLUTproducer.cc
