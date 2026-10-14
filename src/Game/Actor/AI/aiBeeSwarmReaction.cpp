#include "Game/Actor/AI/aiBeeSwarmReaction.h"
#include "Game/Actor/actSwarm.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/Actor/aiUnk_710072A944.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

BeeSwarmReaction::BeeSwarmReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BeeSwarmReaction::~BeeSwarmReaction() = default;

bool BeeSwarmReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BeeSwarmReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm) {
        setFailed();
        return;
    }
    swarm->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    _38 = true;
    *mActor->getLife() = mActor->getMaxLife();
    sub_710032AF18();
}

// NON_MATCHING: register allocation around the final calls (the original keeps a bool in w8 and moves x20 earlier).
void BeeSwarmReaction::calc_() {
    if (isFinished() || isFailed())
        return;

    if (_38) {
        _38 = false;
    } else {
        bool damaged;
        auto* chemical = mActor->getChemicalStuff();
        if (chemical && (chemical->_b8 & 0x284)) {
            damaged = true;
        } else {
            auto* damage_mgr = sub_710072BA90(mActor);
            damaged = damage_mgr && damage_mgr->getField54() != -1 &&
                      s32(damage_mgr->getDamage()) >= 1 &&
                      sub_710072AA48(mActor, damage_mgr->getField50());
        }
        if (damaged) {
            *mActor->getLife() = mActor->getMaxLife();
            sub_710032AF18();
        }
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("死亡")) {
        mActor->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0,
                         nullptr);
        return;
    }

    const bool vanished = isCurrentChild("消滅");
    auto* swarm = static_cast<act::Swarm*>(mActor);
    if (vanished || swarm->_1610 == 0) {
        swarm->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }

    const s32 alive = swarm->_14c8.size() - swarm->_1610;
    if (alive < swarm->getMaxLife()) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_0);
        setFinished();
        return;
    }
    sub_710072AAE4(swarm);
    sub_710072BB28(swarm);
    changeChild("死亡");
}

// NON_MATCHING: the 30 / 31 damage type test is `(type | 1) == 31` in the original (ours: `(type & ~1) == 30`).
void BeeSwarmReaction::sub_710032AF18() {
    if (sub_710032B414()) {
        sub_710072AAE4(mActor);
        sub_710072BB28(mActor);
        changeChild("ケミカル接触");
        return;
    }

    auto* swarm = static_cast<act::Swarm*>(mActor);
    auto* damage_mgr = sub_710072BA90(swarm);
    if (damage_mgr) {
        const s32 num = sub_710072AA48(swarm, damage_mgr->getField50());
        sead::Vector3f pos;
        if (!damage_mgr->getPosition(&pos))
            swarm->getMtx().getTranslation(pos);
        for (s32 i = 0; i < num; ++i) {
            // The unit nearest to the damage position.
            act::Swarm::Unit* nearest = nullptr;
            f32 min_distance = sead::Mathf::infinity();
            for (s32 j = 0, count = swarm->_14c8.size(); j < count; ++j) {
                auto* unit = swarm->_14c8[j];
                if (!unit || (unit->_b8 & 1))
                    continue;
                const f32 distance = (pos - unit->_8.getTranslation()).squaredLength();
                if (distance < min_distance) {
                    min_distance = distance;
                    nearest = unit;
                }
            }
            if (!nearest)
                break;
            nearest->m10();
        }
    }

    if (swarm->_1610 == 0) {
        swarm->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }

    if (swarm->_14c8.size() - swarm->_1610 < swarm->getMaxLife()) {
        if (!damage_mgr) {
            changeChild("通常ダメージ");
            return;
        }
        const s32 type = damage_mgr->getField54();
        if (type == 34) {
            changeChild("消滅");
            return;
        }
        if (type != 30 && type != 31) {
            if (type == 20) {
                sub_710072AAE4(mActor);
                sub_710072BB28(mActor);
                changeChild("突風");
                return;
            }
            if (damage_mgr->getField50() == 4)
                changeChild("範囲ダメージ");
            else
                changeChild("通常ダメージ");
            return;
        }
    }
    sub_710072AAE4(mActor);
    sub_710072BB28(mActor);
    changeChild("死亡");
}

bool BeeSwarmReaction::sub_710032B414() {
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        if (actor->m151(3))
            return true;
        if (actor->m151(4))
            return true;
        if (actor->m151(2))
            return true;
    }
    auto* damage_mgr = mActor->getDamageMgr();
    if (!damage_mgr)
        return false;
    const s32 type = damage_mgr->getField54();
    const s32 other = damage_mgr->getField50();
    if (type == 3 || type == 4 || type == 18)
        return true;
    return u32(other - 9) < 3;
}

void BeeSwarmReaction::leave_() {
    *mActor->getLife() = mActor->getMaxLife();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

void BeeSwarmReaction::loadParams_() {}

}  // namespace uking::ai
