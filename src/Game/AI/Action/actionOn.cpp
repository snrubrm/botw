#include "Game/AI/Action/actionOn.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

On::On(const InitArg& arg) : ActionEx(arg) {}

On::~On() = default;

bool On::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void On::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);

    switch (*mLinkTagType_s) {
    case 0:
        actor->emitBasicSigOn();
        break;
    case 1:
        actor->emitSignalAxisY_1();
        break;
    case 2:
        actor->emitSignalNAxisY_1();
        break;
    }

    if (*mOnWaitRevival_s)
        actor->setRevivalFlagForUsed(true);
    mFlags.set(Flag::Changeable);
}

void On::leave_() {
    ActionEx::leave_();
}

void On::loadParams_() {
    getStaticParam(&mLinkTagType_s, "LinkTagType");
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mOnWaitRevival_s, "OnWaitRevival");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void On::calc_() {
    if (isFinishedAS(*mTargetIdx_s, *mSeqBankIdx_s))
        setFinished();
}

}  // namespace uking::action
