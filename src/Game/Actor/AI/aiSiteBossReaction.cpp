#include "Game/Actor/AI/aiSiteBossReaction.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

void sub_71002D36C8(uking::act::Enemy* boss, const sead::SafeString& part);

namespace uking::ai {

SiteBossReaction::SiteBossReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SiteBossReaction::~SiteBossReaction() {
    ;
}

bool SiteBossReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void SiteBossReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

// 0x710057fb10 (starts the flame-reaction state when the boss wears / draws its flame)
void SiteBossReaction::sub_710057FB10() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (act::SiteBoss::sub_71002D3804(boss, "WearFlame") ||
            act::SiteBoss::sub_71002D3804(boss, "DrawingFlame")) {
            _73 = true;
            sub_71002D36C8(boss, "WearFlame");
            act::SiteBoss::sub_71002D3498(boss, mActor);
            if (boss->_1558.isOnBit(0))
                boss->x_1(true, false, false);
            boss->_1558.setBit(19);
        }
    }
}

// NON_MATCHING: the kind test (2 / 6 / 10) is lowered by the original as a rebased bit test
// (sub 2; cmp 8; lsr 0x111), ours as lsl / and 0x444; same size and instructions otherwise
// 0x7100581050: starts the flame reaction (the flame flag, the half-life flag, the cloth, the boss state).
void SiteBossReaction::sub_7100581050() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss) {
        boss->_14c8._30.set(0x200);
        switch (boss->_1534) {
        case 2:
        case 6:
        case 10:
            if (boss->_1558.isOnBit(9) && checkHpRate(boss, 0.5f))
                boss->_1558.setBit(19);
            break;
        }
    }

    if (auto* physics = mActor->getPhysics()) {
        if (auto* cloth = physics->getClothSet()) {
            auto& entry = cloth->_18[0];
            if (!(entry._18 & 0x400))
                entry._3c = 0.0f;
            _70 = true;
        }
    }

    if (boss)
        boss->sub_71002CFD04(true);
}

// NON_MATCHING: the kind tests are lowered by the original as rebased bit tests and its last addBool
// combines the two flag tests with and / cset (ours branches on the first); same code otherwise
// 0x710057fc40: the flame reaction entry (called by enter_, calc_ and m40).
void SiteBossReaction::sub_710057FC40() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || (!act::SiteBoss::sub_71002D3804(boss, "WearFlame") &&
                  !act::SiteBoss::sub_71002D3804(boss, "DrawingFlame"))) {
        changeChild("特効ダメージ");
        return;
    }

    sub_710057FB10();
    const u16 flame_flags = boss->_14c8._30;
    sub_7100581050();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(getPlayerPosition(), "TargetPos", -1);

    s32 rail_index = 0;
    switch (boss->_1534) {
    case 0:
    case 4:
    case 8:
        rail_index = 2;
        break;
    }
    params.addInt(rail_index, "RailIndex", -1);
    params.addBool(false, "IsReturnHome", -1);
    params.addBool(false, "IsForceWarp", -1);
    params.addBool(true, "IsPartsActorTgOn", -1);

    bool parts_warp_effect_sync = false;
    switch (boss->_1534) {
    case 0:
    case 4:
    case 8:
        parts_warp_effect_sync = !boss->_1558.isOnBit(9);
        break;
    }
    params.addBool(parts_warp_effect_sync, "IsPartsWarpEffectSync", -1);

    params.addBool(!(flame_flags & 0x200) && boss->_1558.isOnBit(26), "IsPlayDamageAnm", -1);

    EnemyDefaultReaction::m40(&params);
}

// NON_MATCHING: the original addresses SiteBoss _2378-_237b through one base register (see
// SiteBossSpearThrow); everything else matches
void SiteBossReaction::leave_() {
    EnemyDefaultReaction::leave_();

    if (_70) {
        if (auto* physics = mActor->getPhysics()) {
            if (auto* cloth = physics->getClothSet()) {
                auto& entry = cloth->_18[0];
                if (!(entry._18 & 0x400))
                    entry._3c = 1.0f;
            }
        }
    }

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (actor->_868 && actor->_868->sub_71006EDDD4())
            actor->sub_71006DD92C(true);
    }

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_2378) {
            boss->_237a = boss->_237b;
            boss->_2378 = 0;
        }
        if (boss->_14c8._30.isOnBit(9)) {
            boss->_14c8._30.resetBit(9);
            changeAS("Wait_Battle", false, 2, 0);
            boss->_1518 = 0;
        }
        if (boss->_14c8._30.isOnBit(1))
            boss->_14c8._30.resetBit(1);
    }
}

void SiteBossReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsChangeEffectiveDamage_s, "IsChangeEffectiveDamage");
}

bool SiteBossReaction::m36(int damage_type) {
    if (_74++ >= 3) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
            boss->_1558.set(4);
    }
    return false;
}

}  // namespace uking::ai
