#include "Game/Actor/Action/actionAirWallAction.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::action {

AirWallAction::AirWallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

// NON_MATCHING: stack layout (accessor / iterators) and the found flag kept live across unlock in the original.
// Shows info overlay 46 while the player (or the horse / sand seal they ride) touches the area.
void AirWallAction::calc_() {
    auto* area = sead::DynamicCast<ksys::act::AreaActor>(mActor);
    if (!area)
        return;

    ksys::act::acc::AreaActor accessor(area);
    bool found = false;
    auto* info = accessor.getField848();
    if (info && info->getCollidingBodies().size() != 0) {
        auto* bodies = info->getCollidingBodies().front();
        info->lock();
        for (; bodies; bodies = info->getCollidingBodies().next(bodies)) {
            found = sub_710008A8C8(bodies->bodies[1]);
            if (found)
                break;
        }
        info->unlock();
    }

    if (!found) {
        auto* contacts = accessor.getField850();
        if (contacts->getNumContactPoints() != 0 && contacts->begin().isEnd())
            return;
        for (const auto* point : *contacts) {
            found |= sub_710008A8C8(point->body_b);
            if (found)
                break;
        }
    }

    if (found)
        ui::showInfoOverlay(46);
}

// Whether `body` belongs to the player, or to the horse / sand seal the player rides.
bool AirWallAction::sub_710008A8C8(ksys::phys::RigidBody* body) {
    if (!body)
        return false;
    auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body->getUserTag());
    if (!tag)
        return false;

    ksys::act::ActorLinkConstDataAccess actor;
    tag->acquireActor(&actor);
    if (!actor.hasProc())
        return false;
    if (actor.isPlayerProfile())
        return true;

    auto* player_info = act::PlayerInfo::instance();
    if (!player_info)
        return false;
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&player_info->getPlayerLink(), &player);
    if (player.isRidingHorse()) {
        ksys::act::ActorLinkConstDataAccess horse;
        ksys::act::acquireActor(&player_info->getHorseLink(), &horse);
        if (actor.getProc() == horse.getProc())
            return true;
    }
    if (player.isRidingSandSeal()) {
        ksys::act::ActorLinkConstDataAccess seal;
        player.getSandSealActor(&seal);
        if (actor.getProc() == seal.getProc())
            return true;
    }
    return false;
}

}  // namespace uking::action
