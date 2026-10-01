#include "Game/AI/AI/aiTargetAttackAttitudeTgtSelectBase.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

TargetAttackAttitudeTgtSelectBase::TargetAttackAttitudeTgtSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TargetAttackAttitudeTgtSelectBase::~TargetAttackAttitudeTgtSelectBase() = default;

void TargetAttackAttitudeTgtSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = ksys::Timer(10.0f, 10.0f);
    m34(params);
}

// NON_MATCHING: the original keeps &_38 in a callee-saved register for the value load after update()
void TargetAttackAttitudeTgtSelectBase::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    }

    if (!getCurrentChild()->isChangeable())
        return;

    if (isCurrentChild("通常")) {
        if (!sub_71005BB85C()) {
            _38 = ksys::Timer(10.0f, 10.0f);
            return;
        }
        _38.update();
        if (_38.value <= sead::Mathf::epsilon()) {
            _38 = ksys::Timer(10.0f, 10.0f);
            m35(nullptr);
        }
    } else if (isCurrentChild("対攻撃")) {
        if (sub_71005BB85C()) {
            _38 = ksys::Timer(10.0f, 10.0f);
            return;
        }
        _38.update();
        if (_38.value <= sead::Mathf::epsilon()) {
            _38 = ksys::Timer(10.0f, 10.0f);
            m34(nullptr);
        }
    }
}

void TargetAttackAttitudeTgtSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetAttackAttitudeTgtSelectBase::loadParams_() {}

}  // namespace uking::ai
