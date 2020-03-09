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
#include <TH2F.h>
#include <TTree.h>
#include <TF1.h>
#include <TCut.h>
#include <TFile.h>
#include <TSystem.h>
#include <TVector3.h>
#include <TRandom.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TList.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TGraph.h>


#include "PhysConstant.h"
#include "PhysConstant.h"

///////////////////////////////////////////////////////////////////////////
/*

This file contains some useful functions and setups for ROOT analysis

Author: Cedric Zhang

*/
///////////////////////////////////////////////////////////////////////////


#define name2str(name) (#name)


TCanvas * NewTCanvas(TString name, TString title, int widthX, int widthY, int splitX = 1, int splitY = 1 ){

  TCanvas * c = new TCanvas(name.Data(),title.Data(),widthX,widthY);
  c->Divide(splitX,splitY);
  return c;

}


void SaveTCanvas(TCanvas* c, TString name, TString path = "./"){

  name.Append(".C");
  c->SaveAs( (path+name).Data() );

  name.ReplaceAll(".C",".png");
  c->SaveAs( (path+name).Data() );

  name.ReplaceAll(".png",".root");
  c->SaveAs( (path+name).Data() );

}


void SaveTH1(TH1* c, TString name, TString path = "./"){

  name.Append(".C");
  c->SaveAs( (path+name).Data() );

  name.ReplaceAll(".C",".png");
  c->SaveAs( (path+name).Data() );

}

void SaveTH2(TH2* c, TString name, TString path = "./"){

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

  gP->SetLineStyle(4);
  gP->SetLineWidth(4);

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
  TString name = nameBranch;
  name.ReplaceAll("(","_");
  name.ReplaceAll(")","_");

  t->Draw(
    Form(" %s >> %s (%i,%i,%i) ", nameBranch.Data(), ("h_"+name).Data(),  bin, startX, endX),
    cut
    );

  //TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");
  TH1F * h = (TH1F*)gDirectory->Get(("h_"+name).Data());

  TH1Style(h,name.Data());

  //delete gDirectory->Get("c1");

  return h;

}


TH2F * TreeToTH2F(TTree* t, TString nameBranch,
  int binX, int startX, int endX,
  int binY, int startY, int endY,
  TCut cut = ""){

  //t->Draw("SpinX>>hspinx(1e3,-1,1)",Form("DecayZ<(%i+1) && DecayZ>%i",i,i),"");
  TString name = nameBranch;
  name.ReplaceAll("(","_");
  name.ReplaceAll(")","_");

  t->Draw(
    Form(" %s >> %s (%i,%i,%i,%i,%i,%i) ", nameBranch.Data(), ("h_"+name).Data(),
      binX, startX, endX,
      binY, startY, endY),
      cut);

  //TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");

  TH2F * h = (TH2F*)gDirectory->Get(("h_"+name).Data());

  TH2Style(h,name.Data());

  //delete gDirectory->Get("c1");

  return h;

}


/*
////// 3D is not suported in ROOT, see https://root.cern.ch/doc/master/classTTree.html#a8a2b55624f48451d7ab0fc3c70bfe8d7

TH3F * TreeToTH3F(TTree* t, TString nameBranch,
  int binX, int startX, int endX,
  int binY, int startY, int endY,
  int binZ, int startZ, int endZ,
  TCut cut = ""){

  //t->Draw("SpinX>>hspinx(1e3,-1,1)",Form("DecayZ<(%i+1) && DecayZ>%i",i,i),"");

  t->Draw(
    Form(" %s >> %s (%i,%i,%i,%i,%i,%i,%i,%i,%i) ", nameBranch.Data(), ("h_"+nameBranch).Data(),
      binX, startX, endX,
      binY, startY, endY,
      binZ, startZ, endZ),
      cut);

  //TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");
  TH3F * h = (TH3F*)gDirectory->Get(("h_"+nameBranch).Data());

  TH3Style(h,nameBranch.Data());

  return h;

}
*/


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
    //cout<<var[Nvar-1]<<endl;

  }

  return t;

}



