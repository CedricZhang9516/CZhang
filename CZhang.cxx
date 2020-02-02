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

///////////////////////////////////////////////////////////////////////////
/*

This file contains some useful functions and setups for ROOT analysis

Author: Cedric Zhang

*/
///////////////////////////////////////////////////////////////////////////

void CZhang(){}
/*
void splitCanvas(){

  TCanvas *c1 = new TCanvas("c1","Example 2 pads (20,80)",200,10,300,500);

  TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0,21);
  //TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0,21);

  //pad1->Draw();
}


void ReplaceString(){
  TString dir = gSystem->UnixPathName(__FILE__);
  dir.ReplaceAll("h1draw.C","../hsimple.C");
  dir.ReplaceAll("/./","/");
}

//From $ROOTSYS/tutorials/hist/h1draw.C
//// 1-D histogram drawing options
*/


void CopyTree(){

  TFile *f = new TFile("Fuck0421_tree_30.root");
  TTree* t4 = (TTree*)f->Get("tree");

  TTree* t5 = t4->CopyTree("LaserX<30 && LaserX>-30");

  TFile *f2 = new TFile("newFuck0421_tree_30.root","recreate");

  f2->cd();
  t5->Write();
  f2->Close();

}


void SetStatus(int i = 0){

  gStyle->SetOptStat(i);
}

void SetStatus(TH1* htemp, int i = 0){

  htemp->SetStats(i);

}

void GeneralSetup(){

  gStyle->SetPalette();



}

