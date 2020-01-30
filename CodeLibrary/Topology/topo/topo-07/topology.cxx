#include "TopologyCategory.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

//using namespace std;

std::string Vint2String(std::vector<int>);

std::string Vint2String(std::vector<int> Vint)
{
 
  std::sort(Vint.begin(), Vint.end());

  //convert int to string
  std::string tempLine = "";
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

int main(int argc, const char* argv[])
{

  std::vector<std::string> Vstr;
  std::vector<std::string> Vtopostr;

  std::ifstream m_inputCards;
  m_inputCards.open("topo.cards", std::ios::in);

  if (m_inputCards.is_open())
  {
    std::string line;
    int particleIndex;
    int particleID;
    bool topoStart = false;
    std::string TopoChainStr = "";
    Vint iChain;
    iChain.clear();
    static int NewOrder = 0;
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
      //std::cout << line << std::endl;
      if (!topoStart)
      {
        Vstr.push_back(line);
      }
      else
      {
        // fill Vtopostr
        istringstream stream(line);
        stream >> particleIndex >> particleID;
        if (particleIndex == 0)
	{
          NewOrder = 0;
          if (!iChain.empty())
	  {
            TopoChainStr += Vint2String(iChain);
            iChain.clear();
	  }

          if (!TopoChainStr.empty())
	  {
            Vtopostr.push_back(TopoChainStr);
            TopoChainStr = "";
	  }
        } // new topology or the first topology
        if (particleIndex != NewOrder)
	{
          NewOrder = particleIndex;
          TopoChainStr += Vint2String(iChain);
          iChain.clear();
	}
        iChain.push_back(particleID);
      } // end of topo start
    } // end of while 
    TopoChainStr += Vint2String(iChain);
    Vtopostr.push_back(TopoChainStr);
    //std::cout << Vtopostr[0] << std::endl;
    //std::cout << Vtopostr[1] << std::endl;
    m_inputCards.close();

    if (Vstr.size() < 2)
    {
      std::cout << "too few string for use !" << std::endl;
      std::cout << "you must give the treeName and ROOT file name!" 
                << std::endl;
      std::cout << "Please check file \"topo.cards\"! " << std::endl;
      return 1;
    }
  }
  else
  {
    std::cout << "file: \"topo.cards\" does not existed!" << std::endl;
    return 1;
  }

  TopologyCategory aTopoCat(Vstr);
  aTopoCat.getSignalTopo(Vtopostr);
  aTopoCat.openRootFile();
  aTopoCat.TopoRead();
  aTopoCat.TopoLog();
  aTopoCat.TopoWrite();
  return 0;
}
