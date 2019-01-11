#ifndef MODELS
#define MODELS

/*
 *
 *
 *
 * This is the c++ file which defines the LCE models for use in the FNUF framework.
 *
 *
 *
 */
#include "models.h"
#include <cmath>
#include <iostream>

bool kFrontDown = false; //invert (over 1) before shower max
bool kFrontFlat = true;

double models::LightCollectionEfficiencyWeighted(double z, double eta, double apdPn, double scale)
{
    double showerMax_EB = 0.26; //defines the location of the LCE normalization in EB
    double showerMax_EE = 0.27; //defines the location of the LCE normalization in EE
	if(z<=0) return 0;
	if(z>=1) return 0;
	double crlength = 0.23;
	if( fabs(eta) > 1.479) crlength = 0.44;
	double mu_ind = -log(apdPn)/crlength; //0.177486932697 = -ln(APD/PN)/0.23, APD/PN = 0.96.
	double mu = mu_ind + 0.7 + 0.35;
	double lmu = log10(mu);

	double e0 =  6.91563e-02;
	double e1 =  1.64406e+00;
	double e2 =  6.42509e-01;
	double E =  e0/(1+exp(e1*(lmu-e2)));

	double d0 =  3.85334e-01;
	double d1 = -1.04647e-02;
	double D = d0*exp(d1*mu);

	double c0 =  3.77629e-01;
	double c1 = -3.23755e-01;
	double c2 =  1.50247e+00;
	double c3 =  3.03278e-01;
	double C =  -1 + c0*exp(c1*mu)*(1+c2*exp(c3*mu));

	double b0 = -3.33575e-01;
	double b1 =  4.44856e-01;
	double b2 =  1.91766e+00;
	double b3 =  2.69423e+00;
	double b4 =  1.06905e+00;
	double B =  (1/mu)*(b0 + b1*lmu + b2*pow(lmu,2)
			+ b3*pow(lmu,3) + b4*pow(lmu,4));

	double a0 = 7.18248e-02;
	double a1 = 1.89016e+00;
	double a2 = 2.15651e-02;
	double a3 = 2.30786e-02;
	double A =  exp(B*mu*0.015)*(a0/(exp(a1*(lmu+a2))+1)+a3);

	double R = 0.01*D*( 4/(0.222+E)/(0.222+E) - 1/((0.22*0.22)*(1.-z)*(z+E/0.22)) );

 // for undamaged crystal, mu0 = 0.7
	double A0 =  0.0631452;
	double B0 = -0.52267;
	double C0 = -0.139646;
	double D0 =  0.382522;
	double E0 =  0.054473;
	double R0 = 0.01*D0*( 4/(0.222+E0)/(0.222+E0) - 1/((0.22*0.22)*(1.-z)*(z+E0/0.22)) );


	double f =  A/A0 * exp(-(B*mu-B0*0.7)*0.22*(1.-z)) * (1+C*exp(R))/(1+C0*exp(R0));
	f = f/scale;
    if( kFrontDown ){
        if( z < showerMax_EB && eta < 1.479) f = 2 - f;
        if( z < showerMax_EE && eta > 1.479) f = 2 - f;
    }
    if( kFrontFlat ){
        if( z < showerMax_EB && eta < 1.479) f = 1;
        if( z < showerMax_EE && eta > 1.479) f = 1;
    }
	return f;
};

double models::LightCollectionEfficiencyDefault( double z ){
	double ret = 0;
	if( z >= 1 ) return ret;
	if( z <= 0 )  return ret;
	if( z > 0 && z < 0.56){
		ret = 1;
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 + ( (z-0.56) * 0.02 / 0.44);
	}
	if(ret == 0){
		std::cout<< "default weight 0" << std::endl;
	}
	return ret;
};
 

double models::linear_A( double z) //+5% at the front face
{
	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0) return ret;
	if( z >= 0 && z < 0.56){
		ret = 1.05 - (z * 0.05/0.56);
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 + ( (z-0.56) * 0.02/ 0.44);
	}
	return ret;
};

double models::linear_B( double z) //+2.5% at the front face
{
	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0) return ret;
	if( z >= 0 && z < 0.56){
		ret = 1.025 - (z * 0.025/0.56);
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 + ( (z-0.56) * 0.02/ 0.44);
	}
	return ret;
};

double models::linear_C( double z) //2012 model 
{
	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0) return ret;
	if( z >= 0 && z < 0.56){
		double b = 1 - 0.0014*0.8903*13;
		ret = b + z*23*0.0014*0.8903;
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 + ( (z-0.56) * 0.02/ 0.44);
	}
	return ret;
};

double models::linear_D( double z) //-5% at the front face
{
	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0) return ret;
	if( z >= 0 && z < 0.56){
		ret = 0.95 + ( z * 0.05 / 0.56);
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 + ( (z-0.56) * 0.02/0.44);
	}
	return ret;
};

double models::linear_E( double z) //-2% at the rear face
{
	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0) return ret;
	if( z >= 0 && z < 0.56){
		ret = 1.;
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 - ( (z-0.56) * 0.02/ 0.44);
	}
	return ret;
};

double models::linear_F( double z) //flat
{
	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0 ) return ret;
	ret = 1;
	return ret;
};

double models::linear_G( double z) //+10% at the rear face
{
	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0) return ret;
	if( z >= 0 && z < 0.56){
		ret = 1.;
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 - ( (z-0.56) * 0.025/ 0.44);
	}
	return ret;
};

double models::linear_H( double z) //-90% at the front face
{

	double ret = 0;
	if( z >= 1) return ret;
	if( z < 0) return ret;
	if( z >= 0 && z < 0.56){
		ret = 0.1 + (z * 0.9/0.56);
	}
	else if( z >= 0.56 && z < 1){
		ret = 1 + ( (z-0.56) * 0.02/ 0.44);
	}
	return ret;
};

#endif
