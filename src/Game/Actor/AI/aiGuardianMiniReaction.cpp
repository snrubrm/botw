#include "Game/Actor/AI/aiGuardianMiniReaction.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007091AC.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

GuardianMiniReaction::GuardianMiniReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

GuardianMiniReaction::~GuardianMiniReaction() = default;

bool GuardianMiniReaction::init_(sead::Heap* heap) {
    _f8[2] = 0;
    _f8[0] = 0;
    _f8[1] = 0;
    return true;
}

void GuardianMiniReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _fc = -1;
    _100.reset();
    EnemyDefaultReaction::enter_(params);
}

void GuardianMiniReaction::leave_() {
    EnemyDefaultReaction::leave_();
    auto* actor = mActor;
    if (actor->getModel() && actor->getASList()) {
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(false);
        actor = mActor;
    }
    if (actor->getASList()) {
        if (actor->getASList()->x_1(0, 0) == "ChanceWaitShader")
            mActor->getASList()->sub_710115B140("WaitBattleShader", 0, 0, 1, 1);
    }
    _100.reset();
}

void GuardianMiniReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mArm1NodeName_s, "Arm1NodeName");
    getStaticParam(&mArm2NodeName_s, "Arm2NodeName");
    getStaticParam(&mArm3NodeName_s, "Arm3NodeName");
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mPreAttackASRight_s, "PreAttackASRight");
    getStaticParam(&mPreAttackASLeft_s, "PreAttackASLeft");
    getStaticParam(&mJustGuardNumForBreak_s, "JustGuardNumForBreak");
    getStaticParam(&mIsChangeWeapon_s, "IsChangeWeapon");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

bool GuardianMiniReaction::m36(int damage_type) {
    if (isCurrentChild("チャンス") || isCurrentChild("ショック") || isCurrentChild("超ショック") ||
        isCurrentChild("左手ショック") || isCurrentChild("左手超ショック") ||
        isCurrentChild("後ろ手ショック") || isCurrentChild("後ろ手超ショック")) {
        changeChild("小ダメージ");
        return true;
    }
    return false;
}

void GuardianMiniReaction::m39(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::m39(params);
}

void sub_7100428358(ksys::act::Actor* actor, bool enabled, s32 slot);

// NON_MATCHING: stack slots of the child name temporaries in the second shock-name test.
void GuardianMiniReaction::calc_() {
    if (getCurrentChild()->isFinishedOrFailed() &&
        (isCurrentChild("弾かれ") || isCurrentChild("左手弾かれ"))) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_4);
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() &&
        (isCurrentChild("超ショック") || isCurrentChild("左手超ショック") ||
         isCurrentChild("後ろ手超ショック") || isCurrentChild("ショック") ||
         isCurrentChild("左手ショック") || isCurrentChild("後ろ手ショック"))) {
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("チャンス")) {
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("武器切替")) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_0);
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("ガード")) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_1);
    } else {
        if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("ふっとび") &&
            *mGuardianMiniChanceTimeState_a == 2) {
            changeToDying();
            *mGuardianMiniChanceTimeState_a = -1;
            return;
        }
        if (*mIsChangeWeapon_s && !sub_71005D8B60(mActor) &&
            getCurrentChild()->isFinishedOrFailed() && isCurrentChild("ふっとび")) {
            auto* actor = mActor;
            if (actor && actor->getModel() && actor->getASList()) {
                actor->getASList()->sub_710115C11C();
                actor->getASList()->sub_710115BED4(true);
            }
            changeChild("武器切替");
            return;
        }
    }

    if (_fc >= 0 && (isCurrentChild("超ショック") || isCurrentChild("左手超ショック") ||
                     isCurrentChild("後ろ手超ショック"))) {
        auto* as_list = mActor->getASList();
        if (as_list && as_list->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_7100428358(mActor, false, _fc);
            if (_100.hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&_100, &accessor);
                sead::Vector3f dir;
                accessor.getActorMtx().getBase(dir, 0);
                getCurrentChild()->setDynamicParam(dir, "DropDir");
            }
        }
    }

    if (isCurrentChild("チャンス"))
        getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");

    EnemyDefaultReaction::calc_();
}

