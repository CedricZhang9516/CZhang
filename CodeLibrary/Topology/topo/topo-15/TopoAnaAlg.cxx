#include "TopoAnaAlg.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// * * * * * * * * * * * * * * * * * * * * * * * * * * *
TopoAnaAlg::TopoAnaAlg()
{ 
  InclusiveParticleID = 0;
}     
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
TopoAnaAlg::~TopoAnaAlg()
{   
  delete chain;
} 
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool CompPid(const int &x, const int &y)
{
  //if (x == 22 || y == 22) return false;
  //if (x == -22 || y == -22) return false;
  if (x == 22) return true;
  if (y == 22) return false;
  if (x == -22) return true;
  if (y == -22) return false;
  return x > y;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::makeMap()
{
  pidTexName.clear();
  pidTexName[-22] = "\\gamma_{FSR}";
  pidTexName[ 22] = "\\gamma ";
  pidTexName[ 11] = "e^{+} ";
  pidTexName[-11] = "e^{-} ";
  pidTexName[ 13] = "\\mu^{+}  ";
  pidTexName[-13] = "\\mu^{-}  ";
  pidTexName[ 15] = "\\tau^{+} ";
  pidTexName[-15] = "\\tau^{-} ";
  pidTexName[ 12] = "\\nu_{e}  ";
  pidTexName[-12] = "\\bar{\\nu}_{e}   ";
  pidTexName[ 14] = "\\nu_{\\mu}       ";
  pidTexName[-14] = "\\bar{\\nu}_{\\mu}";
  pidTexName[ 16] = "\\nu_{\\tau} ";
  pidTexName[-16] = "\\bar{\\nu}_{\\tau}";

  pidTexName[111 ] =   "\\pi^{0} ";
  pidTexName[211 ] =   "\\pi^{+} ";
  pidTexName[-211] =   "\\pi^{-} ";
  pidTexName[113 ] =   "\\rho^{0} ";
  pidTexName[213 ] =   "\\rho^{+} ";
  pidTexName[   -213  ] =   "\\rho^{-} ";
  pidTexName[  10111  ] =   "a_{0}^{0} ";
  pidTexName[  10211  ] =   "a_{0}^{+} ";
  pidTexName[ -10211  ] =   "a_{0}^{-} ";
  pidTexName[ 100111  ] =   "\\pi(1300)^{0} ";
  pidTexName[ 100211  ] =   "\\pi(1300)^{+} ";
  pidTexName[-100211  ] =   "\\pi(1300)^{-}  ";
  pidTexName[  20113  ] =   "a_{1}^{0} ";
  pidTexName[  20213  ] =   "a_{1}^{+} ";
  pidTexName[ -20213  ] =   "a_{1}^{-} ";
  pidTexName[ 100113  ] =   "\\rho^{0}(1450) ";
  pidTexName[ 100213  ] =   "\\rho^{+}(1450) ";
  pidTexName[-100213  ] =   "\\rho^{-}(1450) ";
  pidTexName[9000113  ] =   "\\pi_1(1600)^0 ";
  pidTexName[9000213  ] =   "\\pi_1(1600)^+ ";
  pidTexName[-9000213  ] =  "\\pi_1(1600)^- ";
  pidTexName[    115  ] =   "a_{2}^{0} ";
  pidTexName[    215  ] =   "a_{2}^{+} ";
  pidTexName[   -215  ] =   "a_{2}^{-} ";
  pidTexName[  10113  ] =   "b_{1}^{0} ";
  pidTexName[  10213  ] =   "b_{1}^{+} ";
  pidTexName[ -10213  ] =   "b_{1}^{-} ";
  pidTexName[    221  ] =   "\\eta ";
  pidTexName[    331  ] =   "\\eta^{\\prime} ";
  pidTexName[9000221  ] =   "f_{0}(600) ";
  pidTexName[  10222  ] =   "\\sigma_{0} ";
  pidTexName[9010221  ] =   "f_{0}(980) ";
  pidTexName[ 100221  ] =   "\\eta(1295) ";
  pidTexName[  10221  ] =   "f_{0}(1370) ";
  pidTexName[9020221  ] =   "\\eta(1405) ";
  pidTexName[ 100331  ] =   "\\eta(1475) ";
  pidTexName[  50221  ] =   "f_{0}(1500) ";
  pidTexName[9000223  ] =   "f_{1}(1510) ";
  pidTexName[  10331  ] =   "f_{0}(1710) ";
  pidTexName[9040221  ] =   "\\eta(1760) ";
  pidTexName[8888888  ] =   "f_{0}(1790) ";
  pidTexName[9999999  ] =   "X(1835) ";
  pidTexName[  10335  ] =   "\\eta_2(1870) ";
  pidTexName[9050225  ] =   "f_{2}(1950) ";
  pidTexName[9050221  ] =   "f_{0}(2020) ";
  pidTexName[9060221  ] =   "f_{0}(2100) ";
  pidTexName[9070221  ] =   "f_{0}(2200) ";
  pidTexName[9080221  ] =   "\\eta(2250) ";
  pidTexName[    223  ] =   "\\omega ";
  pidTexName[    333  ] =   "\\phi ";
  pidTexName[    335  ] =   "f_2^{\'} ";
  pidTexName[  10223  ] =   "h_{1}(1170) ";
  pidTexName[  20223  ] =   "f_{1}(1285) ";
  pidTexName[  10333  ] =   "h_{1}(1380) ";
  pidTexName[  20333  ] =   "f_{1}(1420) ";
  pidTexName[ 100223  ] =   "\\omega(1420) ";
  pidTexName[    225  ] =   "f_{2}(1270) ";
  pidTexName[    229  ] =   "f_{4}(2050) ";
  pidTexName[  10221  ] =   "f^{\'}_{0} ";
  pidTexName[    311  ] =   "K^{0} ";
  pidTexName[   -311  ] =   "\\bar{K}^{0} ";
  pidTexName[    321  ] =   "K^{+} ";
  pidTexName[   -321  ] =   "K^{-} ";
  pidTexName[    313  ] =   "K^{*} ";
  pidTexName[   -313  ] =   "\\bar{K}^{*} ";
  pidTexName[  10313  ] =   "K_1^{0} ";
  pidTexName[ -10313  ] =   "\\bar{K}_1^{0} ";
  pidTexName[  10323  ] =   "K_1^{+} ";
  pidTexName[ -10323  ] =   "K_1^{-} ";
  pidTexName[  10311  ] =   "K_0^{0} ";
  pidTexName[ -10311  ] =   "\\bar{K}_0^{*0}";
  pidTexName[  20313  ] =   "K_1^{\'0} ";
  pidTexName[ -20313  ] =   "\\bar{K}_1^{\'0}";
  pidTexName[  20323  ] =   "K_1^{\'+} ";
  pidTexName[ -20323  ] =   "\\bar{K}_1^{\'-} ";
  pidTexName[    310  ] =   "K_{S} ";
  pidTexName[    130  ] =   "K_{L} ";
  pidTexName[    323  ] =   "K^{*+} ";
  pidTexName[   -323  ] =   "K^{*-} ";
  pidTexName[    325  ] =   "K_2^{*+} ";
  pidTexName[   -325  ] =   "K_2^{*-} ";
  pidTexName[    315  ] =   "K_2^{*0} ";
  pidTexName[   -315  ] =   "K_2^{*0} ";
  pidTexName[  10321  ] =   "K_{0}^{*+} ";
  pidTexName[ -10321  ] =   "K_{0}^{*-} ";
  pidTexName[ -10323  ] =   "K_{1}^{-} ";
  pidTexName[  10315  ] =   "K_2^0(1770) ";
  pidTexName[ -10315  ] =   "\\bar{K}_2^0(1770) ";
  pidTexName[  10325  ] =   "K_2^+(1770) ";
  pidTexName[ -10325  ] =   "K_2^-(1770) ";
  pidTexName[  20315  ] =   "K_2^0(1820) ";
  pidTexName[ -20315  ] =   "\\bar{K}_2^0(1820) ";
  pidTexName[  20325  ] =   "K_2^+(1820) ";
  pidTexName[ -20325  ] =   "K_2^-(1820) ";
  pidTexName[    2212 ] =   "p ";
  pidTexName[   -2212 ] =   "\\bar{p} ";
  pidTexName[    2112 ] =   "n ";
  pidTexName[   -2112 ] =   "\\bar{n} ";
  pidTexName[    1114 ] =   "\\Delta^{-} ";
  pidTexName[   -1114 ] =   "\\bar{\\Delta}^{-} ";
  pidTexName[    2114 ] =   "\\Delta^{0} ";
  pidTexName[   -2114 ] =   "\\bar{\\Delta}^{0} ";
  pidTexName[    2214 ] =   "\\Delta^{+} ";
  pidTexName[   -2214 ] =   "\\bar{\\Delta}^{+} ";
  pidTexName[    2224 ] =   "\\Delta^{++} ";
  pidTexName[   -2224 ] =   "\\bar{\\Delta}^{++} ";
  pidTexName[    3122 ] =   "\\Lambda ";
  pidTexName[   -3122 ] =   "\\bar{\\Lambda} ";
  pidTexName[    3222 ] =   "\\Sigma^{+} ";
  pidTexName[   -3222 ] =   "\\bar{\\Sigma}^{-} ";
  pidTexName[    3212 ] =   "\\Sigma^{0} ";
  pidTexName[   -3212 ] =   "\\bar{\\Sigma}^{0} ";
  pidTexName[    3112 ] =   "\\Sigma^{-} ";
  pidTexName[   -3112 ] =   "\\bar{\\Sigma}^{+} ";
  pidTexName[    3224 ] =   "\\Sigma^{*+} ";
  pidTexName[   -3224 ] =   "\\bar{\\Sigma}^{*-} ";
  pidTexName[    3214 ] =   "\\Sigma^{*0} ";
  pidTexName[   -3214 ] =   "\\bar{\\Sigma}^{*0} ";
  pidTexName[    3114 ] =   "\\Sigma^{*-} ";
  pidTexName[   -3114 ] =   "\\bar{\\Sigma}^{*+} ";
  pidTexName[    3322 ] =   "\\Xi^{0} ";
  pidTexName[   -3322 ] =   "\\bar{\\Xi}^{0} ";
  pidTexName[    3312 ] =   "\\Xi^{-} ";
  pidTexName[   -3312 ] =   "\\bar{\\Xi}^{+} ";
  pidTexName[    3324 ] =   "\\Xi^{*0} ";
  pidTexName[   -3324 ] =   "\\bar{\\Xi}^{*0} ";
  pidTexName[    3314 ] =   "\\Xi^{*-} ";
  pidTexName[   -3314 ] =   "\\bar{\\Xi}^{*+} ";
  pidTexName[    3334 ] =   "\\Omega^{-} ";
  pidTexName[   -3334 ] =   "\\bar{\\Omega}^{+} ";
  pidTexName[      441] =   "\\eta_{c} ";
  pidTexName[      443] =   "J/\\psi ";
  pidTexName[    10441] =   "\\chi_{c0} ";
  pidTexName[    20443] =   "\\chi_{c1} ";
  pidTexName[      445] =   "\\chi_{c2} ";
  pidTexName[    10443] =   "h_{c} ";
  pidTexName[   100441] =   "\\eta_{c}(2S) ";
  pidTexName[   100443] =   "\\psi^{\\prime} ";
  pidTexName[    30443] =   "\\psi(3770) ";
  pidTexName[   110441] =   "\\chi_{c0}^{\\prime} ";
  pidTexName[   120443] =   "\\chi_{c1}^{\\prime} ";
  pidTexName[   100445] =   "\\chi_{c2}^{\\prime} ";
  pidTexName[  9000443] =   "\\psi(4040) ";
  pidTexName[       51] =   "\\eta_{c2} ";
  pidTexName[       54] =   "X(3940) ";
  pidTexName[       55] =   "Y(3940) ";
  pidTexName[     411 ] =   "D^{+} ";
  pidTexName[     -411] =   "D^{-} ";
  pidTexName[     413 ] =   "D^{*+} ";
  pidTexName[     -413] =   "\\bar{D}^{*-} ";
  pidTexName[      421] =   "D^{0} ";
  pidTexName[     -421] =   "\\bar{D}^{0} ";
  pidTexName[      423] =   "D^{*0} ";
  pidTexName[     -423] =   "\\bar{D}^{*0} ";
  pidTexName[      431] =   "D_{s}^{+} ";
  pidTexName[     -431] =   "D_{s}^{-} ";
  pidTexName[   100313] =   "K^{*}(1410)^{0} ";
  pidTexName[  -100313] =   "\\bar{K^{*}(1410)^{0}} ";
  pidTexName[   100323] =   "K^{*}(1410)^{+} ";
  pidTexName[  -100323] =   "K^{*}(1410)^{-} ";
  pidTexName[    30313] =   "K^{*}(1680)^{0} ";
  pidTexName[   -30313] =   "\\bar{K^{*}(1680)^{0}} ";
  pidTexName[    30213] =   "\\rho(1700)^{+} ";
  pidTexName[   -30213] =   "\\rho(1700)^{-} ";
  pidTexName[    30113] =   "\\rho(1700)^{0} ";
  pidTexName[   -30113] =   "\\bar{\\rho(1700)^{0}} ";
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
string TopoAnaAlg::Vint2String(vector<int> Vint)
{
 
  sort(Vint.begin(), Vint.end());

  //convert int to string
  string tempLine = "";
  unsigned int vsize = Vint.size();
  for (unsigned int i=0; i<vsize; i++)
  {
    stringstream s;
    s << Vint[i];
    tempLine += s.str();
    tempLine += " ";
  }
  return tempLine;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::BubbleSort(std::vector<int> &pid,
                                  std::vector<int> &midx)
{
  if ( (int) pid.size() != (int) midx.size() )
  {
    std::cout << "the two vector have different length!" << std::endl;
    std::cout << "the size of pid is " << (int) pid.size() << std::endl;
    std::cout << "the size of midx is " << (int) midx.size() << std::endl;
    std::cout << "Please check your code!" << std::endl; 
    exit(1);
  }

  unsigned int vsize = midx.size();
  if (vsize<2) return;

  // sort max->min 
  int pidtemp;
  int idxtemp;
  for ( unsigned int i=0; i<vsize-1; i++ )
  {
    for ( unsigned int j=i+1; j<vsize; j++ )
    {
      if ( midx[i] < midx[j] )
      {
        pidtemp = pid[i]; idxtemp = midx[i];
        pid[i] = pid[j];  midx[i] = midx[j];
        pid[j] = pidtemp; midx[j] = idxtemp;
      }
    } // for j
  } // for i

}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::BubbleSort(vector<int> &idx, vector<int> &pid,
                                  vector<int> &midx)
{
  // sort min -> max
  int m1tmp;
  int m2tmp;
  int m3tmp;
  unsigned int vsize = pid.size();
  for ( unsigned int i=0; i<vsize-1; i++ )
  {
    for ( unsigned int j=i+1; j<vsize; j++ )
    {
      if ( pid[i] > pid[j] )
      {
        m1tmp = idx[i];  m2tmp = pid[i];  m3tmp = midx[i];
        idx[i] = idx[j]; pid[i] = pid[j]; midx[i] = midx[j];
        idx[j] = m1tmp;  pid[j] = m2tmp;  midx[j] = m3tmp;
      }
    } // for j
  } // for i

}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::EventReorder(vector<MCParticle> &event)
{
  vector<int> idx; idx.clear();
  vector<int> pid; pid.clear();
  vector<int> midx; midx.clear();
  for (unsigned int i=0; i<event.size(); i++){
    MCParticle particle = event[i];
    idx.push_back(particle.idx);
    pid.push_back(particle.pid);
    midx.push_back(particle.midx);
  }  

  // sort min->max 
  vector<int> idxtmp; idxtmp.clear();
  vector<int> pidtmp; pidtmp.clear();
  vector<int> midxtmp; midxtmp.clear();

  unsigned int vsize = midx.size();
  //the primary particle, i.e, psi(2S)
  idxtmp.push_back(idx[0]);
  pidtmp.push_back(pid[0]);
  midxtmp.push_back(midx[0]);
  for (unsigned int i=0; i<vsize-1; i++)
  {
    vector<int> sonsidx; sonsidx.clear();
    vector<int> sonsid; sonsid.clear();
    vector<int> fatheridx; fatheridx.clear();

    for (unsigned int j=i+1; j<vsize; j++)
    {
      if (midx[j] == idx[i])
      {
        sonsidx.push_back(idx[j]);
        sonsid.push_back(pid[j]);
        fatheridx.push_back(midx[j]);
      }
    } // for j
    if (!sonsid.empty())
    {
      BubbleSort(sonsidx, sonsid, fatheridx);
      for (unsigned int k=0; k<sonsid.size(); k++)
      {
        idxtmp.push_back(sonsidx[k]);
        pidtmp.push_back(sonsid[k]);
        midxtmp.push_back(fatheridx[k]);
      }
    }
  } // for i
  vector<int> vitmp = midxtmp;
  for (unsigned int ni=0; ni<vsize; ni++)
  {
    for (unsigned int nj=0; nj<vsize; nj++)
    {
      if (midxtmp[ni] == idxtmp[nj])
      {
        vitmp[ni] = nj;
      }
    }
  }
  for (unsigned int ni=0; ni<vsize; ni++)
  {
    idxtmp[ni] = ni;
  }

  event.clear();
  MCParticle particle;
  for (unsigned int ni=0; ni<vsize; ni++) {
    particle.idx = idxtmp[ni];
    particle.pid = pidtmp[ni];
    particle.midx = vitmp[ni];
    event.push_back(particle);
  }

}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::getEvtDecayChain(vector<MCParticle> event)
{

  vector<int> idx; idx.clear();
  vector<int> pid; pid.clear();
  vector<int> midx; midx.clear();
  vector<int> iLeaf; iLeaf.clear();
  vector<int> iChain; iChain.clear();
  for (unsigned int i=0; i<event.size(); i++){
    MCParticle particle = event[i];
    idx.push_back(particle.idx);
    pid.push_back(particle.pid);
    midx.push_back(particle.midx);
    iLeaf.push_back(1);
    iChain.push_back(0);
  }  

  finalState.clear();
  for (unsigned int i=0; i<event.size(); i++){
    if (idx[i] == 0) { finalState.push_back(pid[i]); }
    for (unsigned int j=i+1; j<event.size(); j++){
      if (idx[i] == midx[j]) {
        iLeaf[i] = 0;
        iChain[j] = iChain[i] + 1;
      }
    }
    if (iLeaf[i] == 1) { finalState.push_back(pid[i]); }  
  }
  stable_sort(finalState.begin()+1, finalState.end(), CompPid);

  unsigned int vsize = midx.size();
  unsigned int nChain = iChain[vsize-1] + 1;

  EvtDecayTree.clear();
  list<int> branchid; 
  branchid.clear();
  for (unsigned int i=0; i<nChain; i++) {
    for (unsigned int j=0; j<event.size(); j++) {
      if (iChain[j] == (int)i && iLeaf[j]==0) {
        //branchid.clear();
        branchid.push_back(pid[j]);
        for (unsigned int k=j+1; k<event.size(); k++) {
          if (midx[k] == idx[j]) branchid.push_back(pid[k]);   
        }
        if (pid[j] != 111) EvtDecayTree.push_back(branchid);//piz decay cancelled
        branchid.clear();
      }
    }
  }
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
string TopoAnaAlg::TopoString(vector<MCParticle> event)
{
  Vint TopoChain;
  TopoChain.clear();
  Vint iChain;
  iChain.clear();
  Vint vorder1;
  vorder1.clear();
  Vint vorder2;
  vorder2.clear();

  unsigned int vsize = event.size();
  begin:
  for ( unsigned int i=0; i<vsize; i++ )
  {
    MCParticle particle = event[i];  
    int pid = particle.pid;
    int midx = particle.midx;
    if (vorder1.empty())
    {
      vorder1.push_back(i);
      TopoChain.push_back(pid);
      continue;
    }
    for (unsigned int j=0; j<vorder1.size(); j++)
    {
      if (midx == vorder1[j]) 
      {
        vorder2.push_back(i);
        iChain.push_back(pid);
	    //std::cout << pid << std::endl;
      }
    }
  }

  if (!vorder2.empty())
  {
    std::sort(iChain.begin(), iChain.end());
    for (unsigned int k=0; k<iChain.size(); k++)
    {
      TopoChain.push_back(iChain[k]);
    }
    vorder1.clear();
    vorder1 = vorder2;
    vorder2.clear();
    iChain.clear();
    goto begin;
  }

  std::string tempLine = "";
  //convert int to string
  for (unsigned int i=0; i<TopoChain.size(); i++)
  {
    stringstream s;
    s << TopoChain[i];
    tempLine += s.str();
    tempLine += " ";
  }
  //std::cout << tempLine << std::endl;

  return tempLine;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool TopoAnaAlg::SameFinalState(vector<MCParticle> mcevt1, vector<MCParticle> mcevt2)
{
  vector<int> fs1; fs1.clear();
  vector<int> fs2; fs2.clear();

  vector<int> idx1; idx1.clear();
  vector<int> pid1; pid1.clear();
  vector<int> midx1; midx1.clear();

  vector<int> idx2; idx2.clear();
  vector<int> pid2; pid2.clear();
  vector<int> midx2; midx2.clear();

  MCParticle particle;
  for (unsigned int i=0; i<mcevt1.size(); i++) {
      particle = mcevt1[i];
      idx1.push_back(particle.idx);
      pid1.push_back(particle.pid);
      midx1.push_back(particle.midx);
  }
  for (unsigned int i=0; i<mcevt2.size(); i++) {
      particle = mcevt2[i];
      idx2.push_back(particle.idx);
      pid2.push_back(particle.pid);
      midx2.push_back(particle.midx);
  }

  for (unsigned int i=0; i<mcevt1.size(); i++) {
    bool leaf = true;  
    for (unsigned int j=0; j<mcevt1.size(); j++) {
      if (idx1[i] == midx1[j]) leaf = false;  
    }
    if (leaf) fs1.push_back(pid1[i]);
  }

  for (unsigned int i=0; i<mcevt2.size(); i++) {
    bool leaf = true;  
    for (unsigned int j=0; j<mcevt2.size(); j++) {
      if (idx2[i] == midx2[j]) leaf = false;  
    }
    if (leaf) fs2.push_back(pid2[i]);
  }

  sort(fs1.begin(), fs1.end());
  sort(fs2.begin(), fs2.end());

  if (fs1==fs2) { return true; } else { return false; }
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::ReadCard()
{

  vector<string> vstring;//save for tree name and root file name
  MCParticle particle;
  vector<MCParticle> mcevent;
  mcevent.clear();
  m_MCSignals.clear();

  std::ifstream m_inputCards;
  m_inputCards.open("topo.cards", std::ios::in);

    bool topoStart = false;
    bool inclusiveParticle = false;

  if (m_inputCards.is_open())
  {
    std::string line;
    int particleIndex;
    int particleID;
    int fatherIndex;
    std::string TopoChainStr = "";
    Vint iChain;
    iChain.clear();
    while (!m_inputCards.eof())
    {
      getline (m_inputCards, line);
      if (line.empty()) continue;
      if (line[0] == '#') continue;
      if (line[0] == ' ') continue;
      if (line == "TOPO START") 
      {
        topoStart = true;
        continue;
      }
      if (line == "INCLUSIVE PARTICLE")
      {
         inclusiveParticle = true;
         continue;
      }
      //std::cout << line << std::endl;
      if (!topoStart && !inclusiveParticle)
      {
        vstring.push_back(line);
      }
      else if (topoStart)
      {
        istringstream stream(line);
        stream >> particleIndex >> particleID >> fatherIndex;
        particle.idx = particleIndex;
        particle.pid = particleID;
        particle.midx = fatherIndex;

        if (particleIndex == 0)
	    {
          if (mcevent.size() != 0) {
            EventReorder(mcevent);
            m_MCSignals.push_back(mcevent);
          }
          mcevent.clear();
          mcevent.push_back(particle);

        } // new topology or the first topology
        else
        {
          mcevent.push_back(particle);
        }
      } 
      else if (inclusiveParticle)
      {
        istringstream stream(line);
        stream >> InclusiveParticleID;
        std::cout << " inclusive Particle: " << InclusiveParticleID << std::endl;
      } // end of topo start
    } // end of while 
    if (mcevent.size() != 0) {
      EventReorder(mcevent);
      m_MCSignals.push_back(mcevent);
    } // the last event topology
    mcevent.clear();
    m_inputCards.close();

    if (vstring.size() < 2)
    {
      std::cout << "too few string for use !" << std::endl;
      std::cout << "you must give the treeName and ROOT file name!" 
                << std::endl;
      std::cout << "Please check file \"topo.cards\"! " << std::endl;
      exit(0);
    }else{
      m_treeName = vstring[0];
      m_inputFileName.clear();
      for (unsigned int i = 1; i < vstring.size(); i++) { m_inputFileName.push_back(vstring[i]); } 
    }
  }
  else
  {
    std::cout << "file: \"topo.cards\" does not existed!" << std::endl;
    exit(0);
  }

  /*
  //test
  for (unsigned int i=0; i<m_MCSignals.size(); i++) {
    vector<MCParticle> event = m_MCSignals[i];
    cout << endl;
    cout << std::setw(30) <<"Signal Event listing (summary)" << endl;
    cout.flags(ios::left | ios::fixed);
    cout << std::setw(10) << "I";
    cout.flags(ios::right | ios::fixed);
    cout << std::setw(6) << "KF";
    cout << std::setw(8) << "orig" << endl;
    //cout << endl << endl;

    for (unsigned int j=0; j<event.size(); j++) {
      MCParticle particle = event[j];
      cout.flags(ios::left | ios::fixed);
      cout << setw(8) << setprecision(0) << particle.idx;
      cout.flags(ios::right | ios::fixed);
      cout << setw(8) << setprecision(0) << particle.pid;
      cout << setw(8) << setprecision(0) << particle.midx;
      cout.flags(ios::right | ios::showpoint | ios::fixed);
      cout << endl;
      //cout << particle.idx << " " << particle.pid << " " << particle.midx << endl;
    }
  }
  */
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::OpenRootFile()
{
  chain = new TChain(m_treeName.c_str());
  for (unsigned int i = 0; i < m_inputFileName.size(); i++)
  {
    chain->Add(m_inputFileName[i].c_str());
  }

  chain->SetBranchAddress("indexmc", &indexmc, &b_indexmc);
  chain->SetBranchAddress("pdgid", pdgid, &b_pdgid);
  chain->SetBranchAddress("motheridx", motheridx, &b_motheridx);
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::ReadRootFile()
{

  m_MCTypes.clear();
  Vtopo.clear();

  MCParticle particle;
  vector<MCParticle> mcevent;
  mcevent.clear();
  //Create a new tree
  //write the clone of old tree and the new tree into one new file
  TFile *newfile = new TFile("topo.root","recreate");
  TTree *newtree = chain->CloneTree(0);
  TTree *newtree2 = new TTree("topo", "new tree");

  Int_t n_signal;
  Int_t n_itopo;
  newtree2->Branch("signal", &n_signal,  "n_signal/I");
  newtree2->Branch("itopo",  &n_itopo,   "n_itopo/I");

  vector<string> vtopostrings;
  vtopostrings.clear();
  int totalTopo = 0;
  Long64_t nevent = chain->GetEntries();
  for (Long64_t i=0; i<nevent; i++ ) 
  {
    chain->GetEntry(i);

    n_signal = 0;
    mcevent.clear();
    for (int j=0; j<indexmc; j++)
    {
      particle.idx = j;
      particle.pid = pdgid[j];
      particle.midx = motheridx[j];
      mcevent.push_back(particle);
      if (pdgid[j] == InclusiveParticleID) { n_signal = 1; }
    }
    string tempLine = TopoString(mcevent);
    //cout << tempLine << endl;

    for (unsigned int k=0; k < m_MCSignals.size(); k++)
    {
      string signalString = TopoString(m_MCSignals[k]);
      if (tempLine == signalString) { n_signal = 1; break; }
      if (SameFinalState(mcevent, m_MCSignals[k])) { n_signal = 1; break; }
    }

    Bool_t newType = true;
    for (unsigned int j=0; j<vtopostrings.size(); j++)
    {
      if (tempLine == vtopostrings[j]) { 
        newType = false;
        n_itopo = j;
        Vtopo[j]++;
        break; 
      }
    } 
    if (newType)
    {
      n_itopo = totalTopo;
      totalTopo++;
      Vtopo.push_back(1);
      vtopostrings.push_back(tempLine);
      m_MCTypes.push_back(mcevent);
    }
    //cout << vtopostrings.size() << endl;
    newtree->Fill();
    newtree2->Fill();
  }// loop for all entries

  //cout << vtopostrings.size() << endl;
  vtopostrings.clear();
  newtree->Write();
  newtree2->Write();
  newfile->Close();
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::Result()
{

  //open the file to write
  ofstream m_outputFile;
  if (m_outputFileName.empty()) { m_outputFileName = "mclist.txt"; }
  m_outputFile.open(m_outputFileName.c_str(), ios_base::out); 
  if (!m_outputFile)
  {
    std::cout << "can't open the file: mclist.txt " << std::endl;
    exit(-1);
  }

  int totalTopo = Vtopo.size();

  m_outputFile << "the topology category statisticcal information" 
               << std::endl;
  m_outputFile << "the total topology number is: " << totalTopo << std::endl;

  tidx.clear();
  for (unsigned int i=0; i<Vtopo.size(); i++) { tidx.push_back(i); }
  BubbleSort(tidx, Vtopo);

  for (unsigned int i=0; i<Vtopo.size(); i++) {
    m_outputFile.flags(ios::left | ios::fixed);
    m_outputFile << "\ntopology: " << setw(10) << tidx[i]
                 << " Events: "    << setw(10) << Vtopo[i] 
                 << std::endl << std::endl;
    m_outputFile.flags(ios::right | ios::fixed);
    m_outputFile << std::setw(30) <<"Event listing (summary)" << endl;
    m_outputFile.flags(ios::left | ios::fixed);
    m_outputFile << std::setw(10) << "I";
    m_outputFile << std::setw(15) << "particle/jet";
    m_outputFile.flags(ios::right | ios::fixed);
    m_outputFile << std::setw(8) << "KF";
    m_outputFile << std::setw(8) << "orig" << endl;
    //m_outputFile << endl << endl;

    vector<MCParticle> mcevent = m_MCTypes[tidx[i]];  
    EventReorder(mcevent);
    for (unsigned int j=0; j<mcevent.size(); j++) {
      MCParticle particle = mcevent[j];  
      string mcname = aParticleObject.GetParName(particle.pid);
      m_outputFile.flags(ios::left | ios::fixed);
      m_outputFile << setw(10) << particle.idx; 
      m_outputFile << setw(15) << mcname;
      m_outputFile.flags(ios::right | ios::fixed);
      m_outputFile << setw(8) << setprecision(0) << particle.pid;
      m_outputFile << setw(8) << setprecision(0) << particle.midx;
      m_outputFile.flags(ios::right | ios::showpoint | ios::fixed);
      m_outputFile << endl;
    }
  }
  //log file
  std::cout << "the total topology number is: " << Vtopo.size() << std::endl;
  m_outputFile << "the topology category statisticcal information" 
               << std::endl;
  m_outputFile << "the total topology number is: " << totalTopo << std::endl;
  m_outputFile << "type      " << "Event Number" << std::endl;
  for (unsigned int i=0; i<Vtopo.size(); i++) {
    m_outputFile.flags(ios::left | ios::fixed);
    m_outputFile << setw(10) << tidx[i] 
                 << setw(10) << Vtopo[i] << std::endl;
  }
 
  m_outputFile.close();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void TopoAnaAlg::makeTexFile()
{
  makeMap();
  if (pidTexName.empty()) return;

  ofstream outTexFile;
  outTexFile.open("notice.tex", ofstream::out);

  outTexFile << "\\documentclass[11pt]{article}" << endl;
  outTexFile << "\\usepackage{amsmath,amssymb}" << endl;
  outTexFile << "\\usepackage[dvips]{graphics}" << endl;
  outTexFile << "\\usepackage{graphicx}" << endl;
  outTexFile << "\\usepackage{lscape}" << endl;
  outTexFile << "\\usepackage[section]{placeins}" << endl;
  outTexFile << "\\setlength{\\oddsidemargin}{0pt}" << endl;
  outTexFile << "\\setlength{\\evensidemargin}{0pt}" << endl;
  outTexFile << "\\setlength{\\marginparwidth}{1in}" << endl;
  outTexFile << "\\setlength{\\marginparsep}{0pt}" << endl;
  outTexFile << "\\setlength{\\textwidth} {16.0cm}" << endl;
  outTexFile << "\\setlength{\\textheight}{24.0 cm}" << endl;
  outTexFile << "\\begin{document}" << endl;
  outTexFile << "\\title{MC topology analysis}" << endl;
  outTexFile << "\\author{dusx\\\\" << endl;
  outTexFile << "\\small{ ZZU}}" << endl;
  outTexFile << "\\maketitle" << endl;

  //output the topology according the event number  
  Vint tidx; tidx.clear();
  for (unsigned int i=0; i<Vtopo.size(); i++) { tidx.push_back(i); }
  BubbleSort(tidx, Vtopo);
  
  int nLineOnePage = 30;
  int numLine = 0;
  int numEvent = 0;
  for (unsigned int i=0; i<Vtopo.size(); i++) {
    if (numLine%nLineOnePage == 0) {
      outTexFile << "\\newpage" << endl;
      outTexFile << "\\begin{landscape}" << endl;
      outTexFile << "\\begin{table}[htbp] " << endl;
      outTexFile << "\\begin{center}" << endl;
      outTexFile << "\\begin{small}" << endl;
      outTexFile << "\\begin{tabular}{ll|l|lll}\\hline\\hline" << endl;
      outTexFile << "No. & decay chain & final states &  iTopo & nEvt & nTot \\\\\\hline" << endl;
    }  
    outTexFile << i << "& $"; 
    vector<MCParticle> mcevent = m_MCTypes[tidx[i]];  
    EventReorder(mcevent);
    getEvtDecayChain(mcevent);
    for (unsigned int j=0; j<EvtDecayTree.size(); j++) {
      list<int> sonTree = EvtDecayTree[j];
      for (list<int>::iterator it=sonTree.begin(); it!=sonTree.end(); it++) {
        if (it==sonTree.begin()) {
          //cout << pidTexName[*it] << " \\rightarrow ";
          outTexFile << pidTexName[*it] << " \\rightarrow ";
        } else {
          //cout << pidTexName[*it] ;
          outTexFile << pidTexName[*it] ;
        }
      }
      //cout << endl;
      outTexFile << ",\\ ";
    }
    numEvent += Vtopo[i];
    outTexFile << "$ & $";
    for (unsigned int k=0; k<finalState.size(); k++) {
      if (k==0) {
        outTexFile << pidTexName[finalState[k]] << " \\rightarrow ";
      } else {
        outTexFile << pidTexName[finalState[k]] << " ";   
      }
    }
    outTexFile << "$ & " << tidx[i] << " & " <<  Vtopo[i] << " & " << numEvent << " \\\\" << endl;
    numLine = i+1;
    if (numLine%nLineOnePage == 0 || i == Vtopo.size()-1) {
      outTexFile << "\\hline\\hline" << endl;
      outTexFile << "\\end{tabular}" << endl;
      outTexFile << "\\end{small}" << endl;
      outTexFile << "\\caption{ }" << endl;
      outTexFile << "\\end{center}" << endl;
      outTexFile << "\\end{table}" << endl;
      outTexFile << "\\end{landscape}" << endl;
    }
    //cout << endl;
  }
  outTexFile << "\\end{document}" << endl;
  outTexFile.close();
  system("latex notice");
  system("dvips -o notice.ps notice.dvi");
}
