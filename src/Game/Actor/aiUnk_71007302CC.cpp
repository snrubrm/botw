#include "Game/Actor/aiUnk_71007302CC.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

bool sub_71007302CC(ksys::act::Actor* a, ksys::act::Actor* b, f32 distance) {
    return (a->getMtx().getTranslation() - b->getMtx().getTranslation()).length() <= distance;
}

bool sub_71007303F0(ksys::act::BaseProcLink* a, ksys::act::BaseProcLink* b, f32 distance) {
    ksys::act::ActorLinkConstDataAccess accessor_a;
    ksys::act::ActorLinkConstDataAccess accessor_b;
    ksys::act::acquireActor(a, &accessor_a);
    ksys::act::acquireActor(b, &accessor_b);
    return (accessor_a.getActorMtx().getTranslation() - accessor_b.getActorMtx().getTranslation())
               .length() <= distance;
}

bool sub_710073068C(ksys::act::Actor* actor, f32 min_height, f32 max_height, f32 max_distance,
                    f32 angle, f32 ray_height) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sead::Vector3f position;
    player.getActorMtx().getTranslation(position);
    return sub_71007304CC(actor, position, min_height, max_height, max_distance, angle, ray_height);
}
