#include "Game/AI/Action/actionCameraEventMovePos.h"
#include <prim/seadSafeString.h>

namespace uking::action {

CameraEventMovePos::CameraEventMovePos(const InitArg& arg) : CameraEventMovePosBase(arg) {}

void CameraEventMovePos::m46() {
    CameraEventMovePosBase::m46();
    getStaticParam(&mTargetActor1, "TargetActor1");
    getStaticParam(&mTargetActor2, "TargetActor2");
    getStaticParam(&mAtAppendMode, "AtAppendMode");
    getStaticParam(&mPosAppendMode, "PosAppendMode");
    getStaticParam(&mFovyAppendMode, "FovyAppendMode");
    getStaticParam(&mBaseMode, "BaseMode");
    getStaticParam(&mMotionMode, "MotionMode");
    getDynamicParam_2(&mCount, "Count");
    getDynamicParam_2(&mCushion, "Cushion");
    getDynamicParam_2(&mStartCalcOnly, "StartCalcOnly");
    getDynamicParam_2(&mCollisionInterpolateSkip, "CollisionInterpolateSkip");
    getStaticParam(&mAccept1FrameDelay_s, "Accept1FrameDelay");
    getStaticParam(&mActorName1, "ActorName1");
    getStaticParam(&mActorName2, "ActorName2");
    getStaticParam(&mUniqueName1, "UniqueName1");
    getStaticParam(&mUniqueName2, "UniqueName2");

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
        getStaticParam(&pattern_params.at_x, key.cstr());
        key.copy(pattern);
        key.append("AtY");
        getStaticParam(&pattern_params.at_y, key.cstr());
        key.copy(pattern);
        key.append("AtZ");
        getStaticParam(&pattern_params.at_z, key.cstr());
        key.copy(pattern);
        key.append("PosX");
        getStaticParam(&pattern_params.pos_x, key.cstr());
        key.copy(pattern);
        key.append("PosY");
        getStaticParam(&pattern_params.pos_y, key.cstr());
        key.copy(pattern);
        key.append("PosZ");
        getStaticParam(&pattern_params.pos_z, key.cstr());
        key.copy(pattern);
        key.append("Fovy");
        getStaticParam(&pattern_params.fovy, key.cstr());
        key.copy(pattern);
        key.append("Use");
        getStaticParam(&pattern_params.use, key.cstr());
    }
}

float CameraEventMovePos::m47(const Pattern& pattern) {
    return *pattern.fovy;
}

bool CameraEventMovePos::m48() {
    return *mAccept1FrameDelay_s;
}

}  // namespace uking::action
