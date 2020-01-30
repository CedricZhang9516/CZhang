#include "GaudiKernel/DeclareFactoryEntries.h"
#include "MumuAlg/Mumu.h"

DECLARE_ALGORITHM_FACTORY( Mumu )

DECLARE_FACTORY_ENTRIES( MumuAlg ) {
  DECLARE_ALGORITHM(Mumu);
}