void GuardianMiniReaction::changeToChance() {
    auto* actor = mActor;
    if (actor->getModel() && actor->getASList()) {
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
        actor = mActor;
    }
    actor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("チャンス", &params);
}

void GuardianMiniReaction::changeToDying() {
    auto* actor = mActor;
    if (actor->getModel() && actor->getASList()) {
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
        actor = mActor;
    }
    actor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("瀕死", &params);
}

void GuardianMiniReaction::m40(ksys::act::ai::InlineParamPack* params) {
    if (*mGuardianMiniChanceTimeState_a == 1) {
        sub_71005D7014(mActor);
        changeToChance();
        *mGuardianMiniChanceTimeState_a = -1;
    } else {
        EnemyDefaultReaction::m40(params);
    }
}

void GuardianMiniReaction::m42(ksys::act::ai::InlineParamPack* params) {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);
    EnemyDefaultReaction::m42(params);
}


// NON_MATCHING: same as m35 (unset w4 for sub_71004201A4, child name branch layout).
bool GuardianMiniReaction::m34(act::DamageManagerBase* damage_mgr, int damage_type) {
    if (!damage_mgr)
        return false;
    if (u32(damage_type - 7) < 2) {
        if (!sub_710041F990(ksys::act::isPlayerProfile(damage_mgr->getAttacker()))) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("ショック", &pack);
            mActor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);
            return true;
        }
    } else if (damage_type == 6) {
        s32 a, b, c;
        s32 side;
        auto* actor = mActor;
        if (actor && actor->getASList() && actor->getASList()->x_1(1, 0) == "AttackSpin") {
            a = 0;
            b = 1;
            c = 2;
            auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
            if (!enemy) {
                side = -1;
            } else {
                auto* weapon =
                    sead::DynamicCast<act::Weapon>(enemy->getWeapons()->getEquippedWeapon(0));
                if (weapon && hasAttackInfo(weapon)) {
                    side = 0;
                } else {
                    weapon = sead::DynamicCast<act::Weapon>(enemy->getWeapons()->getEquippedWeapon(1));
                    if (weapon && hasAttackInfo(weapon)) {
                        side = 1;
                    } else {
                        weapon =
                            sead::DynamicCast<act::Weapon>(enemy->getWeapons()->getEquippedWeapon(2));
                        if (weapon && hasAttackInfo(weapon))
                            side = 2;
                        else
                            side = -1;
                    }
                }
            }
        } else {
            sub_71007091AC(mActor, &a, &b, &c);
            if (!mActor->getASList()) {
                side = -1;
            } else {
                const sead::SafeString name = mActor->getASList()->x_1(0, 0);
                if (name == mPreAttackASRight_s)
                    side = 0;
                else if (name == mPreAttackASLeft_s)
                    side = 1;
                else
                    side = -1;
            }
        }
        sub_71004201A4("Wait", a, b, c, -1);
        switch (side) {
        case 2:
            changeChild("後ろ手弾かれ");
            break;
        case 1:
            changeChild("左手弾かれ");
            break;
        default:
            changeChild("弾かれ");
            break;
        }
        const sead::SafeString anim = "MissWait";
        auto* target = mActor;
        if (!target)
            return true;
        auto* as_list = target->getASList();
        if (!as_list || !sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(target))
            return true;
        as_list->startAnimationMaybe(-1.0f, -1.0f, anim.cstr(), 0, 0, true);
        return true;
    }
    return EnemyDefaultReaction::m34(damage_mgr, damage_type);
}

