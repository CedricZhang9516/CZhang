#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "McTruth/McParticle.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"



#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif
#include "RhopiAlg/Rhopi.h"

//#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"

#include <vector>
#include "TMath.h"
#include <iostream>
#include <fstream>
//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mpi = 0.13957;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};
//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm
typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;

int Ncut0,Ncut1,Ncut2,Ncut3,Ncut4,Ncut5,Ncut6;
int Ncutmuc=0;
int Ncutratio=0;
double m_Ecms=3.097;

/////////////////////////////////////////////////////////////////////////////

Rhopi::Rhopi(const std::string& name, ISvcLocator* pSvcLocator) :
	Algorithm(name, pSvcLocator) {

		//Declare the properties  
		declareProperty("OutputFileName",  m_OutputFileName = "rhopi1027.root");
		declareProperty("saveTopo", m_saveTopo = 1);//need to be re-evaluated when running different samples(1 for MC)

		declareProperty("Vr0cut", m_vr0cut =1.0);
		declareProperty("Vz0cut", m_vz0cut = 10.0);
		declareProperty("EnergyThreshold", m_energyThreshold=0.04);
		declareProperty("GammaPhiCut", m_gammaPhiCut =20.0);
		declareProperty("GammaThetaCut", m_gammaThetaCut =20.0);
		declareProperty("GammaAngleCut", m_gammaAngleCut = 10.0);
		declareProperty("Test4C", m_test4C = 1);
		declareProperty("Test5C", m_test5C = 0);
		declareProperty("CheckDedx", m_checkDedx = 1);
		declareProperty("CheckTof",  m_checkTof = 1);
		declareProperty("CheckRatio",  m_checkRatio = 1);
		declareProperty("CheckMuc",  m_checkMuc = 1);
		//		declareProperty("barTheta",  barTheta = 0.);
		//		declareProperty("endThetaMin",  endThetaMin = 0.);
		//		declareProperty("endThetaMax",  endThetaMax = 0.);
		declareProperty("endEnergy",  endEnergy = 0.050);
		declareProperty("barEnergy",  barEnergy = 0.025);
		declareProperty("layerMuc",m_layerMuc);
		declareProperty("hits",m_hits);
	declareProperty("maxHitsInLayer",m_maxHitsInLayer);
	declareProperty("chi2",m_chi2);

	    declareProperty("kalRechi2",m_kalRechi2);
	    //declareProperty("kaldof" , m_kaldof);  
	   // declareProperty("kaldepth"  ,m_kaldepth);
	   // declareProperty("kalbrLastLayer",  m_kalbrLastLayer);
	   // declareProperty("kalecLastLayer" , m_kalecLastLayer);  
	   declareProperty("dof" , m_dof);
	   // declareProperty("brLastLayer" , m_brLastLayer);
	   // declareProperty("ecLastLayer" , m_ecLastLayer);
	 
	    declareProperty("Mdcchi2" , m_Mdcchi2);
	    declareProperty("ndof" , m_ndof);
	    declareProperty("nhits" , m_nhits);
	    declareProperty("nlayer" , m_nlayer);




	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Rhopi::initialize(){
	MsgStream log(msgSvc(), name());

	log << MSG::INFO << "in initialize()" << endmsg;

	StatusCode status;

	pip=new TClonesArray("TLorentzVector");
	pim=new TClonesArray("TLorentzVector");
	gamma1=new TClonesArray("TLorentzVector");
	gamma2=new TClonesArray("TLorentzVector");
	
	pip_unfitted=new TClonesArray("TLorentzVector");
	pim_unfitted=new TClonesArray("TLorentzVector");
	gamma1_unfitted=new TClonesArray("TLorentzVector");
	gamma2_unfitted=new TClonesArray("TLorentzVector");
	
	//Output name
	TString s_OutputFileName(m_OutputFileName);
	saveFile = new TFile(s_OutputFileName, "recreate");
	TreeAna = new TTree("save", "save");
	if(m_saveTopo == 1)
	{
		TreeAna->Branch("indexmc", &m_idxmc, "indexmc/I");
		TreeAna->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
		TreeAna->Branch("drank", m_drank, "drank[indexmc]/I");
		TreeAna->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
		TreeAna->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");
	
		TreeAna->Branch("mpi0", &mpi0, "mpi0/D");

		TreeAna->Branch ("ppos",   &m_ppos_ratio,"ppos/D");
		TreeAna->Branch ("epos",   &m_epos_ratio,"epos/D");
		TreeAna->Branch ("depos",   &m_depos_ratio,"depos/D");
		TreeAna->Branch ("epp",   &m_eppos_ratio,"epp/D");
		TreeAna->Branch ("hitspos",   &m_hitspos_ratio,"hitspos/I");
		TreeAna->Branch ("pneg",   &m_pneg_ratio,"pneg/D");
		TreeAna->Branch ("eneg",   &m_eneg_ratio,"eneg/D");
		TreeAna->Branch ("deneg",   &m_deneg_ratio,"deneg/D");
		TreeAna->Branch ("epn",   &m_epneg_ratio,"epn/D");
		TreeAna->Branch ("hitsneg",   &m_hitsneg_ratio,"hitsneg/I");
		TreeAna->Branch ("tmass",   &m_tmass_ratio,"tmass/D");
		TreeAna->Branch ("layerMuc", &m_layerMuc,"layerMuc/D");
		TreeAna->Branch ("hits",&m_hits,"hits/D");
		
		TreeAna->Branch("maxHitsInlayer",&m_maxHitsInLayer,"maxHitsInlayer/I");
		TreeAna->Branch("chi2",&m_chi2,"chi2/D");



		TreeAna->Branch ("posmucstat",   &m_posmucstat,"posmucstat/I");
		TreeAna->Branch ("negmucstat",   &m_negmucstat,"negmucstat/I");

		TreeAna->Branch ("posdepthMuc",   &m_posdepthMuc,"posdepthMuc/D");
		TreeAna->Branch ("negdepthMuc",   &m_negdepthMuc,"negdepthMuc/D");
		TreeAna->Branch ("poslayerMuc",   &m_poslayerMuc,"poslayerMuc/I");
		TreeAna->Branch ("neglayerMuc",   &m_neglayerMuc,"neglayerMuc/I");
		TreeAna->Branch ("posangMuc",   &m_posangMuc,"posangMuc/D");
		TreeAna->Branch ("negangMuc",   &m_negangMuc,"negangMuc/D");


		TreeAna->Branch ("poskalrechi2",   &m_poskalrechi2,"poskalrechi2/D");
		TreeAna->Branch ("negkalrechi2",   &m_negkalrechi2,"negkalrechi2/D");
		TreeAna->Branch ("poskalecLastLayer",   &m_poskalecLastLayer,"poskalecLastLayer/I");
		TreeAna->Branch ("negkalecLastLayer",   &m_negkalecLastLayer,"negkalecLastLayer/I");
		TreeAna->Branch ("poskalbrLastLayer",   &m_poskalbrLastLayer,"poskalbrLastLayer/I");
		TreeAna->Branch ("negkalbrLastLayer",   &m_negkalbrLastLayer,"negkalbrLastLayer/I");
		TreeAna->Branch ("poskaldepth",   &m_poskaldepth,"poskaldepth/D");
		TreeAna->Branch ("negkaldepth",   &m_negkaldepth,"negkaldepth/D");
		TreeAna->Branch ("kaldof",   &m_kaldof,"kaldof/I");
		TreeAna->Branch ("negkaldof",   &m_negkaldof,"negkaldof/I");


		TreeAna->Branch ("chisq_pi0",   &m_chisq_pi0,"chisq_pi0/D");
		TreeAna->Branch ("chisq_4c",   &m_chisq_4c,"chisq_4c/D");
		TreeAna->Branch ("len",   &len,"len/I");
		TreeAna->Branch ("lvtrpi0",   lvtrpi0,"lvtrpi0[len]/D");
		TreeAna->Branch ("lvtrpip",   lvtrpip,"lvtrpip[len]/D");
		TreeAna->Branch ("lvtrpim",   lvtrpim,"lvtrpim[len]/D");
		TreeAna->Branch ("lvtrpi0unfit",   lvtrpi0unfit,"lvtrpi0unfit[len]/D");
		TreeAna->Branch ("lvtrpipunfit",   lvtrpipunfit,"lvtrpipunfit[len]/D");
		TreeAna->Branch ("lvtrpimunfit",   lvtrpimunfit,"lvtrpimunfit[len]/D");

		 TreeAna->Branch("kalRechi2",&m_kalRechi2,"m_kalRechi2/D");
	      TreeAna->Branch("kaldepth",&m_kaldepth,"m_kaldepth/D");
	           TreeAna->Branch("kalbrLastLayer",&m_kalbrLastLayer,"m_kalbrLastLayer/I");
	           TreeAna->Branch("kalecLastLayer",&m_kalecLastLayer,"m_kalecLastLayer/I");
	           TreeAna->Branch("dof",&m_dof,"m_dof/I");
	            TreeAna->Branch("brLastLayer",&m_brLastLayer,"m_brLastLayer/I");
	            TreeAna->Branch("ecLastLayer",&m_ecLastLayer,"m_ecLastLayer/I");
	            TreeAna->Branch("ndof",&m_ndof,"m_ndof/I");
	            TreeAna->Branch("nhits",&m_nhits,"m_nhits/I");
	           TreeAna->Branch("nlayer",&m_nlayer,"m_nlayer/I");



/*
		TreeAna->Branch("nevt",&nevt,"nevt/I");
		TreeAna->Branch("kmchisq_pi0",kmchisq_pi0,"kmchisq_pi0[nevt]/D");
		TreeAna->Branch("kmchisq_4c",kmchisq_4c,"kmchisq_4c[nevt]/D");
		TreeAna->Branch("id_gamma1",id_gamma1,"id_gamma1[nevt]/I");
		TreeAna->Branch("id_gamma2",id_gamma2,"id_gamma2[nevt]/I");

		TreeAna->Branch("pip","TClonesArray",&pip,256000,0);
		TreeAna->Branch("pim","TClonesArray",&pim,256000,0);
		TreeAna->Branch("gamma1","TClonesArray",&gamma1,256000,0);
		TreeAna->Branch("gamma2","TClonesArray",&gamma2,256000,0);
		TreeAna->Branch("pip_unfitted","TClonesArray",&pip_unfitted,256000,0);
		TreeAna->Branch("pim_unfitted","TClonesArray",&pim_unfitted,256000,0);
		TreeAna->Branch("gamma1_unfitted","TClonesArray",&gamma1_unfitted,256000,0);
		TreeAna->Branch("gamma2_unfitted","TClonesArray",&gamma2_unfitted,256000,0);
*/
	}
	//Tree and File Modified
	NTuplePtr nt1(ntupleSvc(), "FILE1/vxyz");
	if ( nt1 ) m_tuple1 = nt1;
	else {
		m_tuple1 = ntupleSvc()->book ("FILE1/vxyz", CLID_ColumnWiseTuple, "ks N-Tuple example");
		if ( m_tuple1 )    {
			status = m_tuple1->addItem ("vx0",   m_vx0);
			status = m_tuple1->addItem ("vy0",   m_vy0);
			status = m_tuple1->addItem ("vz0",   m_vz0);
			status = m_tuple1->addItem ("vr0",   m_vr0);
			status = m_tuple1->addItem ("rvxy0",  m_rvxy0);
			status = m_tuple1->addItem ("rvz0",   m_rvz0);
			status = m_tuple1->addItem ("rvphi0", m_rvphi0);
		}
		else    { 
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
			return StatusCode::FAILURE;
		}
	}

	NTuplePtr nt2(ntupleSvc(), "FILE1/photon");
	if ( nt2 ) m_tuple2 = nt2;
	else {
		m_tuple2 = ntupleSvc()->book ("FILE1/photon", CLID_ColumnWiseTuple, "ks N-Tuple example");
		if ( m_tuple2 )    {
			status = m_tuple2->addItem ("dthe",   m_dthe);
			status = m_tuple2->addItem ("dphi",   m_dphi);
			status = m_tuple2->addItem ("dang",   m_dang);
			status = m_tuple2->addItem ("eraw",   m_eraw);
		}
		else    { 
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple2) << endmsg;
			return StatusCode::FAILURE;
		}
	}


	NTuplePtr nt3(ntupleSvc(), "FILE1/etot");
	if ( nt3 ) m_tuple3 = nt3;
	else {
		m_tuple3 = ntupleSvc()->book ("FILE1/etot", CLID_ColumnWiseTuple, "ks N-Tuple example");
		if ( m_tuple3 )    {
			status = m_tuple3->addItem ("m2gg",   m_m2gg);
			status = m_tuple3->addItem ("etot",   m_etot);
		}
		else    { 
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple3) << endmsg;
			return StatusCode::FAILURE;
		}
	}
	if(m_test4C==1) {
		NTuplePtr nt4(ntupleSvc(), "FILE1/fit4c");
		if ( nt4 ) m_tuple4 = nt4;
		else {
			m_tuple4 = ntupleSvc()->book ("FILE1/fit4c", CLID_ColumnWiseTuple, "ks N-Tuple example");
			if ( m_tuple4 )    {
//				status = m_tuple4->addItem ("chi2",   m_chi1);
				status = m_tuple4->addItem ("mpi0",   m_mpi0);
			}
			else    { 
				log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple4) << endmsg;
				return StatusCode::FAILURE;
			}
		}
	} // test 4C


	if(m_test5C==1) {
		NTuplePtr nt5(ntupleSvc(), "FILE1/fit5c");
		if ( nt5 ) m_tuple5 = nt5;
		else {
			m_tuple5 = ntupleSvc()->book ("FILE1/fit5c", CLID_ColumnWiseTuple, "ks N-Tuple example");
			if ( m_tuple5 )    {
				//status = m_tuple5->addItem ("chi2",   m_chi2);
				status = m_tuple5->addItem ("mrh0",   m_mrh0);
				status = m_tuple5->addItem ("mrhp",   m_mrhp);
				status = m_tuple5->addItem ("mrhm",   m_mrhm);
			}
			else    { 
				log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple5) << endmsg;
				return StatusCode::FAILURE;
			}
		}

		NTuplePtr nt6(ntupleSvc(), "FILE1/geff");
		if ( nt6 ) m_tuple6 = nt6;
		else {
			m_tuple6 = ntupleSvc()->book ("FILE1/geff", CLID_ColumnWiseTuple, "ks N-Tuple example");
			if ( m_tuple6 )    {
				status = m_tuple6->addItem ("fcos",   m_fcos);
				status = m_tuple6->addItem ("elow",   m_elow);
			}
			else    { 
				log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple6) << endmsg;
				return StatusCode::FAILURE;
			}
		}
	} // test 5c

	if(m_checkDedx == 1) {
		NTuplePtr nt7(ntupleSvc(), "FILE1/dedx");
		if ( nt7 ) m_tuple7 = nt7;
		else {
			m_tuple7 = ntupleSvc()->book ("FILE1/dedx", CLID_ColumnWiseTuple, "ks N-Tuple example");
			if ( m_tuple7 )    {
				status = m_tuple7->addItem ("ptrk",   m_ptrk);
				status = m_tuple7->addItem ("chie",   m_chie);
				status = m_tuple7->addItem ("chimu",   m_chimu);
				status = m_tuple7->addItem ("chipi",   m_chipi);
				status = m_tuple7->addItem ("chik",   m_chik);
				status = m_tuple7->addItem ("chip",   m_chip);
				status = m_tuple7->addItem ("probPH",   m_probPH);
				status = m_tuple7->addItem ("normPH",   m_normPH);
				status = m_tuple7->addItem ("ghit",   m_ghit);
				status = m_tuple7->addItem ("thit",   m_thit);
			}
			else    { 
				log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple7) << endmsg;
				return StatusCode::FAILURE;
			}
		}
	} // check dE/dx

	if(m_checkTof == 1) {
		NTuplePtr nt8(ntupleSvc(), "FILE1/tofe");
		if ( nt8 ) m_tuple8 = nt8;
		else {
			m_tuple8 = ntupleSvc()->book ("FILE1/tofe",CLID_ColumnWiseTuple, "ks N-Tuple example");
			if ( m_tuple8 )    {
				status = m_tuple8->addItem ("ptrk",   m_ptot_etof);
				status = m_tuple8->addItem ("cntr",   m_cntr_etof);
				status = m_tuple8->addItem ("ph",  m_ph_etof);
				status = m_tuple8->addItem ("rhit", m_rhit_etof);
				status = m_tuple8->addItem ("qual", m_qual_etof);
				status = m_tuple8->addItem ("te",   m_te_etof);
				status = m_tuple8->addItem ("tmu",   m_tmu_etof);
				status = m_tuple8->addItem ("tpi",   m_tpi_etof);
				status = m_tuple8->addItem ("tk",   m_tk_etof);
				status = m_tuple8->addItem ("tp",   m_tp_etof);
			}
			else    { 
				log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple8) << endmsg;
				return StatusCode::FAILURE;
			}
		}
	} // check Tof:endcap



	if(m_checkTof == 1) {
		NTuplePtr nt9(ntupleSvc(), "FILE1/tof1");
		if ( nt9 ) m_tuple9 = nt9;
		else {
			m_tuple9 = ntupleSvc()->book ("FILE1/tof1", CLID_ColumnWiseTuple, "ks N-Tuple example");
			if ( m_tuple9 )    {
				status = m_tuple9->addItem ("ptrk",   m_ptot_btof1);
				status = m_tuple9->addItem ("cntr",   m_cntr_btof1);
				status = m_tuple9->addItem ("ph",  m_ph_btof1);
				status = m_tuple9->addItem ("zhit", m_zhit_btof1);
				status = m_tuple9->addItem ("qual", m_qual_btof1);
				status = m_tuple9->addItem ("te",   m_te_btof1);
				status = m_tuple9->addItem ("tmu",   m_tmu_btof1);
				status = m_tuple9->addItem ("tpi",   m_tpi_btof1);
				status = m_tuple9->addItem ("tk",   m_tk_btof1);
				status = m_tuple9->addItem ("tp",   m_tp_btof1);
			}
			else    { 
				log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple9) << endmsg;
				return StatusCode::FAILURE;
			}
		}
	} // check Tof:barrel inner Tof 


	if(m_checkTof == 1) {
		NTuplePtr nt10(ntupleSvc(), "FILE1/tof2");
		if ( nt10 ) m_tuple10 = nt10;
		else {
			m_tuple10 = ntupleSvc()->book ("FILE1/tof2", CLID_ColumnWiseTuple, "ks N-Tuple example");
			if ( m_tuple10 )    {
				status = m_tuple10->addItem ("ptrk",   m_ptot_btof2);
				status = m_tuple10->addItem ("cntr",   m_cntr_btof2);
				status = m_tuple10->addItem ("ph",  m_ph_btof2);
				status = m_tuple10->addItem ("zhit", m_zhit_btof2);
				status = m_tuple10->addItem ("qual", m_qual_btof2);
				status = m_tuple10->addItem ("te",   m_te_btof2);
				status = m_tuple10->addItem ("tmu",   m_tmu_btof2);
				status = m_tuple10->addItem ("tpi",   m_tpi_btof2);
				status = m_tuple10->addItem ("tk",   m_tk_btof2);
				status = m_tuple10->addItem ("tp",   m_tp_btof2);
			}
			else    { 
				log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple10) << endmsg;
				return StatusCode::FAILURE;
			}
		}
	} // check Tof:barrel outter Tof


	NTuplePtr nt11(ntupleSvc(), "FILE1/pid");
	if ( nt11 ) m_tuple11 = nt11;
	else {
		m_tuple11 = ntupleSvc()->book ("FILE1/pid", CLID_ColumnWiseTuple, "ks N-Tuple example");
		if ( m_tuple11 )    {
			status = m_tuple11->addItem ("ptrk",   m_ptrk_pid);
			status = m_tuple11->addItem ("cost",   m_cost_pid);
			status = m_tuple11->addItem ("dedx",   m_dedx_pid);
			status = m_tuple11->addItem ("tof1",   m_tof1_pid);
			status = m_tuple11->addItem ("tof2",   m_tof2_pid);
			status = m_tuple11->addItem ("prob",   m_prob_pid);
		}
		else    { 
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple11) << endmsg;
			return StatusCode::FAILURE;
		}
	}
	//----------------------------------------------------------------------
	/*
	NTuplePtr nt12(ntupleSvc(), "FILE1/save");
	if ( nt12 ) m_tuple12 = nt12;
	else {
		m_tuple12 = ntupleSvc()->book ("FILE1/save", CLID_ColumnWiseTuple, "ks N-Tuple example");
		if ( m_tuple12 )    {
			status = m_tuple12->addItem ("ppos",   m_ppos_ratio);
			status = m_tuple12->addItem ("epos",   m_epos_ratio);
			status = m_tuple12->addItem ("depos",   m_depos_ratio);
			status = m_tuple12->addItem ("EPRatioPlus",   m_eppos_ratio);
			status = m_tuple12->addItem ("hitspos",   m_hitspos_ratio);
			status = m_tuple12->addItem ("pneg",   m_pneg_ratio);
			status = m_tuple12->addItem ("eneg",   m_eneg_ratio);
			status = m_tuple12->addItem ("deneg",   m_deneg_ratio);
			status = m_tuple12->addItem ("EPRatioMius",   m_epneg_ratio);
			status = m_tuple12->addItem ("hitsneg",   m_hitsneg_ratio);
			status = m_tuple12->addItem ("TMass",   m_tmass_ratio);


			status = m_tuple12->addItem ("posmucstat",   m_posmucstat);
			status = m_tuple12->addItem ("negmucstat",   m_negmucstat);

			status = m_tuple12->addItem ("posdepthMuc",   m_posdepthMuc);
			status = m_tuple12->addItem ("negdepthMuc",   m_negdepthMuc);
			status = m_tuple12->addItem ("poslayerMuc",   m_poslayerMuc);
			status = m_tuple12->addItem ("neglayerMuc",   m_neglayerMuc);
			status = m_tuple12->addItem ("posangMuc",   m_posangMuc);
			status = m_tuple12->addItem ("negangMuc",   m_negangMuc);


			status = m_tuple12->addItem ("poskalrechi2",   m_poskalrechi2);
			status = m_tuple12->addItem ("negkalrechi2",   m_negkalrechi2);
			status = m_tuple12->addItem ("poskalecLastLayer",   m_poskalecLastLayer);
			status = m_tuple12->addItem ("negkalecLastLayer",   m_negkalecLastLayer);
			status = m_tuple12->addItem ("poskalbrLastLayer",   m_poskalbrLastLayer);
			status = m_tuple12->addItem ("negkalbrLastLayer",   m_negkalbrLastLayer);
			status = m_tuple12->addItem ("poskaldepth",   m_poskaldepth);
			status = m_tuple12->addItem ("negkaldepth",   m_negkaldepth);
			status = m_tuple12->addItem ("poskaldof",   m_poskaldof);
			status = m_tuple12->addItem ("negkaldof",   m_negkaldof);
		}
		else    { 
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple12) << endmsg;
			return StatusCode::FAILURE;
		}
	}
	*/


	//
	//--------end of book--------
	//

	log << MSG::INFO << "successfully return from initialize()" <<endmsg;
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Rhopi::execute() {

	std::cout << "execute()" << std::endl;

	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in execute()" << endreq;

	SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
	int runNo=eventHeader->runNumber();
	int event=eventHeader->eventNumber();

	if (eventHeader->runNumber()<0)
	{
		SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

		if (!mcParticleCol)
		{
			std::cout << "Could not retrieve McParticelCol" << std::endl;
			return StatusCode::FAILURE;
		}

		else
		{
			Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
			Event::McParticle temp;
			m_idxmc=0;

			bool jpsiDecay = false;
			int jpsiIndex = -1;
			bool strange = false;

			for (; iter_mc != mcParticleCol->end(); iter_mc++)
			{
				if((*iter_mc)->primaryParticle()&&(*iter_mc)->particleProperty()==11&&((*iter_mc)->mother()).particleProperty()==11) {strange = true;}
				if ((*iter_mc)->primaryParticle()) continue;
				if (!(*iter_mc)->decayFromGenerator()) continue;
				//if ( ((*iter_mc)->mother()).trackIndex()<3 ) continue;
				if ((*iter_mc)->particleProperty() == 443) 
				{
					jpsiDecay = true;
					jpsiIndex = (*iter_mc)->trackIndex();
				}
				if (!jpsiDecay) continue;

				//int trkidx = (*iter_mc)->trackIndex() - rootIndex;

				int mcidx = ((*iter_mc)->mother()).trackIndex() - jpsiIndex;
				int pdgid = (*iter_mc)->particleProperty();
				if(strange &&((*iter_mc)->mother()).particleProperty()!=443) mcidx--; 
				if(pdgid == -22) continue;
				m_pdgid[m_idxmc] = pdgid;
				m_motheridx[m_idxmc] = mcidx;
				temp=(*iter_mc)->mother();
				m_motherpid[m_idxmc] = temp.particleProperty();

				if(pdgid == 443) m_drank[m_idxmc]=0;
				else
				{
					for(int i=1;i<100;i++)
					{
						if(temp.particleProperty()==443)
						{
							m_drank[m_idxmc]=i;
							break;
						}
						temp = temp.mother();
					}
				}

				m_idxmc++;    
			}

		}
	}
	log << MSG::DEBUG <<"run, evtnum = "
		<< runNo << " , "
		<< event <<endreq;
	cout<<"event "<<event<<endl;
	Ncut0++;

	SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
	//  log << MSG::INFO << "get event tag OK" << endreq;
	log << MSG::DEBUG <<"ncharg, nneu, tottks = " 
		<< evtRecEvent->totalCharged() << " , "
		<< evtRecEvent->totalNeutral() << " , "
		<< evtRecEvent->totalTracks() <<endreq;

	SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);
	//
	// check x0, y0, z0, r0
	// suggest cut: |z0|<5 && r0<1
	//
	Vint iGood, ipip, ipim;
	iGood.clear();
	ipip.clear();
	ipim.clear();
	Vp4 ppip, ppim;
	ppip.clear();
	ppim.clear();

	int nCharge = 0;

	Hep3Vector xorigin(0,0,0);

	//if (m_reader.isRunNumberValid(runNo)) {
	IVertexDbSvc*  vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if(vtxsvc->isVertexValid()){
		double* dbv = vtxsvc->PrimaryVertex(); 
		double*  vv = vtxsvc->SigmaPrimaryVertex();  
		//    HepVector dbv = m_reader.PrimaryVertex(runNo);
		//    HepVector vv = m_reader.SigmaPrimaryVertex(runNo);
		xorigin.setX(dbv[0]);
		xorigin.setY(dbv[1]);
		xorigin.setZ(dbv[2]);
	}

	for(int i = 0; i < evtRecEvent->totalCharged(); i++){
		EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isMdcTrackValid()) continue;
		RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
		double pch=mdcTrk->p();
		double x0=mdcTrk->x();
		double y0=mdcTrk->y();
		double z0=mdcTrk->z();
		double phi0=mdcTrk->helix(1);
		double xv=xorigin.x();
		double yv=xorigin.y();
		double Rxy=(x0-xv)*cos(phi0)+(y0-yv)*sin(phi0);
		m_vx0 = x0;
		m_vy0 = y0;
		m_vz0 = z0;
		m_vr0 = Rxy;

		HepVector a = mdcTrk->helix();
		HepSymMatrix Ea = mdcTrk->err();
		HepPoint3D point0(0.,0.,0.);   // the initial point for MDC recosntruction
		HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]); 
		VFHelix helixip(point0,a,Ea); 
		helixip.pivot(IP);
		HepVector vecipa = helixip.a();
		double  Rvxy0=fabs(vecipa[0]);  //the nearest distance to IP in xy plane
		double  Rvz0=vecipa[3];         //the nearest distance to IP in z direction
		double  Rvphi0=vecipa[1];
		m_rvxy0=Rvxy0;
		m_rvz0=Rvz0;
		m_rvphi0=Rvphi0;

		m_tuple1->write();
		//    if(fabs(z0) >= m_vz0cut) continue;
		//    if(fabs(Rxy) >= m_vr0cut) continue;

		if(fabs(Rvz0) >= 10.0) continue;
		if(fabs(Rvxy0) >= 1.0) continue;

		iGood.push_back(i);
		nCharge += mdcTrk->charge();
	}

	//
	// Finish Good Charged Track Selection
	//
	int nGood = iGood.size();
	log << MSG::DEBUG << "ngood, totcharge = " << nGood << " , " << nCharge << endreq;
	if((nGood != 2)||(nCharge!=0)){
		return StatusCode::SUCCESS;
	}
	Ncut1++;

	Vint iGam;
	iGam.clear();
	for(int i = evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
		EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isEmcShowerValid()) continue;
		RecEmcShower *emcTrk = (*itTrk)->emcShower();
		Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());
		// find the nearest charged track
		double eraw=emcTrk->energy();
		double the=emcTrk->theta();
		double time=emcTrk->time();

		if(time < 0||time >14) continue;							//time cut

		double e_threshold=10.0;

		if(fabs(cos(the))<0.82)
		{
			e_threshold = barEnergy;
		}
		else if((fabs(cos(the))>0.85) && (fabs(cos(the)) < 0.92))
		{
			e_threshold = endEnergy;
		}
		else 
		{
			continue;
		}

		if(eraw < e_threshold) continue;

		double dthe = 200.;
		double dphi = 200.;
		double dang = 200.; 
		for(int j = 0; j < evtRecEvent->totalCharged(); j++) {
			EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;
			if(!(*jtTrk)->isExtTrackValid()) continue;
			RecExtTrack *extTrk = (*jtTrk)->extTrack();
			if(extTrk->emcVolumeNumber() == -1) continue;
			Hep3Vector extpos = extTrk->emcPosition();
			//      double ctht = extpos.cosTheta(emcpos);
			double angd = extpos.angle(emcpos);
			double thed = extpos.theta() - emcpos.theta();
			double phid = extpos.deltaPhi(emcpos);
			thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
			phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
			if(angd < dang){
				dang = angd;
				dthe = thed;
				dphi = phid;
			}
		}
		if(dang>=200) continue;
		//double eraw = emcTrk->energy();
		dthe = dthe * 180 / (CLHEP::pi);
		dphi = dphi * 180 / (CLHEP::pi);
		dang = dang * 180 / (CLHEP::pi);
		m_dthe = dthe;
		m_dphi = dphi;
		m_dang = dang;
		m_eraw = eraw;
		m_tuple2->write();
		//if(eraw < m_energyThreshold) continue;
		//    if((fabs(dthe) < m_gammaThetaCut) && (fabs(dphi)<m_gammaPhiCut) ) continue;
		if(fabs(dang) < m_gammaAngleCut) continue;
		//
		// good photon cut will be set here
		//
		iGam.push_back(i);
	}

	//
	// Finish Good Photon Selection
	//
	int nGam = iGam.size();

	log << MSG::DEBUG << "num Good Photon " << nGam  << " , " <<evtRecEvent->totalNeutral()<<endreq;
	if(nGam<2 || nGam>4){
		return StatusCode::SUCCESS;
	}
	Ncut2++;
	/* 
	Vp4 pGamma;
	pGamma.clear();

	TLorentzVector p_Gamma;
	for(int i=0;i< nGam;i++)
	{
		EvtRecTrackIterator itTrk=evtRecTrackCol->begin()+iGam[i];
		RecEmcShower* emcTrk=(*itTrk)->emcShower();
		
		double eraw = emcTrk->energy();
		Hep3Vector gammaDirection(emcTrk->x()-vx_infit.x(),emcTrk->y(),emcTrk->z()-vx_infit.z());
		double phi = gammaDirection.phi();
		double the = gammaDirection.theta();

		HepLorentzVector ptrk;
		ptrk.setPx(eraw*sin(the)*cos(phi));
		ptrk.setPy(eraw*sin(the)*sin(phi));
		ptrk.setPz(eraw*cos(the));
		ptrk.setE(eraw);

		p_Gamma.SetPxPyPzE(ptrk.px(),ptrk.py(),ptrk.pz(),ptrk.e());
		pGamma.push_back(ptrk);

	}
	*/


	//
	//
	// check dedx infomation
	//
	//

	if(m_checkDedx == 1) {
		for(int i = 0; i < nGood; i++) {
			EvtRecTrackIterator  itTrk = evtRecTrkCol->begin() + iGood[i];
			if(!(*itTrk)->isMdcTrackValid()) continue;
			if(!(*itTrk)->isMdcDedxValid())continue;
			RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack();
			RecMdcDedx* dedxTrk = (*itTrk)->mdcDedx();
			m_ptrk = mdcTrk->p();

			m_chie = dedxTrk->chiE();
			m_chimu = dedxTrk->chiMu();
			m_chipi = dedxTrk->chiPi();
			m_chik = dedxTrk->chiK();
			m_chip = dedxTrk->chiP();
			m_ghit = dedxTrk->numGoodHits();
			m_thit = dedxTrk->numTotalHits();
			m_probPH = dedxTrk->probPH();
			m_normPH = dedxTrk->normPH();
			m_tuple7->write();
		}
	}

	//
	// check TOF infomation
	//


	if(m_checkTof == 1) {
		for(int i = 0; i < nGood; i++) {
			EvtRecTrackIterator  itTrk = evtRecTrkCol->begin() + iGood[i];
			if(!(*itTrk)->isMdcTrackValid()) continue;
			if(!(*itTrk)->isTofTrackValid()) continue;

			RecMdcTrack * mdcTrk = (*itTrk)->mdcTrack();
			SmartRefVector<RecTofTrack> tofTrkCol = (*itTrk)->tofTrack();

			double ptrk = mdcTrk->p();

			SmartRefVector<RecTofTrack>::iterator iter_tof = tofTrkCol.begin();
			for(;iter_tof != tofTrkCol.end(); iter_tof++ ) { 
				TofHitStatus *status = new TofHitStatus; 
				status->setStatus((*iter_tof)->status());
				if(!(status->is_barrel())){//endcap
					if( !(status->is_counter()) ) continue; // ? 
					if( status->layer()!=0 ) continue;//layer1
					double path=(*iter_tof)->path(); // ? 
					double tof  = (*iter_tof)->tof();
					double ph   = (*iter_tof)->ph();
					double rhit = (*iter_tof)->zrhit();
					double qual = 0.0 + (*iter_tof)->quality();
					double cntr = 0.0 + (*iter_tof)->tofID();
					double texp[5];
					for(int j = 0; j < 5; j++) {
						double gb = ptrk/xmass[j];
						double beta = gb/sqrt(1+gb*gb);
						texp[j] = 10 * path /beta/velc;
					}
					m_cntr_etof  = cntr;
					m_ptot_etof = ptrk;
					m_ph_etof   = ph;
					m_rhit_etof  = rhit;
					m_qual_etof  = qual;
					m_te_etof    = tof - texp[0];
					m_tmu_etof   = tof - texp[1];
					m_tpi_etof   = tof - texp[2];
					m_tk_etof    = tof - texp[3];
					m_tp_etof    = tof - texp[4];
					m_tuple8->write();
				}
				else {//barrel
					if( !(status->is_counter()) ) continue; // ? 
					if(status->layer()==1){ //layer1
						double path=(*iter_tof)->path(); // ? 
						double tof  = (*iter_tof)->tof();
						double ph   = (*iter_tof)->ph();
						double rhit = (*iter_tof)->zrhit();
						double qual = 0.0 + (*iter_tof)->quality();
						double cntr = 0.0 + (*iter_tof)->tofID();
						double texp[5];
						for(int j = 0; j < 5; j++) {
							double gb = ptrk/xmass[j];
							double beta = gb/sqrt(1+gb*gb);
							texp[j] = 10 * path /beta/velc;
						}

						m_cntr_btof1  = cntr;
						m_ptot_btof1 = ptrk;
						m_ph_btof1   = ph;
						m_zhit_btof1  = rhit;
						m_qual_btof1  = qual;
						m_te_btof1    = tof - texp[0];
						m_tmu_btof1   = tof - texp[1];
						m_tpi_btof1   = tof - texp[2];
						m_tk_btof1    = tof - texp[3];
						m_tp_btof1    = tof - texp[4];
						m_tuple9->write();
					}

					if(status->layer()==2){//layer2
						double path=(*iter_tof)->path(); // ? 
						double tof  = (*iter_tof)->tof();
						double ph   = (*iter_tof)->ph();
						double rhit = (*iter_tof)->zrhit();
						double qual = 0.0 + (*iter_tof)->quality();
						double cntr = 0.0 + (*iter_tof)->tofID();
						double texp[5];
						for(int j = 0; j < 5; j++) {
							double gb = ptrk/xmass[j];
							double beta = gb/sqrt(1+gb*gb);
							texp[j] = 10 * path /beta/velc;
						}

						m_cntr_btof2  = cntr;
						m_ptot_btof2 = ptrk;
						m_ph_btof2   = ph;
						m_zhit_btof2  = rhit;
						m_qual_btof2  = qual;
						m_te_btof2    = tof - texp[0];
						m_tmu_btof2   = tof - texp[1];
						m_tpi_btof2   = tof - texp[2];
						m_tk_btof2    = tof - texp[3];
						m_tp_btof2    = tof - texp[4];
						m_tuple10->write();
					} 
				}

				delete status; 
			} 
		} // loop all charged track
	}  // check tof


	//
	// Assign 4-momentum to each photon
	// 
	

	cout<<"before pid"<<endl;
	//
	// Assign 4-momentum to each charged track
	//
	ParticleID *pid = ParticleID::instance();
	for(int i = 0; i < nGood; i++) {
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i]; 
		//    if(pid) delete pid;
		pid->init();
		pid->setMethod(pid->methodProbability());
		//    pid->setMethod(pid->methodLikelihood());  //for Likelihood Method  

		pid->setChiMinCut(4);
		pid->setRecTrack(*itTrk);
		pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTofE()); // use PID sub-system
		pid->identify(pid->onlyPion() | pid->onlyKaon());    // seperater Pion/Kaon
		//    pid->identify(pid->onlyPion());
		//  pid->identify(pid->onlyKaon());
		pid->calculate();
		if(!(pid->IsPidInfoValid())) continue;
		RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack();
		m_ptrk_pid = mdcTrk->p();
		m_cost_pid = cos(mdcTrk->theta());
		m_dedx_pid = pid->chiDedx(2);
		m_tof1_pid = pid->chiTof1(2);
		m_tof2_pid = pid->chiTof2(2);
		m_prob_pid = pid->probPion();
		m_tuple11->write();

		//  if(pid->probPion() < 0.001 || (pid->probPion() < pid->probKaon())) continue;
		if(pid->probPion() < 0.001) continue;
		//    if(pid->pdf(2)<pid->pdf(3)) continue; //  for Likelihood Method(0=electron 1=muon 2=pion 3=kaon 4=proton) 

		RecMdcKalTrack* mdcKalTrk = (*itTrk)->mdcKalTrack();//After ParticleID, use RecMdcKalTrack substitute RecMdcTrack
		RecMdcKalTrack::setPidType  (RecMdcKalTrack::pion);//PID can set to electron, muon, pion, kaon and proton;The default setting is pion

		if(mdcKalTrk->charge() >0) {
			ipip.push_back(iGood[i]);
			HepLorentzVector ptrk;
			ptrk.setPx(mdcKalTrk->px());
			ptrk.setPy(mdcKalTrk->py());
			ptrk.setPz(mdcKalTrk->pz());
			double p3 = ptrk.mag();
			ptrk.setE(sqrt(p3*p3+mpi*mpi));

			//      ptrk = ptrk.boost(-0.011,0,0);//boost to cms

			ppip.push_back(ptrk);
		} else {
			ipim.push_back(iGood[i]);
			HepLorentzVector ptrk;
			ptrk.setPx(mdcKalTrk->px());
			ptrk.setPy(mdcKalTrk->py());
			ptrk.setPz(mdcKalTrk->pz());
			double p3 = ptrk.mag();
			ptrk.setE(sqrt(p3*p3+mpi*mpi));

			//      ptrk = ptrk.boost(-0.011,0,0);//boost to cms

			ppim.push_back(ptrk);
		}
	}

	/*
	   for(int i = 0; i < nGood; i++) {//for rhopi without PID
	   EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i];
	   RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack(); 
	   if(mdcTrk->charge() >0) {
	   ipip.push_back(iGood[i]);
	   HepLorentzVector ptrk;
	   ptrk.setPx(mdcTrk->px());
	   ptrk.setPy(mdcTrk->py());
	   ptrk.setPz(mdcTrk->pz());
	   double p3 = ptrk.mag();
	   ptrk.setE(sqrt(p3*p3+mpi*mpi));
	   ppip.push_back(ptrk);
	   } else {
	   ipim.push_back(iGood[i]);
	   HepLorentzVector ptrk;
	   ptrk.setPx(mdcTrk->px());
	   ptrk.setPy(mdcTrk->py());
	   ptrk.setPz(mdcTrk->pz());
	   double p3 = ptrk.mag();
	   ptrk.setE(sqrt(p3*p3+mpi*mpi));
	   ppim.push_back(ptrk);
	   }
	   }// without PID
	   */

	int npip = ipip.size();
	int npim = ipim.size();
	if(npip*npim != 1) return SUCCESS;

	Ncut3++;






	RecMdcKalTrack *pipTrk = (*(evtRecTrkCol->begin()+ipip[0]))->mdcKalTrack();
	RecMdcKalTrack *pimTrk = (*(evtRecTrkCol->begin()+ipim[0]))->mdcKalTrack();

	WTrackParameter wvpipTrk, wvpimTrk;
	wvpipTrk = WTrackParameter(mpi, pipTrk->getZHelix(), pipTrk->getZError());
	wvpimTrk = WTrackParameter(mpi, pimTrk->getZHelix(), pimTrk->getZError());

	/* Default is pion, for other particles:
	   wvppTrk = WTrackParameter(mp, pipTrk->getZHelixP(), pipTrk->getZErrorP());//proton
	   wvmupTrk = WTrackParameter(mmu, pipTrk->getZHelixMu(), pipTrk->getZErrorMu());//muon
	   wvepTrk = WTrackParameter(me, pipTrk->getZHelixE(), pipTrk->getZErrorE());//electron
	   wvkpTrk = WTrackParameter(mk, pipTrk->getZHelixK(), pipTrk->getZErrorK());//kaon
	   */
	//
	//    Test vertex fit
	//

	HepPoint3D vx(0., 0., 0.);
	HepSymMatrix Evx(3, 0);
	double bx = 1E+6;
	double by = 1E+6;
	double bz = 1E+6;
	Evx[0][0] = bx*bx;
	Evx[1][1] = by*by;
	Evx[2][2] = bz*bz;

	VertexParameter vxpar;
	vxpar.setVx(vx);
	vxpar.setEvx(Evx);

	VertexFit* vtxfit = VertexFit::instance();
	vtxfit->init();
	vtxfit->AddTrack(0,  wvpipTrk);
	vtxfit->AddTrack(1,  wvpimTrk);
	vtxfit->AddVertex(0, vxpar,0, 1);
	if(!vtxfit->Fit(0)) return SUCCESS;
	vtxfit->Swim(0);
	HepPoint3D vx_infit=vtxfit->vx(0);
	HepSymMatrix Evx_infit=vtxfit->Evx(0);

	WTrackParameter wpip = vtxfit->wtrk(0);
	WTrackParameter wpim = vtxfit->wtrk(1);

	//gamma pair

	Vp4 pGam;
	pGam.clear();
	for(int i = 0; i < nGam; i++) {
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGam[i]; 
		RecEmcShower* emcTrk = (*itTrk)->emcShower();
		double eraw = emcTrk->energy();
		Hep3Vector gammaDirection(emcTrk->x()-vx_infit.x(),emcTrk->y(),emcTrk->z()-vx_infit.z());
		double phi = gammaDirection.phi();
		double the = gammaDirection.theta();
	//	double phi = emcTrk->phi();
	//	double the = emcTrk->theta();
		HepLorentzVector ptrk;
		ptrk.setPx(eraw*sin(the)*cos(phi));
		ptrk.setPy(eraw*sin(the)*sin(phi));
		ptrk.setPz(eraw*cos(the));
		ptrk.setE(eraw);

		//    ptrk = ptrk.boost(-0.011,0,0);// boost to cms

		pGam.push_back(ptrk);
	}
	
	//
	// Loop each gamma pair, check ppi0 and pTot 
	//
	KalmanKinematicFit *kmfit=KalmanKinematicFit::instance();
	Vint ipi0gamma1,ipi0gamma2;
	ipi0gamma1.clear();
	ipi0gamma2.clear();
	vector<double> vkmchisq_pi0;
	vkmchisq_pi0.clear();
	int npi0;
	

	//HepLorentzVector pTot;
	for(int i = 0; i < nGam - 1; i++){
		for(int j = i+1; j < nGam; j++) {
			if(fabs((pGam[i]+pGam[j]).m()-0.135) > 0.06) continue;
			
			RecEmcShower* gammaTrk1=(*(evtRecTrkCol->begin()+iGam[i]))->emcShower();
			RecEmcShower* gammaTrk2=(*(evtRecTrkCol->begin()+iGam[j]))->emcShower();

			kmfit->init();
			kmfit->AddTrack(0,0.0,gammaTrk1);
			kmfit->AddTrack(1,0.0,gammaTrk2);
			kmfit->AddResonance(0,0.1349766,0,1);

			bool okfit=kmfit->Fit();

			ipi0gamma1.push_back(i);
			ipi0gamma2.push_back(j);
			vkmchisq_pi0.push_back(kmfit->chisq());
		}
	}
	npi0=ipi0gamma1.size();
	if( npi0< 1 )
	{
		return StatusCode::SUCCESS;
	}

	double minchisqpi0=9999.;
	int gamnb1=-1;
	int gamnb2=-1;
	for(int i=0;i<npi0;i++)
	{
		if(vkmchisq_pi0[i]<minchisqpi0)
		{
			minchisqpi0=vkmchisq_pi0[i];
			gamnb1=ipi0gamma1[i];
			gamnb2=ipi0gamma2[i];
		}

	}

	m_chisq_pi0=minchisqpi0;


			/*
			HepLorentzVector p2g = pGam[i] + pGam[j];
			pTot = ppip[0] + ppim[0];
			pTot += p2g;
			m_m2gg = p2g.m();
			m_etot = pTot.e();
			m_tuple3 -> write();
			*/


	//KinematicFit * kmfit = KinematicFit::instance();

	//
	//  Apply Kinematic 4C fit
	// 
	
	int nevt=0;
	len=4;
	cout<<"before 4c"<<endl;
	if(m_test4C==1){

		cout<<"start to set cms"<<endl;
		HepLorentzVector ecms(0.034,0,0,3.097);
		cout<<"start to get gamma1"<<endl;
		RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[gamnb1]))->emcShower();
		cout<<"start to get gamma2"<<endl;
		RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+iGam[gamnb2]))->emcShower();
		cout<<"kmfit before ini!"<<endl;
		kmfit->init();
		kmfit->setBeamPosition(vx_infit);
		kmfit->setVBeamPosition(Evx_infit);
		kmfit->AddTrack(0, wpip);
		kmfit->AddTrack(1, wpim);
		kmfit->AddTrack(2, 0.0, g1Trk);
		kmfit->AddTrack(3, 0.0, g2Trk);
		kmfit->AddFourMomentum(0, ecms);

		bool okfit=kmfit->Fit();
