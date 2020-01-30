/* @(#)TopoAngAlg.h
 */

#ifndef _TOPOANAALG_H
#define _TOPOANAALG_H 1

#include "ParticleObject.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iomanip> //for setw
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>

#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

typedef vector<int> Vint;
typedef vector<string> Vstring;

struct MCParticle
{
  int idx;
  int pid;
  int midx;
};

bool CompPid(const int&, const int&);

class TopoAnaAlg 
{
public:
  TopoAnaAlg();
  TopoAnaAlg(vector<string>);
  ~TopoAnaAlg();


  void makeMap();
  string Vint2String(vector<int>);
  void BubbleSort(vector<int> &, vector<int> &);
  void BubbleSort(vector<int> &, vector<int> &, vector<int> &);

  void MergeKzero(vector<MCParticle> &);
  void EventReorder(vector<MCParticle> &);
  void getEvtDecayChain(vector<MCParticle>);
  string TopoString(vector<MCParticle> );
  bool SameFinalState(vector<MCParticle>, vector<MCParticle>);

  void ReadCard();
  void OpenRootFile();
  void ReadRootFile();
  void Result();
  void makeTexFile();

private:
  string m_treeName;
  Vstring m_inputFileName;

  ofstream m_outputFile;
  string m_outputFileName;

  TChain *chain;
  // Declaration of leave types
  Int_t indexmc;
  Int_t trkidx[100];   //[indexmc]
  Int_t pdgid[100];   //[indexmc]
  Int_t motheridx[100];   //[indexmc]

  // List of branches
  TBranch *b_indexmc;   //!
  TBranch *b_trkidx;   //!
  TBranch *b_pdgid;   //!
  TBranch *b_motheridx;   //!

  ParticleObject aParticleObject;
  vector< vector<MCParticle> > m_MCSignals;
  vector< vector<MCParticle> > m_MCTypes;
  vector< list<int> > EvtDecayTree;
  vector<int> finalState;
  // counter the number of topology category 
  // and the number of events in this topology
  Vint Vtopo;
  Vint tidx;

  //for inclusive decay
  int InclusiveParticleID;
  map<int, string> pidTexName;
};
#endif /* _TOPOANAALG_H */

