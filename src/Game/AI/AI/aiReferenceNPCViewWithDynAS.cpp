#include "Game/AI/AI/aiReferenceNPCViewWithDynAS.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ReferenceNPCViewWithDynAS::ReferenceNPCViewWithDynAS(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReferenceNPCViewWithDynAS::~ReferenceNPCViewWithDynAS() = default;

bool ReferenceNPCViewWithDynAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReferenceNPCViewWithDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReferenceNPCViewWithDynAS::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReferenceNPCViewWithDynAS::loadParams_() {
    getDynamicParam(&mParams.mDynASKey_d, "DynASKey");
    getStaticParam(&mParams.mTurnStartAngle_s, "TurnStartAngle");
    getStaticParam(&mParams.mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mParams.mDynASKey_d, "DynASKey");
}

bool ReferenceNPCViewWithDynAS::isFinished() const {
    return isCurrentChild("待機") && getCurrentChild()->isFinished();
}

// 0x710053bb30
void ReferenceNPCViewWithDynAS::sub_710053BB30(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addString(mParams.mDynASKey_d, "DynASKey", -1);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

}  // namespace uking::ai
