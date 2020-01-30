#ifndef Physics_Analysis_Rhopi_H
#define Physics_Analysis_Rhopi_H 

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


class Rhopi : public Algorithm {

	public:
		Rhopi(const std::string& name, ISvcLocator* pSvcLocator);
		StatusCode initialize();
		StatusCode execute();
		StatusCode finalize();  

	private:


	//------muc------
         Double_t    m_kalRechi2;
         //int   m_kaldof;
         Double_t    m_kaldepth;
         int    m_kalbrLastLayer;
         int    m_kalecLastLayer;
         int    m_dof;
         int    m_brLastLayer;
         int    m_ecLastLayer;
	
	         //---------mdc-----
	         Double_t    m_Mdcchi2;
	         Int_t   m_ndof;
	         Int_t   m_nhits;
	         Int_t   m_nlayer;


		//ReadBeamParFromDb m_reader;
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
		int m_checkRatio;
		int m_checkMuc;

		//
		double barTheta;
		double endThetaMin;
		double endThetaMax;
		double barEnergy;
		double endEnergy;


		//MC Tree
		std::string m_OutputFileName;
		TFile *saveFile;
		TTree *TreeAna;
		int m_saveTopo;

		int m_idxmc;
		int m_drank[500];
		//int m_trkidx[500];
		int m_pdgid[500];
		int m_motheridx[500];
		int m_motherpid[500];


		// define Ntuples here

		NTuple::Tuple*  m_tuple1;      // charged track vertex
		NTuple::Item<double>  m_vx0;
		NTuple::Item<double>  m_vy0;
		NTuple::Item<double>  m_vz0;
		NTuple::Item<double>  m_vr0;
		NTuple::Item<double>  m_rvxy0;
		NTuple::Item<double>  m_rvz0;
		NTuple::Item<double>  m_rvphi0;

		NTuple::Tuple*  m_tuple2;      // fake photon
		NTuple::Item<double>  m_dthe;
		NTuple::Item<double>  m_dphi;
		NTuple::Item<double>  m_dang;
		NTuple::Item<double>  m_eraw;

		NTuple::Tuple*  m_tuple3;     // rhopi: raw mgg, etot
		NTuple::Item<double>  m_m2gg;
		NTuple::Item<double>  m_etot;

		NTuple::Tuple*  m_tuple4;     // rhopi 4C
		NTuple::Item<double>  m_chi1;
		NTuple::Item<double>  m_mpi0;

		NTuple::Tuple*  m_tuple5;     // rhopi 5C
		//NTuple::Item<double>  m_chi2;
		NTuple::Item<double>  m_mrh0;
		NTuple::Item<double>  m_mrhp;
		NTuple::Item<double>  m_mrhm;

		NTuple::Tuple*  m_tuple6;    // photons
		NTuple::Item<double>  m_fcos;
		NTuple::Item<double>  m_elow;


		NTuple::Tuple* m_tuple7;    // dE/dx
		NTuple::Item<double> m_ptrk;
		NTuple::Item<double> m_chie;
		NTuple::Item<double> m_chimu;
		NTuple::Item<double> m_chipi;
		NTuple::Item<double> m_chik;
		NTuple::Item<double> m_chip;
		NTuple::Item<double> m_probPH;
		NTuple::Item<double> m_normPH;
		NTuple::Item<double> m_ghit;
		NTuple::Item<double> m_thit;

		NTuple::Tuple* m_tuple8;   // endcap tof
		NTuple::Item<double> m_ptot_etof;
		NTuple::Item<double> m_cntr_etof;
		NTuple::Item<double> m_te_etof;
		NTuple::Item<double> m_tmu_etof;
		NTuple::Item<double> m_tpi_etof;
		NTuple::Item<double> m_tk_etof;
		NTuple::Item<double> m_tp_etof;
		NTuple::Item<double> m_ph_etof;
		NTuple::Item<double> m_rhit_etof;
		NTuple::Item<double> m_qual_etof;

		NTuple::Tuple* m_tuple9;  // barrel inner tof
		NTuple::Item<double> m_ptot_btof1;
		NTuple::Item<double> m_cntr_btof1;
		NTuple::Item<double> m_te_btof1;
		NTuple::Item<double> m_tmu_btof1;
		NTuple::Item<double> m_tpi_btof1;
		NTuple::Item<double> m_tk_btof1;
		NTuple::Item<double> m_tp_btof1;
		NTuple::Item<double> m_ph_btof1;
		NTuple::Item<double> m_zhit_btof1;
		NTuple::Item<double> m_qual_btof1;

		NTuple::Tuple* m_tuple10;  // barrel outer tof
		NTuple::Item<double> m_ptot_btof2;
		NTuple::Item<double> m_cntr_btof2;
		NTuple::Item<double> m_te_btof2;
		NTuple::Item<double> m_tmu_btof2;
		NTuple::Item<double> m_tpi_btof2;
		NTuple::Item<double> m_tk_btof2;
		NTuple::Item<double> m_tp_btof2;
		NTuple::Item<double> m_ph_btof2;
		NTuple::Item<double> m_zhit_btof2;
		NTuple::Item<double> m_qual_btof2;

		NTuple::Tuple* m_tuple11;  // Particle ID info.
		NTuple::Item<double> m_ptrk_pid;
		NTuple::Item<double> m_cost_pid;
		NTuple::Item<double> m_dedx_pid;
		NTuple::Item<double> m_tof1_pid;
		NTuple::Item<double> m_tof2_pid;
		NTuple::Item<double> m_prob_pid;

		//NTuple::Tuple* m_tuple12;  // muc&emc ID info.
		double m_ppos_ratio;
		double m_epos_ratio;
		double m_eneg_ratio;
		double m_depos_ratio;
		double m_eppos_ratio;
		double m_pneg_ratio;
		double m_deneg_ratio;
		double m_epneg_ratio;
		double m_tmass_ratio;
		int m_hitspos_ratio;

		int m_hitsneg_ratio;
		double m_hits;
		int m_posmucstat;
		int m_negmucstat;
		double m_posdepthMuc;
		int m_poslayerMuc;
		double m_layerMuc;
		double m_negdepthMuc;
		int m_neglayerMuc;
		
		double m_negangMuc;
		double m_posangMuc;
		double m_poskalrechi2;
		int m_kaldof;
		double m_poskaldepth;
		int m_poskalbrLastLayer;
		int m_poskalecLastLayer;
		double m_negkalrechi2;
		int m_negkaldof;
		double m_negkaldepth;
		int m_negkalbrLastLayer;
		int m_negkalecLastLayer;
		

		int nevt;
		double vx[3],Evx[3];
		double vxchisq;
		double kmchisq_pi0[500];
		double kmchisq_4c[500];

		int id_gamma1[500];
		int id_gamma2[500];

		TClonesArray *pip;
		TClonesArray *pim;
		TClonesArray *gamma1;
		TClonesArray *gamma2;
		TClonesArray *pip_unfitted;
		TClonesArray *pim_unfitted;
		TClonesArray *gamma1_unfitted;
		TClonesArray *gamma2_unfitted;




		double m_chisq_pi0;
		double m_chisq_4c;
		int len;
		double lvtrpi0[10];
		double lvtrpip[10];
		double lvtrpim[10];
		double lvtrpi0unfit[10];
		double lvtrpipunfit[10];
		double lvtrpimunfit[10];
		         double m_chi2;
				 int m_maxHitsInLayer;
		 
//my_item
		double mpi0;


};

#endif 
