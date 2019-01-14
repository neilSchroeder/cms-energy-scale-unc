#include "TH1.h"
#include "TH2.h"
#include "RtypesCore.h"

using namespace std;

struct errors {

    errors(Double_t y, Double_t e1, Double_t e2) : x(y), errLow(e1), errHigh(e2) {
    }

    errors() {
    }
    Double_t x;
    Double_t errLow;
    Double_t errHigh;
};

class quantiser {
public:
    static TH2F* D3toD2(TH3* threeD, UInt_t statistic = 1, UInt_t N = 100);

    static Double_t getHistStatistic(TH1D * hist, Int_t statistic = 1, UInt_t N = 100);

    static Double_t getHistStats(TH1D * hist, UInt_t N, Option_t* option = "");

    static Double_t getHistMedian(TH1D * hist, UInt_t N = 100, Option_t* option = "");

    static Double_t getHistMean(TH1D * hist, UInt_t N = 100, Option_t* option = "");

    static Double_t getHistRMS(TH1D * hist, UInt_t N = 100, Option_t* option = "");

    static Double_t getHistRMSD(TH1D * hist, Double_t av, UInt_t N = 100, Option_t* option = "");

    static Double_t getHistStdDev(TH1D * hist, UInt_t N = 100, Option_t* option = "");

    static Double_t getMedian(vector<Double_t> list);

    static Double_t getPercentile(vector<Double_t> list, Double_t P);

    static TH1D *getNpercentMinHist(TH1D *hist, UInt_t N = 100, Option_t* option = "");

    static TH1D* twoDtoXaverage(TH2 *h2, Int_t statistic = 1, UInt_t N = 100, Option_t* option = "");

    static TH1D* twoDtoXstdev(TH2 *h2, UInt_t N = 100, Option_t* option = "");

    static TGraphAsymmErrors* twoDtoXaverageWerrors(TH2 *h2, Int_t statistic = 1, UInt_t N = 100, Option_t* option = "", UInt_t Nresamples = 100, Double_t confidenceLevel = 95);

    //    static TGraphErrors* twoDtoXaverageWerrors(TH2 *h2, Int_t statistic = 1, UInt_t N= 100, Option_t* option = "", UInt_t Nresamples = 100, Double_t confidenceLevel = 95);

    static errors* getHistAverageWerrors(TH1D * hist, Int_t statistic = 1, UInt_t N = 100, Option_t* option = "", UInt_t Nresamples = 100, Double_t confidenceLevel = 95);

    static errors* getBoostrapMedWconfIntvl(vector<Double_t> sample, UInt_t Nresamples = 1000, Double_t confidenceLevel = 95);

    static errors* getBoostrapMedWconfIntvl(TH1D* hist, UInt_t Nresamples = 100, Double_t confidenceLevel = 95, UInt_t N = 100, Option_t* option = "");

    static errors* getHistMeanWerrors(TH1D * hist, UInt_t N = 100, Option_t* option = "");

    static errors* getBoostrapStddevWconfIntvl(TH1D* hist, UInt_t Nresamples, Double_t confidenceLevel, UInt_t N, Option_t* option);

    static void copyErrorsToDouble(vector<errors*> errorList, vector<Double_t> & vector, Int_t pos = 0);

    static TGraphAsymmErrors* buildGraph(vector<errors*> xCollection, vector<errors*>yCollection);
};
