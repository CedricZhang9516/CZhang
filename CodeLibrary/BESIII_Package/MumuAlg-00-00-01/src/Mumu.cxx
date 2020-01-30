#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/IHistogramSvc.h"


#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "McTruth/McParticle.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"

#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"

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

#include "MumuAlg/Mumu.h"
//#include "VertexFit/IVertexDbsvc.h"
#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"

#include "TMath.h"
#include <vector>
#include <iostream>
#include <fstream>

//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mpi = 0.13957;
const double mmu = 0.105658;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};

//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm

typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;

//int Ncut0,Ncut1,Ncut2,Ncut3,Ncut4,Ncut5,Ncut6,Ncut7,Ncut8,Ncut9,Ng1,Ng2,Ng3;
int Ncut0 = 0;		//total event
int Ncut1 = 0;		//Pass good charged tracks cut
int Ncut2 = 0;		//Pass good photon
int Ncut3 = 0;		//Pass E/p
int Ncut4 = 0;		//Pass MUC
int Ncut5 = 0;		//Pass 4C
int Ncut6 = 0;		//Pass 5C

int Ng1 = 0;
int Ng2 = 0;
int NgAbove2 = 0;

/////////////////////////////////////////////////////////////////////////////

Mumu::Mumu(const std::string& name, ISvcLocator* pSvcLocator) :
	Algorithm(name, pSvcLocator) {

		//Declare the properties
		declareProperty("OutputFileName",  m_OutputFileName  );
		declareProperty("Ecms",  m_Ecms = 3.097);
		//declareProperty("EnergySpread",  m_EnergySpread = 0.0011);
		declareProperty("saveTopo", m_saveTopo = 1);//need to be re-evaluated when running different samples(1 for MC)
		declareProperty("saveMCTruth", m_saveMCTruth = 0);//need to be re-evaluated when running different samples(only 1 for exclusiveMC)

		declareProperty("saveTopoTree", m_saveTopoTree = 0);//need to be re-evaluated when running different samples(1 for MC)
		declareProperty("saveNbInfo", m_saveNbInfo = 1);//need to be re-evaluated when running different samples(1 for MC)
		
		//declareProperty("nbOfTrack",m_nbTrk = 2);//need to re-eevaluated when the number of tracks has changed.
		//For charged track
		//
		//origin
		//declareProperty("Vr0cut", m_vr0cut=1.0);
		//declareProperty("Vz0cut", m_vz0cut=10.0);

		//changed
		declareProperty("Vr0cut", m_vr0cut=1.0);
		declareProperty("Vz0cut", m_vz0cut=10.0);

		//for good photon selection
		declareProperty("EnergyThreshold", m_energyThreshold=0.04);
		declareProperty("GammaPhiCut", m_gammaPhiCut=20.0);
		declareProperty("GammaThetaCut", m_gammaThetaCut=20.0);
		//declareProperty("GammaAngleCut", m_gammaAngleCut=20.0);
		declareProperty("GammaAngleCut", m_gammaAngleCut=10.0);
		declareProperty("BarrelEnergyThreshold", m_barrelEnergyThreshold=0.025);
		declareProperty("EndEnergyThreshold",m_endEnergyThreshold=0.050);


		//for test4c and pid
		declareProperty("Test4C", m_test4C = 1);
		declareProperty("Test5C", m_test5C = 0);
		declareProperty("CheckDedx", m_checkDedx = 0);
		declareProperty("CheckTof",  m_checkTof = 0);
		//////////////////////////////////////////////////////////////////////////////
		////////my private value
		/////////////////////////////////////////////////////////////////////////////
		declareProperty("Ene_lowThreshold",m_ene_lowThreshold = 0.15);
		declareProperty("Ene_highThreshold",m_ene_highThreshold = 0.24);
		declareProperty("Ep_ratioThreshold",m_ep_ratioThreshold = 0.3);
		declareProperty("CheckRatio",m_checkRatio = 1);
		declareProperty("PtThreshold",m_pt_Threshold= 0.3); 
		declareProperty("CheckMuc",m_checkMuc = 1);
		declareProperty("layerMuc",m_layerMuc = 1);
		declareProperty("hits",m_hits = 1);
		
		declareProperty("maxHitsInLayer",m_maxHitsInLayer);
		declareProperty("chi2",m_chi2);
		    declareProperty("kalRechi2",m_kalRechi2);
		    declareProperty("kaldof" , m_kaldof);  
		    declareProperty("kaldepth"  ,m_kaldepth);
		    declareProperty("kalbrLastLayer",  m_kalbrLastLayer);
		    declareProperty("kalecLastLayer" , m_kalecLastLayer);  
		    declareProperty("dof" , m_dof);
		    declareProperty("brLastLayer" , m_brLastLayer);
			    declareProperty("ecLastLayer" , m_ecLastLayer);
							 
			    declareProperty("Mdcchi2" , m_Mdcchi2);
		    declareProperty("ndof" , m_ndof);
			    declareProperty("nhits" , m_nhits);
				 declareProperty("nlayer" , m_nlayer);

				 declareProperty("emcmoment1",m_emcmoment1);
	//	declareProperty("nhits",m_nhits);
	//	declareProperty("nlayer",m_nlayer);
	//
	//
		///////////////////////////  end     ///////////////////////////////////////

	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Mumu::initialize(){
	MsgStream log(msgSvc(), name());
	std::cout<<"~~~~~thx~~~ lify's initialize has started!"<<std::endl;
	log << MSG::INFO << "in initialize()" << endmsg;
	StatusCode status;

	//Output name
    TString s_OutputFileName(m_OutputFileName);

	//Tree and File Modified
	saveFile = new TFile(s_OutputFileName, "recreate");
//	TreeAna = new TTree("save", "save");
	TopoTree = new TTree("topoall","topoall");
	NbInfo = new TTree("nbinfo","nbinfo");
	TreeAna = new TTree("save","save");
	//Overall info
	TreeAna->Branch("runid", &runid, "runid/I");
	TreeAna->Branch("evtid", &evtid, "evtid/I");

	if(m_saveNbInfo == 1)
	{
		NbInfo->Branch("Ncut0", &Ncut0, "Ncut0/I");
		NbInfo->Branch("Ncut1", &Ncut1, "Ncut1/I");
		NbInfo->Branch("Ncut2", &Ncut2, "Ncut2/I");
		NbInfo->Branch("Ncut3", &Ncut3, "Ncut3/I");
		NbInfo->Branch("Ncut4", &Ncut4, "Ncut4/I");
		NbInfo->Branch("Ncut5", &Ncut5, "Ncut5/I");
		NbInfo->Branch("Ncut6", &Ncut6, "Ncut6/I");
	}

	//No. of each events
	TreeAna->Branch("nevt", &nevt, "nevt/I");
	TreeAna->Branch("nNEUTRAL", &nNEUTRAL, "nNEUTRAL/I");
	TreeAna->Branch("nCHARGED",&nCHARGED,"nCHARGED/I");
	TreeAna->Branch("nTRACKS",&nTRACKS,"nTRACKS/I");
	TreeAna->Branch("nGamma", &nGamma, "nGamma/I");

	//parimary vertex and track info
	TreeAna->Branch("vx0", &m_vx0, "vx0/D");
	TreeAna->Branch("vy0", &m_vy0, "vy0/D");
	TreeAna->Branch("vz0", &m_vz0, "vz0/D");
	TreeAna->Branch("vr0", &m_vr0, "vr0/D");
	TreeAna->Branch("rvxy0", &m_rvxy0, "rvxy0/D");
	TreeAna->Branch("rvz0", &m_rvz0, "rvz0/D");
	TreeAna->Branch("rvphi0", &m_rvphi0, "rvphi0/D");
	TreeAna->Branch("rtheta0", &m_rtheta0, "rtheta0/D");
	TreeAna->Branch("rtheta1", &m_rtheta1, "rtheta1/D");

	//momentum and energy
	//positive
	TreeAna->Branch("ppos", &m_ppos_ratio, "ppos/D");
	TreeAna->Branch("epos", &m_epos_ratio, "epos/D");
	TreeAna->Branch("depos", &m_depos_ratio, "depos/D");
	TreeAna->Branch("EPRatioPlus", &m_eppos_ratio, "EPRatioPlus/D");
	TreeAna->Branch("hitspos", &m_hitspos_ratio, "hitspos/D");
	//negative
	TreeAna->Branch("pneg", &m_pneg_ratio, "pneg/D");
	TreeAna->Branch("eneg", &m_eneg_ratio, "eneg/D");
	TreeAna->Branch("deneg", &m_deneg_ratio, "deneg/D");
	TreeAna->Branch("EPRatioMinu", &m_epneg_ratio, "EPRatioMinu/D");
	TreeAna->Branch("hitsneg", &m_hitsneg_ratio, "hitsneg/D");
	//total mass of two tracks
	TreeAna->Branch("TMass", &m_tmass_ratio, "TMass/D");
	
	TreeAna->Branch("hits",&m_hits, "hits/D");
	//TreeAna->Branch("layerMuc",&m_layerMuc, "layerMuc/D");

	//my new emc vars
	//emcmoment1

	 TreeAna->Branch("emcmoment1",&m_emcmoment1,"m_emcmoment1/D");
	  


	 TreeAna->Branch("kalRechi2",&m_kalRechi2,"m_kalRechi2/D");
	  TreeAna->Branch("kaldof",&m_kaldof,"m_kaldof/I");  
	 TreeAna->Branch("kaldepth",&m_kaldepth,"m_kaldepth/D");
	       TreeAna->Branch("kalbrLastLayer",&m_kalbrLastLayer,"m_kalbrLastLayer/I");
	       TreeAna->Branch("kalecLastLayer",&m_kalecLastLayer,"m_kalecLastLayer/I");  
	       TreeAna->Branch("dof",&m_dof,"m_dof/I");
	       TreeAna->Branch("brLastLayer",&m_brLastLayer,"m_brLastLayer/I");
	       TreeAna->Branch("ecLastLayer",&m_ecLastLayer,"m_ecLastLayeri/I");
	       TreeAna->Branch("ndof",&m_ndof,"m_ndof/I");
	       TreeAna->Branch("nhits",&m_nhits,"m_nhits/I");
	       TreeAna->Branch("nlayer",&m_nlayer,"m_nlayer/I");

	//for 4C
	TreeAna->Branch("chi4C", &m_chi4C, "chi4C/D");
	TreeAna->Branch("mmu0", &m_mmu0, "mmu0/D");

	//for 5c
	TreeAna->Branch("chi5C", &m_chi5C, "chi5C/D");
	TreeAna->Branch("mmu1", &m_mmu1, "mmu1/D");

	TreeAna->Branch("chiDeDx", chiDeDx, "chiDeDx[4][5]/D");
	TreeAna->Branch("chiTof1", chiTof1, "chiTof1[4][5]/D");
	TreeAna->Branch("chiTof2", chiDeDx, "chiTof2[4][5]/D");
	TreeAna->Branch("chisq_pid", chisq_pid, "chisq_pid[4][5]/D");
	TreeAna->Branch("prob", prob, "prob[4][5]/D");

	/*
	   if(m_saveTopo == 1)
	   {
	   TreeAna->Branch("indexmc", &m_idxmc, "indexmc/I");
	   TreeAna->Branch("drank", m_drank, "drank[indexmc]/I");
	   TreeAna->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
	   TreeAna->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
	   TreeAna->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");
	   }
	   */

	if(m_saveTopo == 1)
	{

		TreeAna->Branch("run", &m_run, "run/I");
		TreeAna->Branch("rec", &m_rec, "rec/I");
		TreeAna->Branch("indexmc", &m_idxmc, "indexmc/I");

		//		TreeAna->Branch("trkidx", m_trkidx, "trkidx[indexmc]/I");
		TreeAna->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
		TreeAna->Branch("drank", m_drank, "drank[indexmc]/I");
		TreeAna->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
		TreeAna->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");
	}

	if(m_saveTopoTree == 1)
	{
		TopoTree->Branch("run", &m_run, "run/I");
		TopoTree->Branch("rec", &m_rec, "rec/I");
		TopoTree->Branch("indexmc", &m_idxmc, "indexmc/I");

		//TopoTree->Branch("trkidx", m_trkidx, "trkidx[indexmc]/I");
		TopoTree->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
		TopoTree->Branch("drank", m_drank, "drank[indexmc]/I");
		TopoTree->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
		TopoTree->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");

	}

	//for MUC check
	TreeAna->Branch("maxHitsInlayer",&m_maxHitsInLayer,"maxHitsInlayer/I");
	TreeAna->Branch("chi2",&m_chi2,"chi2/D");



	TreeAna->Branch("posmucstat", &m_posmucstat, "posmucstat/I");
	TreeAna->Branch("negmucstat", &m_negmucstat, "negmucstat/I");
	
	TreeAna->Branch("posdepthMuc", &m_posdepthMuc, "posdepthMuc/D");
	TreeAna->Branch("poslayerMuc", &m_poslayerMuc, "poslayerMuc/D");
	TreeAna->Branch("posangMuc", &m_posangMuc, "posangMuc/D");
	TreeAna->Branch("negdepthMuc", &m_negdepthMuc, "negdepthMuc/D");
	TreeAna->Branch("neglayerMuc", &m_neglayerMuc, "neglayerMuc/D");
	TreeAna->Branch("negangMuc", &m_negangMuc, "negangMuc/D");

	TreeAna->Branch("poskalrechi2", &m_poskalrechi2, "poskalrechi2/D");
	TreeAna->Branch("poskaldof", &m_poskaldof, "poskaldof/I");
	TreeAna->Branch("poskaldepth", &m_poskaldepth, "poskaldepth/D");
	TreeAna->Branch("poskalbrLastLayer", &m_poskalbrLastLayer, "poskalbrLastLayer/I");
	TreeAna->Branch("poskalecLastLayer", &m_poskalecLastLayer, "poskalecLastLayer/I");

	TreeAna->Branch("negkalrechi2", &m_negkalrechi2, "negkalrechi2/D");
	TreeAna->Branch("negkaldof", &m_negkaldof, "negkaldof/I");
	TreeAna->Branch("negkaldepth", &m_negkaldepth, "negkaldepth/D");
	TreeAna->Branch("negkalbrLastLayer", &m_negkalbrLastLayer, "negkalbrLastLayer/I");
	TreeAna->Branch("negkalecLastLayer", &m_negkalecLastLayer, "negkalecLastLayer/I");
	
	 //TreeAna->Branch("hits",&m_hits, "hits/D");
  TreeAna->Branch("layerMuc",&m_layerMuc, "layerMuc/D");
	//--------end of book--------
	//

	log << MSG::INFO << "successfully return from initialize()" <<endmsg;
	std::cout<<"success initialize completed!"<<std::endl;
	return StatusCode::SUCCESS;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Mumu::execute() {

	std::cout << "execute()" << std::endl;

	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in execute()" << endreq;

	SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
	int runNo=eventHeader->runNumber();
	int event=eventHeader->eventNumber();
	m_run=runNo;
	m_rec=event;

	//--------------------------------below is topology----------------------------------------------
	/*
	   int saveMC=1;

	   if (saveMC==1){
	   m_run = eventHeader->runNumber();
	   m_rec = eventHeader->eventNumber();
	   if (eventHeader->runNumber()<0)
	   {

	   SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

	   int m_numParticle = 0;
	   if (!mcParticleCol)
	   {
	   std::cout << "Could not retrieve McParticelCol" << std::endl;
	   return StatusCode::FAILURE;
	   }
	   else
	   {
	   bool psipDecay = false;
	   int rootIndex = -1;
	   Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
	   for (; iter_mc != mcParticleCol->end(); iter_mc++)
	   {
	   if ((*iter_mc)->primaryParticle()) continue;
	   if (!(*iter_mc)->decayFromGenerator()) continue;
	//if ( ((*iter_mc)->mother()).trackIndex()<3 ) continue;
	if ((*iter_mc)->particleProperty()==100443) 
	{
	psipDecay = true;
	rootIndex = (*iter_mc)->trackIndex();
	}
	if (!psipDecay) continue;
	int trkidx = (*iter_mc)->trackIndex() - rootIndex;
	int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
	int pdgid = (*iter_mc)->particleProperty();
	m_trkidx[m_numParticle] = trkidx;
	m_pdgid[m_numParticle] = pdgid;
	m_motheridx[m_numParticle] = mcidx;
	m_numParticle += 1;    
	}
	}
	m_idxmc = m_numParticle;
	m_tuple0->write();
	}
	}
	*/
	//---------------------------------------------end---------------------------------------------------

	//MC info.

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
	TopoTree->Fill();


	log << MSG::DEBUG <<"run, evtnum = "
		<< runNo << " , "
		<< event <<endreq;
	cout<<"event "<<event<<endl;
	Ncut0++;

	if(!(Ncut0%100))
	{
		cout<<"Processing "<<Ncut0<<"th event:   "<<" Run Id = "<<runNo<<", Event Id = "<<event<<endl;
		cout<<"Total =  "<<Ncut0<<", after good charged tracks cut = "<<Ncut1<<endl;
	}

	SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
	SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);

	nCHARGED = evtRecEvent->totalCharged();
	nNEUTRAL = evtRecEvent->totalNeutral();
	nTRACKS = evtRecEvent->totalTracks();

	//  log << MSG::INFO << "get event tag OK" << endreq;
	log << MSG::DEBUG <<"ncharg, nneu, tottks = " 
		<< nCHARGED << " , "
		<< nNEUTRAL << " , "
		<< nTRACKS <<endreq;

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

	int nGood = 0;
	int nCharge = 0;

	HepLorentzVector p4_cms(0.011*m_Ecms,0.,0.,m_Ecms);
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
		if(!(*itTrk)->isMdcKalTrackValid()) continue;

		RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
		RecMdcKalTrack *mdcKalTrk = (*itTrk)->mdcKalTrack();

		if(mdcKalTrk->charge()==0) continue;

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
		//m_rtheta0=mdcTrk->theta();

		//m_tuple1->write();
		//    if(fabs(z0) >= m_vz0cut) continue;
		//    if(fabs(Rxy) >= m_vr0cut) continue;

		//  if(fabs(Rvz0) >= 10.0) continue;
		//  if(fabs(Rvxy0) >= 1.0) continue;
		//	if(fabs(cos(mdcTrk->theta())) > 0.93) continue;	
		//    cut for track     

		if(fabs(Rvz0) >= m_vz0cut) continue;
		if(fabs(Rvxy0) >= m_vr0cut) continue;
		if(fabs(cos(mdcTrk->theta())) > 0.93) continue;	
		//
		iGood.push_back(i);
		nCharge += mdcTrk->charge();
	}

	//
	// Finish Good Charged Track Selection
	//
	nGood = iGood.size();
	log << MSG::DEBUG << "ngood, totcharge = " << nGood << " , " << nCharge << endreq;
	if((nGood != 2)||(nCharge!=0)){
		return StatusCode::SUCCESS;
	}
	Ncut1++;

	//*************************************************************************************
	/*
	   Vint iGamma;
	   iGamma.clear();
	//cout << "begin good photon selection" << endl;
	for(int i = evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) 
	{
	if(i >= evtRecTrkCol->size()) break;

	EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
	if(!(*itTrk)->isEmcShowerValid()) continue;
	RecEmcShower *emcTrk = (*itTrk)->emcShower();

	double eraw = emcTrk->energy();
	Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());  //have problem??
	double theta = emcpos.theta();
	double time = emcTrk->time();

	if((time > 14) || (time < 0)) continue;

	double e_threshold = 100.;

	if((fabs(cos(theta)) > 0.86) && (fabs(cos(theta)) < 0.92))
	e_threshold = m_endEnergyThreshold;

	if(fabs(cos(theta)) < 0.8)
	e_threshold = m_barrelEnergyThreshold;

	if(eraw < e_threshold ) continue;

	// find the nearest charged track  
	double dang = 200.; 
	for(int j = 0; j < evtRecEvent->totalCharged(); j++)
	{
	if(j >= evtRecTrkCol->size()) break;

	EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;
	if(!(*jtTrk)->isExtTrackValid()) continue;
	RecExtTrack *extTrk = (*jtTrk)->extTrack();
	if(extTrk->emcVolumeNumber() == -1) continue;
	Hep3Vector extpos = extTrk->emcPosition();// - xorigin;//vertex correction!maybe effect is small

	double angd = extpos.angle(emcpos);

	if(angd < dang)
	{
	dang = angd;
	}
	}

	if(dang >= 200) continue;
	dang = dang*180/(CLHEP::pi);
	if(fabs(dang) < 10.0) continue;

	iGamma.push_back(i);
	}

	//nGamma = iGamma.size();
	//log << MSG::DEBUG << "Good Photon, totalNeutral =  " << nGamma  << " , " <<evtRecEvent->totalNeutral()<<endreq;

	//if(nGamma < m_NGamma)
	// {
	//  return StatusCode::SUCCESS;
	//	} 
	*/
	//*************************************************************************************

	ParticleID *pid = ParticleID::instance();
	for(int j = 0; j < nGood; j++)
	{
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[j];
		RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();

		pid->init();
		pid->setMethod(pid->methodProbability());

		pid->setChiMinCut(4);
		pid->setRecTrack(*itTrk);
		pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2()); // use PID sub-system
		pid->identify( pid->onlyElectron() | pid->onlyMuon() | pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());    // seperater Pion/Kaon/Proton/Muon/Electron
		//0=electron,1=muon,2=pion,3=kaon,4=proton
		pid->calculate();
		int m;
		if(mdcTrk->charge()>0) m=0;
		else m=1;
		if(!(pid->IsPidInfoValid()))
		{
			chiDeDx[m][0] = -99;
			chiDeDx[m][1] = -99;
			chiDeDx[m][2] = -99;
			chiDeDx[m][3] = -99;
			chiDeDx[m][4] = -99;

			chiTof1[m][0] = -99;
			chiTof1[m][1] = -99;
			chiTof1[m][2] = -99;
			chiTof1[m][3] = -99;
			chiTof1[m][4] = -99;

			chiTof2[m][0] = -99;
			chiTof2[m][1] = -99;
			chiTof2[m][2] = -99;
			chiTof2[m][3] = -99;
			chiTof2[m][4] = -99;

			chisq_pid[m][0] = -99;
			chisq_pid[m][1] = -99;
			chisq_pid[m][2] = -99;
			chisq_pid[m][3] = -99;
			chisq_pid[m][4] = -99;

			prob[m][0] = -99;
			prob[m][1] = -99;
			prob[m][2] = -99;
			prob[m][3] = -99;
			prob[m][4] = -99;
		}
		else
		{
			chiDeDx[m][0] = pid->chiDedx(0);
			chiDeDx[m][1] = pid->chiDedx(1);
			chiDeDx[m][2] = pid->chiDedx(2);
			chiDeDx[m][3] = pid->chiDedx(3);
			chiDeDx[m][4] = pid->chiDedx(4);

			chiTof1[m][0] = pid->chiTof1(0);
			chiTof1[m][1] = pid->chiTof1(1);
			chiTof1[m][2] = pid->chiTof1(2);
			chiTof1[m][3] = pid->chiTof1(3);
			chiTof1[m][4] = pid->chiTof1(4);

			chiTof2[m][0] = pid->chiTof2(0);
			chiTof2[m][1] = pid->chiTof2(1);
			chiTof2[m][2] = pid->chiTof2(2);
			chiTof2[m][3] = pid->chiTof2(3);
			chiTof2[m][4] = pid->chiTof2(4);

			chisq_pid[m][0] = chiDeDx[m][0]*chiDeDx[m][0] + chiTof1[m][0]*chiTof1[m][0] + chiTof2[m][0]*chiTof2[m][0];
			chisq_pid[m][1] = chiDeDx[m][1]*chiDeDx[m][1] + chiTof1[m][1]*chiTof1[m][1] + chiTof2[m][1]*chiTof2[m][1];
			chisq_pid[m][2] = chiDeDx[m][2]*chiDeDx[m][2] + chiTof1[m][2]*chiTof1[m][2] + chiTof2[m][2]*chiTof2[m][2];
			chisq_pid[m][3] = chiDeDx[m][3]*chiDeDx[m][3] + chiTof1[m][3]*chiTof1[m][3] + chiTof2[m][3]*chiTof2[m][3];
			chisq_pid[m][4] = chiDeDx[m][4]*chiDeDx[m][4] + chiTof1[m][4]*chiTof1[m][4] + chiTof2[m][4]*chiTof2[m][4];

			prob[m][0] = pid->probElectron();
			prob[m][1] = pid->probMuon();
			prob[m][2] = pid->probPion();
			prob[m][3] = pid->probKaon();
			prob[m][4] = pid->probProton();
		}
	}

	//*************************************************************************************


	Vint iGam;
	iGam.clear();
	for(int i = evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
		EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isEmcShowerValid()) continue;
		RecEmcShower *emcTrk = (*itTrk)->emcShower();


		//backup
		//double time=emcTrk->time();
		double eraw=emcTrk->energy();
		double the=emcTrk->theta();

		double time=emcTrk->time();
		//double the=emcTrk->theta();
		//double eraw=emcTrk->energy();

		if(time < 0||time >14) continue;							//time cut
		Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

		double e_threshold=10.0;

		if(fabs(cos(the))<0.82)
		{
			e_threshold = m_barrelEnergyThreshold;
		}
		else if((fabs(cos(the))>0.85) && (fabs(cos(the)) < 0.92))
		{
			e_threshold = m_endEnergyThreshold;
		}
		else 
		{
			continue;
		}

		if(eraw < e_threshold) continue;



		// find the nearest charged track
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

		//		m_dthe = dthe;
		//	m_dphi = dphi;
		//	m_dang = dang;
		//	m_eraw = eraw;
		//	m_tuple2->write();

		//	if(eraw < m_energyThreshold) continue;
		//	if((fabs(dthe) < m_gammaThetaCut) && (fabs(dphi)<m_gammaPhiCut) ) continue;
		if(fabs(dang) < m_gammaAngleCut) continue;
		//
		// good photon cut will be set here
		//
		iGam.push_back(i);
	}

	//
	// Finish Good Photon Selection
	//


	//int nGam = iGamma.size();
	int nGam = iGam.size();
	nGamma=nGam;

	log << MSG::DEBUG << "num Good Photon " << nGam  << " , " <<evtRecEvent->totalNeutral()<<endreq;
	// if(nGam<2){
	//    return StatusCode::SUCCESS;
	//  }
	int showGam=1;

	if(showGam==1)  

	{
		if(nGam==1)
		{
			Ng1++;
		}
		if(nGam==2)
		{
			Ng2++;
		}
		if(nGam>2)
		{
			NgAbove2++;
		}
	}
	if(nGam!=0)
	{
		return StatusCode::SUCCESS;
	} 
	Ncut2++;
	/*
	   if(m_writePredata==1)
	   {
	   double e_epremass=0.0;
	   double e_mupremass=0.0;
	   double p_pre=0.0;

	   for(int i = 0; i < nGood; i++){
	   EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + iGood[i];
	   if(!(*itTrk)->isMdcTrackValid()) continue;

	   RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
	   p_pre=mdcTrk->p();

	   e_epremass+=sqrt(p_pre*p_pre+xmass[0]*xmass[0]);
	   e_mupremass+=sqrt(p_pre*p_pre+xmass[1]*xmass[1]);

	   if(i==0)
	   {
	   m_prep1=p_pre;
	   }
	   else if(i==1)
	   {
	   m_prep2=p_pre;
	   m_epremass=e_epremass;
	   m_mupremass=e_mupremass;
	   }
	   }
	   m_tuple14->write();
	   }
	   */

	
