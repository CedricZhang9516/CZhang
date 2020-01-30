#include "TopoAnaAlg.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// * * * * * * * * * * * * * * * * * * * * * * * * * * *
int main(int argc, const char* argv[])
{

  //const char* cardName = argv[1];

  TopoAnaAlg TopoAna;
  TopoAna.ReadCard();
  TopoAna.OpenRootFile();
  TopoAna.ReadRootFile();
  //TopoAna.Result();
  TopoAna.makeTexFile();
  return 0;
}
