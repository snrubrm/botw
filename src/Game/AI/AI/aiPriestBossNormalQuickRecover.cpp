#include "Game/AI/AI/aiPriestBossNormalQuickRecover.h"

namespace uking::ai {

PriestBossNormalQuickRecover::PriestBossNormalQuickRecover(const InitArg& arg)
    : PriestBossMode(arg) {}

PriestBossNormalQuickRecover::~PriestBossNormalQuickRecover() = default;

bool PriestBossNormalQuickRecover::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossNormalQuickRecover::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
    if (*mIsFromRagdoll_d)
        changeChild("ラグドールから復帰");
    else
        changeChild("ダウンから復帰");
}

void PriestBossNormalQuickRecover::calc_() {
    PriestBossMode::calc_();
    auto* child = getCurrentChild();
    if (child && (child->isFinished() || child->isFailed())) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void PriestBossNormalQuickRecover::leave_() {
    PriestBossMode::leave_();
}

void PriestBossNormalQuickRecover::loadParams_() {
    PriestBossMode::loadParams_();
    getDynamicParam(&mIsFromRagdoll_d, "IsFromRagdoll");
}

}  // namespace uking::ai
