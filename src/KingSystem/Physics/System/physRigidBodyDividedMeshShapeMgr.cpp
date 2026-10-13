#include "KingSystem/Physics/System/physRigidBodyDividedMeshShapeMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

RigidBodyDividedMeshShapeMgr*
RigidBodyDividedMeshShapeMgr::makeInstance(const Config& config, sead::Heap* heap) {
    auto* mgr = new (heap, 8) RigidBodyDividedMeshShapeMgr(config, heap);
    System::instance()->setRigidBodyDividedMeshShapeMgr(mgr);
    return mgr;
}

}  // namespace ksys::phys