/*  	
	m_posdepthMuc=-2;
	m_poslayerMuc=-2;
	m_posangMuc=-2;
	m_poskalrechi2=-2;
	m_poskaldof=-2;
	m_poskaldepth=-2;
	m_poskalbrLastLayer=-2;
	m_poskalecLastLayer=-2;


	m_negdepthMuc=-2;
	m_neglayerMuc=-2;
	m_negangMuc=-2;
	m_negkalrechi2=-2;
	m_negkaldof=-2;
	m_negkaldepth=-2;
	m_negkalbrLastLayer=-2;
	m_negkalecLastLayer=-2;
*/

		/* 
		if(m_poslayerMuc<2 || m_neglayerMuc<2) return StatusCode::SUCCESS;

		if(p_pos>0.4 && p_pos<1.1)
		{
			if(m_posdepthMuc < -40+70*p_pos) return StatusCode::SUCCESS;
		}
		if(p_pos>1.1)
		{
			if(m_posdepthMuc < 41) return StatusCode::SUCCESS;
		}

		if(p_neg>0.4 && p_neg<1.1)
		{
			if(m_negdepthMuc < -40+70*p_neg) return StatusCode::SUCCESS;
		}
		if(p_neg>1.1)
		{
			if(m_negdepthMuc < 41) return StatusCode::SUCCESS;
		}
		*/

	//	m_tuple12->write();	
	//	m_tuple15->write();	
	//	Ncut9++;
	/*
	   if(m_checkRatio==1)
	   {
	   double ene_cur[2];
	   int count_dou=0; 

	   for(int i=0;i<nGood;i++)
	   {
	   EvtRecTrackIterator itTrk = evtRecTrkCol->begin()+iGood[i];

	   if(!(*itTrk)->isMdcTrackValid()) continue;
	   if(!(*itTrk)->isExtTrackValid()) continue;

	   RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
	   RecExtTrack *extTrk=(*itTrk)->extTrack();

	   if(extTrk->emcVolumeNumber()==-1) continue;
	   Hep3Vector extpos = extTrk->emcPosition();

	   double dthe = 200.;
	   double dphi = 200.;
	   double dang = 200.; 
	   double eraw = 0.0;

	   for(int j=0;j<nGam;j++)
	   {
	   EvtRecTrackIterator jtTrk=evtRecTrkCol->begin()+iGam[j];
	//for(int j=evtRecEvent->totalCharged();j<evtRecEvent->totalTracks();j++){
	//EvtRecTrackIterator jtTrk=evtRecTrkCol->begin()+j;

	if(!(*jtTrk)->isEmcShowerValid()) continue;
	RecEmcShower *emcTrk=(*jtTrk)->emcShower();
	Hep3Vector emcpos(emcTrk->x(),emcTrk->y(),emcTrk->z());

	double angd = extpos.angle(emcpos);
	double thed = extpos.theta() - emcpos.theta();
	double phid = extpos.deltaPhi(emcpos);

	thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
	phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
	if(angd < dang)
	{
	dang = angd;
	dthe = thed;
	dphi = phid;
	eraw = emcTrk->energy();
	}
	}  
	if(dang>=200) return StatusCode::SUCCESS;
	dthe = dthe *180/(CLHEP::pi);
	dphi = dphi *180/(CLHEP::pi);
	dang = dang *180/(CLHEP::pi);

	if( eraw < m_ene_lowThreshold || eraw > m_ene_highThreshold) return StatusCode::SUCCESS;
	double pt_cur=mdcTrk->pxy();
	double p_cur=mdcTrk->p();
	double ep_ratio_cur=eraw/p_cur;
	//		   double ep_ratio_cur=0.2;
	if(pt_cur < m_pt_Threshold)  return StatusCode::SUCCESS;
	if(ep_ratio_cur > m_ep_ratioThreshold) return StatusCode::SUCCESS;

	m_e_ratio=eraw;
	m_p_ratio=p_cur;
	m_ep_ratio=ep_ratio_cur;

	m_tuple12->write();
	ene_cur[i]=eraw;
	count_dou++;
	Ncut7++;
	}
	if(count_dou==2)
	{
		m_ene1=ene_cur[0];
		m_ene2=ene_cur[1];
		m_tuple13->write();
		Ncut8++;
	}
}
*/
///////////////////////////////////Vertex fit///////////////////////////////

