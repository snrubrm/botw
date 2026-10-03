#include "Game/AI/AI/aiEscapeOrWaitSelect.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EscapeOrWaitSelect::EscapeOrWaitSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EscapeOrWaitSelect::~EscapeOrWaitSelect() = default;

bool EscapeOrWaitSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack layout only (see LynelEscapeFromTarget::enter_)
void EscapeOrWaitSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    if (sub_71003C9440(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("逃走", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &pack);
    }
}

void EscapeOrWaitSelect::calc_() {}

bool EscapeOrWaitSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EscapeOrWaitSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void EscapeOrWaitSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeOrWaitSelect::loadParams_() {
    getStaticParam(&mEscapeRange_s, "EscapeRange");
    getStaticParam(&mEscapeMoveDistMin_s, "EscapeMoveDistMin");
    getStaticParam(&mEscapeMoveDistMax_s, "EscapeMoveDistMax");
    getStaticParam(&mCheckBackAngle_s, "CheckBackAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
