#include "Game/AI/Action/actionAirWallCurseGanon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

AirWallCurseGanon::AirWallCurseGanon(const InitArg& arg) : AirWallHorse(arg) {}

AirWallCurseGanon::~AirWallCurseGanon() {
    if (auto* physics = mActor->getPhysics()) {
        physics->sub_7100FBDFA4(physics->get178(0));
        physics->sub_7100FBDFA4(physics->get178(1));
    }
}

bool AirWallCurseGanon::init_(sead::Heap* heap) {
    return AirWallHorse::init_(heap);
}

void AirWallCurseGanon::enter_(ksys::act::ai::InlineParamPack* params) {
    AirWallHorse::enter_(params);
    ksys::act::ActorConstDataAccess player;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &player);
    if (!player.hasProc())
        return;
    auto* handler = player.x(0);
    if (!handler)
        return;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    physics->sub_7100FBDFA4(handler);
    const int num_sets = physics->getNumRigidBodySets();
    for (int i = 0; i < num_sets; ++i) {
        if (auto* set = physics->getRigidBodySet(i)) {
            const int num_bodies = set->getRigidBodies().size();
            for (int j = 0; j < num_bodies; ++j) {
                if (auto* body = set->getRigidBody(j))
                    body->setFlag200();
            }
        }
    }
}

void AirWallCurseGanon::leave_() {
    AirWallHorse::leave_();
}

void AirWallCurseGanon::loadParams_() {
    AirWallHorse::loadParams_();
}

void AirWallCurseGanon::calc_() {
    AirWallHorse::calc_();
}

}  // namespace uking::action
