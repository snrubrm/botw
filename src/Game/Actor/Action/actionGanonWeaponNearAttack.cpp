#include "Game/Actor/Action/actionGanonWeaponNearAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actWeapon.h"
#include <cmath>
#include <prim/seadStringUtil.h>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

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

// NON_MATCHING: float register allocation in the cancel-angle test.
void GanonWeaponNearAttack::calc_() {
    sub_71005DAB2C(mActor, *mJustAvoidSideDist_s + 7.0f, *mJustAvoidBackDist_s + 7.0f,
                   *mJustAvoidAngle_s, 0);
    sub_71005D7444(mActor, *mTargetPos_d, true, true);
    sub_71005DB51C(mActor, *mBattleNodeOffsetLR_s, false);
    sub_71005DB558(mActor, *mBattleNodeOffsetUD_s, false);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(controller->get70());
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0) || sub_71005DD780(mActor, 0x51, &query, 0, 0)) {
        sub_710017E400(&query);
        _a0 = false;
        _a1 = false;
    } else if (sub_71005DD74C(mActor, &query, 0, 0)) {
        sub_710017E550(&query);
        if (!_a1)
            _a2 = true;
    }

    if (!_a3 && sub_71005DD798(mActor, 0x12, nullptr, 0, 0))
        _a3 = true;
    if (_a3 && sub_71005DD734(mActor, 0x12, nullptr, 0, 0)) {
        sub_71005D74E8(mActor);
        sub_71005DB51C(mActor, 0.0f, false);
        sub_71005DB558(mActor, 0.0f, false);
    }

    if (!_a1) {
        _a1 = hasAttackInfo(mActor);
        if (_a0) {
            const auto& mtx = mActor->getMtx();
            const sead::Vector3f& target = *mTargetPos_d;
            const f32 dx = mtx(0, 3) - target.x;
            const f32 dz = mtx(2, 3) - target.z;
            if (dx * dx + dz * dz >= *mAttackCancelDist_s * *mAttackCancelDist_s) {
                _a2 = true;
            } else {
                const sead::Vector3f diff = target - mtx.getTranslation();
                sead::Vector3f dir;
                mtx.getBase(dir, 2);
                _a2 = std::cos(*mAttackCancelAng_s) > diff.dot(dir);
            }
        }
    }

    if ((sub_710072B6C8() || _a2) && sub_71005DD798(mActor, 2, nullptr, 0, 0))
        setFinished();
    if (isFinishedAS(0, 0))
        setFinished();
}

// NON_MATCHING: the original duplicates the flag computation into both index branches.
void GanonWeaponNearAttack::sub_710017E400(ksys::as::ASList::Unk4* query) {
    sead::FixedSafeString<64> idx_str;
    sub_71005DD7E4(&idx_str, query->name);
    s32 idx;
    if (idx_str.isEmpty()) {
        idx = *mWeaponIdx_s;
    } else {
        idx = 0;
        sead::StringUtil::tryParseS32(&idx, idx_str, sead::StringUtil::CardinalNumber::BaseAuto);
    }
    u32 flags = 1 << *mAtAttr_s;
    if (*mIsGuardPierce_s)
        flags |= 8;
    else if (*mIsGuardBreak_s)
        flags |= 0x100;
    sub_71005D7ADC(mActor, idx, flags, &query->name, nullptr, *mAtkMinPower_s, 1, 0, 1,
                   static_cast<f32>(*mAttackPower_s), 1.0f);
}

// NON_MATCHING: the original builds the request separately in both index branches.
void GanonWeaponNearAttack::sub_710017E550(ksys::as::ASList::Unk4* query) {
    sead::FixedSafeString<64> idx_str;
    sub_71005DD7E4(&idx_str, query->name);
    s32 idx;
    if (idx_str.isEmpty()) {
        idx = *mWeaponIdx_s;
    } else {
        idx = 0;
        sead::StringUtil::tryParseS32(&idx, idx_str, sead::StringUtil::CardinalNumber::BaseAuto);
    }
    sub_71005D79AC(mActor, idx, act::Unk_71002edaec(1));
}

bool GanonWeaponNearAttack::isFinished() const {
    if (isFinishedAS(0, 0))
        return true;
    return ksys::act::ai::Action::isFinished();
}

}  // namespace uking::action