// NON_MATCHING: the original leaves w4 (the unused fourth argument of sub_71004201A4) unset; the final child
// name choice is laid out differently.
void GuardianMiniReaction::m35(act::DamageManagerBase* damage_mgr, int damage_type, bool x,
                               ksys::act::ai::InlineParamPack* params) {
    if (u32(damage_type - 7) < 2) {
        const bool from_player = damage_mgr && ksys::act::isPlayerProfile(damage_mgr->getAttacker());
        if (sub_710041F990(from_player))
            return;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("ショック", &pack);
        mActor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);
        return;
    }

    const char* child;
    switch (damage_type) {
    case 6: {
        s32 a, b, c;
        s32 side;
        auto* actor = mActor;
        if (actor && actor->getASList() && actor->getASList()->x_1(1, 0) == "AttackSpin") {
            a = 0;
            b = 1;
            c = 2;
            auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
            if (!enemy) {
                side = -1;
            } else {
                auto* weapon =
                    sead::DynamicCast<act::Weapon>(enemy->getWeapons()->getEquippedWeapon(0));
                if (weapon && hasAttackInfo(weapon)) {
                    side = 0;
                } else {
                    weapon = sead::DynamicCast<act::Weapon>(enemy->getWeapons()->getEquippedWeapon(1));
                    if (weapon && hasAttackInfo(weapon)) {
                        side = 1;
                    } else {
                        weapon =
                            sead::DynamicCast<act::Weapon>(enemy->getWeapons()->getEquippedWeapon(2));
                        if (weapon && hasAttackInfo(weapon))
                            side = 2;
                        else
                            side = -1;
                    }
                }
            }
        } else {
            sub_71007091AC(mActor, &a, &b, &c);
            if (!mActor->getASList()) {
                side = -1;
            } else {
                const sead::SafeString name = mActor->getASList()->x_1(0, 0);
                if (name == mPreAttackASRight_s)
                    side = 0;
                else if (name == mPreAttackASLeft_s)
                    side = 1;
                else
                    side = -1;
            }
        }
        sub_71004201A4("Wait", a, b, c, -1);
        switch (side) {
        case 2:
            changeChild("後ろ手弾かれ");
            break;
        case 1:
            changeChild("左手弾かれ");
            break;
        default:
            changeChild("弾かれ");
            break;
        }
        const sead::SafeString anim = "MissWait";
        auto* target = mActor;
        if (!target)
            return;
        auto* as_list = target->getASList();
        if (!as_list || !sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(target))
            return;
        as_list->startAnimationMaybe(-1.0f, -1.0f, anim.cstr(), 0, 0, true);
        return;
    }
    case 9:
    case 11:
    case 14: {
        s32 a, b, c;
        sub_71007091AC(mActor, &a, &b, &c);
        sub_71004201A4("Wait", a, b, c, -1);
        child = "ガードブレイク";
        break;
    }
    case 12: {
        s32 a, b, c;
        sub_71007091AC(mActor, &a, &b, &c);
        sub_71004201A4("Wait", a, b, c, -1);
        child = "ガード";
        break;
    }
    default:
        EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
        return;
    }
    changeChild(child);
}


// NON_MATCHING: stack slots of the names (as in GuardianMiniViewWait::sub_7100429D14). Same bone binding as GuardianMiniViewWait::sub_7100429D14, then plays
// `name` on the AS slots 1 to 3 except the one of the side `e` (0: right, 1: left).
void GuardianMiniReaction::sub_71004201A4(const sead::SafeString& name, s32 a, s32 b, s32 unused,
                                          s32 e) {
    auto* actor = mActor;
    if (!actor || !actor->getModel())
        return;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;

    sead::SafeString root = mRootNodeName_s;
    sead::SafeString arms[3];
    if (a == 2 && b == 0) {
        arms[2] = mArm3NodeName_s;
        arms[1] = mArm1NodeName_s;
        arms[0] = mArm2NodeName_s;
    } else if (a == 1 && b == 2) {
        arms[2] = mArm2NodeName_s;
        arms[1] = mArm3NodeName_s;
        arms[0] = mArm1NodeName_s;
    } else {
        arms[2] = mArm1NodeName_s;
        arms[1] = mArm2NodeName_s;
        arms[0] = mArm3NodeName_s;
    }

    const auto root_key = actor->getModel()->searchBone(root);
    const auto right_key = actor->getModel()->searchBone(arms[2]);
    const auto left_key = actor->getModel()->searchBone(arms[1]);
    const auto back_key = actor->getModel()->searchBone(arms[0]);
    if (!root_key.isValid() || !right_key.isValid() || !left_key.isValid() || !back_key.isValid())
        return;

    as_list->sub_710115C9E0(0);
    as_list->mSlots[0].sub_7101165008(root_key, 0, true);
    as_list->mSlots[0].sub_7101165008(right_key, 3, true);
    as_list->mSlots[0].sub_7101165008(left_key, 3, true);
    as_list->mSlots[0].sub_7101165008(back_key, 3, true);
    as_list->mSlots[0].sub_7101164E38(false);

    const s32 right_slot = *mASSlotRight_s;
    as_list->sub_710115C9E0(right_slot);
    as_list->mSlots[right_slot].sub_7101165008(root_key, 3, true);
    as_list->mSlots[right_slot].sub_7101165008(right_key, 0, true);
    as_list->mSlots[right_slot].sub_7101164E38(false);

    const s32 left_slot = *mASSlotLeft_s;
    as_list->sub_710115C9E0(left_slot);
    as_list->mSlots[left_slot].sub_7101165008(root_key, 3, true);
    as_list->mSlots[left_slot].sub_7101165008(left_key, 0, true);
    as_list->mSlots[left_slot].sub_7101164E38(false);

    const s32 back_slot = *mASSlotBack_s;
    as_list->sub_710115C9E0(back_slot);
    as_list->mSlots[back_slot].sub_7101165008(root_key, 3, true);
    as_list->mSlots[back_slot].sub_7101165008(back_key, 0, true);
    as_list->mSlots[back_slot].sub_7101164E38(false);

    s32 skip = 0;
    if (e == 1)
        skip = *mASSlotLeft_s;
    else if (e == 0)
        skip = *mASSlotRight_s;

    for (s32 slot = 1; slot != 4; ++slot) {
        if (slot == skip)
            continue;
        const sead::SafeString anim = name.cstr();
        auto* target = mActor;
        if (!target)
            continue;
        auto* list = target->getASList();
        if (!list || !sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(target))
            continue;
        list->startAnimationMaybe(-1.0f, -1.0f, anim, slot, 0, true);
    }
}


