#include "Game/AI/Action/actionForkModelVisibleOff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

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
    auto* actor = mActor;
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20)) {
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        if (*mUseFadeIn_s) {
            actor->setStartModelOpacity(0.0f);
            actor->sub_71011CCB1C(0.0f);
        }
    }
}

void ForkModelVisibleOff::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mUseFadeIn_s, "UseFadeIn");
    getStaticParam(&mUseASEvent_s, "UseASEvent");
}

void ForkModelVisibleOff::calc_() {
    Fork::calc_();
    if (!*mUseASEvent_s)
        return;
    if (sub_71005DD734(mActor, 0x14, nullptr, 0, 0)) {
        auto* actor = mActor;
        if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20)) {
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            if (*mUseFadeIn_s) {
                actor->setStartModelOpacity(0.0f);
                actor->sub_71011CCB1C(0.0f);
            }
        }
    }
    if (sub_71005DD5B0(mActor, 0x14, nullptr, 0, 0)) {
        if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20))
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    }
}

}  // namespace uking::action
