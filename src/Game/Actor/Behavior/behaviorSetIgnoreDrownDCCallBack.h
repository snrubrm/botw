#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetIgnoreDrownDCCallBack : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetIgnoreDrownDCCallBack, SetDamageCallback)
public:
    explicit SetIgnoreDrownDCCallBack(const InitArg& arg);
    ~SetIgnoreDrownDCCallBack() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102451a88 _30;
};
KSYS_CHECK_SIZE_NX150(SetIgnoreDrownDCCallBack, 0x58);

}  // namespace uking::behavior
