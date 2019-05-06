#include "TH1.h"
#include "TH2.h"
#include <vector>


class myLookUpTableProducer{

    public:
        void produce_LookUpTables(std::string, bool);
        void produce_PionLookUpTables(std::string, bool);
        void plot_LookUpTable(TH2F*, std::string, double, double, double, double);
};
