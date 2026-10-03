#include "Game/AI/Behavior/behaviorCloseEye.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

CloseEye::CloseEye(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
CloseEye::~CloseEye() {
    ;
}

bool CloseEye::m6(sead::Heap* heap) {
    return true;
}

void CloseEye::m7() {}

void CloseEye::m8() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        enemy->_f60.sub_7100701BE4(mLeftEyeLidName_s, mRightEyeLidName_s, *mCloseOffset_s);
        enemy->_f60.sub_7100701CE8();
        enemy->_f60.sub_7100701DF0();
    }
}

void CloseEye::m9() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        enemy->_f60.removeOrDefer();
}

void CloseEye::loadParams() {
    getStaticParam(&mLeftEyeLidName_s, "LeftEyeLidName");
    getStaticParam(&mRightEyeLidName_s, "RightEyeLidName");
    getStaticParam(&mCloseOffset_s, "CloseOffset");
}

}  // namespace uking::behavior
