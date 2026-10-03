#include "Game/AI/AI/aiSwarmReaction.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actSwarm.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

SwarmReaction::SwarmReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmReaction::~SwarmReaction() = default;

bool SwarmReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm) {
        setFailed();
        return;
    }
    swarm->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    _38 = true;
    *mActor->getLife() = mActor->getMaxLife();
    m35();
}

void SwarmReaction::calc_() {
    if (isFinished() || isFailed())
        return;

    if (_38) {
        _38 = false;
    } else if (m34()) {
        *mActor->getLife() = mActor->getMaxLife();
        m35();
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("死亡") || isCurrentChild("ビタロック")) {
        if (auto* unk = mActor->m135()) {
            unk->_0 = 1;
            unk->_4 = 0;
        }
        mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0,
                         nullptr);
        return;
    }

    auto* swarm = static_cast<act::Swarm*>(mActor);
    if (swarm->_1610 == 0) {
        swarm->deleteAndEmit(1);
        return;
    }

    const s32 alive = swarm->_14c8.size() - swarm->_1610;
    if (alive < mActor->getMaxLife()) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_0);
        setFinished();
    } else {
        m36();
    }
}

void SwarmReaction::leave_() {
    *mActor->getLife() = mActor->getMaxLife();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

bool SwarmReaction::m34() {
    auto* damage_mgr = sub_710072BA90(mActor);
    if (damage_mgr && damage_mgr->getField54() != -1)
        return true;
    return false;
}

// NON_MATCHING: the damage type tests are merged into one switch (0x22 tested before 0x12); the
// original tests 3..4 / 18 with ccmp first
void SwarmReaction::m35() {
    auto* swarm = static_cast<act::Swarm*>(mActor);
    if (swarm->_1610 == 0) {
        swarm->deleteAndEmit(1);
        return;
    }

    if (swarm->_1614) {
        changeChild("ビタロック");
        return;
    }

    auto* damage_mgr = sub_710072BA90(swarm);
    if (!damage_mgr) {
        changeChild("通常ダメージ");
        return;
    }

    const s32 type = damage_mgr->getField54();
    if (type == 3 || type == 4 || type == 18) {
        changeChild("ケミカルダメージ");
    } else if (type == 34) {
        changeChild("消滅");
    } else {
        const s32 kind = damage_mgr->getField50();
        if (kind == 4)
            changeChild("範囲ダメージ");
        else if (kind == 3)
            changeChild("矢ダメージ");
        else
            changeChild("通常ダメージ");
    }
}

void SwarmReaction::m36() {
    changeChild("死亡");
}

void SwarmReaction::loadParams_() {}

}  // namespace uking::ai
