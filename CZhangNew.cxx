#ifndef _CZhang
#define _CZhang

#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include <TH1.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLatex.h>
#include <TList.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TGraph.h>


#include <PhysConstant.h>

///////////////////////////////////////////////////////////////////////////
/*

This file contains some useful functions and setups for ROOT analysis

Author: Cedric Zhang

*/
///////////////////////////////////////////////////////////////////////////

void CZhangNew(){

/* Default TGraph, THistrogram settings shoule be put here */
  //TCanvas * c = NewTCanvas("c","c",100,100,1,2);
  //c->cd(1);
  //c->SaveAs("test.png");
  cout<<"???"<<endl;

  TCanvas * c2 = new TCanvas("c2","c2",100,100)

}


TCanvas * NewTCanvas(string name, string title, int widthX, int widthY, int splitX, int splitY ){

  TCanvas * c = new TCanvas(name.data(),title.data(),widthX,widthY);
  c->Divide(splitX,splitY);
  return c;

}







#endif