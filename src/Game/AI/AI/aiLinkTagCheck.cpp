#include "Game/AI/AI/aiLinkTagCheck.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LinkTagCheck::LinkTagCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool LinkTagCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original inlines the type dispatch / job timer test as helpers (actor loaded
// before the type, the timer test duplicated after every state change); see lane1 log s22
void LinkTagCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    bool is_on;
    bool has_link = false;
    switch (*mSignalType_s) {
    case 0:
        has_link = mActor->hasPlacementLinkForBasicSig();
        break;
    case 2:
        has_link = mActor->hasPlacementLinkWithTypeRemains();
        break;
    case 1:
        has_link = mActor->hasForbidAttentionLink_0();
        break;
    }
    if (has_link) {
        is_on = false;
        switch (*mSignalType_s) {
        case 0:
            is_on = mActor->checkBasicSig();
            break;
        case 2:
            is_on = mActor->checkRemainsSignal();
            break;
        case 1:
            is_on = mActor->checkForbidAttentionSignal();
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
    case 3:
        mActor->m107();
        break;
    case 2:
        if (isCurrentChild("オフ"))
            mActor->m107();
        break;
    case 1:
        if (isCurrentChild("オン"))
            mActor->m107();
        break;
    }
    mFlags.set(Flag::Changeable);
}

// NON_MATCHING: as enter_ (and `child_done & isCurrentChild(..)` is not short-circuited in the
// original)
void LinkTagCheck::calc_() {
    bool has_link = false;
    switch (*mSignalType_s) {
    case 0:
        has_link = mActor->hasPlacementLinkForBasicSig();
        break;
    case 2:
        has_link = mActor->hasPlacementLinkWithTypeRemains();
        break;
    case 1:
        has_link = mActor->hasForbidAttentionLink_0();
        break;
    }
    if (has_link) {
        bool is_on = false;
        switch (*mSignalType_s) {
        case 0:
            is_on = mActor->checkBasicSig();
            break;
        case 2:
            is_on = mActor->checkRemainsSignal();
            break;
        case 1:
            is_on = mActor->checkForbidAttentionSignal();
            break;
        }
        bool child_done = true;
        if (*mIsCheckChildEnd_s) {
            auto* child = getCurrentChild();
            child_done = child->isFinished() || child->isFailed();
        }
        if (is_on) {
            if (child_done && isCurrentChild("オフ"))
                changeChild("オン");
        } else {
            if (child_done && isCurrentChild("オン"))
                changeChild("オフ");
        }
    } else if (*mIsNotConnectOn_s) {
        if (isCurrentChild("オフ"))
            changeChild("オン");
    }
    switch (*mSetEnableJobTimerTiming_s) {
    case 3:
        mActor->m107();
        break;
    case 2:
        if (isCurrentChild("オフ"))
            mActor->m107();
        break;
    case 1:
        if (isCurrentChild("オン"))
            mActor->m107();
        break;
    }
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
