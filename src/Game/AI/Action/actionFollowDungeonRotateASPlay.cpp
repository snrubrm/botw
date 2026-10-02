#include "Game/AI/Action/actionFollowDungeonRotateASPlay.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FollowDungeonRotateASPlay::FollowDungeonRotateASPlay(const InitArg& arg)
    : FollowDungeonRotate(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
FollowDungeonRotateASPlay::~FollowDungeonRotateASPlay() {
    ;
}

bool FollowDungeonRotateASPlay::init_(sead::Heap* heap) {
    return FollowDungeonRotate::init_(heap);
}

void FollowDungeonRotateASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    FollowDungeonRotate::enter_(params);
    auto* actor = mActor;
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
    if (*mOnWaitRevival_s)
        actor->setRevivalFlagForUsed(true);
    if (*mOnLinkTagBasic_s)
        actor->emitBasicSigOn();
}

void FollowDungeonRotateASPlay::leave_() {
    FollowDungeonRotate::leave_();
}

void FollowDungeonRotateASPlay::loadParams_() {
    FollowDungeonRotate::loadParams_();
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mIsSuccessEndOnASFinish_s, "IsSuccessEndOnASFinish");
    getStaticParam(&mOnWaitRevival_s, "OnWaitRevival");
    getStaticParam(&mOnLinkTagBasic_s, "OnLinkTagBasic");
    getStaticParam(&mASName_s, "ASName");
}

void FollowDungeonRotateASPlay::calc_() {
    FollowDungeonRotate::calc_();
    if (*mIsSuccessEndOnASFinish_s && isFinishedAS(*mTargetIdx_s, *mSeqBankIdx_s))
        setFinished();
}

}  // namespace uking::action
