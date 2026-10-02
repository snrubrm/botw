#include "Game/AI/Behavior/behaviorGiantWeaponGrabAS.h"
#include "Game/AI/aiUnk_71025be918.h"

namespace uking::behavior {

GiantWeaponGrabAS::GiantWeaponGrabAS(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void GiantWeaponGrabAS::m8() {
    _d8 = false;
    _d9 = false;
}

void GiantWeaponGrabAS::loadParams() {
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLeftTargetBone_s, "LeftTargetBone");
    getStaticParam(&mVeryThinFrame_s, "VeryThinFrame");
    getStaticParam(&mThinFrame_s, "ThinFrame");
    getStaticParam(&mNormalFrame_s, "NormalFrame");
    getStaticParam(&mThickFrame_s, "ThickFrame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPartialBone0_s, "PartialBone0");
    getStaticParam(&mPartialBone1_s, "PartialBone1");
    getStaticParam(&mPartialBone2_s, "PartialBone2");
    getStaticParam(&mLeftPartialBone0_s, "LeftPartialBone0");
    getStaticParam(&mLeftPartialBone1_s, "LeftPartialBone1");
    getStaticParam(&mLeftPartialBone2_s, "LeftPartialBone2");
    getAITreeVariable(&mGiantPartBoneUnit_a, "GiantPartBoneUnit");
}

// NON_MATCHING: the original tests the decremented count with b.ne on the subs flags (cbnz here)
GiantWeaponGrabAS::~GiantWeaponGrabAS() {
    if (_e0) {
        auto* unit = sead::DynamicCast<Unk_71025be918>(*_e0);
        if (unit && unit->_98 > 0 && --unit->_98 == 0) {
            *_e0 = nullptr;
            delete unit;
        }
        _e0 = nullptr;
    }
}

}  // namespace uking::behavior
