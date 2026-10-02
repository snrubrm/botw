#include "Game/AI/Action/actionCameraEventMovePosFlow.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadSafeString.h>

namespace uking::action {

CameraEventMovePosFlow::CameraEventMovePosFlow(const InitArg& arg)
    : CameraEventMovePosBase(arg) {}

// The base class stores the parameters as const pointers (CameraEventMovePos loads them as static
// parameters); this class loads most of them as dynamic parameters.
void CameraEventMovePosFlow::m46() {
    CameraEventMovePosBase::m46();
    getStaticParam(&mBaseMode, "BaseMode");
    getDynamicParam_2(const_cast<s32**>(&mTargetActor1), "TargetActor1");
    getDynamicParam_2(const_cast<s32**>(&mTargetActor2), "TargetActor2");
    getDynamicParam_2(const_cast<s32**>(&mAtAppendMode), "AtAppendMode");
    getDynamicParam_2(const_cast<s32**>(&mPosAppendMode), "PosAppendMode");
    getDynamicParam_2(const_cast<s32**>(&mFovyAppendMode), "FovyAppendMode");
    getDynamicParam_2(const_cast<s32**>(&mMotionMode), "MotionMode");
    getDynamicParam_2(&mCount, "Count");
    getDynamicParam_2(&mCushion, "Cushion");
    getDynamicParam_2(&mStartCalcOnly, "StartCalcOnly");
    getDynamicParam_2(&mCollisionInterpolateSkip, "CollisionInterpolateSkip");
    getDynamicParam_2(&mAccept1FrameDelay_d, "Accept1FrameDelay");
    getDynamicParam(&mActorName1, "ActorName1");
    getDynamicParam(&mActorName2, "ActorName2");
    getDynamicParam(&mUniqueName1, "UniqueName1");
    getDynamicParam(&mUniqueName2, "UniqueName2");
    getDynamicParam(&mGameDataVec3fCameraPos, "GameDataVec3fCameraPos");
    getDynamicParam(&mGameDataVec3fCameraAt, "GameDataVec3fCameraAt");

    // A loop over the patterns (only one): the original computes all parameter addresses before the
    // key strings are built (loop-invariant code), and formats the pattern number from the index.
    for (int i = 0; i < 1; ++i) {
        Pattern& pattern_params = mPattern;
        sead::FixedSafeString<16> pattern;
        pattern.copy("Pattern");
        pattern.appendWithFormat("%d", i + 1);
        sead::FixedSafeString<32> key;
        key.copy(pattern);
        key.append("AtX");
        getDynamicParam_2(const_cast<f32**>(&pattern_params.at_x), key.cstr());
        key.copy(pattern);
        key.append("AtY");
        getDynamicParam_2(const_cast<f32**>(&pattern_params.at_y), key.cstr());
        key.copy(pattern);
        key.append("AtZ");
        getDynamicParam_2(const_cast<f32**>(&pattern_params.at_z), key.cstr());
        key.copy(pattern);
        key.append("PosX");
        getDynamicParam_2(const_cast<f32**>(&pattern_params.pos_x), key.cstr());
        key.copy(pattern);
        key.append("PosY");
        getDynamicParam_2(const_cast<f32**>(&pattern_params.pos_y), key.cstr());
        key.copy(pattern);
        key.append("PosZ");
        getDynamicParam_2(const_cast<f32**>(&pattern_params.pos_z), key.cstr());
        key.copy(pattern);
        key.append("Fovy");
        getDynamicParam_2(const_cast<f32**>(&pattern_params.fovy), key.cstr());
        key.copy(pattern);
        key.append("Use");
        getStaticParam(&pattern_params.use, key.cstr());
    }
}

float CameraEventMovePosFlow::m47(const Pattern& pattern) {
    return sead::Mathf::deg2rad(*pattern.fovy);
}

bool CameraEventMovePosFlow::m48() {
    return *mAccept1FrameDelay_d;
}

}  // namespace uking::action
