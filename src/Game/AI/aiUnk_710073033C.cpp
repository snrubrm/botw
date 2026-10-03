#include "Game/AI/aiUnk_710073033C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

bool sub_710073033C(ksys::act::Actor* actor, ksys::act::BaseProcLink* link, f32 distance) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f target;
    accessor.getActorMtx().getTranslation(target);
    const sead::Vector3f pos(actor->getMtx().m[0][3], actor->getMtx().m[1][3], actor->getMtx().m[2][3]);
    return (pos - target).length() <= distance;
}
