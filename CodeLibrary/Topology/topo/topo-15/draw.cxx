void draw(Char_t *treeName = "gghh")
{
  gROOT->SetStyle("BES");

  TFile *f  = TFile::Open("topo.root");
  TTree *T  = (TTree*)f->Get(treeName);
  TTree *TF  = (TTree*)f->Get("topo");
  TF->SetName("TF");
  T->AddFriend("TF");

  Double_t mab;
  Int_t signal;
  T->SetBranchAddress("mab",&mab);
  T->SetBranchAddress("signal",&signal);
  TF->SetBranchAddress("signal",&signal);

  Double_t xlow = 1.08;
  Double_t xup  = 1.15;
  Int_t nbins = 70;
  TH1F *hall = new TH1F("hall", "", nbins, xlow, xup);
  TH1F *hbkg = new TH1F("hbkg", "", nbins, xlow, xup);
  TH1F *hitp = new TH1F("hitp", "", nbins, xlow, xup);
  hall->SetLineColor(1);
  hall->SetXTitle("m(#gamma #gamma) (GeV/c^{2})");
  hall->SetYTitle("ENTRIES/(2 MeV/c^{2})");

  hbkg->SetLineColor(4);
  hbkg->SetLineWidth(0.4);

  TCut cut1 = "mab > 1.08 && mab < 1.15";
  TCut cut2 = "signal == 0";
  TCut cut3 = "itopo == 0 || itopo==1";
  TCanvas *c1 = new TCanvas("c1", "topology", 200, 10, 700, 500);  
  //c1->Divide(2,2);
  //c1->cd(1);
  T->Draw("mab>>hall", cut1, "e");
  T->Draw("mab>>hbkg", cut1 && cut2, "sames");
  //c1->cd(2);
  //hbkg->Draw();
  //c1->cd(3);
  //T->Draw("mab>>hitp", cut3);
}
