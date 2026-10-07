#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

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
    void m7() override;

    // 2026-10-07: m7 passes the complete actor/LOD timer object at28 to D3BCE4.
    /* 0x28 */ ksys::act::Unk_7100d3bce4 _28{mActor};
};
KSYS_CHECK_SIZE_NX150(SetEnableResetToInitialState, 0x40);

}  // namespace uking::behavior
