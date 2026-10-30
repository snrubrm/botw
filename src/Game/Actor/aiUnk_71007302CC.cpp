#include "Game/Actor/aiUnk_71007302CC.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

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

// NON_MATCHING: vector loads, temporary stack slots and return scheduling differ.
bool sub_71007304CC(ksys::act::Actor* actor, const sead::Vector3f& target, f32 min_height,
                    f32 max_height, f32 max_distance, f32 angle, f32 ray_height) {
    if (!actor)
        return false;
    const auto& mtx = actor->getMtx();
    const sead::Vector3f position = mtx.getTranslation();
    sead::Vector3f direction = target - position;
    direction.y = 0.0f;
    const f32 distance = direction.normalize();
    const f32 height = target.y - position.y;
    if (height < min_height || height > max_height || distance > max_distance)
        return false;
    if (!(mtx.getBase(2).dot(direction) >= sead::Mathf::cos(angle)))
        return false;

    sead::Vector3f start = position;
    sead::Vector3f end = target;
    start.y += ray_height;
    end.y += ray_height;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    query.setStartAndEnd(start, end);
    return !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

bool sub_710073068C(ksys::act::Actor* actor, f32 min_height, f32 max_height, f32 max_distance,
                    f32 angle, f32 ray_height) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    sead::Vector3f position;
    player.getActorMtx().getTranslation(position);
    return sub_71007304CC(actor, position, min_height, max_height, max_distance, angle, ray_height);
}
