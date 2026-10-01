#include "Game/AI/Action/actionSendSignalForSignalFlowAct.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SendSignalForSignalFlowAct::SendSignalForSignalFlowAct(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SendSignalForSignalFlowAct::~SendSignalForSignalFlowAct() = default;

bool SendSignalForSignalFlowAct::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SendSignalForSignalFlowAct::oneShot_() {
    if (*mValue_d != 0)
        mActor->emitBasicSigOn();
    else
        mActor->emitBasicSigOff();
    return true;
}

void SendSignalForSignalFlowAct::loadParams_() {
    getDynamicParam(&mSignalType_d, "SignalType");
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
