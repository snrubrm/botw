#include "Game/AI/Action/actionForkASPlayBase.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASPlayBase::ForkASPlayBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASPlayBase::~ForkASPlayBase() = default;

bool ForkASPlayBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASPlayBase::enter_(ksys::act::ai::InlineParamPack* params) {
    const char* name = m32();
    if (name && *name) {
        playAS(name, *mIsIgnoreSame_s, *mTargetBone_s, *mSeqBank_s, -1.0f);
        const f32 ratio = *mFirstRandomRatio_s;
        if (ratio > 0.0f) {
            mActor->getASList()->sub_710115F1D8(0, 0,
                                                ratio * sead::GlobalRandom::instance()->getF32());
        }
    }
    if (*mChangeableTiming_s == 0)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
}

void ForkASPlayBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASPlayBase::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mFirstRandomRatio_s, "FirstRandomRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
}

// NON_MATCHING: same code and control flow (as LynelAttackASPlay::sub_71001DF2E0); the original loads the 0x30 member pointer
// before the 0x38 one and evaluates the case-2 arguments in the other order
void ForkASPlayBase::calc_() {
    switch (*mChangeableTiming_s) {
    case 3:
        if (sub_71005DD798(mActor, 22, nullptr, *mTargetBone_s, *mSeqBank_s))
            mFlags.reset(Flag::Changeable);
        else
            mFlags.set(Flag::Changeable);
        break;
    case 2:
        if (mActor->getASList()->x_7(*mTargetBone_s, *mSeqBank_s,
                                     &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            mFlags.set(Flag::Changeable);
        } else {
            mFlags.reset(Flag::Changeable);
        }
        break;
    }

    if (isFinishedAS(*mTargetBone_s, *mSeqBank_s)) {
        switch (*mEndState_s) {
        case 2:
            mFlags.set(Flag::Changeable);
            break;
        case 1:
            setFinished();
            break;
        }
    }
}

const char* ForkASPlayBase::m32() {
    return nullptr;
}

bool ForkASPlayBase::isChangeable() const {
    switch (*mChangeableTiming_s) {
    case 2:
        if (mActor->getASList()->x_7(*mTargetBone_s, *mSeqBank_s,
                                     &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            return true;
        }
        break;
    case 3:
        if (!sub_71005DD798(mActor, 22, nullptr, *mTargetBone_s, *mSeqBank_s))
            return true;
        break;
    }
    return ActionBase::isChangeable();
}

}  // namespace uking::action
