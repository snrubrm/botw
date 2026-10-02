#include "Game/AI/AI/aiJustAvoidFinishWait.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

JustAvoidFinishWait::JustAvoidFinishWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

JustAvoidFinishWait::~JustAvoidFinishWait() = default;

bool JustAvoidFinishWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void JustAvoidFinishWait::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("メイン", params);
}

void JustAvoidFinishWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void JustAvoidFinishWait::loadParams_() {
    getStaticParam(&mIsUseWaitAfterMain_s, "IsUseWaitAfterMain");
}

void JustAvoidFinishWait::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;

    if (child->isChangeable())
        mFlags.set(Flag::Changeable);

    if ((child->isFinished() || child->isFailed()) && !sub_710072B7C4()) {
        if (isCurrentChild("メイン") && *mIsUseWaitAfterMain_s)
            changeChild("待機");
        else if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
}

}  // namespace uking::ai
