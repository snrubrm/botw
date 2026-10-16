#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::behavior {

class SetEnableResetToInitialState : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetEnableResetToInitialState, ksys::act::ai::Behavior)
public:
    explicit SetEnableResetToInitialState(const InitArg& arg);
    ~SetEnableResetToInitialState() override;
    bool init_(sead::Heap* heap) override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void calc() override;

    // 2026-10-07: calc passes the complete actor/LOD timer object at28 to D3BCE4.
    /* 0x28 */ ksys::act::Unk_7100d3bce4 _28{mActor};
};
KSYS_CHECK_SIZE_NX150(SetEnableResetToInitialState, 0x40);

}  // namespace uking::behavior
