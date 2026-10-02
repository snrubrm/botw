#include "Game/AI/Action/actionSetWorldRotOffsetFromTransBone.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::action {

SetWorldRotOffsetFromTransBone::SetWorldRotOffsetFromTransBone(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetWorldRotOffsetFromTransBone::~SetWorldRotOffsetFromTransBone() = default;

bool SetWorldRotOffsetFromTransBone::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetWorldRotOffsetFromTransBone::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void SetWorldRotOffsetFromTransBone::leave_() {
    if (auto* bone_control = mActor->sub_71011D8A10())
        bone_control->sub_7100D8A830(0.0f, false);
}

void SetWorldRotOffsetFromTransBone::loadParams_() {}

void SetWorldRotOffsetFromTransBone::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
