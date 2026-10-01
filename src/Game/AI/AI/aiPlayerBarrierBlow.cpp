#include "Game/AI/AI/aiPlayerBarrierBlow.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PlayerBarrierBlow::PlayerBarrierBlow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerBarrierBlow::~PlayerBarrierBlow() = default;

bool PlayerBarrierBlow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerBarrierBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx);
    else
        changeChild("吹き飛び");
}

void PlayerBarrierBlow::calc_() {
    if (handlePendingChildChange())
        return;

    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("吹き飛び")) {
        _40.reset(*mBlowRagdollTime_s);
        ksys::act::ai::InlineParamPack params;
        params.addBool(false, "IsAddImpulse", -1);
        params.addFloat(0.0f, "InitAddLinearImpulse", -1);
        params.addFloat(0.0f, "InitAddRollImpulse", -1);
        changeChild("ラグドール", &params);
        return;
    }

    if (!isCurrentChild("ラグドール"))
        return;

    if (_40.value <= sead::Mathf::epsilon())
        setFinished();
    else
        _40.update();
}

void PlayerBarrierBlow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerBarrierBlow::loadParams_() {
    getStaticParam(&mBlowRagdollTime_s, "BlowRagdollTime");
}

}  // namespace uking::ai
