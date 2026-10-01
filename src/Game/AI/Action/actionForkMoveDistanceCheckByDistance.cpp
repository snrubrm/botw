#include "Game/AI/Action/actionForkMoveDistanceCheckByDistance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkMoveDistanceCheckByDistance::ForkMoveDistanceCheckByDistance(const InitArg& arg) : Fork(arg) {}

ForkMoveDistanceCheckByDistance::~ForkMoveDistanceCheckByDistance() = default;

bool ForkMoveDistanceCheckByDistance::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkMoveDistanceCheckByDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    mActor->getMtx().getTranslation(_38);
}

void ForkMoveDistanceCheckByDistance::leave_() {
    Fork::leave_();
}

void ForkMoveDistanceCheckByDistance::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mIsCheckOnlyXZ_s, "IsCheckOnlyXZ");
}

// NON_MATCHING: original branches on mIsCheckOnlyXZ_s (x*x vs x*x + y*y), we get an fcsel on y
void ForkMoveDistanceCheckByDistance::calc_() {
    Fork::calc_();
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f diff = _38 - pos;
    if (*mIsCheckOnlyXZ_s)
        diff.y = 0.0f;
    if (diff.length() >= m32())
        setEndState();
}

float ForkMoveDistanceCheckByDistance::m32() {
    return 0.0f;
}

}  // namespace uking::action
