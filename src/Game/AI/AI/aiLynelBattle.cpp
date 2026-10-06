#include "Game/AI/AI/aiLynelBattle.h"
#include <math/seadMathCalcCommon.h>
#include <limits>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelBattle::LynelBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
LynelBattle::~LynelBattle() {
    ;
}

bool LynelBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseBattleRepeatMax_s, "CloseBattleRepeatMax");
    getStaticParam(&mThroughAttackRepeatNum_s, "ThroughAttackRepeatNum");
    getStaticParam(&mCloseBattleStartDist_s, "CloseBattleStartDist");
    getStaticParam(&mCloseBattleStartAngle_s, "CloseBattleStartAngle");
    getStaticParam(&mHornAttackRate_s, "HornAttackRate");
    getStaticParam(&mRoarRate_s, "RoarRate");
    getStaticParam(&mBreathStartLifeRate_s, "BreathStartLifeRate");
    getStaticParam(&mRoarStartLifeRate_s, "RoarStartLifeRate");
    getStaticParam(&mBattleEndDist_s, "BattleEndDist");
    getStaticParam(&mSkipBreathRoarRate_s, "SkipBreathRoarRate");
    getStaticParam(&mRoarFlamePartsKey_s, "RoarFlamePartsKey");
    getStaticParam(&mBreathPartsKey0_s, "BreathPartsKey0");
    getStaticParam(&mBreathPartsKey1_s, "BreathPartsKey1");
    getStaticParam(&mBreathPartsKey2_s, "BreathPartsKey2");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

// NON_MATCHING: stack layout (the original keeps the NaN start vector and the accessor in separate slots, frame 0x90
// instead of 0x80), the vtable reload placement after the child's isFinished / isFailed calls, and the operand order of
// the XZ direction subtraction.
void LynelBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        bool is_through_failed = false;
        if (child->isFailed() && isCurrentChild("斬り抜け")) {
            _dc = *mThroughAttackRepeatNum_s;
            is_through_failed = true;
        }
        auto* actor = mActor;
        if (sub_710072E40C(actor, sub_71005D9330(actor), 3.0f)) {
            sead::Vector3f from;
            actor = mActor;
            const sead::Vector3f& target = sub_71005D9330(actor);
            const sead::Matrix34f& mtx = actor->getMtx();
            if (sead::Vector2f(mtx(0, 3) - target.x, mtx(2, 3) - target.z).length() > *mBattleEndDist_s) {
                setFailed();
                return;
            }
            if (sub_710048D794())
                return;
            if (!sub_710072E368(mActor)) {
                setFailed();
                return;
            }
            const sead::Vector3f position = mActor->getMtx().getTranslation();
            const sead::Vector3f& target_pos = sub_71005D9330(mActor);
            const f32 dist = sead::Vector2f(position.x - target_pos.x, position.z - target_pos.z).length();
            if (dist <= *mCloseBattleStartDist_s + sub_71007320F0(mActor, *mWeaponIdx_s)) {
                const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
                const sead::Vector3f& target_now = sub_71005D9330(mActor);
                sead::Vector3f to_target(target_now.x - actor_pos.x, 0.0f, target_now.z - actor_pos.z);
                to_target.normalize();
                sead::Vector3f forward;
                mActor->getMtx().getBase(forward, 2);
                forward.y = 0;
                forward.normalize();
                if (to_target.dot(forward) >= sead::Mathf::cos(*mCloseBattleStartAngle_s)) {
                    bool player_sees = false;
                    if (auto* player_link = sub_71005D9050(mActor)) {
                        ksys::act::acc::PlayerBase player;
                        ksys::act::acquireActor(player_link, &player);
                        player_sees = player.x_13();
                    }
                    if (!player_sees && (*mCloseBattleRepeatMax_s < 1 || _d8 < *mCloseBattleRepeatMax_s)) {
                        if (!isCurrentChild("近接戦闘") || !child->isFailed()) {
                            from = {std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                                    std::numeric_limits<f32>::quiet_NaN()};
                            if (sub_710072F854(mActor, from, sub_71005D9330(mActor), nullptr,
                                               sub_71007320F0(mActor, *mWeaponIdx_s), -1)) {
                                changeToMeleeBattle();
                                return;
                            }
                        }
                    }
                }
            }
            _d8 = 0;
            if (is_through_failed && !sub_710072E154(mActor, sub_71005D9330(mActor), nullptr, -1)) {
                setFailed();
                return;
            }
            m34(is_through_failed);
        } else {
            auto* target_link = sub_71005D9050(mActor);
            if (!target_link || !ksys::act::isPlayerProfile(target_link) || !sub_71005D83E8(mActor, 2)) {
                setFailed();
                return;
            }
            bool is_m194;
            {
                ksys::act::acc::PlayerBase player;
                ksys::act::acquireActor(target_link, &player);
                is_m194 = player.m194();
            }
            if (!is_m194) {
                setFailed();
                return;
            }
            changeChild("d_RotRight", nullptr);
        }
    } else {
        if (child->isChangeable() && !isCurrentChild("近接戦闘") &&
            !sub_710072E304(sub_71005D9330(mActor), 3.0f)) {
            auto* target_link = sub_71005D9050(mActor);
            if (!target_link || !ksys::act::isPlayerProfile(target_link) || !sub_71005D83E8(mActor, 2)) {
                setFailed();
                return;
            }
            bool is_m194;
            {
                ksys::act::acc::PlayerBase player;
                ksys::act::acquireActor(target_link, &player);
                is_m194 = player.m194();
            }
            if (!is_m194) {
                setFailed();
                return;
            }
            changeChild("d_RotRight", nullptr);
            return;
        }
        getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
        getCurrentChild()->setDynamicParam(sub_71005D9548(mActor), "TargetVel");
    }
}

