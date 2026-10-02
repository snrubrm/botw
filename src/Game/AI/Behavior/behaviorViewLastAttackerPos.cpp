#include "Game/AI/Behavior/behaviorViewLastAttackerPos.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

ViewLastAttackerPos::ViewLastAttackerPos(const InitArg& arg) : NeckControl(arg) {}

ViewLastAttackerPos::~ViewLastAttackerPos() = default;

bool ViewLastAttackerPos::m6(sead::Heap* heap) {
    return NeckControl::m6(heap);
}

void ViewLastAttackerPos::m7() {
    NeckControl::m7();
}

void ViewLastAttackerPos::m8() {
    NeckControl::m8();
}

void ViewLastAttackerPos::m9() {
    NeckControl::m9();
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
