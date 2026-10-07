#include "KingSystem/World/worldChemicalMgr.h"

// Original 0x71010c9cfc: a four-byte forwarder to sub_71010C9B48. It lives in the original
// ChemicalMgr translation unit; keeping it in its own TU preserves the call in its callers.
void WorldMgrStruct0_8_a::sub_71010C9CFC() {
    sub_71010C9B48();
}
