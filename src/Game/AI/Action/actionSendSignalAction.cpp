#include "Game/AI/Action/actionSendSignalAction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SendSignalAction::SendSignalAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SendSignalAction::~SendSignalAction() = default;

bool SendSignalAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SendSignalAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mSignalType_d != 0) {
        setFailed();
    } else if (mActor->checkLinkBasicSig() == *mValue_d) {
        setFinished();
    } else {
        _30.reset(300.0f);
        return;
    }
    mFlags.set(Flag::Changeable);
}

void SendSignalAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SendSignalAction::loadParams_() {
    getDynamicParam(&mSignalType_d, "SignalType");
    getDynamicParam(&mValue_d, "Value");
}

void SendSignalAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
