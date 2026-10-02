#include "Game/AI/Action/actionForkAnimDriveTurn.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAnimDriveTurn::ForkAnimDriveTurn(const InitArg& arg) : ForkAnimDriveMove(arg) {}

ForkAnimDriveTurn::~ForkAnimDriveTurn() = default;

bool ForkAnimDriveTurn::init_(sead::Heap* heap) {
    return ForkAnimDriveMove::init_(heap);
}

void ForkAnimDriveTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimDriveMove::enter_(params);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= mActor->getMtx().getTranslation();
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(axis.y * angle));
}

void ForkAnimDriveTurn::leave_() {
    ForkAnimDriveMove::leave_();
}

void ForkAnimDriveTurn::loadParams_() {
    ForkAnimDriveMove::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkAnimDriveTurn::calc_() {
    ForkAnimDriveMove::calc_();
}

}  // namespace uking::action
