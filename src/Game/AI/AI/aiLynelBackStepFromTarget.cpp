#include "Game/AI/AI/aiLynelBackStepFromTarget.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelBackStepFromTarget::LynelBackStepFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelBackStepFromTarget::~LynelBackStepFromTarget() = default;

bool LynelBackStepFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelBackStepFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    if (sub_710048CEBC(&pos))
        changeToEscapeMove(pos);
    else
        changeToCannotEscape();
}

void LynelBackStepFromTarget::calc_() {}

bool LynelBackStepFromTarget::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool LynelBackStepFromTarget::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void LynelBackStepFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelBackStepFromTarget::loadParams_() {
    getStaticParam(&mMoveDistMin_s, "MoveDistMin");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mAddCheckAngle_s, "AddCheckAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
