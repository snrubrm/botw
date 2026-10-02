#include "Game/AI/AI/aiWithoutWeaponArrow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

WithoutWeaponArrow::WithoutWeaponArrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
WithoutWeaponArrow::~WithoutWeaponArrow() {
    ;
}

bool WithoutWeaponArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WithoutWeaponArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WithoutWeaponArrow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WithoutWeaponArrow::loadParams_() {
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mStickTime_s, "StickTime");
    getStaticParam(&mAccel_s, "Accel");
    getStaticParam(&mAimSpeed_s, "AimSpeed");
    getStaticParam(&mFallAccel_s, "FallAccel");
    getStaticParam(&mFallAimSpeed_s, "FallAimSpeed");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mAtRange_s, "AtRange");
    getStaticParam(&mAtImpulse_s, "AtImpulse");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mReflectDamageRate_s, "ReflectDamageRate");
    getStaticParam(&mCanReflect_s, "CanReflect");
    getStaticParam(&mIsReflectToParent_s, "IsReflectToParent");
    getStaticParam(&mIsDelete_s, "IsDelete");
    getStaticParam(&mIsBreakIceBlock_s, "IsBreakIceBlock");
    getStaticParam(&mIsAtHitPlayerIgnore_s, "IsAtHitPlayerIgnore");
    getStaticParam(&mIsDeleteAtHit_s, "IsDeleteAtHit");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getStaticParam(&mCallHitSEKey_s, "CallHitSEKey");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getStaticParam(&mRotOffset_s, "RotOffset");
    getStaticParam(&mTransOffset_s, "TransOffset");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

void WithoutWeaponArrow::m36() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c0 != 4)
            chemical->sub_7100D909A4();
    }
    changeChild("爆発");
}

bool WithoutWeaponArrow::m39() {
    return true;
}

void WithoutWeaponArrow::m40() {
    if (*mIsDelete_s)
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    else
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

s32 WithoutWeaponArrow::m41() {
    return _13c;
}

s32 WithoutWeaponArrow::m47() {
    return *mStickTime_s;
}

bool WithoutWeaponArrow::m48() {
    return isCurrentChild("発射");
}

}  // namespace uking::ai
