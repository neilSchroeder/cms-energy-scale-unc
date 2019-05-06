#include "TH1.h"
#include "TH2.h"
#include <vector>


class myHistogramProducer{

    public:
        void produce_FNUF_Histograms( std::string, std::string, std::string, std::string);
        void produce_PION_Histograms( std::string, std::string, std::string, std::string);
};
