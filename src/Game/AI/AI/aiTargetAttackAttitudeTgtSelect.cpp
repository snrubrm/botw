#include "Game/AI/AI/aiTargetAttackAttitudeTgtSelect.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetAttackAttitudeTgtSelect::TargetAttackAttitudeTgtSelect(const InitArg& arg)
    : TargetAttackAttitudeTgtSelectBase(arg) {}

TargetAttackAttitudeTgtSelect::~TargetAttackAttitudeTgtSelect() = default;

void TargetAttackAttitudeTgtSelect::calc_() {
    TargetAttackAttitudeTgtSelectBase::calc_();
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void TargetAttackAttitudeTgtSelect::loadParams_() {
    TargetAttackAttitudeTgtSelectBase::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TargetAttackAttitudeTgtSelect::m34(ksys::act::ai::InlineParamPack* params) {
    sub_71005BB664(false);
    ksys::act::ai::InlineParamPack params_;
    params_.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("通常", &params_);
}

void TargetAttackAttitudeTgtSelect::m35(ksys::act::ai::InlineParamPack* params) {
    sub_71005BB664(true);
    ksys::act::ai::InlineParamPack params_;
    params_.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("対攻撃", &params_);
}

}  // namespace uking::ai
