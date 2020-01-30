#include <iostream>
//#include <fstream>

void scan()
{

  Double_t        mgg;

  //open your root file
  TChain *chain = new TChain("gghh");
  chain->Add("/ihepbatch/besd11/dusx/root640/gghh/psipmc2001.root");
  //chain->Add("/ihepbatch/besd11/dusx/root640/gghh/psipmc2002.root");
  //chain->Add("/ihepbatch/besd11/dusx/root640/gghh/psipmc2003.root");
  //chain->Add("/ihepbatch/besd11/dusx/root640/gghh/psipmc2004.root");
  //chain->Add("/ihepbatch/besd11/dusx/root640/gghh/psipmc2005.root");

  chain->SetBranchAddress("mgg", &mgg);

  TFile *newfile = new TFile("topo_psip23pi.root","recreate");
  TTree *newtree = chain->CloneTree(0);

  Double_t xlow = 0.05;
  Double_t xup  = 0.7;
  Int_t nbin = 130;
  //TH1D *h100 = new TH1D("h100", "mass", nbin, xlow, xup);

  Long64_t nevent = chain->GetEntries();
  for(Long64_t j=0; j<nevent; j++ ) 
  {
    chain->GetEntry(j);
    //your cut condition
    if (mgg < xlow || mgg > xup) continue;

    //h100->Fill(mgg);

    newtree->Fill();
  }
   newtree->Write();
   newfile->Close();

  //h100->DrawCopy();
  //delete h100;
}
