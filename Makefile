CFLAGS = -pthread -m64 -Wno-deprecated -lboost_program_options
CFLAGS += $(shell root-config --cflags --libs)
HERE = $(shell pwd)

all: Check 

Check: src/producer_PhotonSystematics.cc
	g++ ${CFLAGS} -o src/producer_PhotonSystematics ./src/producer_PhotonSystematics.cc ${HERE}/src/frameworkHistogramProducer.cc ${HERE}/src/frameworkLUTproducer.cc ${HERE}/src/frameworkSystematicsPlotter.cc
