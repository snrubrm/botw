#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class UnderSelectedReactionNoAction : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(UnderSelectedReactionNoAction, SetDamageCallback)
public:
    explicit UnderSelectedReactionNoAction(const InitArg& arg);
    ~UnderSelectedReactionNoAction() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;

    /* 0x30 */ const int* mReactionID_s{};
    /* 0x38 */ Unk_7102451d78 _38;
};
KSYS_CHECK_SIZE_NX150(UnderSelectedReactionNoAction, 0x60);

}  // namespace uking::behavior
