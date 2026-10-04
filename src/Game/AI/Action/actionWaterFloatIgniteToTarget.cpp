#include "Game/AI/Action/actionWaterFloatIgniteToTarget.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WaterFloatIgniteToTarget::WaterFloatIgniteToTarget(const InitArg& arg)
    : OneTimeWaterFloatStopASPlay(arg) {}

WaterFloatIgniteToTarget::~WaterFloatIgniteToTarget() = default;

bool WaterFloatIgniteToTarget::init_(sead::Heap* heap) {
    return OneTimeWaterFloatStopASPlay::init_(heap);
}

void WaterFloatIgniteToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    OneTimeWaterFloatStopASPlay::enter_(params);
}

void WaterFloatIgniteToTarget::leave_() {
    OneTimeWaterFloatStopASPlay::leave_();
}

void WaterFloatIgniteToTarget::loadParams_() {
    OneTimeWaterFloatStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
}

void WaterFloatIgniteToTarget::calc_() {
    OneTimeWaterFloatStopASPlay::calc_();
    if (mActor->getASList()->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        sub_71002B5E34(*mIgniteHandle_d);
}

}  // namespace uking::action
