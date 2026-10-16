#include "Game/Actor/Behavior/behaviorViewLastAttackerPos.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

ViewLastAttackerPos::ViewLastAttackerPos(const InitArg& arg) : NeckControl(arg) {}

ViewLastAttackerPos::~ViewLastAttackerPos() = default;

bool ViewLastAttackerPos::init_(sead::Heap* heap) {
    return NeckControl::init_(heap);
}

void ViewLastAttackerPos::calc() {
    NeckControl::calc();
}

void ViewLastAttackerPos::enter() {
    NeckControl::enter();
}

void ViewLastAttackerPos::leave() {
    NeckControl::leave();
}

void ViewLastAttackerPos::m15(sead::Vector3f* out) {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        if (enemy->_e08._5d) {
            mActor->getMtx().getTranslation(*out);
            sub_71005DB198(out, mActor);
            *out -= enemy->_e08._40;
        } else {
            *out = enemy->_e08._4c;
        }
    }
}

void ViewLastAttackerPos::loadParams() {
    NeckControl::loadParams();
}

}  // namespace uking::behavior
