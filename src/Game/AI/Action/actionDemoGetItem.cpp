#include "Game/AI/Action/actionDemoGetItem.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

DemoGetItem::DemoGetItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoGetItem::~DemoGetItem() = default;

bool DemoGetItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoGetItem::loadParams_() {}

bool DemoGetItem::oneShot_() {
    auto* actor = mActor;
    actor->x_8(false);
    if (auto* attention = actor->getAttention())
        attention->disableAllClients();
    if (auto* xlink = actor->getXLink())
        xlink->sleep(1);
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    return true;
}

}  // namespace uking::action
