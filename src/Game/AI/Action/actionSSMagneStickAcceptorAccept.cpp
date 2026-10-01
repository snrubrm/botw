#include "Game/AI/Action/actionSSMagneStickAcceptorAccept.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SSMagneStickAcceptorAccept::SSMagneStickAcceptorAccept(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SSMagneStickAcceptorAccept::~SSMagneStickAcceptorAccept() = default;

bool SSMagneStickAcceptorAccept::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SSMagneStickAcceptorAccept::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor)
        mActor->emitBasicSigOn();
}

void SSMagneStickAcceptorAccept::leave_() {
    ksys::act::ai::Action::leave_();
}

void SSMagneStickAcceptorAccept::loadParams_() {}

void SSMagneStickAcceptorAccept::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
