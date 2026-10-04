#include "Game/AI/Action/actionForkBoneControlFrontGround.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkBoneControlFrontGround::ForkBoneControlFrontGround(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBoneControlFrontGround::~ForkBoneControlFrontGround() = default;

bool ForkBoneControlFrontGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBoneControlFrontGround::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkBoneControlFrontGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkBoneControlFrontGround::loadParams_() {
    getStaticParam(&mTargetOffset_s, "TargetOffset");
}

void ForkBoneControlFrontGround::calc_() {
    if (sub_71005DD798(mActor, 44, nullptr, 0, 0)) {
        sead::Vector3f v;
        sub_7100148EB0(1.0f, &v);
        sub_71005DB068(mActor, v);
    }
}

}  // namespace uking::action
