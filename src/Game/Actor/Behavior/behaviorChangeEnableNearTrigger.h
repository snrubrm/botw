#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ChangeEnableNearTrigger : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ChangeEnableNearTrigger, ksys::act::ai::Behavior)
public:
    explicit ChangeEnableNearTrigger(const InitArg& arg);
    ~ChangeEnableNearTrigger() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const bool* mEnable_s{};
    /* 0x30 */ const bool* mIsRestoreWhenLeave_s{};
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(ChangeEnableNearTrigger, 0x40);

}  // namespace uking::behavior
