#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// Original 0x71010c9cfc: a four-byte forwarder to sub_71010C9B48. It lives in the original
// ChemicalMgr translation unit; keeping it in its own TU preserves the call in its callers.
void WorldMgrStruct0_8_a::sub_71010C9CFC() {
    sub_71010C9B48();
}

// ChemicalMgr's destructor (0x71010ca33c) calls both destructors out of line (0x71010c90bc and
// 0x71010c5d2c), so they were not visible when it was compiled.
WorldMgrStruct0_8_a::~WorldMgrStruct0_8_a() {
    _8.sub_71010C90F4();
}

Unk_710250c698::~Unk_710250c698() {
    if (_18) {
        if (_18->isAddedToWorld())
            _18->removeFromWorldImmediately(nullptr);
        delete _18;
        _18 = nullptr;
    }
}
