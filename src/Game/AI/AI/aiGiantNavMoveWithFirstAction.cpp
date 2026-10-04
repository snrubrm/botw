#include "Game/AI/AI/aiGiantNavMoveWithFirstAction.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GiantNavMoveWithFirstAction::GiantNavMoveWithFirstAction(const InitArg& arg)
    : GiantNavMoveTarget(arg) {}

GiantNavMoveWithFirstAction::~GiantNavMoveWithFirstAction() = default;

bool GiantNavMoveWithFirstAction::init_(sead::Heap* heap) {
    return GiantNavMoveTarget::init_(heap);
}

void GiantNavMoveWithFirstAction::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantNavMoveTarget::enter_(params);
}

void GiantNavMoveWithFirstAction::calc_() {
    GiantNavMoveTarget::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("先行動"))
            changeToLookAround();
    } else if (child->isChangeable()) {
        if (isCurrentChild("先行動"))
            sub_71003F8E3C();
    }
}

void GiantNavMoveWithFirstAction::m34() {
    sub_71003F7DA8();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("先行動", &pack);
}

void GiantNavMoveWithFirstAction::leave_() {
    GiantNavMoveTarget::leave_();
}

void GiantNavMoveWithFirstAction::loadParams_() {
    GiantNavMoveTarget::loadParams_();
}

}  // namespace uking::ai
