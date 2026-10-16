#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetNoWeakHitReactionDCCallBack : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetNoWeakHitReactionDCCallBack, SetDamageCallback)
public:
    explicit SetNoWeakHitReactionDCCallBack(const InitArg& arg);
    ~SetNoWeakHitReactionDCCallBack() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102451cd0 _30;
};
KSYS_CHECK_SIZE_NX150(SetNoWeakHitReactionDCCallBack, 0x58);

}  // namespace uking::behavior
