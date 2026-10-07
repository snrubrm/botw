#include "Game/AI/Action/actionZoraSurfing.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ZoraSurfing::ZoraSurfing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraSurfing::~ZoraSurfing() = default;

bool ZoraSurfing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraSurfing::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ZoraSurfing::leave_() {
    ksys::act::ai::Action::leave_();
}

void ZoraSurfing::loadParams_() {
    getStaticParam(&mRotRadPerSec_s, "RotRadPerSec");
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinHeight_s, "FinHeight");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mIsClampRotVel_s, "IsClampRotVel");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASNameJump_s, "ASNameJump");
    getStaticParam(&mAddCalcStickX_s, "AddCalcStickX");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void ZoraSurfing::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: instruction scheduling only (the original loads the target x/y pair before the actor translation).
float ZoraSurfing::m32() {
    const auto& target = _20._8.sub_7100EEB370();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const float distance = (pos - target).length();
    const float t = sead::Mathf::clamp((distance - *mOnRailDistance_s) / (*mFarDistance_s - *mOnRailDistance_s), 0.0f, 1.0f);
    return (1.0f - t) * 10.0f;
}

ksys::map::Rail* ZoraSurfing::m33() {
    if (!mUniqueName_d.isEmpty()) {
        for (s32 i = 0; i < 10; ++i) {
            auto* rail = sub_7100EEF264(mActor, i);
            if (rail && rail->getUniqueName() &&
                mUniqueName_d == sead::SafeString(rail->getUniqueName()))
                return rail;
        }
    }
    return sub_7100EEF264(mActor, 0);
}

// NON_MATCHING: the common distance variable keeps -1.0f in a saved register; the original uses a separate fallback block.
void ZoraSurfing::m34() {
    if (!_20.sub_7100EEBB74())
        return;
    if (!_20.sub_7100EEBE88() && _20.m3() && m37())
        _20.sub_7100EEBE9C(-_20._58);
    f32 distance = -1.0f;
    if (_20._8.rail && _20._8.rail->isBezier())
        distance = m32() * ksys::VFR::instance()->getDeltaFrame();
    // called through a pointer in the original (not devirtualised)
    (&_20)->m4(distance, nullptr, nullptr);
}

void ZoraSurfing::m36() {
    sub_7100EEF078(_20._8.rail, _20._30.progress);
    sub_71002C2AD0();
}

bool ZoraSurfing::m37() {
    return true;
}

void ZoraSurfing::m38() {
    if (m39()->isEmpty())
        return;
    playAS(m39()->cstr(), true, 0, 0, -1.0f);
}

// NON_MATCHING: select operand order only (the original adds 0x130 first and selects with eq).
const sead::SafeString* ZoraSurfing::m39() {
    return _1d5 != 0 ? &mASNameJump_s : &mASName_s;
}

}  // namespace uking::action
