#include "Game/AI/AI/aiLynelArrowAttackSelect.h"

namespace uking::ai {

LynelArrowAttackSelect::LynelArrowAttackSelect(const InitArg& arg)
    : LynelArrowAttackSelectBase(arg) {}

LynelArrowAttackSelect::~LynelArrowAttackSelect() = default;

bool LynelArrowAttackSelect::init_(sead::Heap* heap) {
    return LynelArrowAttackSelectBase::init_(heap);
}

void LynelArrowAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelArrowAttackSelectBase::enter_(params);
}

void LynelArrowAttackSelect::calc_() {
    LynelArrowAttackSelectBase::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("通常撃ち"))
            sub_710048B294(nullptr);
    } else if (child->isChangeable()) {
        if (isCurrentChild("通常撃ち") && !sub_710048B2B8())
            sub_710048B294(nullptr);
    }
}

void LynelArrowAttackSelect::leave_() {
    LynelArrowAttackSelectBase::leave_();
}

void LynelArrowAttackSelect::loadParams_() {
    LynelArrowAttackSelectBase::loadParams_();
}

}  // namespace uking::ai