void LynelBattle::changeToThroughAttack() {
    ++_dc;
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x40;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
    pack.addBool(false, "IsSkipPrepare", -1);
    changeChild("斬り抜け", &pack);
}

void LynelBattle::changeToChargeAttack(bool skip_prepare) {
    _dc = 0;
    _e0 = sead::Mathi::clamp(_e0 - 1, -5, 5);
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x80;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
    pack.addBool(skip_prepare, "IsSkipPrepare", -1);
    changeChild("突進切り", &pack);
}

void LynelBattle::changeToSixLegAttack(bool skip_prepare) {
    _dc = 0;
    _e0 = sead::Mathi::clamp(_e0 + 1, -5, 5);
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x100;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
    pack.addBool(skip_prepare, "IsSkipPrepare", -1);
    changeChild("6足攻撃", &pack);
}

void LynelBattle::changeToBreath() {
    _e4 = sead::Mathi::clamp(_e4 - 1, -5, 5);
    _dc = 0;
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x200;
    *mLynelAIFlags_a |= 4;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("ブレス", &pack);
}

void LynelBattle::changeToRoarAttack() {
    _e4 = sead::Mathi::clamp(_e4 + 1, -5, 5);
    _dc = 0;
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x400;
    *mLynelAIFlags_a |= 8;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("咆哮攻撃", &pack);
}

void LynelBattle::changeToMeleeBattle() {
    ++_d8;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("近接戦闘", &pack);
}

void LynelBattle::changeToChargeOrSixLegAttack(bool skip_prepare) {
    const f32 random = sead::GlobalRandom::instance()->getF32Range(0.0f, 1.0f);
    f32 rate = *mHornAttackRate_s;
    if (!(rate <= 0.0f || rate >= 1.0f))
        rate = sead::Mathf::clamp(rate + f32(_e0) * -0.1f, 0.0f, 1.0f);
    if (random < rate)
        changeToSixLegAttack(skip_prepare);
    else
        changeToChargeAttack(skip_prepare);
}

void LynelBattle::m34(bool skip_prepare) {
    if (*mLynelAIFlags_a & 0x40) {
        if (_dc >= *mThroughAttackRepeatNum_s) {
            changeToChargeOrSixLegAttack(skip_prepare);
            return;
        }
    } else if (*mLynelAIFlags_a & 0x180) {
        if (sub_710048E778())
            return;
    }
    changeToThroughAttack();
}

bool LynelBattle::sub_710048D794() {
    if (!(*mLynelAIFlags_a & 4)) {
        const s32* life = mActor->getLife();
        const f32 current = life ? f32(*life) : 1.0f;
        if (current <= f32(mActor->getMaxLife()) * *mBreathStartLifeRate_s && sub_710048E8BC()) {
            changeToBreath();
            return true;
        }
    }
    if (!(*mLynelAIFlags_a & 8)) {
        const s32* life = mActor->getLife();
        const f32 current = life ? f32(*life) : 1.0f;
        if (current <= f32(mActor->getMaxLife()) * *mRoarStartLifeRate_s && sub_710048E9EC()) {
            changeToRoarAttack();
            return true;
        }
    }
    return false;
}

bool LynelBattle::sub_710048DEEC() {
    auto* target = sub_71005D9050(mActor);
    if (!target)
        return false;
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(target, &player);
    return player.x_13();
}

bool LynelBattle::sub_710048E778() {
    if (sead::GlobalRandom::instance()->getF32Range(0.0f, 1.0f) < *mSkipBreathRoarRate_s)
        return false;
    const bool can_breath = sub_710048E8BC();
    const bool can_roar = sub_710048E9EC();
    if (can_breath && can_roar) {
        const f32 random = sead::GlobalRandom::instance()->getF32Range(0.0f, 1.0f);
        f32 rate = *mRoarRate_s;
        if (!(rate <= 0.0f || rate >= 1.0f))
            rate = sead::Mathf::clamp(rate + f32(_e4) * -0.1f, 0.0f, 1.0f);
        if (random < rate)
            changeToRoarAttack();
        else
            changeToBreath();
    } else if (can_roar) {
        changeToRoarAttack();
    } else if (can_breath) {
        changeToBreath();
    } else {
        return false;
    }
    return true;
}

bool LynelBattle::sub_710048E8BC() {
    const s32* life = mActor->getLife();
    const f32 current = life ? f32(*life) : 1.0f;
    if (current <= f32(mActor->getMaxLife()) * *mBreathStartLifeRate_s) {
        if (auto* parts = mActor->m101()) {
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(&parts->getActorPartsActor(mBreathPartsKey0_s), &accessor) &&
                !accessor.isStateSleep()) {
                return false;
            }
            if (ksys::act::acquireActor(&parts->getActorPartsActor(mBreathPartsKey1_s), &accessor) &&
                !accessor.isStateSleep()) {
                return false;
            }
            if (ksys::act::acquireActor(&parts->getActorPartsActor(mBreathPartsKey2_s), &accessor) &&
                !accessor.isStateSleep()) {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool LynelBattle::sub_710048E9EC() {
    const s32* life = mActor->getLife();
    const f32 current = life ? f32(*life) : 1.0f;
    if (current <= f32(mActor->getMaxLife()) * *mRoarStartLifeRate_s) {
        if (auto* parts = mActor->m101()) {
            ksys::act::ActorConstDataAccess accessor;
            return ksys::act::acquireActor(&parts->getActorPartsActor(mRoarFlamePartsKey_s), &accessor) &&
                   accessor.isStateSleep();
        }
    }
    return false;
}

}  // namespace uking::ai
