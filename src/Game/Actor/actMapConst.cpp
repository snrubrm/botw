#include "Game/Actor/actMapConst.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

bool sub_7100700428(const sead::Matrix34f& lhs, const sead::Matrix34f& rhs, f32 epsilon);

namespace uking::act {

MapConst::MapConst(const CreateArg& arg) : Actor(arg) {
    _1c0 = 3;
}

// NON_MATCHING: the original destructors (D1 / D0) keep the vtable pointer stores before the tail call to
// ~Actor; we drop them (the destructor has no members to destroy).
MapConst::~MapConst() { ; }  // see GameDataFlagSelector::~GameDataFlagSelector() in upstream (commit 96101229)

bool MapConst::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

void MapConst::m63() {
    _83c = getMaxLife();
    _844 = true;
    _840 = ksys::map::getActorTraverseDist(getName(), 1.0f);
    if (mFieldBodyGroup) {
        getHomeMtx(&mMtx);
        nullsub_4648();
    }
    if (mPhysics)
        mPhysics->sub_7100FC012C(nullptr);
}

void MapConst::updatePositionMaybe() {
    if (mActorFlags2.isOn(ActorFlag2::_10))
        return;
    if (mFieldBodyGroup) {
        getHomeMtx(&mMtx);
        nullsub_4648();
        if (auto* body = getMainBody()) {
            if (!body->isAddedToWorld()) {
                sead::Matrix34f transform;
                body->getTransform(&transform);
                if (!sub_7100700428(transform, mMtx, sead::Mathf::epsilon()))
                    body->setTransform(mMtx, ksys::phys::PropagateToLinkedMotions{false});
            }
        }
    } else if (auto* body = getMainBody()) {
        sead::Matrix34f transform;
        body->getTransform(&transform);
        mMtx = transform;
        nullsub_4648();
    }
}

}  // namespace uking::act
