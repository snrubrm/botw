#include "Game/Actor/Behavior/behaviorDeleteConnectedCalcChild.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

DeleteConnectedCalcChild::DeleteConnectedCalcChild(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

DeleteConnectedCalcChild::~DeleteConnectedCalcChild() = default;

bool DeleteConnectedCalcChild::init_(sead::Heap* heap) {
    return true;
}

void DeleteConnectedCalcChild::calc() {}

void DeleteConnectedCalcChild::leave() {}

void DeleteConnectedCalcChild::loadParams() {

}

void DeleteConnectedCalcChild::enter() {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (!child)
        return;
    mActor->resetConnectedCalcChild(false);
    child->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason(0));
}

}  // namespace uking::behavior
