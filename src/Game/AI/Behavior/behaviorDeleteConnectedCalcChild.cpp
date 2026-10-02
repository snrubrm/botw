#include "Game/AI/Behavior/behaviorDeleteConnectedCalcChild.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

DeleteConnectedCalcChild::DeleteConnectedCalcChild(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

DeleteConnectedCalcChild::~DeleteConnectedCalcChild() = default;

bool DeleteConnectedCalcChild::m6(sead::Heap* heap) {
    return true;
}

void DeleteConnectedCalcChild::m7() {}

void DeleteConnectedCalcChild::m9() {}

void DeleteConnectedCalcChild::loadParams() {

}

void DeleteConnectedCalcChild::m8() {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (!child)
        return;
    mActor->resetConnectedCalcChild(false);
    child->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason(0));
}

}  // namespace uking::behavior
