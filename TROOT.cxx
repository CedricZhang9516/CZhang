#include "/Users/zhangce/Application/root_61406/include/TRint.h"
#include "/Users/zhangce/Application/root_61406/include/TROOT.h"

int Error; //left undefined by Motif

extern void  InitGui();  // initializer for GUI needed for interactive interface
VoidFuncPtr_t initfuncs[] = { InitGui, 0 };
TROOT root("Rint","The ROOT Interactive Interface", initfuncs);

int main(int argc, char **argv)
{
   TRint *theApp = new TRint("ROOT example", &argc, argv);
   // Init Intrinsics, build all windows, and enter event loop
   theApp->Run();
   return(0);
}