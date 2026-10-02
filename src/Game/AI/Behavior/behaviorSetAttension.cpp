#include "Game/AI/Behavior/behaviorSetAttension.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::behavior {

SetAttension::SetAttension(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetAttension::~SetAttension() {
    ;
}

bool SetAttension::m6(sead::Heap* heap) {
    return true;
}

void SetAttension::m7() {}

void SetAttension::loadParams() {
    getStaticParam(&mSetState_s, "SetState");
    getStaticParam(&mAttKey_s, "AttKey");
}

void SetAttension::m8() {
    switch (*mSetState_s) {
    case 0:
    case 2:
        ksys::act::disableAttClient(mActor, mAttKey_s);
        break;
    case 1:
    case 3:
        ksys::act::enableAttClient(mActor, mAttKey_s);
        break;
    default:
        break;
    }
}

void SetAttension::m9() {
    switch (*mSetState_s) {
    case 0:
        ksys::act::enableAttClient(mActor, mAttKey_s);
        break;
    case 1:
        ksys::act::disableAttClient(mActor, mAttKey_s);
        break;
    default:
        break;
    }
}

}  // namespace uking::behavior
