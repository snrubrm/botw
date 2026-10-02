#include "Game/AI/AI/aiGanonBattleOnFloorRoot.h"

namespace uking::ai {

GanonBattleOnFloorRoot::GanonBattleOnFloorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBattleOnFloorRoot::~GanonBattleOnFloorRoot() = default;

bool GanonBattleOnFloorRoot::init_(sead::Heap* heap) {
    _50 = ksys::Timer(900.0f, 900.0f);
    _5c = false;
    return true;
}

void GanonBattleOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBattleOnFloorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBattleOnFloorRoot::loadParams_() {
    getStaticParam(&mFarAttackDist_s, "FarAttackDist");
    getDynamicParam(&mIsNoWait_d, "IsNoWait");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool GanonBattleOnFloorRoot::isFinished() const {
    auto* child = getCurrentChild();
    if (child && (isCurrentChild("近接攻撃") || isCurrentChild("遠距離攻撃")))
        return child->isFinished();
    return ActionBase::isFinished();
}

}  // namespace uking::ai
