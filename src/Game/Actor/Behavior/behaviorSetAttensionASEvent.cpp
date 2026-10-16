#include "Game/Actor/Behavior/behaviorSetAttensionASEvent.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::behavior {

SetAttensionASEvent::SetAttensionASEvent(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetAttensionASEvent::~SetAttensionASEvent() {
    ;
}

bool SetAttensionASEvent::init_(sead::Heap* heap) {
    return true;
}

void SetAttensionASEvent::loadParams() {
    getStaticParam(&mAttKey_s, "AttKey");
}

void SetAttensionASEvent::enter() {
    _38 = false;
    if (sub_71005DD798(mActor, 0, nullptr, 0, 0)) {
        _38 = true;
        ksys::act::enableAttClient(mActor, mAttKey_s);
    }
}

void SetAttensionASEvent::calc() {
    const bool on = sub_71005DD798(mActor, 0, nullptr, 0, 0);
    if (_38) {
        if (!on) {
            _38 = false;
            ksys::act::disableAttClient(mActor, mAttKey_s);
        }
    } else if (on) {
        _38 = true;
        ksys::act::enableAttClient(mActor, mAttKey_s);
    }
}

void SetAttensionASEvent::leave() {
    if (sub_71005DD798(mActor, 0, nullptr, 0, 0) || sub_71005DD734(mActor, 0, nullptr, 0, 0))
        ksys::act::disableAttClient(mActor, mAttKey_s);
}

}  // namespace uking::behavior