//		if(!okfit) return StatusCode::SUCCESS;
//		kmchisq_4c[nevt]=kmfit->chisq();
		m_chisq_4c=kmfit->chisq();

		cout<<"end of 4C"<<endl;
		HepLorentzVector gamma1_=kmfit->pfit(2);
		HepLorentzVector gamma2_=kmfit->pfit(3);
		HepLorentzVector pip_=kmfit->pfit(0);
		HepLorentzVector pim_=kmfit->pfit(1);
		
		HepLorentzVector pi0_=gamma1_+gamma2_;

		mpi0 = pi0_.m();

		TLorentzVector p_gamma1,p_gamma2;
		TLorentzVector p_pip,p_pim;

		p_gamma1.SetPxPyPzE(gamma1_.px(), gamma1_.py(), gamma1_.pz(), gamma1_.e());
		p_gamma2.SetPxPyPzE(gamma2_.px(), gamma2_.py(), gamma2_.pz(), gamma2_.e());
		
		p_pip.SetPxPyPzE(pip_.px(), pip_.py(), pip_.pz(), pip_.e());	
		p_pim.SetPxPyPzE(pim_.px(), pim_.py(), pim_.pz(), pim_.e());	

		lvtrpi0[0]=pi0_.px();
		lvtrpi0[1]=pi0_.py();
		lvtrpi0[2]=pi0_.pz();
		lvtrpi0[3]=pi0_.e();

		lvtrpip[0]=pip_.px();
		lvtrpip[1]=pip_.py();
		lvtrpip[2]=pip_.pz();
		lvtrpip[3]=pip_.e();

		lvtrpim[0]=pim_.px();
		lvtrpim[1]=pim_.py();
		lvtrpim[2]=pim_.pz();
		lvtrpim[3]=pim_.e();

	
		TLorentzVector p_gamma1_unfitted,p_gamma2_unfitted;
		TLorentzVector p_pip_unfitted,p_pim_unfitted;
	
		

		p_gamma1_unfitted.SetPxPyPzE((pGam[gamnb1]).px(), (pGam[gamnb1]).py(), (pGam[gamnb1]).pz(), (pGam[gamnb1]).e());
		p_gamma2_unfitted.SetPxPyPzE((pGam[gamnb2]).px(), (pGam[gamnb2]).py(), (pGam[gamnb2]).pz(), (pGam[gamnb2]).e());

		p_pip_unfitted.SetPxPyPzE((wpip.p()).px(), (wpip.p()).py(), (wpip.p()).pz(), (wpip.p()).e());
		p_pim_unfitted.SetPxPyPzE((wpim.p()).px(), (wpim.p()).py(), (wpim.p()).pz(), (wpim.p()).e());
	
		TLorentzVector p_pi0_unfitted=p_gamma1_unfitted+p_gamma2_unfitted;

		lvtrpi0unfit[0]=p_pi0_unfitted.Px();
		lvtrpi0unfit[1]=p_pi0_unfitted.Py();
		lvtrpi0unfit[2]=p_pi0_unfitted.Pz();
		lvtrpi0unfit[3]=p_pi0_unfitted.E();
		
		lvtrpipunfit[0]=p_pip_unfitted.Px();
		lvtrpipunfit[1]=p_pip_unfitted.Py();
		lvtrpipunfit[2]=p_pip_unfitted.Pz();
		lvtrpipunfit[3]=p_pip_unfitted.E();
		
		lvtrpimunfit[0]=p_pim_unfitted.Px();
		lvtrpimunfit[1]=p_pim_unfitted.Py();
		lvtrpimunfit[2]=p_pim_unfitted.Pz();
		lvtrpimunfit[3]=p_pim_unfitted.E();
		
		
		/* 
		new ((*gamma1)[nevt]) TLorentzVector(p_gamma1);
		new ((*gamma2)[nevt]) TLorentzVector(p_gamma2);

		new ((*pip)[nevt]) TLorentzVector(p_pip);
		new ((*pim)[nevt]) TLorentzVector(p_pim);
		
		TLorentzVector p_gamma1_unfitted,p_gamma2_unfitted;
		TLorentzVector p_pip_unfitted,p_pim_unfitted;
	

		p_gamma1_unfitted.SetPxPyPzE((pGam[gamnb1]).px(), (pGam[gamnb1]).py(), (pGam[gamnb1]).pz(), (pGam[gamnb1]).e());
		p_gamma2_unfitted.SetPxPyPzE((pGam[gamnb2]).px(), (pGam[gamnb2]).py(), (pGam[gamnb2]).pz(), (pGam[gamnb2]).e());

		p_pip_unfitted.SetPxPyPzE((wpip.p()).px(), (wpip.p()).py(), (wpip.p()).pz(), (wpip.p()).e());
		p_pim_unfitted.SetPxPyPzE((wpim.p()).px(), (wpim.p()).py(), (wpim.p()).pz(), (wpim.p()).e());

		new ((*gamma1_unfitted)[nevt]) TLorentzVector(p_gamma1_unfitted);
		new ((*gamma2_unfitted)[nevt]) TLorentzVector(p_gamma2_unfitted);
		new ((*pip_unfitted)[nevt]) TLorentzVector(p_pip_unfitted);
		new ((*pim_unfitted)[nevt]) TLorentzVector(p_pim_unfitted);

	//	id_gamma1[nevt]=ipi0gamma1[i1];
	//	id_gamma2[nevt]=ipi0gamma2[i1];

//		kmchisq_pi0[nevt]=vkmchisq_pi0[i1];
		kmchisq_pi0[nevt]=minchisqpi0;

	//	nevt++;
	*/


	}

		/*
	 if(m_test4C==1) {
		//    double ecms = 3.097;
		HepLorentzVector ecms(0.034,0,0,3.097);

		double chisq = 9999.;
		int ig1 = -1;
		int ig2 = -1;
		for(int i = 0; i < nGam-1; i++) {
			RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[i]))->emcShower();
			for(int j = i+1; j < nGam; j++) {
				RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+iGam[j]))->emcShower();
				kmfit->init();
				kmfit->AddTrack(0, wpip);
				kmfit->AddTrack(1, wpim);
				kmfit->AddTrack(2, 0.0, g1Trk);
				kmfit->AddTrack(3, 0.0, g2Trk);
				kmfit->AddFourMomentum(0, ecms);
				bool oksq = kmfit->Fit();
				if(oksq) {
					double chi2 = kmfit->chisq();
					if(chi2 < chisq) {
						chisq = chi2;
						ig1 = iGam[i];
						ig2 = iGam[j];
					}
				}
			}
		}

		if(chisq < 200) { 

			RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+ig1))->emcShower();
			RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+ig2))->emcShower();
			kmfit->init();
			kmfit->AddTrack(0, wpip);
			kmfit->AddTrack(1, wpim);
			kmfit->AddTrack(2, 0.0, g1Trk);
			kmfit->AddTrack(3, 0.0, g2Trk);
			kmfit->AddFourMomentum(0, ecms);
			bool oksq = kmfit->Fit();
			if(oksq) {
				HepLorentzVector ppi0 = kmfit->pfit(2) + kmfit->pfit(3);
				m_mpi0 = ppi0.m();
				m_chi1 = kmfit->chisq();
				m_tuple4->write();
				Ncut4++;
			}
		}
	}
	*/

	//
	//  Apply Kinematic 5C Fit
	//
	Ncut4++;
	// find the best combination over all possible pi+ pi- gamma gamma pair
	int write_info=1;
	
	if(m_test5C==1) {
		//    double ecms = 3.097;
		HepLorentzVector ecms(0.034,0,0,3.097);
		double chisq = 9999.;
		int ig1 = -1;
		int ig2 = -1;
		for(int i = 0; i < nGam-1; i++) {
			RecEmcShower *g1Trk = (*(evtRecTrkCol->begin()+iGam[i]))->emcShower();
			for(int j = i+1; j < nGam; j++) {
				RecEmcShower *g2Trk = (*(evtRecTrkCol->begin()+iGam[j]))->emcShower();
				kmfit->init();
				kmfit->AddTrack(0, wpip);
				kmfit->AddTrack(1, wpim);
				kmfit->AddTrack(2, 0.0, g1Trk);
				kmfit->AddTrack(3, 0.0, g2Trk);
				kmfit->AddResonance(0, 0.135, 2, 3);
				kmfit->AddFourMomentum(1, ecms);
				if(!kmfit->Fit(0)) continue;
				if(!kmfit->Fit(1)) continue;
				bool oksq = kmfit->Fit();
				if(oksq) {
					double chi2 = kmfit->chisq();
					if(chi2 < chisq) {
						chisq = chi2;
						ig1 = iGam[i];
						ig2 = iGam[j];
					}
				}
			}
		}


		log << MSG::INFO << " chisq = " << chisq <<endreq;

		if(chisq < 200) {
			RecEmcShower* g1Trk = (*(evtRecTrkCol->begin()+ig1))->emcShower();
			RecEmcShower* g2Trk = (*(evtRecTrkCol->begin()+ig2))->emcShower();

			kmfit->init();
			kmfit->AddTrack(0, wpip);
			kmfit->AddTrack(1, wpim);
			kmfit->AddTrack(2, 0.0, g1Trk);
			kmfit->AddTrack(3, 0.0, g2Trk);
			kmfit->AddResonance(0, 0.135, 2, 3);
			kmfit->AddFourMomentum(1, ecms);
			bool oksq = kmfit->Fit();
			if(oksq){
				HepLorentzVector ppi0 = kmfit->pfit(2) + kmfit->pfit(3);
				HepLorentzVector prho0 = kmfit->pfit(0) + kmfit->pfit(1);
				HepLorentzVector prhop = ppi0 + kmfit->pfit(0);
				HepLorentzVector prhom = ppi0 + kmfit->pfit(1);

				m_chi2  = kmfit->chisq();
				m_mrh0 = prho0.m();
				m_mrhp = prhop.m();
				m_mrhm = prhom.m();
				double eg1 = (kmfit->pfit(2)).e();
				double eg2 = (kmfit->pfit(3)).e();
				double fcos = abs(eg1-eg2)/ppi0.rho();
				m_tuple5->write();
				Ncut5++;
				// 
				//  Measure the photon detection efficiences via
				//          J/psi -> rho0 pi0
				//

				if(fabs(prho0.m()-0.770)<0.150) {  
					if(fabs(fcos)<0.99) {
						m_fcos = (eg1-eg2)/ppi0.rho();
						m_elow =  (eg1 < eg2) ? eg1 : eg2;
						m_tuple6->write();
						write_info=1;
						Ncut6++;
					}
				} // rho0 cut


				/*
				//control 3rhopi
				int isrhopi=0;
				if(fabs(prho0.m()-0.770)<0.150)	isrhopi=1;
				else if(fabs(prhop.m()-0.770)<0.150)	isrhopi=1;
				else if(fabs(prhom.m()-0.770)<0.150)	isrhopi=1;
				else isrhopi=0;

				if(isrhopi==1)
				{
				if(fabs(fcos)<0.99)
				{
				//	m_fcos = (eg1-eg2)/ppi0.rho();
				//	m_elow =  (eg1 < eg2) ? eg1 : eg2;
				m_tuple6->write();
				write_info=1;
				Ncut6++;
				}
				}
				*/

			}  //oksq
		} 
	}

	//-------------------------------------------------------------------------

	if(write_info==1)
	{

		if(m_checkRatio==1)
		{
			cout<<"Checkratio!"<<endl;
			for(int i=0;i<nGood;i++)
			{
				int emcValid=1;
				double deTrk=-10.0;
				int nhits=-10;
				EvtRecTrackIterator itTrk = evtRecTrkCol->begin()+iGood[i];

				cout<<"get track successfully!"<<endl;
				if(!(*itTrk)->isMdcTrackValid()) continue;
				cout<<"get MDCtrack successfully!"<<endl;
				if(!(*itTrk)->isEmcShowerValid()) 
				{
					emcValid=0;
					cout<<"emc valid"<<endl;
					cout<<"deTrk in EMC:"<<deTrk<<endl;
					cout<<"emcValid is :"<<emcValid<<endl;
				}

				RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();

				if(emcValid==1)
				{
					RecEmcShower *emcTrk=(*itTrk)->emcShower();
					deTrk=emcTrk->energy();	
					nhits=emcTrk->numHits();
					cout<<"get EMCtrack successfully!"<<endl;
				}
				else 
				{
					deTrk= -1.0;
				}
				//	else	return StatusCode::SUCCESS;


				//cout<<"start to get info!"<<endl;
				//cout<<"charge is:"<<mdcTrk->charge()<<endl;
				if(mdcTrk->charge()>0)
				{
					m_ppos_ratio=mdcTrk->p();
					//	cout<<"get momentum!"<<m_ppos_ratio<<endl;
					m_epos_ratio=sqrt(m_ppos_ratio*m_ppos_ratio+xmass[2]*xmass[2]);
					//	cout<<"get e!"<<m_epos_ratio<<endl;
					m_depos_ratio=deTrk;
					//	cout<<"get de!"<<m_depos_ratio<<endl;
					m_eppos_ratio=deTrk/m_ppos_ratio;
					//	cout<<"get ep!"<<endl;
					m_hitspos_ratio=nhits;
					m_hits= m_hitspos_ratio;
					//	cout<<"get hits!"<<endl;
					//			m_rtheta0=mdcTrk->theta();
				}

				else if(mdcTrk->charge()<0)
				{
					m_pneg_ratio=mdcTrk->p();
					//	cout<<"get momentum!:"<<m_pneg_ratio<<endl;
					m_eneg_ratio=sqrt(m_pneg_ratio*m_pneg_ratio+xmass[2]*xmass[2]);
					//	cout<<"get e!"<<m_eneg_ratio<<endl;
					m_deneg_ratio=deTrk;
					//	cout<<"get de!"<<m_deneg_ratio<<endl;
					m_epneg_ratio=deTrk/m_pneg_ratio;
					//	cout<<"get ep!"<<endl;
					m_hitsneg_ratio=nhits;
					m_hits = m_hitsneg_ratio;
					//	cout<<"get hits!"<<endl;
					//			m_rtheta1=mdcTrk->theta();
				}
				else
				{
					return StatusCode::SUCCESS;
				}

				if(emcValid==0)
				{
					cout<<"deTrk in EMC:"<<deTrk<<endl;
				}

			}

			m_tmass_ratio=m_epos_ratio+m_eneg_ratio;
			Ncutratio++;
			cout<<"end of Ratio checking!"<<endl;

			//here is cut
			/*	
				if(m_depos_ratio<m_ene_lowThreshold || m_depos_ratio>m_ene_highThreshold) return StatusCode::SUCCESS;
				if(m_deneg_ratio<m_ene_lowThreshold || m_deneg_ratio>m_ene_highThreshold) return StatusCode::SUCCESS;

				if(m_eppos_ratio > m_ep_ratioThreshold) return StatusCode::SUCCESS;
				if(m_epneg_ratio > m_ep_ratioThreshold) return StatusCode::SUCCESS;
				*/
		}

		//-------------------------------------------------------------------------
		if(m_checkMuc==1)
		{

			cout<<"Muc!"<<endl;
			//m_posmucstat=0;
			//m_negmucstat=0;
			//double p_pos=0.0;
			//double p_neg=0.0;
			for(int i=0;i<nGood;i++)
			{

				EvtRecTrackIterator itTrk = evtRecTrkCol->begin()+iGood[i];
				if(!(*itTrk)->isMdcTrackValid()) continue;
				RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();

				if(!(*itTrk)->isMucTrackValid()) 
				{
					cout<<"muc invalid"<<endl;
					if(mdcTrk->charge()>0) m_posmucstat=-1;
					if(mdcTrk->charge()<0) m_negmucstat=-1;
					continue;
				}
				RecMucTrack *mucTrk = (*itTrk)->mucTrack();

				if(!(*itTrk)->isExtTrackValid()) continue;

				RecExtTrack *extTrk = (*itTrk)->extTrack();
				Hep3Vector extmuc = extTrk->mucPosition();
				Hep3Vector mucpos = (mucTrk->px(),mucTrk->py(),mucTrk->pz());

				double angg=extmuc.angle(mucpos);
				if(angg>=200) continue;

				angg = angg * 180 / (CLHEP::pi);

				if(mdcTrk->charge()>0)
				{
					m_posmucstat=1;
					m_posdepthMuc=mucTrk->depth();
					m_poslayerMuc=mucTrk->numLayers();
					m_layerMuc = m_poslayerMuc;
					m_posangMuc=angg;
					m_poskalrechi2=mucTrk->kalRechi2();
					m_kaldof=mucTrk->kaldof();
					m_poskaldepth=mucTrk->kaldepth();
					m_poskalbrLastLayer=mucTrk->kalbrLastLayer();
					m_poskalecLastLayer=mucTrk->kalecLastLayer();
					  m_chi2 = mucTrk->chi2();
					  m_maxHitsInLayer = mucTrk->maxHitsInLayer();
						
			             m_kaldepth=mucTrk->kaldepth();
			             m_kalbrLastLayer=mucTrk->kalbrLastLayer();
			             m_kalecLastLayer=mucTrk->kalecLastLayer();
			          //   m_kaldof=m_poskaldof;
			             m_brLastLayer=mucTrk->brLastLayer();
			             m_ecLastLayer=mucTrk->ecLastLayer();


				}

				else if(mdcTrk->charge()<0)
				{
					m_negmucstat=1;
					m_negdepthMuc=mucTrk->depth();
					m_neglayerMuc=mucTrk->numLayers();
					m_layerMuc = m_neglayerMuc;
					m_negangMuc=angg;
					m_negkalrechi2=mucTrk->kalRechi2();
					m_negkaldof=mucTrk->kaldof();
					m_negkaldepth=mucTrk->kaldepth();
					m_negkalbrLastLayer=mucTrk->kalbrLastLayer();
					m_negkalecLastLayer=mucTrk->kalecLastLayer();
				  m_chi2 = mucTrk->chi2();
				  m_maxHitsInLayer = mucTrk->maxHitsInLayer();
			
		            m_kaldepth=mucTrk->kaldepth();
		             m_kalbrLastLayer=mucTrk->kalbrLastLayer();
		             m_kalecLastLayer=mucTrk->kalecLastLayer();
		        //     m_kaldof=m_negkaldof;
		             m_brLastLayer=mucTrk->brLastLayer();
		             m_ecLastLayer=mucTrk->ecLastLayer();
				
				
				}

				else
				{
					return StatusCode::SUCCESS;
				}
			}
			Ncutmuc++;

		}
		//m_tuple12->write();
		TreeAna->Fill();
		//-------------------------------------------------------------------------

	}



	return StatusCode::SUCCESS;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Rhopi::finalize() {
	saveFile->cd();
	TreeAna->Write();
	saveFile->Close();

	cout<<"total number:         "<<Ncut0<<endl;
	cout<<"nGood==2, nCharge==0: "<<Ncut1<<endl;
	cout<<"nGam>=2:              "<<Ncut2<<endl;
	cout<<"Pass Pid:             "<<Ncut3<<endl;
	cout<<"Pass 4C:              "<<Ncut4<<endl;
//	cout<<"Pass 5C:              "<<Ncut5<<endl;
	cout<<"J/psi->rho pi:      "<<Ncut6<<endl;
	cout<<"write ep              "<<Ncutratio<<endl;
	cout<<"write muc:            "<<Ncutmuc<<endl;
	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in finalize()" << endmsg;
	return StatusCode::SUCCESS;
}

