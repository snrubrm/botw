#include "Game/AI/AI/aiAddPlayerLargeAttackJustGuard.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

AddPlayerLargeAttackJustGuard::AddPlayerLargeAttackJustGuard(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

bool AddPlayerLargeAttackJustGuard::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AddPlayerLargeAttackJustGuard::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool AddPlayerLargeAttackJustGuard::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool AddPlayerLargeAttackJustGuard::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddPlayerLargeAttackJustGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("行動");
}

void AddPlayerLargeAttackJustGuard::calc_() {
    auto* link = sub_71005D9050(mActor);
    auto* info = ksys::act::PlayerInfo::instance();
    if (link == nullptr || info == nullptr || !(*link == info->getPlayerLink()))
        return;

    bool x;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        x = player.x_28();
    }
    if (x && getCurrentChild()->isChangeable())
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10000000);
}

void AddPlayerLargeAttackJustGuard::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000000);
}

void AddPlayerLargeAttackJustGuard::loadParams_() {}

}  // namespace uking::ai
