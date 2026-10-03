#include "Game/AI/AI/aiGuardianCloseBattle.h"

namespace uking::ai {

GuardianCloseBattle::GuardianCloseBattle(const InitArg& arg) : GuardianAI(arg) {}

GuardianCloseBattle::~GuardianCloseBattle() = default;

bool GuardianCloseBattle::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianCloseBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
    if (!sub_710040DA6C()) {
        setFailed();
        return;
    }
    sub_710040E088(2);
    changeChild("待機");
}

void GuardianCloseBattle::calc_() {
    GuardianAI::calc_();
    if (!sub_710040DA6C()) {
        setFailed();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!sub_710040DF74()) {
            isCurrentChild("ビーム攻撃") || isCurrentChild("掴み攻撃");
            sub_710040E088(2);
            changeChild("待機");
        } else {
            setFailed();
        }
    }
}

bool GuardianCloseBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianCloseBattle::leave_() {
    GuardianAI::leave_();
    sub_710040E088(0);
}

void GuardianCloseBattle::loadParams_() {
    GuardianAI::loadParams_();
}

}  // namespace uking::ai
