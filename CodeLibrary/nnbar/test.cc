#include "TMath.h"
#include "TF1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace::std;

void test(){
  Double_t PION = 3.1415927;
  Double_t m_ecms = 3.686;
  Double_t P_nnbar = 1.231;                            //FROM PDG
  Double_t PION_MASS = 0.139570;
  Double_t MU_MASS = 0.105658;
  Double_t JPSI_MASS= 3.0969;
  Double_t Neutron_MASS = 0.939566;

  Double_t pion_polar_angle_max=0.8;
  Double_t pion_momentum_max=0.45;
  Double_t prob_pion_min=0.001;
  Double_t pipi_costheta_max=0.95;
  Double_t pipisys_costheta_max=0.90;

  Int_t counter[10]={0,0,0,0,0,0,0,0,0,0};

//***************input root file*******************
  TFile *file = new TFile("nnbar_data.root");
  // common info 
  Int_t run, event;
  
  // MC-topo
//  Int_t rec, indexmc, drank[500], pdgid[500], motheridx[500], motherpid[500];

  // charged tracks
  Int_t ncharged, nptrk, nmtrk;
  Double_t pip_px, pip_py, pip_pz, pip_p, pip_theta, pip_phi, pip_costhe, pip_eraw, pip_eop, pim_px, pim_py, pim_pz, pim_p, pim_theta, pim_phi, pim_costhe, pim_eraw, pim_eop;
  
  // neutral tracks
  Int_t nshow, ngam, indexntk, show_isgamma[100];
  Double_t ntk_px[100], ntk_py[100], ntk_pz[100], ntk_p[100], ntk_theta[100], ntk_phi[100], ntk_eraw[100], ntk_hit[100], ntk_secmom[100], ntk_status[100];
   
  // vertex 
  Double_t vr0, vz0;
  
  // PID info
  Double_t prob_pip, prob_pim, prob_kp, prob_km;
  
  //final state particle
  Double_t p4_pip[4], p4_pim[4];
  
  //vertex fit
  Double_t p4_vtx_pip[4], p4_vtx_pim[4], vtx_cospipi, vtx_cos2pisys, vtx_mpipi, vtx_mrecpipi;

  TTree *tree_signal = (TTree *)file->Get("signal");

  // common info
  tree_signal->SetBranchAddress("run",&run);
  tree_signal->SetBranchAddress("event",&event);

  // charged tracks  
  tree_signal->SetBranchAddress("ncharged",&ncharged);
  tree_signal->SetBranchAddress("nptrk",&nptrk);
  tree_signal->SetBranchAddress("nmtrk",&nmtrk);
  
  tree_signal->SetBranchAddress("pip_px",&pip_px);
  tree_signal->SetBranchAddress("pip_py",&pip_py);
  tree_signal->SetBranchAddress("pip_pz",&pip_pz);
  tree_signal->SetBranchAddress("pip_p",&pip_p);
  tree_signal->SetBranchAddress("pip_theta",&pip_theta);
  tree_signal->SetBranchAddress("pip_phi",&pip_phi);
  tree_signal->SetBranchAddress("pip_costhe",&pip_costhe);
  tree_signal->SetBranchAddress("pip_eraw",&pip_eraw);
  tree_signal->SetBranchAddress("pip_eop",&pip_eop);
  
  tree_signal->SetBranchAddress("pim_px",&pim_px);  
  tree_signal->SetBranchAddress("pim_py",&pim_py);
  tree_signal->SetBranchAddress("pim_pz",&pim_pz);
  tree_signal->SetBranchAddress("pim_p",&pim_p);
  tree_signal->SetBranchAddress("pim_theta",&pim_theta);
  tree_signal->SetBranchAddress("pim_phi",&pim_phi);
  tree_signal->SetBranchAddress("pim_costhe",&pim_costhe);
  tree_signal->SetBranchAddress("pim_eraw",&pim_eraw);
  tree_signal->SetBranchAddress("pim_eop",&pim_eop);
  
  // neutral tracks
  tree_signal->SetBranchAddress("nshow",&nshow);
  tree_signal->SetBranchAddress("ngam",&ngam);
  tree_signal->SetBranchAddress("indexntk",&indexntk);
  
  tree_signal->SetBranchAddress("ntk_px",&ntk_px);
  tree_signal->SetBranchAddress("ntk_py",&ntk_py);
  tree_signal->SetBranchAddress("ntk_pz",&ntk_pz);
  tree_signal->SetBranchAddress("ntk_p",&ntk_p);  
  tree_signal->SetBranchAddress("ntk_theta",&ntk_theta);
  tree_signal->SetBranchAddress("ntk_phi",&ntk_phi);
  tree_signal->SetBranchAddress("ntk_eraw",&ntk_eraw);
  tree_signal->SetBranchAddress("ntk_hit",&ntk_hit);
  tree_signal->SetBranchAddress("ntk_secmom",&ntk_secmom);
  tree_signal->SetBranchAddress("ntk_status",&ntk_status);
  tree_signal->SetBranchAddress("show_isgamma",&show_isgamma);

  // vertex 
  tree_signal->SetBranchAddress("vr0",&vr0);
  tree_signal->SetBranchAddress("vz0",&vz0);
  
  // PID info
  tree_signal->SetBranchAddress("prob_pip",&prob_pip);
  tree_signal->SetBranchAddress("prob_pim",&prob_pim);
  tree_signal->SetBranchAddress("prob_kp",&prob_kp);
  tree_signal->SetBranchAddress("prob_km",&prob_km);
  
  //final state particle
  tree_signal->SetBranchAddress("p4_pip",&p4_pip);
  tree_signal->SetBranchAddress("p4_pim",&p4_pim);
  
  //vertex fit
  tree_signal->SetBranchAddress("p4_vtx_pip",&p4_vtx_pip);
  tree_signal->SetBranchAddress("p4_vtx_pim",&p4_vtx_pim);  
  tree_signal->SetBranchAddress("vtx_cospipi",&vtx_cospipi);  
  tree_signal->SetBranchAddress("vtx_cos2pisys",&vtx_cos2pisys);  
  tree_signal->SetBranchAddress("vtx_mpipi",&vtx_mpipi);  
  tree_signal->SetBranchAddress("vtx_mrecpipi",&vtx_mrecpipi);  


  //TTree *tree_topoall = (TTree *)file->Get("topoall");

  // MC-topo
  /*tree_topoall->SetBranchAddress("rec",&rec);
  tree_topoall->SetBranchAddress("indexmc",&indexmc);
  tree_topoall->SetBranchAddress("drank",&drank);
  tree_topoall->SetBranchAddress("pdgid",&pdgid);  
  tree_topoall->SetBranchAddress("motheridx",&motheridx);
  tree_topoall->SetBranchAddress("motherpid",&motherpid);
*/
//******************output root file*************************

  TString  Output = "ReduFile_data.root";
  TFile *ReduFile = new TFile(Output, "RECREATE");
  TTree * newtree = new TTree("sss","sss");

  // common info 
  Int_t m_run, m_event;
  
  // MC-topo
  Int_t m_rec, m_indexmc, m_drank[500], m_pdgid[500], m_motheridx[500], m_motherpid[500];

  // charged tracks
  Int_t m_ncharged, m_nptrk, m_nmtrk;
  Double_t m_pip_px, m_pip_py, m_pip_pz, m_pip_p, m_pip_theta, m_pip_phi, m_pip_costhe, m_pip_eraw, m_pip_eop, m_pim_px, m_pim_py, m_pim_pz, m_pim_p, m_pim_theta, m_pim_phi, m_pim_costhe, m_pim_eraw, m_pim_eop;
  
  // neutral tracks
  Int_t m_nshow, m_ngam, m_indexntk, m_ngam_x;
  Double_t m_ntk_px[100], m_ntk_py[100], m_ntk_pz[100], m_ntk_p[100], m_ntk_theta[100], m_ntk_phi[100], m_ntk_eraw[100], m_ntk_hit[100], m_ntk_secmom[100], m_ntk_status[100], m_show_isgamma[100];
  Double_t m_nbar_energy, m_n_energy, m_nhits, m_secondmoment, m_emiss;
   
  // vertex 
  Double_t m_vr0, m_vz0;
  
  // PID info
  Double_t m_prob_pip, m_prob_pim, m_prob_kp, m_prob_km;
  
  //final state particle
  Double_t m_p4_pip[4], m_p4_pim[4];
  
  //vertex fit
  Double_t m_p4_vtx_pip[4], m_p4_vtx_pim[4], m_vtx_cospipi, m_vtx_cos2pisys, m_vtx_mpipi, m_vtx_mrecpipi;



  //commom info
  newtree->Branch("run",&m_run,"run/I");
  newtree->Branch("event",&m_event,"event/I");
  
  //topo info
  newtree->Branch("run", &m_run, "run/I");
  newtree->Branch("rec", &m_rec, "rec/I");
  newtree->Branch("indexmc", &m_indexmc, "indexmc/I");

  newtree->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
  newtree->Branch("drank", m_drank, "drank[indexmc]/I");
  newtree->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
  newtree->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");

  //charged tracks
  newtree->Branch("ncharged", &m_ncharged, "ncharged/I");
  newtree->Branch("nptrk", &m_nptrk, "nptrk/I");
  newtree->Branch("nmtrk", &m_nmtrk, "nmtrk/I");
  
  newtree->Branch("pip_p", &m_pip_p, "pip_p/D"); 
  newtree->Branch("pip_px", &m_pip_px, "pip_px/D"); 
  newtree->Branch("pip_py", &m_pip_py, "pip_py/D"); 
  newtree->Branch("pip_pz", &m_pip_pz, "pip_pz/D"); 
  newtree->Branch("pip_theta", &m_pip_theta, "pip_theta/D"); 
  newtree->Branch("pip_phi", &m_pip_phi, "pip_phi/D"); 
  newtree->Branch("pip_eraw", &m_pip_eraw, "pip_eraw/D");
  newtree->Branch("pip_costhe", &m_pip_costhe, "pip_costhe/D");
  newtree->Branch("pip_eop", &m_pip_eop, "pip_eop/D");  

  newtree->Branch("pim_p", &m_pim_p, "pim_p/D"); 
  newtree->Branch("pim_px", &m_pim_px, "pim_px/D"); 
  newtree->Branch("pim_py", &m_pim_py, "pim_py/D"); 
  newtree->Branch("pim_pz", &m_pim_pz, "pim_pz/D"); 
  newtree->Branch("pim_theta", &m_pim_theta, "pim_theta/D"); 
  newtree->Branch("pim_phi", &m_pim_phi, "pim_phi/D"); 
  newtree->Branch("pim_eraw", &m_pim_eraw, "pim_eraw/D"); 
  newtree->Branch("pim_costhe", &m_pim_costhe, "pim_costhe/D");
  newtree->Branch("pim_eop", &m_pim_eop, "pim_eop/D");  
	  
  // vertex
  newtree->Branch("vr0",&m_vr0, "vr0/D");
  newtree->Branch("vz0",&m_vz0, "vz0/D");
  
  // netual tracks  
  newtree->Branch("nshow", &m_nshow, "nshow/I");
  newtree->Branch("ngam", &m_ngam, "ngam/I");
  newtree->Branch("ngam_x", &m_ngam_x, "ngam_x/I");
  newtree->Branch("indexntk", &m_indexntk, "indexntk/I");  
  newtree->Branch("ntk_px", &m_ntk_px, "ntk_px[indexntk]/D");
  newtree->Branch("ntk_py", &m_ntk_py, "ntk_py[indexntk]/D");
  newtree->Branch("ntk_pz", &m_ntk_pz, "ntk_pz[indexntk]/D");
  newtree->Branch("ntk_p", &m_ntk_p, "ntk_p[indexntk]/D");
  newtree->Branch("ntk_theta", &m_ntk_theta,"ntk_theta[indexntk]/D");
  newtree->Branch("ntk_phi", &m_ntk_phi,"ntk_phi[indexntk]/D");
  newtree->Branch("ntk_eraw", &m_ntk_eraw,"ntk_eraw[indexntk]/D");
  newtree->Branch("ntk_hit", &m_ntk_hit,"ntk_hit[indexntk]/D");
  newtree->Branch("ntk_secmom", &m_ntk_secmom,"ntk_secmom[indexntk]/D");
  newtree->Branch("ntk_status", &m_ntk_status,"ntk_status[indexntk]/D");
  newtree->Branch("show_isgamma", &m_show_isgamma,"show_isgamma[indexntk]/I");

  newtree->Branch("nbar_energy", &m_nbar_energy,"nbar_energy/D");
  newtree->Branch("n_energy", &m_n_energy,"n_energy/D");
  newtree->Branch("nhits", &m_nhits,"nhits/D");
  newtree->Branch("secondmoment", &m_secondmoment,"secondmoment/D");
  newtree->Branch("emiss", &m_emiss,"emiss/D");

  // PID info
  newtree->Branch("prob_pip", &m_prob_pip, "prob_pip/D"); 
  newtree->Branch("prob_pim", &m_prob_pim, "prob_pim/D"); 
  newtree->Branch("prob_kp", &m_prob_kp, "prob_kp/D"); 
  newtree->Branch("prob_km", &m_prob_km, "prob_km/D"); 
  
  // final state particle
  newtree->Branch("p4_pip", &m_p4_pip, "p4_pip[4]/D"); 
  newtree->Branch("p4_pim", &m_p4_pim, "p4_pim[4]/D");   
  
  // vertex fit
  newtree->Branch("p4_vtx_pip", &m_p4_vtx_pip, "p4_vtx_pip[4]/D"); 
  newtree->Branch("p4_vtx_pim", &m_p4_vtx_pim, "p4_vtx_pim[4]/D"); 
  newtree->Branch("vtx_cospipi",&m_vtx_cospipi, "vtx_cospipi/D");
  newtree->Branch("vtx_cos2pisys",&m_vtx_cos2pisys, "vtx_cos2pisys/D");
  newtree->Branch("vtx_mpipi",&m_vtx_mpipi, "vtx_mpipi/D");
  newtree->Branch("vtx_mrecpipi",&m_vtx_mrecpipi, "vtx_mrecpipi/D"); 

 TH1D* h_E_nbar = new TH1D("h_E_nbar","h_E_nbar",100,0,2.5);
 TH1D* h_E_n = new TH1D("h_E_n","h_E_n",100,0,2);
 TH1D* h_E_miss = new TH1D("h_E_miss","h_E_miss",100,0,10);
 TH1D* h_nhits = new TH1D("h_nhits","h_nhits",100,0,200);
 TH1D* h_SecondMoment = new TH1D("h_SecondMoment","h_SecondMoment",100,0,150);
 TH1D* h_cos_nbar = new TH1D("h_cos_nbar","h_cos_nbar",100,-1,1);
 TH1D* h_theta_nnbar = new TH1D("h_theta_nnbar","h_theta_nnbar",100,0,180);

//******************event selection*********************

//********************select pi_p & pi_m*******************
  for(Int_t i = 0;i < tree_signal->GetEntries();i++){
  tree_signal->GetEntry(i);
  //tree_topoall->GetEntry(i);
  if(indexntk>1){
  cout<<counter[0]<<endl;
  counter[0]++;
//pipi
  bool cut_pip_costhe;
  bool cut_pim_costhe;
  bool cut_pi_costhe;
  bool cut_pip_p;
  bool cut_pim_p;
  bool cut_PID;
  bool cut_cospipi;
  bool cut_cos2pisys;
  bool cut_mjpsi_signal;

//nnbar
  bool cut_E_nbar;
  bool cut_SecondMoment;
  bool cut_nhits;
  bool cut_E_n;
  bool cut_E_miss;
  bool cut_cos_nbar;
  bool cut_recoil;

  cut_pip_costhe = (fabs(pip_costhe) < pion_polar_angle_max);
  cut_pim_costhe = (fabs(pim_costhe) < pion_polar_angle_max);
  cut_pi_costhe = cut_pip_costhe && cut_pim_costhe;
  cut_pip_p = (0 < pip_p && pip_p < pion_momentum_max);
  cut_pim_p = (0 < pim_p && pim_p < pion_momentum_max);
  cut_PID = (prob_pip > prob_kp && prob_pip > prob_pion_min && prob_pim > prob_km && prob_pim > prob_pion_min);
  cut_cospipi = (vtx_cospipi < pipi_costheta_max);
  cut_cos2pisys = (fabs(vtx_cos2pisys) < pipisys_costheta_max);
  cut_mjpsi_signal = (vtx_mrecpipi > 3.081916 && vtx_mrecpipi < 3.111916);

  if(cut_pip_costhe && cut_pim_costhe && cut_pi_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal)
  {
    counter[1]++;
  }
  else continue;

//******************select n & nbar********************
  Double_t energy_temp = 0;
  Int_t num_temp;

//************select nbar candidate***************
  for(Int_t j = 0; j < indexntk; j++)
  {
    if(ntk_eraw[j] > energy_temp)
    {  
	energy_temp = ntk_eraw[j];
	num_temp = j;
    }
  }

//************use nbar selection critria
  Int_t nhit_cone=0;
  TVector3 vect_2;
  vect_2.SetXYZ(sin(ntk_theta[num_temp])*cos(ntk_phi[num_temp]),sin(ntk_theta[num_temp])*sin(ntk_phi[num_temp]),cos(ntk_theta[num_temp]));
  for(Int_t k = 0;k < indexntk;k++)
  {
    TVector3 vect_1;
    vect_1.SetXYZ(sin(ntk_theta[k])*cos(ntk_phi[k]),sin(ntk_theta[k])*sin(ntk_phi[k]),cos(ntk_theta[k]));
    if(vect_1.Angle(vect_2)<=((Double_t)50/180*3.141592653))
	nhit_cone = nhit_cone + ntk_hit[k];
  }


//****************select n**********************
  Double_t angle_nnbar=5;
  Int_t num_n;

  TLorentzVector vect_pip(p4_vtx_pip[0],p4_vtx_pip[1],p4_vtx_pip[2],p4_vtx_pip[3]);
  TLorentzVector vect_pim(p4_vtx_pim[0],p4_vtx_pim[1],p4_vtx_pim[2],p4_vtx_pim[3]);
  TLorentzVector pcms(0.011*m_ecms, 0., 0., m_ecms);
  TLorentzVector vect_jpsi = pcms - vect_pip -vect_pim;
  Double_t p_jpsi = sqrt(vect_jpsi[0]*vect_jpsi[0]+vect_jpsi[1]*vect_jpsi[1]+vect_jpsi[2]*vect_jpsi[2]);
  Double_t v_jpsi = p_jpsi/sqrt(p_jpsi*p_jpsi+JPSI_MASS*JPSI_MASS);
  Double_t v_nnbar = P_nnbar/sqrt(P_nnbar*P_nnbar+Neutron_MASS*Neutron_MASS);

  Double_t angle_1 = vect_jpsi.Angle(vect_2);
  Double_t A=v_nnbar , B=tan(angle_1)*v_nnbar/sqrt(1-v_jpsi*v_jpsi) , C=tan(angle_1)*v_jpsi/sqrt(1-v_jpsi*v_jpsi);
  Double_t theta = asin(C/sqrt(A*A+B*B))+asin(B/sqrt(A*A+B*B));
  Double_t angle_3 = fabs(atan(v_jpsi*sin(theta)*sqrt(1-v_jpsi*v_jpsi)/(v_nnbar-v_jpsi*cos(theta))));

  TVector3 vect_ntemp;
  for(Int_t kk = 0;kk < indexntk;kk++)
    if(kk != num_temp)
    {  
      Double_t sin_the = sin(ntk_theta[kk]) , cos_the = cos(ntk_theta[kk]) , sin_phi = sin(ntk_phi[kk]) , cos_phi = cos(ntk_phi[kk]);
      vect_ntemp.SetXYZ(sin_the*cos_phi,sin_the*sin_phi,cos_the);
      Double_t angle_ntempjpsi = vect_ntemp.Angle(vect_2);
      Double_t fabs_angle;
      if(angle_ntempjpsi-angle_3>=0) 
        fabs_angle= angle_ntempjpsi-angle_3;
      else 
        fabs_angle = -angle_ntempjpsi+angle_3;
      if(fabs_angle < angle_nnbar)
      {
        angle_nnbar=fabs_angle;
        num_n=kk;
      }
    }
  TVector3 vect_n;
  vect_n.SetXYZ(sin(ntk_theta[num_n])*cos(ntk_phi[num_n]),sin(ntk_theta[num_n])*sin(ntk_phi[num_n]),cos(ntk_theta[num_n]));

//*****************Event level****************
  Double_t emiss = 0;
  for(Int_t k = 0;k < indexntk;k++)
  {
    TVector3 vect_5;
    vect_5.SetXYZ(sin(ntk_theta[k])*cos(ntk_phi[k]),sin(ntk_theta[k])*sin(ntk_phi[k]),cos(ntk_theta[k]));
    if(vect_5.Angle(vect_2)>((Double_t)50/180*3.141592653) && k!=num_n)
	emiss = emiss+ntk_eraw[k];
  }


//**********************save informations*********************

//MC topo
/*  m_rec = rec;
  m_indexmc = indexmc;
  for(Int_t ii=0;ii<indexmc;ii++)
  {
    m_drank[ii] = drank[ii];
    m_pdgid[ii] = pdgid[ii];
    m_motherpid[ii] = motherpid[ii];
    m_motheridx[ii] = motheridx[ii];
  }
*/
  m_nbar_energy = ntk_eraw[num_temp];
  m_n_energy = ntk_eraw[num_n];
  m_nhits = nhit_cone;
  m_secondmoment = ntk_secmom[num_temp];
  m_emiss = emiss;
  m_pip_p = pip_p;
  m_ngam = ngam;
  m_ngam_x = ngam;  if(show_isgamma[num_n]==1)m_ngam_x--;  if(show_isgamma[num_temp]==1)m_ngam_x--;
  m_nshow = nshow;
  
  cut_E_nbar = (energy_temp < 2.0 && energy_temp > 0.5);
  cut_SecondMoment = (ntk_secmom[num_temp] > 16.5);
  cut_nhits = (nhit_cone > 30);
  cut_E_n = (ntk_eraw[num_n]<0.6 && ntk_eraw[num_n]>0.04);
  cut_E_miss = (emiss <0.4);//== 0);
  cut_cos_nbar = (fabs(cos(ntk_theta[num_temp]))<0.88);
  cut_recoil = (angle_nnbar*180/3.141592653 < 20); 
 
//  h_E_nbar->Fill(m_nbar_energy);
  if(cut_E_nbar)
  {
    counter[2]++;   // h_SecondMoment->Fill(m_secondmoment);
    if(cut_SecondMoment)
    {
      counter[3]++;  //  h_nhits->Fill(m_nhits);
      if(cut_nhits)
	{
        counter[4]++;  // h_theta_nnbar->Fill(angle_nnbar*180/3.141592653);
        if(cut_recoil)
        {
          counter[5]++;    //h_E_n->Fill(m_n_energy); 
        if(cut_E_n)
	{
	  counter[6]++;  // h_E_miss->Fill(m_emiss);
	  if(cut_E_miss)
	  {
	    counter[7]++;   // h_cos_nbar->Fill(cos(ntk_theta[num_temp]));
	    if(cut_cos_nbar)
	    {
	      counter[8]++;
	      newtree->Fill();
	    }
	    }
	    }
	}
      }
    }
  }

  if(cut_SecondMoment && cut_nhits && cut_recoil && cut_E_n && cut_E_miss && cut_cos_nbar)
    h_E_nbar->Fill(m_nbar_energy);
  if(cut_E_nbar && cut_SecondMoment && cut_nhits && cut_recoil && cut_E_miss && cut_cos_nbar)
    h_E_n->Fill(m_n_energy);
  if(cut_E_nbar && cut_nhits && cut_E_n && cut_recoil && cut_E_miss && cut_cos_nbar)
    h_SecondMoment->Fill(m_secondmoment);
  if(cut_E_nbar && cut_SecondMoment && cut_E_n && cut_recoil && cut_E_miss && cut_cos_nbar)
    h_nhits->Fill(m_nhits);
  if(cut_E_nbar && cut_SecondMoment && cut_nhits && cut_E_n && cut_recoil && cut_cos_nbar)
    h_E_miss->Fill(m_emiss);
  if(cut_E_nbar && cut_SecondMoment && cut_nhits && cut_E_n && cut_recoil && cut_E_miss)
    h_cos_nbar->Fill(cos(ntk_theta[num_temp]));
  if(cut_E_nbar && cut_SecondMoment && cut_nhits && cut_E_n && cut_E_miss && cut_cos_nbar)
    h_theta_nnbar->Fill(angle_nnbar*180/3.141592653);

  }
  }

  ReduFile->cd();
  newtree->Write();
  h_E_nbar->Write();
  h_E_n->Write();
  h_cos_nbar->Write();
  h_theta_nnbar->Write();
  h_nhits->Write();
  h_E_miss->Write();
  h_SecondMoment->Write();
  ReduFile->Close();

  cout<<"total number:         "<<counter[0]<<endl;
  cout<<"pipi select:          "<<counter[1]<<endl;
  cout<<"0.6<E<2.0:            "<<counter[2]<<endl;
  cout<<"SecondMoment>20:      "<<counter[3]<<endl;
  cout<<"numHits>40            "<<counter[4]<<endl;
  cout<<"recoil direction:     "<<counter[5]<<endl;
  cout<<"0.06<E<0.6:           "<<counter[6]<<endl;
  cout<<"E_miss = 0:           "<<counter[7]<<endl;
  cout<<"|cos_theta|<0.8:      "<<counter[8]<<endl;
  return;
}
