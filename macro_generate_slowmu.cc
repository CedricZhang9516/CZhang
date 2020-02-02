
const string pdffile = "pdf.root";
const string pdfname = "pdf";


void get_pdf(){
  const string filename = "dump_1_300000.root";
  TFile* fF = new TFile(filename.c_str(), "read");
  TTree* fT = fF->Get("tree");
  TFile* fFw = new TFile(pdffile.c_str(), "recreate");
  const int    xnbin = 40;
  const double xmin  = 0;
  const double xmax  = 10;
  const int    ynbin = 20;
  const double ymin  = 0;
  const double ymax  = 80;

  TH2F*  pdf = new TH2F(pdfname.c_str(),"",xnbin, xmin, xmax, ynbin, ymin, ymax);

  double ke, px, py, pz;
  fT -> SetBranchAddress("ke", &ke);
  fT -> SetBranchAddress("px", &px);
  fT -> SetBranchAddress("py", &py);
  fT -> SetBranchAddress("pz", &pz);

  for(int i=0; i<fT->GetEntries(); i++){
    fT -> GetEntry(i);
    if(ke*1000<10){
      pdf -> Fill(ke*1000, TMath::ATan(sqrt(px*px+py*py)/pz)/TMath::Pi()*180);
    }//if
  }//i
 
  //fT -> Draw("TMath::ATan(sqrt(px*px+py*py)/pz)/TMath::Pi()*180:ke*1000>>pdf","ke*1000<10");
  gStyle -> SetOptStat(0000);
  TCanvas* c1 = new TCanvas("c1","c1");
  pdf -> Draw("colz");
  c1 -> Update();
  cin.get();

  fFw -> cd();
  pdf -> Write();
  fFw -> Write();
  fFw -> Close();

}


void get_bgtof_pdf(){
  const string filename = "dump_1_300000.root";
  TFile* fF = new TFile(filename.c_str(), "read");
  TTree* fT = fF->Get("tree");
  TFile* fFw = new TFile("pdf_bg_tof.root", "recreate");
  const int    xnbin = 400;
  const double xmin  = 0;
  const double xmax  = 4000;
  const double mumass  = 105.658;
  const double dist  = 3.4;//distance from target to detector

  TH1F*  pdf = new TH1F(pdfname.c_str(),"", xnbin, xmin, xmax);

  double ke, px, py, pz;
  fT -> SetBranchAddress("ke", &ke);
  fT -> SetBranchAddress("px", &px);
  fT -> SetBranchAddress("py", &py);
  fT -> SetBranchAddress("pz", &pz);

  for(int i=0; i<fT->GetEntries(); i++){
    fT -> GetEntry(i);
    double p = sqrt(px*px+py*py+pz*pz);
    double v = p/mumass/sqrt(1.0+p*p/mumass/mumass)*0.2998;//m/nsec
    double t = dist/v;
    pdf -> Fill(t);

  }//i
  pdf -> Scale(5.3e-6/2.94e8);

  //fT -> Draw("TMath::ATan(sqrt(px*px+py*py)/pz)/TMath::Pi()*180:ke*1000>>pdf","ke*1000<10");
  gStyle -> SetOptStat(0000);
  TCanvas* c1 = new TCanvas("c1","c1");
  pdf -> Draw("");
  c1 -> Update();
  cin.get();

  fFw -> cd();
  pdf -> Write();
  fFw -> Write();
  fFw -> Close();

}

