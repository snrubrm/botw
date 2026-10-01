#include "Game/AI/Action/actionChuchuPreAttack.h"

namespace uking::action {

ChuchuPreAttack::ChuchuPreAttack(const InitArg& arg) : ChuchuPreAttackBase(arg) {}

ChuchuPreAttack::~ChuchuPreAttack() = default;

bool ChuchuPreAttack::init_(sead::Heap* heap) {
    return ChuchuPreAttackBase::init_(heap);
}

void ChuchuPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ChuchuPreAttackBase::enter_(params);
    _168 = false;
    setDamageCallbackTiming(mActor, 4, &_140);
    if (!mSubAS_s.isEmpty())
        playAS(mSubAS_s.cstr(), false, 0, *mSubASSlot_s, -1.0f);
}

void ChuchuPreAttack::leave_() {
    sub_71005DA114(mActor, &_140);
    if (!mLeaveSubAS_s.isEmpty())
        playAS(mLeaveSubAS_s.cstr(), true, 0, *mSubASSlot_s, -1.0f);
    ChuchuPreAttackBase::leave_();
}

void ChuchuPreAttack::loadParams_() {
    ChuchuPreAttackBase::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mPosReduceRatioByDamage_s, "PosReduceRatioByDamage");
    getStaticParam(&mDamageAS_s, "DamageAS");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
    getStaticParam(&mDamageSubAS_s, "DamageSubAS");
}

void ChuchuPreAttack::calc_() {
    ChuchuPreAttackBase::calc_();
}

}  // namespace uking::action
