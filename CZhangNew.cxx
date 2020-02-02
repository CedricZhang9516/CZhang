
#include "CZhangNew.h"

///////////////////////////////////////////////////////////////////////////
/*

This file contains some useful functions and setups for ROOT analysis

Author: Cedric Zhang

*/
///////////////////////////////////////////////////////////////////////////





void CZhangNew_Tutorial(){

/* Default TGraph, THistrogram settings shoule be put here */




  TCanvas * c = NewTCanvas("c","c",1000,1000,1,4);

  TString name = "NameCanvasOrHistogram";
  SaveTCanvas(c,name); // save to .C and .png


  TString nameVar[3] = {"E","TOF","ErrTOF"};

  TTree * t = TxtToTree(
    "/Users/zhangce/WorkArea/Mu1S2S/DataHydroIon/ana-20191122-tof/Data_TOF.txt",
    nameVar,3,10);

  TGraph * g = TreeToTGraph(t,"E","TOF");
  c->cd(1);
  g->SetTitle("TOF vs. E; E [MeV];  TOF [us]");
  g->Draw("APL*");

  c->cd(2);
  TGraphErrors * g2 = TreeToTGraphErrors(t,"E","TOF","ErrTOF");
  g2->Draw("APL*");

  c->cd(3);
  TH1F * hTOF = TreeToTH1F(t,"TOF",100,0,50);
  hTOF->Draw("");

  c->cd(4);
  TH1F * hE = TreeToTH1F(t,"E",100,0,50);
  hE->Draw("");

  SaveTH1(hE,"E"); // save to .C and .png





}


void CZhangNew(){

  CZhangNew_Tutorial();

  //std::Vector<TH1F*> HistCollection;


}


