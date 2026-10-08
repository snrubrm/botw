#include "Game/AI/Action/actionDemoVisibleOn.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

DemoVisibleOn::DemoVisibleOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVisibleOn::~DemoVisibleOn() = default;

bool DemoVisibleOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoVisibleOn::loadParams_() {}

bool DemoVisibleOn::oneShot_() {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    if (!ksys::evt::Manager::instance()->sub_7100DB20D0()) {
        if (auto* xlink = actor->getXLink()) {
            xlink->toggle(ksys::xlink::XLink::MaskBit::_1);
            xlink->_cc.set(4);
        }
    }
    if (auto* physics = mActor->getPhysics()) {
        physics->clothVisibleStuff();
        physics->clothVisibleStuff_0(1);
    }
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2b, false);
    return true;
}

}  // namespace uking::action
