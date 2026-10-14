#include "Game/AI/Behavior/behaviorNpcClerkCheck.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

// Source ownership is unknown; declarations only.
bool sub_7100EE2800(ksys::act::BaseProcAccessor* accessor, ksys::act::Actor* actor);
bool sub_7100023244(ksys::act::BaseProcAccessor* accessor);

namespace uking::behavior {

NpcClerkCheck::NpcClerkCheck(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NpcClerkCheck::~NpcClerkCheck() = default;

bool NpcClerkCheck::m6(sead::Heap* heap) {
    return true;
}

void NpcClerkCheck::m8() {}

void NpcClerkCheck::m7() {
    auto* actor = mActor;
    ksys::act::ActorLinkConstDataAccess accessor;
    sub_7100EE2800(&accessor, actor);
    if (accessor.getProc() && sub_7100023244(&accessor))
        ksys::act::enableAttClient(actor, "Buy");
    else
        ksys::act::disableAttClient(actor, "Buy");
}

void NpcClerkCheck::m9() {}

void NpcClerkCheck::loadParams() {

}

}  // namespace uking::behavior
