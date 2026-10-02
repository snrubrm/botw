#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

// NON_MATCHING: regalloc (keeps &_68 in x20 across the memset)
TakeHitImpactForce::TakeHitImpactForce(const InitArg& arg) : ActionEx(arg) {}

void TakeHitImpactForce::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void TakeHitImpactForce::loadParams_() {
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mHighSpeedY_s, "HighSpeedY");
    getStaticParam(&mVelReduceY_s, "VelReduceY");
}

void TakeHitImpactForce::calc_() {
    ActionEx::calc_();
}

bool TakeHitImpactForce::isChangeable() const {
    return true;
}

void TakeHitImpactForce::m32(sead::Vector3f* dir, ksys::act::Actor* actor,
                             uking::dmg::DamageManager* mgr) {
    sub_71005E2318(dir, actor, mgr);
}

bool TakeHitImpactForce::m33(sead::Vector3f* dir, uking::dmg::DamageManager* mgr) {
    if (!mgr)
        return false;
    return mgr->m30(dir);
}

}  // namespace uking::action