/////// STILL ON WORKING

void DrawTLegend(TH1F* h1,TH1F* h2,TH1F* h3){

  TLegend * l = new TLegend(0.4,0.6,0.8,0.8);
  l->AddEntry(h1,"signal region","L");
  l->AddEntry(h2,"first region","L");
  l->AddEntry(h3,"last region","L");
  l->Draw();

}

void SetOptStat(TString option = "mr"){

  //gStyle->SetOptStat("mr");
  gStyle->SetOptStat(option.Data());
  //gStyle->SetOptStat("mr");

  //SetOptStat("0000");

}

//////////////////////////

/*

https://root.cern.ch/doc/master/classTStyle.html
https://root.cern.ch/doc/master/classTPaveStats.html
https://root.cern.ch/doc/master/classTStyle.html#a0ae6f6044b6d7a32756d7e98bb210d6c

The type of information printed in the histogram statistics box can be selected via the parameter mode.

The parameter mode can be = ksiourmen

k = 1; kurtosis printed
k = 2; kurtosis and kurtosis error printed
s = 1; skewness printed
s = 2; skewness and skewness error printed
i = 1; integral of bins printed
i = 2; integral of bins with option "width" printed
o = 1; number of overflows printed
u = 1; number of underflows printed
r = 1; rms printed
r = 2; rms and rms error printed
m = 1; mean value printed
m = 2; mean and mean error values printed
e = 1; number of entries printed
n = 1; name of histogram is printed
Example: gStyle->SetOptStat(11); print only name of histogram and number of entries. gStyle->SetOptStat(1101); displays the name of histogram, mean value and RMS.

Notes:
never call SetOptStat(000111); but SetOptStat(1111), 0001111 will be taken as an octal number !!
SetOptStat(1) is s shortcut allowing to set the most common case, and is taken as SetOptStat(1111) (for backward compatibility with older versions. If you want to print only the name of the histogram call SetOptStat(1000000001).
that in case of 2-D histograms, when selecting just underflow (10000) or overflow (100000), the stats box will show all combinations of underflow/overflows and not just one single number!

*/

//////////////////////////

void SetPalette(int N = 55){

  gStyle->SetPalette(55);// kRainBow, tranditional
  //gStyle->SetPalette(56);// kInvertedDarkBodyRadiator, 0 is white
  //gStyle->SetPalette(57);// kBird, default

  // See: https://root.cern.ch/doc/master/classTColor.html#C05

}

void ProcessLineInRoot(){
  gROOT->ProcessLine("new TBrowser");
}

void UpdateTCanvasOline(){


  TH2D * hXY2D = new TH2D("hXY2D","hXY2D",100,2,3,100,2,3);

  TCanvas * c = NewTCanvas("c","c",1000,1000,2,3);
  c->cd(1);

  while(true){

    hXY2D->FillRandom("x*x+y*y",1000);
    hXY2D->Draw("colz");
    c->Modified();
    c->Update();
    //c_intrnl->SaveAs(Form("./png/%i.png",i));
    gSystem->ProcessEvents();
    gSystem->Sleep(100);
    //if (gSystem->ProcessEvents()) break;
  }


  /// SEE https://root-forum.cern.ch/t/online-histogram-update-through-macro/17819/1
  /////// https://root.cern.ch/graphics-pad


}

void ResetROOT(){
  gROOT->Reset();
  //Resetting the interpreter (erasing variables etc):

}

void SetRootSaveDirectory(){

  ///////////// How to save the file in the typical directory
  TCanvas * c = new TCanvas();
  TH2F * hZY2D;
  TString filename = "TestRootFile";
  gROOT->ProcessLine(Form(".!mkdir %s",filename.Data()));
  SaveTCanvas(c,(filename+"/"+hZY2D->GetName()).Data());

  //IF necessary:
  //filename.ReplaceAll(".dat.txt","");
  //SaveTCanvas(c,(filename+"/"+filename).Data());

}
#endif