void SetStyleHist1(TH2 *h, Int_t c = 1){
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



void SetStyleHist1(TH1 *h, Int_t c = 1){
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

void SetstyleHist1(TH1 *h, Int_t c = 1){
  h->SetFillColor(c);
  h->SetFillStyle(3003);
  //h->SetLineWidth(4);
  h->SetLineColor(c);
  //h->SetMarkerStyle(14);
  h->SetMarkerColor(1);
  h->SetMarkerSize(0.5);
  h->SetMarkerStyle(20);

  //h->SetTitleSize(3);
  gStyle->SetTitleFontSize(0.08);

  h->GetYaxis()->SetTitleOffset(0.5);
  h->GetYaxis()->SetTitleSize(0.07);
  h->GetYaxis()->SetLabelSize(0.05);

  //h->GetXaxis()->SetTitleOffset(0.5);
  h->GetXaxis()->SetTitleOffset(0.7);
  h->GetXaxis()->SetTitleSize(0.065);
  h->GetXaxis()->SetLabelSize(0.05);
}

void SetStyleHist2(TH2 *h, Int_t c = 1){

  gStyle->SetTitleFontSize(0.08);

  //h->SetTitleSize(2);

  h->GetYaxis()->SetTitleOffset(0.5);
  h->GetYaxis()->SetTitleSize(0.07);
  h->GetYaxis()->SetLabelSize(0.05);

  h->GetXaxis()->SetTitleOffset(0.7);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetLabelSize(0.05);
}

void FormatMC1(TH1 * mc1hist){
  mc1hist->SetLineColor(2);
  mc1hist->SetLineWidth(2);
}




void SetStyleGraph1(TGraph *g, Int_t c = 1){
    g->SetLineColor(c);
    g->SetLineStyle(4);
    g->SetLineWidth(4);
    g->SetMarkerColor(c);
    g->SetMarkerStyle(14);

}

void SetStyleGraph2(TGraph *g, Int_t c = 2){
    g->SetLineColor(c);
    g->SetLineStyle(4);
    g->SetLineWidth(4);
    g->SetMarkerColor(c);
    g->SetMarkerStyle(14);

}

void SetXTitleTreeDraw(const char * title){
  TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
  htemp->GetXaxis()->SetTitle(title);
  SetStyleHist1(htemp);
  gPad->Update();
}

void SetTitleTreeDraw(const char * title){
  TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
  htemp->SetTitle(title);
  //htemp->SetStats(0);
  SetStyleHist1(htemp);
  gPad->Update();
}

void SetStyleTreeDraw(){

  TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
  //SetStyleHist1(htemp);
  //htemp->SetTitle(title);
  htemp->SetLineColor(kBlack);
  htemp->SetFillColor(kBlack);
  gPad->Update();
}

void SetStyleTreeDraw(const char * h){

  TH1D *htemp = (TH1D*)gPad->GetPrimitive(h);
  //SetStyleHist1(htemp);
  //htemp->SetTitle(title);
  htemp->SetLineColor(kBlack);
  htemp->SetLineWidth(2);
  //htemp->SetFillColor(kBlack);
  gPad->Update();
}

void SetStyleTreeDraw(int i){

  TH1D *htemp = (TH1D*)gPad->GetPrimitive("htemp");
  //SetStyleHist1(htemp);
  //htemp->SetTitle(title);
  htemp->SetLineColor(i);
  gPad->Update();
}

//$ROOTSYS/tutorials/graphics/palettes.C
//// This macro draws all the high definition palettes available in ROOT.
/*

  TF2 *f2 = new TF2("f2","0.1+(1-(x-2)*(x-2))*(1-(y-2)*(y-2))",0.999,3.002,0.999,3.002);
  f2->SetContour(99);
  gStyle->SetPalette(p);

  TLatex *l = new TLatex(-0.8704441,0.9779387,Form("Palette #%d: %s #scale[0.7]{(#font[82]{k%s})}",p,n.Data(),num.Data()));
  l->SetTextFont(42);
  l->SetTextSize(0.035);
  l->Draw();
  c->Update();
  c->Print(Form("palette_%d.png",p));

  gROOT->SetBatch(1);


*/

std::vector<TH1F*> CreateVecH1F( const int Nhis, string name[], string title[], Int_t nbin[], Int_t xmin[], Int_t xmax[]){

  vector<TH1F*> H1F;

  for(int i = 0; i<Nhis; i++){
    TH1F *h = new TH1F(Form("%s",name[i].c_str()),Form("%s",title[i].c_str()),nbin[i],xmin[i],xmax[i]);
    H1F.push_back(h);
  }

  return H1F;

}

void copytree3()
{
   // Get old file, old tree and set top branch address
   TString dir = "$ROOTSYS/test/Event.root";
   gSystem->ExpandPathName(dir);
   const auto filename = gSystem->AccessPathName(dir) ? "./Event.root" : "$ROOTSYS/test/Event.root";

   TFile oldfile(filename);
   TTree *oldtree;
   oldfile.GetObject("T", oldtree);

   const auto nentries = oldtree->GetEntries();

   //Event *event = nullptr;
   //oldtree->SetBranchAddress("event", &event);

   // Create a new file + a clone of old tree in new file
   TFile newfile("small.root", "recreate");
   auto newtree = oldtree->CloneTree(0);

   for (auto i : ROOT::TSeqI(nentries)) {
      oldtree->GetEntry(i);
      //if (event->GetNtrack() > 605)
         newtree->Fill();
     // event->Clear();
   }

   newtree->Print();
   newfile.Write();
}

void copytree2()
{

   TString dir = "$ROOTSYS/test/Event.root";
   gSystem->ExpandPathName(dir);
   const auto filename = gSystem->AccessPathName(dir) ? "./Event.root" : "$ROOTSYS/test/Event.root";

   TFile oldfile(filename);
   TTree *oldtree;
   oldfile.GetObject("T", oldtree);

   // Activate only four of them
   for (auto activeBranchName : {"event", "fNtrack", "fNseg", "fH"}) {
      oldtree->SetBranchStatus(activeBranchName, 1);
   }

   // Create a new file + a clone of old tree header. Do not copy events
   TFile newfile("small.root", "recreate");
   auto newtree = oldtree->CloneTree(0);

   // Divert branch fH to a separate file and copy all events
   newtree->GetBranch("fH")->SetFile("small_fH.root");
   newtree->CopyEntries(oldtree);

   newtree->Print();
   newfile.Write();
}

int ColorSet[28]={1,
2,
3,
4,
//5,
6,
7,
8,
9,
14,
28,
30,
38,
40,
46,
49,
50,
51,
54,
59,
60,
61,
66,
69,
75,
79,
89,
99
};


#endif