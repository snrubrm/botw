#include "Game/Actor/AI/aiForestGiantReaction.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::ai {

ForestGiantReaction::ForestGiantReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
ForestGiantReaction::~ForestGiantReaction() {
    ;
}

bool ForestGiantReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

// NON_MATCHING: block layout (the original sets the child name in x1 per case and keeps the default chain in the
// switch), and the original passes a null second argument to changeToJustGuard.
// NON_MATCHING: block layout (the original shares the m40 / m42 tail calls between both switches).
bool ForestGiantReaction::m34(act::DamageManagerBase* damage_mgr, int damage_type) {
    auto* child = getCurrentChild();
    if (isCurrentChild("凍結"))
        return false;
    auto* manager = static_cast<act::DamageManager*>(damage_mgr);
    if (isCurrentChild("弱点ダメージ")) {
        if (!(manager->_8c & 1) || u32(damage_mgr->getField54() - 21) >= 2)
            return false;
        m40(nullptr);
        return true;
    }
    if (isCurrentChild("ふっとび"))
        return false;
    if (isCurrentChild("ジャストガード")) {
        if (!sub_71005D6E28(mActor))
            return false;
        sub_710038782C(nullptr);
        return true;
    }

    const bool paralysed = isCurrentChild("痺れ");
    const s32 type = damage_mgr->getField54();
    if (paralysed) {
        switch (type) {
        case 10:
        case 22:
        case 23:
        case 27:
            m40(nullptr);
            return true;
        case 20:
            changeChild("突風");
            return true;
        case 21:
            if (manager->_8c & 1) {
                m40(nullptr);
                return true;
            }
            break;
        case 29:
        case 30:
        case 31:
            m42(nullptr);
            return true;
        default:
            break;
        }
        if (damage_type < 6 || !(manager->_8c & 1))
            return false;
        changeChild("弱点ダメージ");
        return true;
    }

    const char* name = nullptr;
    switch (type) {
    case 6:
        name = "弾かれ";
        break;
    case 7:
    case 19:
        name = "ショック";
        break;
    case 8:
        name = "超ショック";
        break;
    case 9:
    case 11:
    case 14:
        name = "ガードブレイク";
        break;
    case 12:
        changeToGuard(nullptr);
        return true;
    case 13:
        changeToJustGuard();
        return true;
    case 18:
        if (!isCurrentChild("小ダメージ") && !isCurrentChild("ガード") &&
            !(isCurrentChild("炎上") && child->isChangeable())) {
            return false;
        }
        name = "炎上";
        break;
    case 20:
        name = "突風";
        break;
    case 21:
        if (manager->_8c & 1) {
            m40(nullptr);
            return true;
        }
        if (damage_mgr->isDamageSourceObjectMaybe(
                mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), mTgArmR_s.cstr()))) {
            name = "右腕大ダメージ";
        }
        break;
    case 10:
    case 22:
    case 23:
    case 27:
        m40(nullptr);
        return true;
    case 29:
    case 30:
    case 31:
        m42(nullptr);
        return true;
    default:
        break;
    }

    if (!name) {
        if (damage_type < 6)
            return false;
        ksys::act::PlayerOrEnemy* player_or_enemy;
        if (manager->_8c & 1) {
            name = "弱点ダメージ";
        } else if (!isCurrentChild("炎上") &&
                   (player_or_enemy = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) &&
                   player_or_enemy->m151(2)) {
            name = "炎上";
        } else if (!isCurrentChild("痺れ") &&
                   (player_or_enemy = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) &&
                   player_or_enemy->m151(4)) {
            name = "痺れ";
        } else if (damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(),
                                                                 mTgArmR_s.cstr()))) {
            name = "右腕大ダメージ";
        } else if (damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(),
                                                                 mTgLegR_s.cstr())) ||
                   damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(),
                                                                 mBgLegR_s.cstr()))) {
            name = "右足ダメージ";
        } else if (damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(),
                                                                 mTgLegL_s.cstr())) ||
                   damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(),
                                                                 mBgLegL_s.cstr()))) {
            name = "左足ダメージ";
        } else {
            name = "小ダメージ";
        }
    }
    changeChild(name);
    return true;
}

void ForestGiantReaction::m35(act::DamageManagerBase* damage_mgr, int damage_type, bool x,
                              ksys::act::ai::InlineParamPack* params) {
    if (u32(damage_type - 29) >= 3 && x) {
        changeChild("崩れ落ち", params);
        return;
    }
    auto* manager = static_cast<act::DamageManager*>(damage_mgr);
    if ((manager->_8c & 1) && u32(damage_mgr->getField54() - 21) < 2) {
        m40(params);
        return;
    }

    const char* name = nullptr;
    switch (damage_type) {
    case 6:
        name = "弾かれ";
        break;
    case 7:
    case 19:
        name = "ショック";
        break;
    case 8:
        name = "超ショック";
        break;
    case 9:
    case 11:
    case 14:
        name = "ガードブレイク";
        break;
    case 12:
        changeToGuard(nullptr);
        return;
    case 13:
        changeToJustGuard();
        return;
    case 20:
        name = "突風";
        break;
    case 21:
        if (!(manager->_8c & 1)) {
            if (damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(),
                                                              mTgArmR_s.cstr()))) {
                name = "右腕大ダメージ";
            }
            break;
        }
        m40(params);
        return;
    case 10:
    case 22:
    case 23:
    case 27:
        m40(params);
        return;
    case 25:
        name = "落下";
        break;
    case 26:
        m43(params);
        return;
    case 29:
    case 30:
    case 31:
        m42(params);
        return;
    default:
        break;
    }

    // Weak point, burning, paralysis, the leg sensors (right first) or a small damage.
    if (!name) {
        auto* player_or_enemy = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
        if (manager->_8c & 1) {
            name = "弱点ダメージ";
        } else if (player_or_enemy && player_or_enemy->m151(2)) {
            name = "炎上";
        } else if ((player_or_enemy = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) &&
                   player_or_enemy->m151(4)) {
            name = "痺れ";
        } else if (damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(),
                                                                 mTgLegR_s.cstr())) ||
                   damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(),
                                                                 mBgLegR_s.cstr()))) {
            name = "右足ダメージ";
        } else if (damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(),
                                                                 mTgLegL_s.cstr())) ||
                   damage_mgr->isDamageSourceObjectMaybe(mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(),
                                                                 mBgLegL_s.cstr()))) {
            name = "左足ダメージ";
        } else {
            name = "小ダメージ";
        }
    }
    changeChild(name, params);
}

void ForestGiantReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void ForestGiantReaction::calc_() {
    EnemyDefaultReaction::calc_();
}

void ForestGiantReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void ForestGiantReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mRightLegArmorSlot_s, "RightLegArmorSlot");
    getStaticParam(&mLeftLegArmorSlot_s, "LeftLegArmorSlot");
    getStaticParam(&mTgLegL_s, "TgLegL");
    getStaticParam(&mBgLegL_s, "BgLegL");
    getStaticParam(&mTgLegR_s, "TgLegR");
    getStaticParam(&mBgLegR_s, "BgLegR");
    getStaticParam(&mTgArmR_s, "TgArmR");
}

}  // namespace uking::ai
