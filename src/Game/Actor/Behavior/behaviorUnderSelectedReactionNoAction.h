#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class UnderSelectedReactionNoAction : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(UnderSelectedReactionNoAction, SetDamageCallback)
public:
    explicit UnderSelectedReactionNoAction(const InitArg& arg);
    ~UnderSelectedReactionNoAction() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ const int* mReactionID_s{};
    /* 0x38 */ Unk_7102451d78 _38;
};
KSYS_CHECK_SIZE_NX150(UnderSelectedReactionNoAction, 0x60);

}  // namespace uking::behavior