RecMdcKalTrack *mupTrk = (*(evtRecTrkCol->begin()+iGood[0]))->mdcKalTrack();
RecMdcKalTrack *mumTrk = (*(evtRecTrkCol->begin()+iGood[1]))->mdcKalTrack();

WTrackParameter wvmupTrk, wvmumTrk;
wvmupTrk = WTrackParameter(mmu, mupTrk->getZHelixMu(), mupTrk->getZErrorMu());
wvmumTrk = WTrackParameter(mmu, mumTrk->getZHelixMu(), mumTrk->getZErrorMu());

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
vtxfit->AddTrack(0,  wvmupTrk);
vtxfit->AddTrack(1,  wvmumTrk);
vtxfit->AddVertex(0, vxpar,0, 1);
if(!vtxfit->Fit(0)) return SUCCESS;
vtxfit->Swim(0);

WTrackParameter wmup = vtxfit->wtrk(0);
WTrackParameter wmum = vtxfit->wtrk(1);

///////////////////////////////////apply 4C fit/////////////////////////////

KalmanKinematicFit * kmfit = KalmanKinematicFit::instance();

if(m_test4C==1)
{
	HepLorentzVector ecms(0.034,0,0,3.097);
	double chisq = 9999.;
	kmfit->init();
	kmfit->AddTrack(0,wmup);
	kmfit->AddTrack(1,wmum);
	kmfit->AddFourMomentum(0,ecms);
	bool oksq = kmfit->Fit();
	if(oksq) 
	{
		HepLorentzVector mumu0 = kmfit->pfit(0) + kmfit->pfit(1);
		m_mmu0 = mumu0.m();
		m_chi4C = kmfit->chisq();
		//		m_tuple4->write();
		Ncut5++;
	}
	else
	{
		return StatusCode::SUCCESS;

	}
}
////////////////////////////////////end of 4C////////////////////////////////
if(m_checkRatio==1)
{
	for(int i=0;i<nGood;i++)
	{
		int emcValid=1;
		double deTrk=-10.0;
		int nhits=-10;
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin()+iGood[i];

		if(!(*itTrk)->isMdcTrackValid()) continue;
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
			// my modification
			EmcRecShowerShape shape;
			shape.CalculateMoment(emcTrk);
			emcmoment1=emcTrk->secondMoment();
			//emcmoment2=emcTrk->latMoment();
			//emcmoment3=emcTrk->a20Moment();
			//emcmoment4=emcTrk->a42Moment();
				
		}
		else if(emcValid==0)
		{
			deTrk= -1.0;
		}
		else	return StatusCode::SUCCESS;
		

		if(mdcTrk->charge()>0)
		{
			m_ppos_ratio=mdcTrk->p();
			m_epos_ratio=sqrt(m_ppos_ratio*m_ppos_ratio+xmass[1]*xmass[1]);
			m_depos_ratio=deTrk;
			m_eppos_ratio=m_depos_ratio/m_ppos_ratio;
			m_hitspos_ratio=nhits;
			m_hits = m_hitspos_ratio;
			m_rtheta0=mdcTrk->theta();
		}

		else if(mdcTrk->charge()<0)
		{
			m_pneg_ratio=mdcTrk->p();
			m_eneg_ratio=sqrt(m_pneg_ratio*m_pneg_ratio+xmass[1]*xmass[1]);
			m_deneg_ratio=deTrk;
			m_epneg_ratio=m_deneg_ratio/m_pneg_ratio;
			m_hitsneg_ratio=nhits;
			m_hits = m_hitsneg_ratio;
			m_rtheta1=mdcTrk->theta();
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

	//here is cut
	/*	
		if(m_depos_ratio<m_ene_lowThreshold || m_depos_ratio>m_ene_highThreshold) return StatusCode::SUCCESS;
		if(m_deneg_ratio<m_ene_lowThreshold || m_deneg_ratio>m_ene_highThreshold) return StatusCode::SUCCESS;

		if(m_eppos_ratio > m_ep_ratioThreshold) return StatusCode::SUCCESS;
		if(m_epneg_ratio > m_ep_ratioThreshold) return StatusCode::SUCCESS;
		*/
}
Ncut3++;

/////////////////////////////////apply 5C fit////////////////////////////////

if(m_test5C==1)
{
	HepLorentzVector ecms(0.034,0,0,3.097);
	kmfit->init();
	kmfit->AddTrack(0, wmup);
	kmfit->AddTrack(1, wmum);
	kmfit->AddResonance(0, 3.097, 0, 1);
	kmfit->AddFourMomentum(1, ecms);
	bool oksq = kmfit->Fit();
	//  log << MSG::INFO << " chisq = " << chisq <<endreq;
	if(oksq)
	{
		HepLorentzVector mumu1 = kmfit->pfit(0) + kmfit->pfit(1);
		m_chi5C  = kmfit->chisq();
		m_mmu1 =mumu1.m();
		//	double eg1 = (kmfit->pfit(2)).e();
		//	double eg2 = (kmfit->pfit(3)).e();
		//	double fcos = abs(eg1-eg2)/ppi0.rho();
		//m_tuple5->write();
		Ncut6++;
	}
	else
	{
		return StatusCode::SUCCESS;
	}
	// 
	//  Measure the photon detection efficiences via
	//          J/psi -> rho0 pi0
	//
	/*
	   if(fabs(prho0.m()-0.770)<0.150) {  
	   if(fabs(fcos)<0.99) {
	   m_fcos = (eg1-eg2)/ppi0.rho();
	   m_elow =  (eg1 < eg2) ? eg1 : eg2;
	   m_tuple6->write();
	   Ncut6++;
	   }
	   } // rho0 cut
	   }  //oksq
	   */
}

//*******************************************MUC***************************

	if(m_checkMuc==1)
	{
		
		//m_posmucstat=0;
		//m_negmucstat=0;
		double p_pos=0.0;
		double p_neg=0.0;
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
				m_chi2 = mucTrk->chi2();
				m_maxHitsInLayer = mucTrk->maxHitsInLayer();
				m_posangMuc=angg;
				m_poskalrechi2=mucTrk->kalRechi2();
				m_poskaldof=mucTrk->kaldof();
				m_poskaldepth=mucTrk->kaldepth();
				m_poskalbrLastLayer=mucTrk->kalbrLastLayer();
				m_poskalecLastLayer=mucTrk->kalecLastLayer();
		
			    m_kaldepth=mucTrk->kaldepth();
			    m_kalbrLastLayer=mucTrk->kalbrLastLayer();
			    m_kalecLastLayer=mucTrk->kalecLastLayer();
		//	    m_kaldof=mucTrk->kaldof();
			    m_brLastLayer=mucTrk->brLastLayer();
			    m_ecLastLayer=mucTrk->ecLastLayer();
			
			}

			else if(mdcTrk->charge()<0)
			{
				m_negmucstat=1;
				m_negdepthMuc=mucTrk->depth();
				m_neglayerMuc=mucTrk->numLayers();
				m_layerMuc = m_neglayerMuc;
				m_chi2 = mucTrk->chi2();
			    m_maxHitsInLayer = mucTrk->maxHitsInLayer();
				m_negangMuc=angg;
				m_negkalrechi2=mucTrk->kalRechi2();
				m_negkaldof=mucTrk->kaldof();
				m_negkaldepth=mucTrk->kaldepth();
				m_negkalbrLastLayer=mucTrk->kalbrLastLayer();
				m_negkalecLastLayer=mucTrk->kalecLastLayer();
		
			m_kaldepth=mucTrk->kaldepth();
			         m_kalbrLastLayer=mucTrk->kalbrLastLayer();
			         m_kalecLastLayer=mucTrk->kalecLastLayer();
			         m_kaldof=mucTrk->kaldof();
			         m_brLastLayer=mucTrk->brLastLayer();
			         m_ecLastLayer=mucTrk->ecLastLayer();
			
			}

			else
			{
				return StatusCode::SUCCESS;
			}
		}
		Ncut4++;

	}
