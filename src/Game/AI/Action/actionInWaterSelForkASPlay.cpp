#include "Game/AI/Action/actionInWaterSelForkASPlay.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

inWaterSelForkASPlay::inWaterSelForkASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

inWaterSelForkASPlay::~inWaterSelForkASPlay() = default;

bool inWaterSelForkASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void inWaterSelForkASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void inWaterSelForkASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void inWaterSelForkASPlay::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mFirstRandomRatio_s, "FirstRandomRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: regalloc only (the original loads the mSeqBank_s pointer before mTargetBone_s in each arm; x20 / x21 swapped)
void inWaterSelForkASPlay::calc_() {
    if (*mChangeableTiming_s == 2) {
        if (mActor->getASList()->x_7(*mTargetBone_s, *mSeqBank_s,
                                     &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            mFlags.set(Flag::Changeable);
        } else {
            mFlags.reset(Flag::Changeable);
        }
    } else if (*mChangeableTiming_s == 3) {
        if (!sub_71005DD798(mActor, 0x16, nullptr, *mTargetBone_s, *mSeqBank_s))
            mFlags.set(Flag::Changeable);
        else
            mFlags.reset(Flag::Changeable);
    }
    if (isFinishedAS(*mTargetBone_s, *mSeqBank_s) || _60 > 31.0f) {
        switch (*mEndState_s) {
        case 2:
            mFlags.set(Flag::Changeable);
            break;
        case 1:
            setFinished();
            break;
        }
    }
    _60 += ksys::VFR::instance()->getDeltaFrame();
}

}  // namespace uking::action
