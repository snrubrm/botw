#include "Game/AI/Behavior/behaviorDisableCloth.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::behavior {

DisableCloth::DisableCloth(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableCloth::~DisableCloth() = default;

bool DisableCloth::m6(sead::Heap* heap) {
    return true;
}

void DisableCloth::m7() {}

void DisableCloth::m8() {
    if (auto* physics = mActor->getPhysics()) {
        if (auto* cloth_set = physics->getClothSet()) {
            for (int i = 0; i < cloth_set->_18.size(); ++i)
                cloth_set->_18[i]._18 |= 8;
        }
    }
}

void DisableCloth::m9() {
    if (auto* physics = mActor->getPhysics()) {
        if (auto* cloth_set = physics->getClothSet()) {
            for (int i = 0; i < cloth_set->_18.size(); ++i)
                cloth_set->_18[i]._18 &= ~8u;
        }
    }
}

void DisableCloth::loadParams() {

}

}  // namespace uking::behavior
