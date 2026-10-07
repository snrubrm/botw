#include "Game/AI/Action/actionSlippedBackWalkBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SlippedBackWalkBase::SlippedBackWalkBase(const InitArg& arg) : BackWalkBase(arg) {}

SlippedBackWalkBase::~SlippedBackWalkBase() = default;

bool SlippedBackWalkBase::init_(sead::Heap* heap) {
    return BackWalkBase::init_(heap);
}

void SlippedBackWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkBase::enter_(params);
}

void SlippedBackWalkBase::leave_() {
    BackWalkBase::leave_();
}

void SlippedBackWalkBase::loadParams_() {
    BackWalkBase::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
}

void SlippedBackWalkBase::calc_() {
    BackWalkBase::calc_();
}

void SlippedBackWalkBase::m32(ksys::phys::CharacterController* controller) {
    auto* actor = mActor;
    sead::Vector3f dir;
    actor->getMtx().getBase(dir, 2);
    dir.normalize();
    sub_71005E2540(controller, actor, -dir * (*mParams.mDecelRatio_s * *mParams.mSpeed_s), 0.1f);
}

void SlippedBackWalkBase::m33(ksys::phys::CharacterController* controller) {
    auto* actor = mActor;
    sead::Vector3f dir;
    actor->getMtx().getBase(dir, 2);
    dir.normalize();
    sub_71005E2540(controller, actor, -dir * *mParams.mSpeed_s, 0.1f);
}

}  // namespace uking::action
