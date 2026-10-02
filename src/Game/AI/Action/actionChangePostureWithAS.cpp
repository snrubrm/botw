#include "Game/AI/Action/actionChangePostureWithAS.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

ChangePostureWithAS::ChangePostureWithAS(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangePostureWithAS::~ChangePostureWithAS() = default;

bool ChangePostureWithAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangePostureWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangePostureWithAS::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangePostureWithAS::loadParams_() {
    getDynamicParam(&mPosture_d, "Posture");
}

void ChangePostureWithAS::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
