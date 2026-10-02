#include "Game/AI/Action/actionForkAlwaysColTgOff.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ForkAlwaysColTgOff::ForkAlwaysColTgOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysColTgOff::~ForkAlwaysColTgOff() = default;

bool ForkAlwaysColTgOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysColTgOff::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71007A397C(mActor);
    mFlags.set(Flag::Changeable);
}

void ForkAlwaysColTgOff::leave_() {
    sub_71007A3800(mActor);
}

void ForkAlwaysColTgOff::loadParams_() {}

void ForkAlwaysColTgOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
