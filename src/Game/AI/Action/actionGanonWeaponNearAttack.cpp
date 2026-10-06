#include "Game/AI/Action/actionGanonWeaponNearAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

GanonWeaponNearAttack::GanonWeaponNearAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonWeaponNearAttack::~GanonWeaponNearAttack() = default;

bool GanonWeaponNearAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonWeaponNearAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
    if (auto* boss = sead::DynamicCast<uking::act::LastBoss>(mActor))
        boss->_14e8.set(0x200);
    _a0 = true;
    _a1 = false;
    _a2 = false;
    _a3 = false;
}

void GanonWeaponNearAttack::leave_() {
    for (int i = 0; i < 4; ++i)
        sub_71005D79AC(mActor, i, act::Unk_71002edaec(1));
    sub_71005DB434(mActor);
    sub_71005D74E8(mActor);
    sub_71005DB51C(mActor, 0.0f, false);
    sub_71005DB558(mActor, 0.0f, false);
    if (auto* boss = sead::DynamicCast<uking::act::LastBoss>(mActor))
        boss->_14e8.reset(0x200);
}

void GanonWeaponNearAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtkMinPower_s, "AtkMinPower");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mAttackCancelDist_s, "AttackCancelDist");
    getStaticParam(&mAttackCancelAng_s, "AttackCancelAng");
    getStaticParam(&mBattleNodeOffsetLR_s, "BattleNodeOffsetLR");
    getStaticParam(&mBattleNodeOffsetUD_s, "BattleNodeOffsetUD");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsGuardBreak_s, "IsGuardBreak");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonWeaponNearAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GanonWeaponNearAttack::isFinished() const {
    if (isFinishedAS(0, 0))
        return true;
    return ksys::act::ai::Action::isFinished();
}

}  // namespace uking::action