// NON_MATCHING: block layout of the inlined pre-attack name compares (the original places them after the
// first child change).
bool GuardianMiniReaction::sub_710041F990(bool from_player) {
    if (!from_player) {
        changeToChance();
        return true;
    }
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    s32 idx;
    ksys::act::WeaponBase* weapon = enemy->getWeapons()->getEquippedWeapon(0);
    if (sead::IsDerivedFrom<act::Weapon>(weapon) && hasAttackInfo(weapon)) {
        idx = 0;
    } else {
        weapon = enemy->getWeapons()->getEquippedWeapon(1);
        if (sead::IsDerivedFrom<act::Weapon>(weapon) && hasAttackInfo(weapon)) {
            idx = 1;
        } else {
            weapon = enemy->getWeapons()->getEquippedWeapon(2);
            if (!sead::IsDerivedFrom<act::Weapon>(weapon) || !hasAttackInfo(weapon))
                return false;
            idx = 2;
        }
    }

    if (_f8[idx] < *mJustGuardNumForBreak_s) {
        s32 side = idx;
        auto* actor = mActor;
        if (!actor->getASList() || !(actor->getASList()->x_1(1, 0) == "AttackSpin")) {
            if (!mActor->getASList()) {
                side = -1;
            } else {
                const sead::SafeString name = mActor->getASList()->x_1(0, 0);
                if (name == mPreAttackASRight_s)
                    side = 0;
                else if (name == mPreAttackASLeft_s)
                    side = 1;
                else
                    side = -1;
            }
        }
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        const char* child;
        if (side == 1)
            child = "左手ショック";
        else if (side == 2)
            child = "後ろ手ショック";
        else
            child = "ショック";
        changeChild(child, &pack);
        mActor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);
        return true;
    }

    {
        _fc = idx;
        s32 side = idx;
        auto* actor = mActor;
        if (!actor->getASList() || !(actor->getASList()->x_1(1, 0) == "AttackSpin")) {
            if (!mActor->getASList()) {
                side = -1;
            } else {
                const sead::SafeString name = mActor->getASList()->x_1(0, 0);
                if (name == mPreAttackASRight_s)
                    side = 0;
                else if (name == mPreAttackASLeft_s)
                    side = 1;
                else
                    side = -1;
            }
        }
        ksys::act::ai::InlineParamPack pack;
        pack.acquireActor(weapon, "DropWeapon", -1);
        pack.addVec3({0.0f, 0.0f, 0.0f}, "DropDir", -1);
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        const char* child;
        if (side == 1)
            child = "左手超ショック";
        else if (side == 2)
            child = "後ろ手超ショック";
        else
            child = "超ショック";
        changeChild(child, &pack);
        mActor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);
        return true;
    }
}

}  // namespace uking::ai
