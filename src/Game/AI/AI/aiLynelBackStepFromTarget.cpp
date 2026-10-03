#include "Game/AI/AI/aiLynelBackStepFromTarget.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelBackStepFromTarget::LynelBackStepFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelBackStepFromTarget::~LynelBackStepFromTarget() = default;

bool LynelBackStepFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack layout only (the original keeps `pos` at sp+8 and the objects of both branches at the same
// slots; ours places `pos` in the outer frame)
void LynelBackStepFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    if (sub_710048CEBC(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("バックステップ", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("後退不能", &pack);
    }
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
