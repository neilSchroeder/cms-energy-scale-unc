/*
 *
 *
 *
 *
 * This is the header file for models.
 * All LCE models for use in the FNUF Framework are listed here.
 *
 *
 *
 *
 *
 */

using namespace std;

class models{
    public:

        //default 
        double LightCollectionEfficiencyDefault( double z);

        //updated and Variations
        static double LightCollectionEfficiencyWeighted( double z, double eta, double apdPn, double scale);
        double updatedFBSM( double z, double eta);
        double updatedFBSMX( double z, double eta);
        double updatedFASM( double z, double eta);

        //2012 LCE and Variations
        double linear_A( double z); //+5% at the front face
        double linear_B( double z); //+2.5% at the front face
        double linear_C( double z); //2012 model 
        double linear_D( double z); //-5% at the front face
        double linear_E( double z); //-2% at the rear face
        double linear_F( double z); //flat
        double linear_G( double z); //+10% at the rear face
        double linear_H( double z); //-90% at the front face

};
