#include "Game/Actor/Action/actionMultiVacuumRotBase.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/VFR.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MultiVacuumRotBase::MultiVacuumRotBase(const InitArg& arg)
    : MultiVacuumBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
MultiVacuumRotBase::~MultiVacuumRotBase() {
    ;
}

bool MultiVacuumRotBase::init_(sead::Heap* heap) {
    return MultiVacuumBase::init_(heap);
}

void MultiVacuumRotBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MultiVacuumBase::enter_(params);
    sub_710073FA90(&_1d8, mActor);
    _1fc = mActor->getAngVelocity().length();
}

void MultiVacuumRotBase::leave_() {
    MultiVacuumBase::leave_();
}

void MultiVacuumRotBase::loadParams_() {
    MultiVacuumBase::loadParams_();
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mPosReduceRatio_s, "PosReduceRatio");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void MultiVacuumRotBase::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    MultiVacuumBase::calc_();
    sub_710073FA94(&_1d8, mActor);
    const sead::Vector3f up = getUpDir(getGravity(mActor));
    sead::Vector3f dir = *mParams.mTargetPos_d;
    dir -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    ksys::VFR::lerp(&_1fc, *mParams.mRotSpd_s, 0.16f, *mParams.mRotSpd_s / 10.0f);
    sub_710074006C(&_1d8, dir, up, true, 0.16f, _1fc, _1fc / 10.0f);
    sub_7100740E04(_1d8, controller);
    sub_7100738488(mActor, *mParams.mPosReduceRatio_s, -sead::Vector3f::ey);
}

}  // namespace uking::action
