#include "Game/AI/Action/actionForkAlwaysOneColTgOff.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ForkAlwaysOneColTgOff::ForkAlwaysOneColTgOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysOneColTgOff::~ForkAlwaysOneColTgOff() = default;

bool ForkAlwaysOneColTgOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysOneColTgOff::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71007A3910(mActor, mRigidBodyName_s);
    mFlags.set(Flag::Changeable);
}

void ForkAlwaysOneColTgOff::leave_() {
    sub_71007A3778(mActor, mRigidBodyName_s);
}

void ForkAlwaysOneColTgOff::loadParams_() {
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkAlwaysOneColTgOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
