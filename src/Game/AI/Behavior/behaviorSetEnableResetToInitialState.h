#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

class SetEnableResetToInitialState : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetEnableResetToInitialState, ksys::act::ai::Behavior)
public:
    explicit SetEnableResetToInitialState(const InitArg& arg);
    ~SetEnableResetToInitialState() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100639e4c)

    /* 0x28 */ ksys::act::Actor* _28{mActor};
    /* 0x30 */ ksys::Timer _30;
};
KSYS_CHECK_SIZE_NX150(SetEnableResetToInitialState, 0x40);

}  // namespace uking::behavior
