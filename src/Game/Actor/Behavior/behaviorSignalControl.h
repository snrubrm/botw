#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SignalControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SignalControl, ksys::act::ai::Behavior)
public:
    explicit SignalControl(const InitArg& arg);
    ~SignalControl() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const int* mSignalType_s{};
    /* 0x30 */ const bool* mIsOnOnEnter_s{};
    /* 0x38 */ const bool* mIsReverseOnLeave_s{};
};
KSYS_CHECK_SIZE_NX150(SignalControl, 0x40);

}  // namespace uking::behavior
