#pragma once

#include "Game/AI/Behavior/behaviorSetDamageCallback.h"
#include "Game/AI/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetNoReactionDCCallBack : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetNoReactionDCCallBack, SetDamageCallback)
public:
    explicit SetNoReactionDCCallBack(const InitArg& arg);
    ~SetNoReactionDCCallBack() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    uking::dmg::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102451c98 _30;
};
KSYS_CHECK_SIZE_NX150(SetNoReactionDCCallBack, 0x58);

}  // namespace uking::behavior
