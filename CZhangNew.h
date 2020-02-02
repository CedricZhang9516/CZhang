#ifndef _CZhangNew
#define _CZhangNew

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


#include "PhysConstant.h"

///////////////////////////////////////////////////////////////////////////
/*

This file contains some useful functions and setups for ROOT analysis

Author: Cedric Zhang

*/
///////////////////////////////////////////////////////////////////////////


TCanvas * NewTCanvas(TString name, TString title, int widthX, int widthY, int splitX, int splitY ){

  TCanvas * c = new TCanvas(name.Data(),title.Data(),widthX,widthY);
  c->Divide(splitX,splitY);
  return c;

}


void SaveTCanvas(TCanvas* c, TString name, TString path = "./"){

  name.Append(".C");
  c->SaveAs( (path+name).Data() );

  name.ReplaceAll(".C",".png");
  c->SaveAs( (path+name).Data() );

}


void SaveTH1(TH1* c, TString name, TString path = "./"){

  name.Append(".C");
  c->SaveAs( (path+name).Data() );

  name.ReplaceAll(".C",".png");
  c->SaveAs( (path+name).Data() );

}



void TGraphStyle(TGraph* gP, TString title = ""){

  //gP->Draw("APL*");
  gP->SetLineColor(1);
  gP->SetMarkerStyle(20);
  gP->SetMarkerSize(0.3);
  gP->SetMarkerColor(1);

  //gP->SetTitle("Polarization vs. DecayZ; DecayZ [mm]; Polarization");
  gP->SetTitle(title.Data());
  gP->GetYaxis()->SetTitleOffset(0.58);
  gP->GetYaxis()->SetTitleSize(0.06);
  gP->GetXaxis()->SetTitleSize(0.06);
  gP->GetXaxis()->SetTitleOffset(0.8);

}


void TH1Style(TH1*h, TString title = "", int c = 1){

  //gP->Draw("APL*");
  h->SetFillColor(c);
  h->SetFillStyle(3001);
  h->SetLineColor(c);
  h->SetMarkerColor(1);
  h->SetMarkerSize(0.5);
  h->SetMarkerStyle(20);

  h->SetTitle(title.Data());

}


void TH2Style(TH2*h, TString title = "", int c = 1){

  //gP->Draw("APL*");
  h->SetFillColor(c);
  h->SetFillStyle(3001);
  h->SetLineColor(c);
  h->SetMarkerColor(1);
  h->SetMarkerSize(0.5);
  h->SetMarkerStyle(20);

  h->SetTitle(title.Data());

}

TH1F * TreeToTH1F(TTree* t, TString nameBranch,  int bin, int startX, int endX, TCut cut = ""){

  //t->Draw("SpinX>>hspinx(1e3,-1,1)",Form("DecayZ<(%i+1) && DecayZ>%i",i,i),"");

  t->Draw(
    Form(" %s >> %s (%i,%i,%i) ", nameBranch.Data(), ("h_"+nameBranch).Data(),  bin, startX, endX),
    cut
    );

  //TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");
  TH1F * h = (TH1F*)gDirectory->Get(("h_"+nameBranch).Data());

  TH1Style(h,nameBranch.Data());

  return h;

}


TH2F * TreeToTH2F(TTree* t, TString nameBranch,
  int binX, int startX, int endX,
  int binY, int startY, int endY,
  TCut cut = ""){

  //t->Draw("SpinX>>hspinx(1e3,-1,1)",Form("DecayZ<(%i+1) && DecayZ>%i",i,i),"");

  t->Draw(
    Form(" %s >> %s (%i,%i,%i,%i,%i,%i) ", nameBranch.Data(), ("h_"+nameBranch).Data(),
      binX, startX, endX,
      binY, startY, endY),
      cut);

  //TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");
  TH2F * h = (TH2F*)gDirectory->Get(("h_"+nameBranch).Data());

  TH2Style(h,nameBranch.Data());

  return h;

}

TGraph * TreeToTGraph(TTree* t, TString nameBranchX, TString nameBranchY, TString titleGraph =  ""){

  double varX, varY;

  t->SetBranchAddress(nameBranchX.Data(),&varX);
  t->SetBranchAddress(nameBranchY.Data(),&varY);

  TGraph * g  = new TGraph();
  g->SetTitle(titleGraph.Data());

  int N = t->GetEntries();

  for(int i = 0; i < N; i++){
    t->GetEntry(i);
    g->SetPoint(i,varX,varY);
  }

  TGraphStyle(g,nameBranchY.Data());

  return g;

}



TGraphErrors * TreeToTGraphErrors(TTree* t, TString nameBranchX, TString nameBranchY, TString nameBranchErrY, TString titleGraph =  ""){

  double varX, varY, varErrY;

  t->SetBranchAddress(nameBranchX.Data(),&varX);
  t->SetBranchAddress(nameBranchY.Data(),&varY);
  t->SetBranchAddress(nameBranchErrY.Data(),&varErrY);

  TGraphErrors * g  = new TGraphErrors();
  g->SetTitle(titleGraph.Data());

  int N = t->GetEntries();

  for(int i = 0; i < N; i++){
    t->GetEntry(i);
    g->SetPoint(i,varX,varY);
    g->SetPointError(i,0,varErrY);
  }

  TGraphStyle(g,nameBranchY.Data());

  return g;

}



TTree* TxtToTree(TString nameFile, TString nameVar[], const int Nvar, const int Nline){


  ifstream ReadTXT(nameFile.Data());//

  TTree *  t = new TTree("tree","tree");
  //tree->Branch("LaserY",&LaserY,"LaserY/D");
  Double_t  var[Nvar];
  for(int i = 0; i< Nvar; i++)t->Branch(nameVar[i].Data(),&var[i],Form("%s/D",nameVar[i].Data()) );

  for( int i = 0; i < Nline; i++ ){
    for(int j = 0; j <Nvar; j++)ReadTXT>>var[j];
    t->Fill();
  }

  return t;

}







#endif

