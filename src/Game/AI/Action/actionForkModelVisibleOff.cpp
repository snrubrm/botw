#include "Game/AI/Action/actionForkModelVisibleOff.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkModelVisibleOff::ForkModelVisibleOff(const InitArg& arg) : Fork(arg) {}

ForkModelVisibleOff::~ForkModelVisibleOff() = default;

bool ForkModelVisibleOff::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkModelVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    if (!*mUseASEvent_s) {
        auto& flags = mActor->getActorFlags2();
        if (!flags.isOn(ksys::act::Actor::ActorFlag2::_20))
            flags.set(ksys::act::Actor::ActorFlag2::_20);
    }
}

void ForkModelVisibleOff::leave_() {
    Fork::leave_();
}

void ForkModelVisibleOff::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mUseFadeIn_s, "UseFadeIn");
    getStaticParam(&mUseASEvent_s, "UseASEvent");
}

void ForkModelVisibleOff::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
