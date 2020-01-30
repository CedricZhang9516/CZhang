#include <iostream>
#include <iomanip> //for setw
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

map<int, string> pidTexName;
//pidTexName.clear();
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
string vint2string(vector<int> vint)
{
   string tempLine = "";
  //convert int to string
  sort(vint.begin(), vint.end());
  for (unsigned int i=0; i<vint.size(); i++)
  {
    stringstream s;
    s << vint[i];
    tempLine += s.str();
    tempLine += " ";
  }
  //cout << tempLine << endl;

  return tempLine;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void BubbleSort(vector<int> &idx, vector<int> &pid,
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
void topo_reorder(vector<int> &idx, vector<int> &pid,
                                  vector<int> &midx)
{
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
  for (unsigned int ni=0; ni<vsize-1; ni++)
  {
    idxtmp[ni] = ni;
  }

  idx = idxtmp;
  pid = pidtmp;
  midx = vitmp;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * *
vector<string> pyramid(vector<int> idx, vector<int> pid, vector<int> midx)
{
  vector<string> res;
  res.clear();

  unsigned int vsize = idx.size();

  //is leaf?
  vector<int> vleaf(vsize, 0);
  for (unsigned int i=0; i<vsize; i++)
  {
    int leaf = 0;
    for (unsigned int j=0; j<vsize; j++)
    {
      if (midx[i] == idx[j]) { leaf += 1; break;}
    }
    if (leaf == 1) vleaf[i] = 1;
  }
  for (unsigned int i=0; i<vsize; i++)
  {
    cout << i << " " << vleaf[i] << " " << pid[i] << " " << midx[i] << endl;
  }
  vector<int> iChain;
  iChain.clear();
  vector<int> vorder1;
  vorder1.clear();
  vector<int> vorder2;
  vorder2.clear();

  begin:
  for (unsigned int i=0; i<vsize; i++)
  {
    if (vorder1.empty())
    {
      vorder1.push_back(i);
      vector<int> a;
      a.clear();
      a.push_back(pid[i]);
      res.push_back(vint2string(a));
      continue;
    }
    for (unsigned int j=0; j<vorder1.size(); j++)
    {
      if (midx[i] == vorder1[j]) 
      {
        vorder2.push_back(i);
        iChain.push_back(pid[i]);
	    //cout << pid[i] << endl;
      }
    }
  }
  if (!vorder2.empty())
  {
    //for (unsigned int ki=0; ki<vorder2.back(); ki++)
    for (unsigned int k=0; k<=vorder1.back(); k++)
    {
      //cout << k <<  " " << vleaf[k] << " " << pid[k] << endl;
      if (vleaf[k] == 1) iChain.push_back(pid[k]);
    }
    res.push_back(vint2string(iChain));
    vorder1.clear();
    vorder1 = vorder2;
    vorder2.clear();
    iChain.clear();
    goto begin;
  }

  return res;
}

int main()
{
  vector<int> idx;
  idx.clear();
  idx.push_back(0);
  idx.push_back(1);
  idx.push_back(2);
  idx.push_back(3);
  idx.push_back(4);
  idx.push_back(5);
  idx.push_back(6);

  vector<int> pid;
  pid.clear();
  pid.push_back(100443);
  pid.push_back(211);
  pid.push_back(-10211);
  pid.push_back(221); 
  pid.push_back(-211); 
  pid.push_back(22);
  pid.push_back(22);

  vector<int> midx;
  midx.clear();
  midx.push_back(-1); 
  midx.push_back(0); 
  midx.push_back(0); 
  midx.push_back(2); 
  midx.push_back(2); 
  midx.push_back(3); 
  midx.push_back(3); 

  topo_reorder(idx, pid, midx);

  vector<string> sa = pyramid(idx, pid, midx);
  for (unsigned i=0; i<sa.size(); i++)
  {
    cout << sa[i] << endl;
  }
  for (unsigned i=0; i<pid.size(); i++)
  {
    cout.flags(ios::left | ios::fixed);
    cout << setw(10) << idx[i];
    cout.flags(ios::right | ios::fixed);
    cout << setw(10) << setprecision(0) << pid[i];
    cout << setw(10) << setprecision(0) << midx[i] << endl;
  }

  string a("abcdefghijklmnopqrstuvwxyz");
  int subs = a.find("jkl");
  cout << subs << endl;
  return 0;
}
