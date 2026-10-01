#include "Game/AI/AI/aiRestreintTired.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RestreintTired::RestreintTired(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RestreintTired::~RestreintTired() = default;

bool RestreintTired::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RestreintTired::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsTryingReturnRestreint_a = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mCentralPos_d, "TargetPos", -1);
    changeChild("帰還", &pack);
}

void RestreintTired::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("帰還")) {
            *mIsTryingReturnRestreint_a = true;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("注意", &pack);
        } else {
            setFailed();
        }
        return;
    }

    if (isCurrentChild("注意"))
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void RestreintTired::leave_() {
    *mIsTryingReturnRestreint_a = false;
}

void RestreintTired::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getAITreeVariable(&mIsTryingReturnRestreint_a, "IsTryingReturnRestreint");
}

}  // namespace uking::ai
