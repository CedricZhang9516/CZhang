#include "ParticleObject.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

ParticleObject::ParticleObject()
{

  parListFile.open("/ihepbatch/bes/dusx/common/particle.table", ios::in);
  //parListFile.open("/afs/ihep.ac.cn/bes3/offline/Boss/6.6.0/Generator/BesEvtGen/BesEvtGen-00-01-17/share/pdt.table", ios::in);
  string line;
  if (parListFile.is_open())
  {

    while (!parListFile.eof())
    {
      //getline (parListFile, line);
      //if (line.substr(0,3)=="add") { cout << line << endl; }      
      parListFile >> aMyParticle.col1        >> aMyParticle.col2 
                  >> aMyParticle.ParType     >> aMyParticle.ParName 
                  >> aMyParticle.ParId       >> aMyParticle.ParMass 
                  >> aMyParticle.ParWidth    >> aMyParticle.ParDm
                  >> aMyParticle.Par3Charge  >> aMyParticle.Par2Spin
                  >> aMyParticle.ParLifeTime >> aMyParticle.ParLundKC;
      //if ((aMyParticle.col1).substr(0,3) != "add") continue;
      Vparticle.push_back(aMyParticle);
      //cout << aMyParticle.ParName << endl;
    }

  }
  else
  {
    cout << "Unable to open file: particle.table" << endl;
    exit(1);
  }

}

ParticleObject::~ParticleObject()
{
  parListFile.close();
}

string ParticleObject::GetParName(int pdgid) const
{
  string aParName = "Unknown";

  int listLength = Vparticle.size();
  for (int i=0; i<listLength; i++)
  {
    if (Vparticle[i].ParId == pdgid)
    {
      aParName = Vparticle[i].ParName;
      break; 
    }
  }
  return aParName;
}

double ParticleObject::GetParMass(int pdgid) const
{
  double aParMass = 0.0;

  int listLength = Vparticle.size();
  for (int i=0; i<listLength; i++)
  {
    if (Vparticle[i].ParId == pdgid)
    {
      aParMass = Vparticle[i].ParMass;
      break;
    }
  }
  return aParMass;
}
