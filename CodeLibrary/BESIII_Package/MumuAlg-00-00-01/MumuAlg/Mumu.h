#ifndef Physics_Analysis_Mumu_H
#define Physics_Analysis_Mumu_H 

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
//#include "VertexFit/ReadBeamParFromDb.h"


#include <string>
#include <TTree.h>
#include <TROOT.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TClonesArray.h>

class Mumu:public Algorithm{

	public:
		Mumu(const std::string& name, ISvcLocator* pSvcLocator);
		StatusCode initialize();
		StatusCode execute();
		StatusCode finalize();  

	private:

		Double_t m_Ecms;
		Double_t m_EnergySpread;

		//------muc------
		Double_t	m_kalRechi2;
		Int_t	m_kaldof; 
		Double_t	m_kaldepth;
		Int_t	m_kalbrLastLayer;
		Int_t	m_kalecLastLayer; 
		Int_t	m_dof;
		Int_t	m_brLastLayer;
		Int_t	m_ecLastLayer;
	    
		//---------mdc-----
        Double_t	m_Mdcchi2;
	    Int_t	m_ndof;
	    Int_t	m_nhits;
	    Int_t	m_nlayer;
		
		
		//-------------------------file and MC -------------------------------------

		std::string m_OutputFileName;
		TFile *saveFile;
		TTree *TreeAna;
		TTree *genTree;
		TTree *TopoTree;
		TTree *NbInfo;

		int m_saveTopo;
		int m_saveMCTruth;
		int m_saveTopoTree;
		int m_saveNbInfo;

		int m_run;
		int m_rec;

		//  int m_idxmc;
		// int m_trkidx;

		int m_idxmc;
		int m_drank[500];
		//int m_trkidx[500];
		int m_pdgid[500];
		int m_motheridx[500];
		int m_motherpid[500];

		int runid;
		int evtid;
		int nevt;

		int nNEUTRAL;
		int nCHARGED;
		int nTRACKS;
		int nGamma;

		//---------------------------------------------------------------------

		//######################################################################		
		//below is origin variable
		// Declare r0, z0 cut for charged tracks
		double m_vr0cut;
		double m_vz0cut;

		//Declare energy, dphi, dthe cuts for fake gamma's
		double m_energyThreshold;
		double m_gammaPhiCut;
		double m_gammaThetaCut;
		double m_gammaAngleCut;

		// 
		int m_test4C;
		int m_test5C;

		// 
		int m_checkDedx;
		int m_checkTof;

		//------------------------my private value---------
		////////////////////////////////////////////////////
		double m_ene_lowThreshold;
		double m_ene_highThreshold;
		double m_ep_ratioThreshold;
		double m_pt_Threshold;

		double m_barrelEnergyThreshold;
		double m_endEnergyThreshold;

		int m_writePredata;
		int m_checkRatio;
		int m_checkMuc;
		//////////////////////////end of declare///////////
		//charged track vertex
		double m_vx0;
		double m_vy0;
		double m_vz0;
		double m_vr0;
		double m_rvxy0;
		double m_rvz0;
		double m_rvphi0;
		double m_rtheta0;
		double m_rtheta1;

		//storeage of momentum and E/p
		double m_ppos_ratio;
		double m_depos_ratio;
		double m_eppos_ratio;
		double m_pneg_ratio;
		double m_deneg_ratio;
		double m_epneg_ratio;
		double m_tmass_ratio;
		double m_hitspos_ratio;
		double m_hitsneg_ratio;
		double m_hits;
	
		//fate photon
		double m_dthe;
		double m_dphi;
		double m_dang;
		double m_eraw;


		double chiDeDx[4][5];
		double chiTof1[4][5];
		double chiTof2[4][5];
		double chisq_pid[4][5];
		double prob[4][5];

		//mumu 4C
		double m_chi4C;
		double m_mmu0;

		//mumu 5C
		double m_chi5C;
		double m_mmu1;

		//tuple13
		double m_ene1;
		double m_ene2;

		//tuple14
		// double m_prep1;
		// double m_prep2;
		// double m_epremass;
		// double m_mupremass;

		//tuple15
		int m_posmucstat;
		int m_negmucstat;
		double m_posdepthMuc;
		double m_poslayerMuc;
		double m_negdepthMuc;
		double m_neglayerMuc;
		double m_negangMuc;
		double m_posangMuc;
		double m_poskalrechi2;
		double m_poskaldof;
		double m_poskaldepth;
		int m_poskalbrLastLayer;
		int m_poskalecLastLayer;
		double m_negkalrechi2;
		int m_negkaldof;
		double m_negkaldepth;
		int m_negkalbrLastLayer;
		int m_negkalecLastLayer;
		double m_layerMuc;
		double m_chi2;
		int m_maxHitsInLayer; 
		//tuple16
		double m_eposmu;
		double m_enegmu;
		double m_pposmu;
		double m_pnegmu;
		double m_tmassmumu;

		//
		double m_epos_ratio;
		double m_eneg_ratio;



		//above is origin variable
		//###############################################################################

};

#endif 
