#include "Game/AI/Action/actionSetWorldRotOffsetFromTransBone.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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

// NON_MATCHING: the original keeps all three rotation components in memory (the stores happen before the second
// atan2f call); ours keeps the values in registers and stores only y.
void SetWorldRotOffsetFromTransBone::calc_() {
    if (auto* bone_control = mActor->sub_71011D8A10()) {
        sead::Vector3f rotation = mActor->getASList()->_80.getRotation();
        rotation.x = 0.0f;
        rotation.z = 0.0f;
        bone_control->sub_7100D8A830(rotation.y, false);
    }
}

}  // namespace uking::action
