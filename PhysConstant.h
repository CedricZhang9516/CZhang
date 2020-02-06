#ifndef __PHYSCONSTANT_H__
#define __PHYSCONSTANT_H__


#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TMath.h>

using namespace std;


//static const double TSW = 2.5;//sampling width 2.5 nsec
//static const double TSW = 1.0;
static const double TSW = 4.0;//sampling width: 4.0 nsec, after 2014/12/8

static const int    NTS = 4096*2;//number of time sampling
//static const int    NTS = 2048*2;//number of time sampling

//double light = 299792458; // m/s
//double massMu = 106.16/light/light; // MeV/c2

//static const double T0  = 0;
//static const string rawtree = "rawtree";
//#define NCH_V1720 8

#endif
