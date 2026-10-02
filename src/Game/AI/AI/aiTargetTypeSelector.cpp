#include "Game/AI/AI/aiTargetTypeSelector.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::ai {

TargetTypeSelector::TargetTypeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetTypeSelector::~TargetTypeSelector() = default;

bool TargetTypeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetTypeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsTrgTargetChangeToPlayer_a = false;
    auto* link = sub_71005D9050(mActor);
    if (!link) {
        changeChild("対象それ以外");
        return;
    }

    if (ksys::act::isPlayerProfile(link))
        changeChild("対象プレイヤー");
    else if (ksys::act::isNPCProfile(link))
        changeChild("対象NPC");
    else if (ksys::act::isPreyOrSwarm(link) || ksys::act::hasTag(link, ksys::act::tags::EnemyTarget))
        changeChild("対象獲物");
    else
        changeChild("対象それ以外");

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    _40 = accessor.getId();
}

void TargetTypeSelector::calc_() {
    *mIsTrgTargetChangeToPlayer_a = false;
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        auto* actor = mActor;
        auto* link = sub_71005D9050(actor);
        if (!link || !link->hasProc()) {
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
            setFailed();
            return;
        }
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            const u32 id = accessor.getId();
            if (_40 != id) {
                actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
                actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
                sub_71005D8DE8(actor, *link, nullptr, nullptr);
                _40 = id;
            }
        }
        if (ksys::act::isPlayerProfile(link)) {
            *mIsTrgTargetChangeToPlayer_a = true;
            changeChild("対象プレイヤー");
        } else if (ksys::act::isNPCProfile(link)) {
            changeChild("対象NPC");
        } else if (ksys::act::isPreyOrSwarm(link) ||
                   ksys::act::hasTag(link, ksys::act::tags::EnemyTarget)) {
            changeChild("対象獲物");
        } else {
            changeChild("対象それ以外");
        }
    } else if (child->isChangeable()) {
        auto* actor = mActor;
        auto* link = sub_71005D9050(actor);
        if (!link || !link->hasProc()) {
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
            setFailed();
            return;
        }
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        const u32 id = accessor.getId();
        if (_40 != id) {
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
            sub_71005D8DE8(actor, *link, nullptr, nullptr);
            _40 = id;
            if (ksys::act::isPlayerProfile(link)) {
                *mIsTrgTargetChangeToPlayer_a = true;
                changeChild("対象プレイヤー");
            } else if (ksys::act::isNPCProfile(link)) {
                changeChild("対象NPC");
            } else if (ksys::act::isPreyOrSwarm(link) ||
                       ksys::act::hasTag(link, ksys::act::tags::EnemyTarget)) {
                changeChild("対象獲物");
            } else {
                changeChild("対象それ以外");
            }
        }
    }
}

void TargetTypeSelector::leave_() {
    *mIsTrgTargetChangeToPlayer_a = false;
}

void TargetTypeSelector::loadParams_() {
    getAITreeVariable(&mIsTrgTargetChangeToPlayer_a, "IsTrgTargetChangeToPlayer");
}

bool TargetTypeSelector::isFailed() const {
    if (getCurrentChild())
        return getCurrentChild()->isFailed();
    return true;
}

bool TargetTypeSelector::isFinished() const {
    if (getCurrentChild())
        return getCurrentChild()->isFinished();
    return true;
}

bool TargetTypeSelector::isChangeable() const {
    if (getCurrentChild())
        return getCurrentChild()->isChangeable();
    return true;
}

}  // namespace uking::ai
