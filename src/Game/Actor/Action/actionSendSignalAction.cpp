#include "Game/Actor/Action/actionSendSignalAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiDemoRootAI.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::action {

SendSignalAction::SendSignalAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SendSignalAction::~SendSignalAction() = default;

bool SendSignalAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SendSignalAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mSignalType_d != 0) {
        setFailed();
    } else if (mActor->checkLinkBasicSig() == *mValue_d) {
        setFinished();
    } else {
        _30.reset(300.0f);
        return;
    }
    mFlags.set(Flag::Changeable);
}

void SendSignalAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SendSignalAction::loadParams_() {
    getDynamicParam(&mSignalType_d, "SignalType");
    getDynamicParam(&mValue_d, "Value");
}

// NON_MATCHING: register allocation in the DemoRootAI signal bit tests.
void SendSignalAction::calc_() {
    if (isFinished() || isFailed())
        return;

    if (_30.value <= sead::Mathf::epsilon()) {
        sead::FixedSafeString<16> name;
        if (*mSignalType_d == 0) {
            if (*mValue_d)
                name = "OnBasic";
            else
                name = "OffBasic";
        }
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }

    if (*mSignalType_d != 0) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }

    if (mActor->checkLinkBasicSig() == *mValue_d) {
        const int bit = *mSignalType_d * 2;
        if (mActor->getRootAi()->sub_7100D65CBC()->get4a().isOnBit(bit) ||
            mActor->getRootAi()->sub_7100D65CBC()->get4a().isOnBit(bit | 1)) {
            setFinished();
            mFlags.set(Flag::Changeable);
        }
    } else if (*mSignalType_d == 0) {
        if (*mValue_d)
            mActor->emitBasicSigOn();
        else
            mActor->emitBasicSigOff();
    }
    _30.update();
}

}  // namespace uking::action