void get_bg_after_flight(){
  const string filename = "dump_1_300000.root";
  TFile* fF = new TFile(filename.c_str(), "read");
  TTree* fT = fF->Get("tree");
  TFile* fFw = new TFile("pdf_bg_after_flight.root", "recreate");
  const int    xnbin = 200;
  const double xmin  = -100;
  const double xmax  = 100;
  const int    ynbin = 200;
  const double ymin  = -100;
  const double ymax  = 100;
  const double mumass  = 105.658;
  const double dist  = 3.4;//distance from target to detector

  TH2F*  pdf = new TH2F(pdfname.c_str(),"", xnbin, xmin, xmax, ynbin, ymin, ymax);

  double ke, px, py, pz, x, y;
  fT -> SetBranchAddress("ke", &ke);
  fT -> SetBranchAddress("px", &px);
  fT -> SetBranchAddress("py", &py);
  fT -> SetBranchAddress("pz", &pz);
  fT -> SetBranchAddress("x", &x);
  fT -> SetBranchAddress("y", &y);

  int count = 0;
  for(int i=0; i<fT->GetEntries(); i++){
    fT -> GetEntry(i);
    double p   = sqrt(px*px+py*py+pz*pz);
    double gam = sqrt(mumass*mumass+p*p)/mumass;
    double vx = px/mumass/gam*0.2998; //m/nsec
    double vy = py/mumass/gam*0.2998;
    double vz = pz/mumass/gam*0.2998;

    //rfqin
    double t1  = 0.5/vz;
    double xp1 = x+vx*t1*1000;
    double yp1 = y+vy*t1*1000;
    double r1  = sqrt(xp1*xp1+yp1*yp1);

    //rfqout
    double t2  = 2.5/vz;
    double xp2 = x+vx*t2*1000;
    double yp2 = y+vy*t2*1000;
    double r2  = sqrt(xp2*xp2+yp2*yp2);


    //rfqout
    double t25  = 1.5/vz;
    double xp25 = x+vx*t25*1000;
    double yp25 = y+vy*t25*1000;
    double r25  = sqrt(xp25*xp25+yp25*yp25);

    //MCP
    double t3  = dist/vz;
    double xp3 = x+vx*t3*1000;
    double yp3 = y+vy*t3*1000;
    double r3  = sqrt(xp3*xp3+yp3*yp3);

    pdf -> Fill(xp3,yp3);
    if( r1<10&&r2<10&&r3<20&&r25<4)count++;

  }//i
  //pdf -> Scale(1.3e-6);
  cout << count << endl;
  //fT -> Draw("TMath::ATan(sqrt(px*px+py*py)/pz)/TMath::Pi()*180:ke*1000>>pdf","ke*1000<10");
  gStyle -> SetOptStat(0000);
  TCanvas* c1 = new TCanvas("c1","c1");
  pdf -> Draw("");
  c1 -> Update();
  cin.get();

  fFw -> cd();
  pdf -> Write();
  fFw -> Write();
  fFw -> Close();

}



//_______________________________________
//cm, mrad, cm, mrad, GeV/c, -1 -1 -1 -1
//target area x X y = 35 X 43 mm
//const double TX = 1.75; //170124, modified
//const double TX = 2.6;
const double TX = 2.15;

//const double TY = 2.00;//170124, modified
const double TY = 1.75;

const double sigmax = 2.0;
const double sigmay = 2.7;

//const int    Nevt = 1000000;
//const int    Nevt = 10000000;
//const int    Nevt = 1000000;
const int    Nevt = 1000000;

#define MUSRSIM
//#define PARMTEQM

#ifdef MUSRSIM
//const string output = "slowmu_rand_171024_e5.dat";
const string output = "slowmu_rand_171121_e6.dat";
//const string output = "slowmu_rand_acctest.dat";
//const string output = "slowmu_rand_v30.dat";
//const string output = "slowmu_500pm50eV_1e5.dat";
//const string output = "slowmu_run0552_2016B.dat";
//const string output = "slowmu_rand_acctest_mupbg.dat";
const double mmu  = 105.658e3;//keV
//const double KE_THR = 0.6;
const double KE_THR = 2.0;
//const double KE_THR = 1.0;:

#endif

#ifdef PARMTEQM
const string output = "input_rfq.txt";
const double mmu  = 106.427e3;//keV
#endif

