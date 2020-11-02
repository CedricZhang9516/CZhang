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
#include <TProfile.h>
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
#include <TROOT.h>


#include "PhysConstant.h"

///////////////////////////////////////////////////////////////////////////
/*

This file contains some useful functions and setups for ROOT analysis

Author: Cedric Zhang

*/
///////////////////////////////////////////////////////////////////////////


#define name2str(name) (#name)

void CZhangNew(){}

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

void TGraphStyle2(TGraphErrors *g1, TString title = ""){

  g1->SetTitle(title.Data());
  g1->SetMarkerColor(1);//g1->SetMarkerColor(kRed);
  g1->SetLineColor(1);//g1->SetLineColor(kRed);
  g1->SetLineStyle(1);
  g1->SetLineWidth(2);
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(0.8);

  //g1->Draw("APL*");

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



/*
  g1->SetMarkerColor(kRed);
  g1->SetLineColor(kRed);
  g1->SetLineStyle(1);
  g1->SetLineWidth(1);
  g1->GetYaxis()->SetRangeUser(0,100);
  g1->Draw("APL*");
*/


}

void TProfileStyle(TProfile* gP, int c = 1, TString title = ""){

  //gP->Draw("APL*");
  gP->SetLineColor(c);
  //gP->SetMarkerStyle(20);
  //gP->SetMarkerSize(0.3);
  gP->SetMarkerColor(c);

  //gP->SetLineStyle(4);
  //gP->SetLineWidth(4);

  //gP->SetTitle("Polarization vs. DecayZ; DecayZ [mm]; Polarization");
  //gP->SetTitle(title.Data());
  gP->GetYaxis()->SetTitleOffset(0.58);
  gP->GetYaxis()->SetTitleSize(0.06);
  gP->GetXaxis()->SetTitleSize(0.06);
  gP->GetXaxis()->SetTitleOffset(0.8);



/*
  g1->SetMarkerColor(kRed);
  g1->SetLineColor(kRed);
  g1->SetLineStyle(1);
  g1->SetLineWidth(1);
  g1->GetYaxis()->SetRangeUser(0,100);
  g1->Draw("APL*");
*/


}


void TH1Style(TH1*h, TString title = "", int c = 1){

  //gP->Draw("APL*");
  //h->SetFillColor(c);
  //h->SetFillStyle(3001);
  h->SetLineColor(c);
  h->SetLineWidth(2);
  h->SetMarkerColor(1);
  h->SetMarkerSize(0.5);
  h->SetMarkerStyle(20);

  h->GetYaxis()->SetTitleOffset(0.58);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(0.8);

  h->SetTitle(title.Data());

}

void TH1Style1(TH1 *h, Int_t c = 1){
  h->SetFillColor(c);
  h->SetFillStyle(3003);
  //h->SetLineWidth(4);
  h->SetLineColor(c);
  //h->SetMarkerStyle(14);
  h->SetMarkerColor(1);
  h->SetMarkerSize(0.5);
  h->SetMarkerStyle(20);

  //h->SetTitleSize(3);
  //gStyle->SetTitleFontSize(0.08);

  h->GetXaxis()->SetNdivisions(505);
  h->GetYaxis()->SetTitleOffset(0.4);
  h->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(0.8);

/*
  h->GetYaxis()->SetTitleOffset(0.5);
  h->GetYaxis()->SetTitleSize(0.07);
  h->GetYaxis()->SetLabelSize(0.05);

  //h->GetXaxis()->SetTitleOffset(0.5);
  h->GetXaxis()->SetTitleOffset(0.7);
  h->GetXaxis()->SetTitleSize(0.065);
  h->GetXaxis()->SetLabelSize(0.05);
*/
}

void TH2Style(TH2*h, TString title = "", int c = 1){

  //gP->Draw("APL*");
  //h->SetFillColor(c);
  //h->SetFillStyle(3001);
  h->SetLineColor(c);
  h->SetMarkerColor(1);
  h->SetMarkerSize(0.5);
  h->SetMarkerStyle(20);

  h->GetYaxis()->SetTitleOffset(0.58);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(0.8);

  h->SetTitle(title.Data());

}



TH1F * TreeToTH1F(TTree* t, TString nameBranch,  int bin, double startX, double endX, TCut cut = "",
  TString Name = ""){

  //t->Draw("SpinX>>hspinx(1e3,-1,1)",Form("DecayZ<(%i+1) && DecayZ>%i",i,i),"");
  TString name = nameBranch;
  name.ReplaceAll("(","_");
  name.ReplaceAll(")","_");
  name.ReplaceAll("/","_");

  t->Draw(
    Form(" %s >> %s (%i,%f,%f) ", nameBranch.Data(), ("h_"+name).Data(),  bin, startX, endX),
    cut
    );

  //TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");
  TH1F * h = (TH1F*)gDirectory->Get(("h_"+name).Data());

  TH1Style(h,name.Data());

  if(Name == "")Name = nameBranch;
  h->SetName(Name.Data());

  //delete gDirectory->Get("c1");

  return h;

}


TH2F * TreeToTH2F(TTree* t, TString nameBranch,
  int binX, double startX, double endX,
  int binY, double startY, double endY,
  TCut cut = ""){

  //t->Draw("SpinX>>hspinx(1e3,-1,1)",Form("DecayZ<(%i+1) && DecayZ>%i",i,i),"");
  TString name = nameBranch;
  name.ReplaceAll("(","_");
  name.ReplaceAll(")","_");
  name.ReplaceAll("/","_");

  t->Draw(
    Form(" %s >> %s (%i,%f,%f,%i,%f,%f) ", nameBranch.Data(), ("h_"+name).Data(),
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

    //cout<<varX<<" "<<varY<<endl;
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


/*
void SetXTitleTreeDraw(const char * title){
  TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
  htemp->GetXaxis()->SetTitle(title);
  gPad->Update();
}
*/

#endif

