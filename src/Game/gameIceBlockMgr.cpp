#include "Game/gameIceBlockMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"

namespace uking {

// NON_MATCHING: register allocation of the last link reset (the original keeps it in x20).
IceBlockMgr::~IceBlockMgr() {
    _38.clear();
    if (_150) {
        delete _150;
        _150 = nullptr;
    }
    if (_158) {
        ksys::phys::QueryContactPointInfo::free(_158);
        _158 = nullptr;
    }
}

}  // namespace uking
