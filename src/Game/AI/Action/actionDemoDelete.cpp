#include "Game/AI/Action/actionDemoDelete.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DemoDelete::DemoDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoDelete::~DemoDelete() = default;

bool DemoDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DemoDelete::oneShot_() {
    mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    return true;
}

void DemoDelete::loadParams_() {}

}  // namespace uking::action
