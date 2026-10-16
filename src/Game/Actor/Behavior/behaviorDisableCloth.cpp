#include "Game/Actor/Behavior/behaviorDisableCloth.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::behavior {

DisableCloth::DisableCloth(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableCloth::~DisableCloth() = default;

bool DisableCloth::init_(sead::Heap* heap) {
    return true;
}

void DisableCloth::calc() {}

void DisableCloth::enter() {
    if (auto* physics = mActor->getPhysics()) {
        if (auto* cloth_set = physics->getClothSet()) {
            for (int i = 0; i < cloth_set->_18.size(); ++i)
                cloth_set->_18[i]._18 |= 8;
        }
    }
}

void DisableCloth::leave() {
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
