#include "Game/AI/Action/actionForkNoWeaponAttackParamWeapon.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkNoWeaponAttackParamWeapon::ForkNoWeaponAttackParamWeapon(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkNoWeaponAttackParamWeapon::~ForkNoWeaponAttackParamWeapon() = default;

bool ForkNoWeaponAttackParamWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNoWeaponAttackParamWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkNoWeaponAttackParamWeapon::leave_() {
    sub_71007A2D34(
        mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkBodyName_s.cstr()));
}

void ForkNoWeaponAttackParamWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mAtkBodyName_s, "AtkBodyName");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
}

void ForkNoWeaponAttackParamWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
