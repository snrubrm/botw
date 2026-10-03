#include "Game/AI/AI/aiSnowBallNormal.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SnowBallNormal::SnowBallNormal(const InitArg& arg) : FixableLiftable(arg) {}

SnowBallNormal::~SnowBallNormal() = default;

bool SnowBallNormal::init_(sead::Heap* heap) {
    return FixableLiftable::init_(heap);
}

void SnowBallNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    FixableLiftable::enter_(params);
}

void SnowBallNormal::leave_() {
    FixableLiftable::leave_();
}

void SnowBallNormal::loadParams_() {
    FixableLiftable::loadParams_();
    getStaticParam(&mScaleRate_s, "ScaleRate");
    getStaticParam(&mScaleMax_s, "ScaleMax");
    getStaticParam(&mCarryScaleLimit_s, "CarryScaleLimit");
    getStaticParam(&mSendSignalLinearVelTh_s, "SendSignalLinearVelTh");
    getStaticParam(&mSendSignalScaleTh_s, "SendSignalScaleTh");
    getStaticParam(&mScaleMin_s, "ScaleMin");
    getStaticParam(&mDeleteUnderWaterDepth_s, "DeleteUnderWaterDepth");
    getStaticParam(&mMaxImpulseMassRate_s, "MaxImpulseMassRate");
    getStaticParam(&mAttReturnOnOffset_s, "AttReturnOnOffset");
    getStaticParam(&mScaleIncreaseDistance_s, "ScaleIncreaseDistance");
    getStaticParam(&mItemDropSetScaleOffset_s, "ItemDropSetScaleOffset");
    getStaticParam(&mItemDropDeleteScaleOffset_s, "ItemDropDeleteScaleOffset");
    getStaticParam(&mMinImpulseRatio_s, "MinImpulseRatio");
}

bool SnowBallNormal::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000009 && !isCurrentChild("壊れる")) {
        changeChild("壊れる");
        return true;
    }
    return FixableLiftable::handleMessage_(message);
}

void SnowBallNormal::m38() {
    auto* actor = mActor;
    const f32 scale_min = *mScaleMin_s;
    _d8 = sead::Mathf::clamp(actor->getScale().x, scale_min, *mScaleMax_s);
    actor->setScale({_d8, _d8, _d8});
}

}  // namespace uking::ai
