#include "Game/AI/Action/actionFreeMoveByGuideBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FreeMoveByGuideBase::FreeMoveByGuideBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FreeMoveByGuideBase::~FreeMoveByGuideBase() = default;

bool FreeMoveByGuideBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreeMoveByGuideBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getMainBody())
        return;
    if (!mASKeyName_s.isEmpty())
        playAS(mASKeyName_s.cstr(), false, 0, 0, -1.0f);
    _a8.value = 0;
    _a8.prev_value = 0;
    sub_7100741034(&_84, mActor);
    sub_7100741038(&_84, mActor);
}

void FreeMoveByGuideBase::leave_() {
    ksys::act::ai::Action::leave_();
}

bool FreeMoveByGuideBase::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::Action::reenter_(other, true))
        return false;
    auto* prev = sead::DynamicCast<FreeMoveByGuideBase>(other);
    if (!prev)
        return false;
    _78 = prev->_78;
    _84 = prev->_84;
    _a8 = prev->_a8;
    _b4 = prev->_b4;
    return true;
}

void FreeMoveByGuideBase::loadParams_() {
    getStaticParam(&mRotateAngleMax_s, "RotateAngleMax");
    getStaticParam(&mMaxAngleAcc_s, "MaxAngleAcc");
    getStaticParam(&mAngleAccRatio_s, "AngleAccRatio");
    getStaticParam(&mKeepPlacementRotation_s, "KeepPlacementRotation");
    getStaticParam(&mIsTraceRailPointRotation_s, "IsTraceRailPointRotation");
    getStaticParam(&mKeepRotationBaseBoneName_s, "KeepRotationBaseBoneName");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetFrontDir_d, "TargetFrontDir");
}

void FreeMoveByGuideBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