//***************************************************************************

//m_layerMuc = m_poslayerMuc + m_neglayerMuc;	
//m_poslayerMuc=mucTrk->numLayers();
//m_hits = m_hitspos_ratio + m_hitsneg_ratio;

TreeAna->Fill();
return StatusCode::SUCCESS;
}

//***************************************************************************



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Mumu::finalize() {
	
	NbInfo->Fill();
	saveFile->cd();
	TreeAna->Write();
	if(m_saveTopoTree == 1)	TopoTree->Write();
	if(m_saveNbInfo == 1) NbInfo->Write();
	saveFile->Close();



	cout<<"~~thx senior! lify's finalize has completed!"<<endl;
	cout<<"Total number:         "<<Ncut0<<endl;
	cout<<"nGood==2, nCharge==0: "<<Ncut1<<endl;
	cout<<"nGam=0:               "<<Ncut2<<endl;
	//  cout<<"Pass Pid:             "<<Ncut3<<endl;
	//  cout<<"Pass 4C:              "<<Ncut4<<endl;
	//  cout<<"Pass 5C:              "<<Ncut5<<endl;
	//  cout<<"J/psi->rho0 pi0:      "<<Ncut6<<endl;
	
	   cout<<"nGam=1:               "<<Ng1<<endl;
	   cout<<"nGam=2:               "<<Ng2<<endl;
	   cout<<"nGam>2:               "<<NgAbove2<<endl;

	//  cout<<"Only 1  partile Pass: "<<Ncut7<<endl;
	if(m_test4C==1) cout<<"The event Pass 4C:   "<<Ncut5<<endl;
	if(m_checkRatio==1) cout<<"after check ratio:   "<<Ncut3<<endl;
	if(m_checkMuc==1) cout<<"The event Pass MUC:   "<<Ncut4<<endl;
	if(m_test5C==1) cout<<"The event Pass 5C:   "<<Ncut6<<endl;


	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in finalize()" << endmsg;
	return StatusCode::SUCCESS;
}

