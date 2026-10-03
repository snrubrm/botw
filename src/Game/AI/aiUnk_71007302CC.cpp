#include "Game/AI/aiUnk_71007302CC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

bool sub_71007302CC(ksys::act::Actor* a, ksys::act::Actor* b, f32 distance) {
    return (a->getMtx().getTranslation() - b->getMtx().getTranslation()).length() <= distance;
}

bool sub_71007303F0(ksys::act::BaseProcLink* a, ksys::act::BaseProcLink* b, f32 distance) {
    ksys::act::ActorConstDataAccess accessor_a;
    ksys::act::ActorConstDataAccess accessor_b;
    ksys::act::acquireActor(a, &accessor_a);
    ksys::act::acquireActor(b, &accessor_b);
    return (accessor_a.getActorMtx().getTranslation() - accessor_b.getActorMtx().getTranslation())
               .length() <= distance;
}
