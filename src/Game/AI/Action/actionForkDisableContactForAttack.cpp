#include "Game/AI/Action/actionForkDisableContactForAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkDisableContactForAttack::ForkDisableContactForAttack(const InitArg& arg)
    : ForkDisableContact(arg) {}

ForkDisableContactForAttack::~ForkDisableContactForAttack() = default;

bool ForkDisableContactForAttack::init_(sead::Heap* heap) {
    return ForkDisableContact::init_(heap);
}

void ForkDisableContactForAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDisableContact::enter_(params);
}

void ForkDisableContactForAttack::leave_() {
    ForkDisableContact::leave_();
}

void ForkDisableContactForAttack::loadParams_() {
    ForkDisableContact::loadParams_();
}

void ForkDisableContactForAttack::calc_() {
    ForkDisableContact::calc_();
}

bool ForkDisableContactForAttack::m32() {
    return sub_71005DD66C(mActor, nullptr, 0, 0);
}

bool ForkDisableContactForAttack::m33() {
    return sub_71005DD7B0(mActor, nullptr, 0, 0);
}

}  // namespace uking::action
