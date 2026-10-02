#include "Game/AI/Behavior/behaviorDieEye.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

DieEye::DieEye(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
DieEye::~DieEye() {
    ;
}

bool DieEye::m6(sead::Heap* heap) {
    return true;
}

void DieEye::m7() {}

void DieEye::m8() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        enemy->_f60.sub_7100701BE4(mLeftEyeLidName_s, mRightEyeLidName_s, *mCloseOffset_s);
        enemy->_f60.sub_7100701CE8();
        enemy->_f60.sub_7100701DD8();
    }
}

// NON_MATCHING: the original computes &_f60 once before the branch and stores through it (+0x192)
void DieEye::m9() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        if (enemy->_f60._178 <= 0)
            enemy->_f60.sub_7100701D4C();
        else
            enemy->_f60._192 = true;
    }
}

void DieEye::loadParams() {
    getStaticParam(&mLeftEyeLidName_s, "LeftEyeLidName");
    getStaticParam(&mRightEyeLidName_s, "RightEyeLidName");
    getStaticParam(&mCloseOffset_s, "CloseOffset");
}

}  // namespace uking::behavior
