#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"

namespace uking::ai {

EnemyDefaultReaction::EnemyDefaultReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyDefaultReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::act::isAttClientEnabled(mActor, "Grab")) {
        _62 = true;
        ksys::act::disableAttClient(mActor, "Grab");
    } else {
        _62 = false;
    }
    m44();
    sub_710038782C(params);
    _5c = *mSmallDamageCancelTimes_s;
}

void EnemyDefaultReaction::leave_() {
    if (_62)
        ksys::act::enableAttClient(mActor, "Grab");
    _58 = -1;
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
}

void EnemyDefaultReaction::loadParams_() {
    getStaticParam(&mJustGuardTimesMin_s, "JustGuardTimesMin");
    getStaticParam(&mJustGuardTimesMax_s, "JustGuardTimesMax");
    getStaticParam(&mSmallDamageCancelTimes_s, "SmallDamageCancelTimes");
    getStaticParam(&mInComboSmallDamageNoCancel_s, "InComboSmallDamageNoCancel");
}

bool EnemyDefaultReaction::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool EnemyDefaultReaction::m37() {
    return isCurrentChild("死亡");
}

bool EnemyDefaultReaction::m38(dmg::DamageManagerBase* damage_mgr) {
    return damage_mgr->getField50() == 1;
}

void EnemyDefaultReaction::m39(ksys::act::ai::InlineParamPack* params) {
    changeChild("突風", params);
}

void EnemyDefaultReaction::m40(ksys::act::ai::InlineParamPack* params) {
    sub_71005D7014(mActor);
    changeChild("ふっとび", params);
}

void EnemyDefaultReaction::m41(ksys::act::ai::InlineParamPack* params) {
    changeChild("崩れ落ち", params);
}

void EnemyDefaultReaction::m42(ksys::act::ai::InlineParamPack* params) {
    sub_710072BB28(mActor);
    auto* actor = mActor;
    sub_71005D7014(actor);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::Alive);
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
    sub_710073DE08(mActor);
    changeChild("死亡", params);
}

// NON_MATCHING: the death-type range test (types 29-31 -> m42) compiles to `cmp #2; b.hi` instead of
// the original's `cmp #3; b.hs`; everything else is identical.
void EnemyDefaultReaction::m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool flag,
                               ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    bool check_death = true;
    if (auto* player_or_enemy = sead::DynamicCast<ksys::act::PlayerOrEnemy>(actor)) {
        if (player_or_enemy->m151(3)) {
            changeChild("凍結", params);
            return;
        }
        if (player_or_enemy->m151(4)) {
            if (damage_type != 22) {
                changeChild("痺れ", params);
                return;
            }
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
                enemy->m149(4);
            check_death = false;
        }
    }

    if (check_death && u32(damage_type - 29) < 3) {
        m42(params);
        return;
    }
    if (flag) {
        m41(params);
        return;
    }

    {
        switch (damage_type) {
        case 3:
            changeChild("凍結", params);
            return;
        case 4:
            changeChild("痺れ", params);
            return;
        case 6:
            changeChild("弾かれ", params);
            return;
        case 7:
        case 19:
            changeChild("ショック", params);
            return;
        case 8:
            changeChild("超ショック", params);
            return;
        case 9:
        case 11:
        case 14:
            changeChild("ガードブレイク", params);
            return;
        case 10:
        case 21:
        case 22:
        case 23:
        case 27:
            m40(nullptr);
            return;
        case 12:
            if (m38(damage_mgr)) {
                changeChild("ガードブレイク", nullptr);
                return;
            }
            if (auto* attack = sub_7100739578(mActor))
                _61 = attack->sub_71007A1F78(0x20);
            {
                const auto* level = mActor->getParam()->getRes().mGParamList->getEnemyLevel();
                if (level && level->mIsJustGuard.ref()) {
                    if (--_58 <= 0)
                        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10000000);
                }
            }
            changeChild("ガード", nullptr);
            return;
        case 13:
            sub_710038794C();
            return;
        case 18:
            changeChild("炎上", params);
            return;
        case 20:
            m39(params);
            return;
        case 25:
            changeChild("落下", params);
            return;
        case 26:
            m43(params);
            return;
        default:
            changeChild("小ダメージ", params);
            return;
        }
    }
}

bool EnemyDefaultReaction::m45() {
    auto* actor = mActor;
    auto* damage_mgr = actor->getDamageMgr();
    if (damage_mgr) {
        const s32 field54 = damage_mgr->getField54();
        switch (field54) {
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x20:
        case 0x22:
            return true;
        default:
            break;
        }
        if (auto* damage_mgr2 = sead::DynamicCast<dmg::DamageManager>(damage_mgr)) {
            if (damage_mgr2->sub_71006D8534() > 0)
                return false;
        }
        if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
            if (enemy->_e84.isOnBit(0) && !damage_mgr->checkDamageFlags(8)) {
                if (!sub_7100736BD8(field54) && field54 != 0x17)
                    return false;
            }
        }
    }
    auto* life = actor->getLife();
    return life && *life < 1;
}

void EnemyDefaultReaction::m43(ksys::act::ai::InlineParamPack* params) {
    changeChild("大落下", params);
}

void EnemyDefaultReaction::m44() {
    _60 = true;
    _61 = false;
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

void EnemyDefaultReaction::sub_710038794C() {
    const s32 min = *mJustGuardTimesMin_s;
    const s32 max = *mJustGuardTimesMax_s;
    _58 = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000000);
    ksys::act::ai::InlineParamPack params;
    if (sub_71005D8F28(mActor))
        params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    else
        params.addVec3(sead::Vector3f::zero, "TargetPos", -1);
    changeChild("ジャストガード", &params);
}

void EnemyDefaultReaction::sub_710038782C(ksys::act::ai::InlineParamPack* params) {
    if (_58 <= 0) {
        const s32 min = *mJustGuardTimesMin_s;
        const s32 max = *mJustGuardTimesMax_s;
        _58 = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
    }

    auto* damage_mgr = sub_710072BA90(mActor);
    s32 damage_type = -1;
    bool flag = false;
    if (damage_mgr) {
        damage_type = damage_mgr->getField54();
        flag = damage_mgr->checkDamageFlags(10);
    }
    mActor->getLife();

    if (m45()) {
        m42(params);
        return;
    }
    m35(damage_mgr, damage_type, flag, params);
}

}  // namespace uking::ai
