#include "Game/AI/AI/aiSeqFirstPointTwo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SeqFirstPointTwo::SeqFirstPointTwo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqFirstPointTwo::~SeqFirstPointTwo() = default;

bool SeqFirstPointTwo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqFirstPointTwo::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_48, "TargetPos", -1);
    changeChild("先行動", &pack);
}

void SeqFirstPointTwo::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (child->isFailed() && *mIsFinishedByFailAction_s) {
        setFailed();
        return;
    }

    if (isCurrentChild("先行動")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_48, "TargetPos", -1);
        changeChild("後行動", &pack);
    } else if (child->isFinished()) {
        setFinished();
    } else {
        setFailed();
    }
}

void SeqFirstPointTwo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqFirstPointTwo::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
