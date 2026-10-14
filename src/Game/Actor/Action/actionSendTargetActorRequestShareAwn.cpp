#include "Game/Actor/Action/actionSendTargetActorRequestShareAwn.h"

namespace uking::action {

SendTargetActorRequestShareAwn::SendTargetActorRequestShareAwn(const InitArg& arg)
    : SendTargetActorMessageBase(arg) {}

SendTargetActorRequestShareAwn::~SendTargetActorRequestShareAwn() = default;

bool SendTargetActorRequestShareAwn::init_(sead::Heap* heap) {
    return SendTargetActorMessageBase::init_(heap);
}

void SendTargetActorRequestShareAwn::enter_(ksys::act::ai::InlineParamPack* params) {
    SendTargetActorMessageBase::enter_(params);
}

void SendTargetActorRequestShareAwn::leave_() {
    SendTargetActorMessageBase::leave_();
}

void SendTargetActorRequestShareAwn::loadParams_() {
    SendTargetActorMessageBase::loadParams_();
}

void SendTargetActorRequestShareAwn::calc_() {
    SendTargetActorMessageBase::calc_();
}

void SendTargetActorRequestShareAwn::m33() {
    _30._18.y(mActor);
}

Unk_7102357d20* SendTargetActorRequestShareAwn::m34() {
    return &_30;
}

}  // namespace uking::action
