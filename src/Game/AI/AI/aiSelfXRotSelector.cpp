#include "Game/AI/AI/aiSelfXRotSelector.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SelfXRotSelector::SelfXRotSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SelfXRotSelector::~SelfXRotSelector() = default;

bool SelfXRotSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SelfXRotSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 angle = sead::Mathf::abs(
        sead::Mathf::asin(sead::Mathf::clamp(mActor->getMtx()(1, 2), -1.0f, 1.0f)));
    if (angle >= *mAngle_s)
        changeChild("以上", params);
    else
        changeChild("未満", params);
}

void SelfXRotSelector::calc_() {}

void SelfXRotSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SelfXRotSelector::loadParams_() {
    getStaticParam(&mAngle_s, "Angle");
}

}  // namespace uking::ai
