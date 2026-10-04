#include "Game/Actor/actMapConst.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

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

}  // namespace uking::act
