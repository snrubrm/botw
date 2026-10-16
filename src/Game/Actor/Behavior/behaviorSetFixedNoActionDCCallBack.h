#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetFixedNoActionDCCallBack : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetFixedNoActionDCCallBack, SetDamageCallback)
public:
    explicit SetFixedNoActionDCCallBack(const InitArg& arg);
    ~SetFixedNoActionDCCallBack() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ Unk_71024519e0 _30;
};
KSYS_CHECK_SIZE_NX150(SetFixedNoActionDCCallBack, 0x58);

}  // namespace uking::behavior
