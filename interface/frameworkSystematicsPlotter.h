#include "TH1.h"
#include "TH2.h"
#include <vector>


class mySystematicsPlotter{

    public:
        void produce_FNUF_Plots(std::string);
        void produce_Ratio_Plots(std::string, std::string);
        void produce_RatioLookUpTables(std::string, std::string);
        void plot_LookUpTable( TH2F*, std::string, double, double, double, double);
        void produce_2016_2017_Plots(std::string);
        void plot_2016( TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, std::string, std::string, double, double);
        void plot_2017( TH1F*, TH1F*, TH1F*, TH1F*, TH1F*, std::string, std::string, double, double);
};
