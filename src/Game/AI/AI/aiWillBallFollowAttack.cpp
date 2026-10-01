#include "Game/AI/AI/aiWillBallFollowAttack.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

WillBallFollowAttack::WillBallFollowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallFollowAttack::~WillBallFollowAttack() = default;

bool WillBallFollowAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallFollowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = 0;
    _80 = _84 = *mDelayTimer_s;
    _7c = _80;
    _88 = false;

    sead::Vector3f target = *mTargetPos_d;
    const f32 freq = sead::Mathf::pi2() / *mCycleY_s;
    target.y += *mAmplitudeY_s * sead::Mathf::sin(freq * _78);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (sead::Mathf::sqrt(ksys::util::sqXZDistance(target, pos)) < *mImmidiateLightningXZ_s &&
        sead::Mathf::abs(pos.y - target.y) < *mImmidiateLightningY_s) {
        sub_71005F34A0();
    } else {
        sub_71005F35E4();
    }
}

// NON_MATCHING: instruction scheduling of the cycle/amplitude loads and fmul operand order
void WillBallFollowAttack::sub_71005F34A0() {
    sead::Vector3f target = *mTargetPos_d;
    const f32 cycle = *mCycleY_s;
    const f32 amp = *mAmplitudeY_s;
    const f32 rate = sead::Mathf::pi2() / cycle;
    target.y += amp * sead::Mathf::sin(_78 * rate);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    params.addVec3(*mCenterPos_d, "CenterPos", -1);
    changeChild("待機", &params);
}

// NON_MATCHING: instruction scheduling of the cycle/amplitude loads and fmul operand order
void WillBallFollowAttack::sub_71005F35E4() {
    sead::Vector3f target = *mTargetPos_d;
    const f32 cycle = *mCycleY_s;
    const f32 amp = *mAmplitudeY_s;
    const f32 rate = sead::Mathf::pi2() / cycle;
    target.y += amp * sead::Mathf::sin(_78 * rate);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    params.addVec3(*mCenterPos_d, "CenterPos", -1);
    m34(&params);
    changeChild("追尾", &params);
}

void WillBallFollowAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallFollowAttack::loadParams_() {
    getStaticParam(&mImmidiateLightningTime_s, "ImmidiateLightningTime");
    getStaticParam(&mCycleY_s, "CycleY");
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mImmidiateLightningXZ_s, "ImmidiateLightningXZ");
    getStaticParam(&mImmidiateLightningY_s, "ImmidiateLightningY");
    getStaticParam(&mAmplitudeY_s, "AmplitudeY");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

}  // namespace uking::ai
