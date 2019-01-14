#include "TH1.h"
#include "TH2.h"
#include <vector>


class mySystematicsProducer{

    public:
        void produce_LookUpTables(std::string);
        void plot_LookUpTable(TH2F*, std::string, double, double, double, double);
};
