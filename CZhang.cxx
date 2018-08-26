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

#include <iostream>

void Setstyle(TH1D *g, int c){
	g->SetFillColor(c);
    g->SetFillStyle(3001);
    //g->SetLineWidth(4);
    g->SetLineColor(c);
    //g->SetMarkerStyle(14);
    g->SetMarkerColor(1);
   	g->SetMarkerSize(0.5);
    g->SetMarkerStyle(20);
}

void FormatMC1(TH1 * mc1hist){
  mc1hist->SetLineColor(2);
  mc1hist->SetLineWidth(2);
}