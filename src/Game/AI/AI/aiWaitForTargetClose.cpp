#include "Game/AI/AI/aiWaitForTargetClose.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WaitForTargetClose::WaitForTargetClose(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitForTargetClose::~WaitForTargetClose() = default;

bool WaitForTargetClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitForTargetClose::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005E87FC();
}

void WaitForTargetClose::sub_71005E87FC() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 distance = (pos - *mTargetPos_d).length();
    if (m34(distance)) {
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("近づき反応", &params);
    } else {
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &params);
    }
}

void WaitForTargetClose::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitForTargetClose::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mFailRange_s, "FailRange");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
