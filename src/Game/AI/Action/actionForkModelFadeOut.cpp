#include "Game/AI/Action/actionForkModelFadeOut.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkModelFadeOut::ForkModelFadeOut(const InitArg& arg) : Fork(arg) {}

ForkModelFadeOut::~ForkModelFadeOut() = default;

bool ForkModelFadeOut::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkModelFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    mActor->get68c() = true;
}

void ForkModelFadeOut::leave_() {
    Fork::leave_();
}

void ForkModelFadeOut::loadParams_() {
    Fork::loadParams_();
}

bool ForkModelFadeOut::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x3000010)
        return false;
    setEndState();
    return true;
}

void ForkModelFadeOut::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
