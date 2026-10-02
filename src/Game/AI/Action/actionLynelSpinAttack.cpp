#include "Game/AI/Action/actionLynelSpinAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"

namespace uking::action {

LynelSpinAttack::LynelSpinAttack(const InitArg& arg) : ForkWeaponAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
LynelSpinAttack::~LynelSpinAttack() {
    ;
}

bool LynelSpinAttack::init_(sead::Heap* heap) {
    return ForkWeaponAttack::init_(heap);
}

// NON_MATCHING: the original computes &mStartASName_s before the m132() call (scheduling)
void LynelSpinAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponAttackBase::enter_(params);
    mFlags.reset(Flag::Changeable);
    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E786F0(mStartASName_s);
    playAS(mStartASName_s.cstr(), false, *mTargetBone_s, *mSeqBank_s, -1.0f);
    _cc = 0;
    _d0 = 0;
}

void LynelSpinAttack::leave_() {
    ForkWeaponAttack::leave_();
}

void LynelSpinAttack::loadParams_() {
    ForkWeaponAttack::loadParams_();
    getStaticParam(&mMinLoopTime_s, "MinLoopTime");
    getStaticParam(&mLoopEndAngle_s, "LoopEndAngle");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mLoopASName_s, "LoopASName");
    getStaticParam(&mEndASName_s, "EndASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LynelSpinAttack::calc_() {
    ForkWeaponAttack::calc_();
}

}  // namespace uking::action