void gen_slowmu(){
  TFile* fF = new TFile(pdffile.c_str(), "read");
  TH2F* pdf = (TH2F*)(fF->Get(pdfname.c_str()));
  pdf -> Smooth(1);
  pdf -> Smooth(2);

  //171107
#ifdef MUM1711
  string Q0 = "1.0-(-[3]*[3]+1.0+x*x/[4]/[4])/(2.0*x/[4])";
  string Qm = "1.0-(-[2]*[2]+1.0+x*x/[4]/[4])/(2.0*x/[4])";
  string Yds_ratio = Form("[0]*[1]*(%s)*(%s)/(1.0-%s)/(1.0-%s)", Q0.c_str(), Qm.c_str(), Q0.c_str(), Qm.c_str());
  TF1* f = new TF1("f",
		   //		   Form("(%s)*exp(([6]-[5])/(x/1.47e-3))",Yds_ratio.c_str()), 0.0001, 0.01);
		   Form("(%s)*exp(([6]-[5])/(x))",Yds_ratio.c_str()), 0.0001, 1);
		   //Form("(%s)*exp(([6]-[5])/(x/(1.47e-3)))",Yds_ratio.c_str()), 0.02*1.47e-3, 5.0*1.47e-3);
  f->SetParameter(0, 0.953);
  f->SetParameter(1, 0.029);
  f->SetParameter(2, 0.991);
  f->SetParameter(3, 0.989);
  f->SetParameter(4, 1.178);
  f->SetParameter(5, 0.284);
  f->SetParameter(6, 0.193);
  int nx = pdf->GetNbinsX();
  int ny = pdf->GetNbinsY();
  const double v0=7.4e-3;
  for(int iy=0; iy<ny+2; iy++){
    for(int ix=0; ix<nx+2; ix++){
      if(ix==0)continue;
      int bing = iy*(nx+2)+ix; 
      double r = pdf->GetBinContent(iy*(nx+2)+ix);
      double kel = 0.5*(ix-1);
      double keh = 0.5*(ix);
      double vl  = sqrt(2.0*mmu*kel+kel*kel)/(mmu+kel)/v0;
      double vh  = sqrt(2.0*mmu*keh+keh*keh)/(mmu+keh)/v0;
      double fl  = f->Eval(vl);
      double fh  = f->Eval(vh);
      double fm  = 0.5*(fl+fh);
      //cout << ix << "\t" << iy << "\t" << r << "\t" << fl << "\t"<<fh <<"\t"<<endl;
      pdf -> SetBinContent(bing, r*fm);
    }
  }
  
  //TCanvas* c1 = new TCanvas("c1","");
  //pdf->Draw("colz");
  //c1->Update();
  //cin.get(); 
  //return 1;
#endif



  gStyle -> SetOptStat(0000);
  TCanvas* c1 = new TCanvas("c1","c1");
  pdf -> SetNdivisions(606,"X");
  pdf -> SetNdivisions(606,"Y");
  pdf -> SetXTitle("T [keV]");
  pdf -> SetYTitle("angle [deg]");
  pdf -> Draw("colz");
  TF1* gausx = new TF1("gausx","gaus",-10,10);
  gausx -> SetParameter(0,1);
  gausx -> SetParameter(1,0);
  //gausx -> SetParameter(2,1.9);//170124, modified
  gausx -> SetParameter(2,sigmax);
  TF1* gausy = new TF1("gausy","gaus",-10,10);
  gausy -> SetParameter(0,1);
  gausy -> SetParameter(1,0);
  //gausy -> SetParameter(2,2.7);//170124, modified
  gausy -> SetParameter(2,sigmay);
  TF1* unif = new TF1("unif","1",-180,180);

  double ang, ke, x, y, theta, p, px, py, pz, thetax, thetay;

  TFile* fFw = new TFile("gen.root","recreate");
  TTree* fTw = new TTree("tree","");
  fTw -> Branch("x", &x, "x/D");
  fTw -> Branch("y", &y, "y/D");
  fTw -> Branch("ang", &ang, "ang/D");
  fTw -> Branch("ke", &ke, "ke/D");
  fTw -> Branch("theta", &theta, "theta/D");
  fTw -> Branch("p", &p, "p/D");
  fTw -> Branch("px", &px, "px/D");
  fTw -> Branch("py", &py, "py/D");
  fTw -> Branch("pz", &pz, "pz/D");
  fTw -> Branch("thetax", &thetax, "thetax/D");
  fTw -> Branch("thetay", &thetay, "thetay/D");
  ofstream wf(output.c_str());
  for(int ievt=0; ievt<Nevt; ievt++){
    x = -1000; y=-1000, ke=1000;
    while( fabs(x) > TX)
      x = gausx->GetRandom();
    while( fabs(y) > TY)
      y = gausy->GetRandom();
  
    //while( ke > 2 ){ //slowmu_rand_1e6
    //while( ke > 0.3 ){//slowmu_rand_opt2
    //while( ke > 0.3 ){//slowmu_rand_opt2
#ifdef MUSRSIM
    while( ke > KE_THR ){//slowmu_rand_opt2
    //while( fabs(ke-5.65)>1 ){//slowmu_rand_opt2
    //while( fabs(ke-0.5)>0.05 ){//
    //while( fabs(ke)>1 ){//0521
    //while( fabs(ke-10)>0.5 ){//0551
    //while( fabs(ke-5.6)>0.5 ){//0523
    //while( fabs(ke-5.0)>0.5 ){//0543
    //while( fabs(ke-4.0)>0.5 ){//0544
    //while( fabs(ke-3.0)>0.5 ){//0545
    //while( fabs(ke-2.0)>0.5 ){//0546
    //while( fabs(ke-1.0)>0.5 ){//0547
    //while( fabs(ke-7.0)>0.5 ){//0548
    //while( fabs(ke-2.5)>0.5 ){//0550
    //while( fabs(ke-0.5)>0.5 ){//0552
    //while( fabs(ke-5.65-3.65)>0.5 ){//
      pdf   -> GetRandom2(ke, ang);
    }
    // ke += 2;

#endif
#ifdef PARMTEQM
    while( fabs(ke-5.65)>1 ){//slowmu_rand_opt2
      pdf   -> GetRandom2(ke, ang);
    }
#endif
  theta = unif->GetRandom();
 
    p     = sqrt(ke*ke+2.0*ke*mmu) * 1e-6;//GeV/c

    px    = p * sin( ang/180.0*TMath::Pi() ) * cos( theta/180.0*TMath::Pi() );
    py    = p * sin( ang/180.0*TMath::Pi() ) * sin( theta/180.0*TMath::Pi() );
    pz    = p * cos( ang/180.0*TMath::Pi() ) ;

    //for nominal
    thetax = px/pz * 1e3;
    thetay = py/pz * 1e3;
    //modified 170124, same definition for musrPrimaryGeneratorAction
    //for definition of musrPrimaryGeneratorAction
#ifdef MUSRSIM
    thetax = TMath::ASin(px/p) * 1e3;
    thetay = TMath::ASin(py/p) * 1e3;
#endif
    fTw   -> Fill();

#ifdef MUSRSIM
    wf << x << "\t"
       << thetax << "\t"
      //<< 0 << "\t"
       << y << "\t"
       << thetay << "\t"
      //<< 0 << "\t"
       << p << "\t"
      //<< 0.00075 << "\t"
      //<< 0.00043 << "\t"
       << "-1" << "\t"
       << "-1" << "\t"
       << "-1" << "\t"
       << "-1" << "\t"
       << endl;
#endif

#ifdef PARMTEQM
    double E = ke/1.0e3+mmu/1.0e3; //MeV
    wf << ke/1.0e3 << "\t"
       << px*1e3/E << "\t"
       << py*1e3/E << "\t"
       << pz*1e3/E << "\t"
       << x << "\t"
       << y << "\t"
       << -1 << "\t"
       << endl;

#endif

  }//ievt
  wf.close();
  fTw -> Write();
  fFw -> Write();
  fFw -> Close();



}//
