#include "Game/AI/AI/aiLinkTagCheck.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LinkTagCheck::LinkTagCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool LinkTagCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original probes the case values of the second and third switch in a different order
// (0, 2, 1 / 3, 2, 1); the code and the calls are the same
void LinkTagCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    bool has_link = false;
    switch (*mSignalType_s) {
    case 0:
        has_link = mActor->hasPlacementLinkForBasicSig();
        break;
    case 1:
        has_link = mActor->hasForbidAttentionLink();
        break;
    case 2:
        has_link = mActor->hasPlacementLinkWithTypeRemains();
        break;
    }

    bool is_on = false;
    if (has_link) {
        switch (*mSignalType_s) {
        case 0:
            is_on = mActor->checkBasicSig();
            break;
        case 1:
            is_on = mActor->checkForbidAttentionSignal();
            break;
        case 2:
            is_on = mActor->checkRemainsSignal();
            break;
        }
    } else {
        is_on = *mIsNotConnectOn_s;
    }

    if (is_on)
        changeChild("オン");
    else
        changeChild("オフ");

    switch (*mSetEnableJobTimerTiming_s) {
    case 1:
        if (isCurrentChild("オン"))
            mActor->m107();
        break;
    case 2:
        if (isCurrentChild("オフ"))
            mActor->m107();
        break;
    case 3:
        mActor->m107();
        break;
    }

    mFlags.set(Flag::Changeable);
}

void LinkTagCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LinkTagCheck::loadParams_() {
    getStaticParam(&mSignalType_s, "SignalType");
    getStaticParam(&mSetEnableJobTimerTiming_s, "SetEnableJobTimerTiming");
    getStaticParam(&mIsNotConnectOn_s, "IsNotConnectOn");
    getStaticParam(&mIsCheckChildEnd_s, "IsCheckChildEnd");
}

}  // namespace uking::ai
