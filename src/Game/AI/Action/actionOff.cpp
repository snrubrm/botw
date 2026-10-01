#include "Game/AI/Action/actionOff.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Off::Off(const InitArg& arg) : ActionEx(arg) {}

Off::~Off() = default;

bool Off::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void Off::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);

    switch (*mLinkTagType_s) {
    case 0:
        actor->emitBasicSigOff();
        break;
    case 1:
        actor->emitSignalAxisY_0();
        break;
    case 2:
        actor->emitSignalNAxisY_0();
        break;
    case 3:
        actor->emitSignalAxisY_0();
        actor->emitSignalNAxisY_0();
        break;
    }

    if (*mOffWaitRevival_s)
        actor->setRevivalFlagForUsed(false);
    mFlags.set(Flag::Changeable);
}

void Off::leave_() {
    ActionEx::leave_();
}

void Off::loadParams_() {
    getStaticParam(&mLinkTagType_s, "LinkTagType");
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mOffWaitRevival_s, "OffWaitRevival");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void Off::calc_() {
    if (isFinishedAS(*mTargetIdx_s, *mSeqBankIdx_s))
        setFinished();
}

}  // namespace uking::action
