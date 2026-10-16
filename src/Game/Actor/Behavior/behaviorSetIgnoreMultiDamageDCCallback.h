#pragma once

#include "Game/Actor/Behavior/behaviorSetDamageCallback.h"
#include "Game/Actor/aiUnkDamageCallbacks.h"

namespace uking::behavior {

class SetIgnoreMultiDamageDCCallback : public SetDamageCallback {
    SEAD_RTTI_OVERRIDE(SetIgnoreMultiDamageDCCallback, SetDamageCallback)
public:
    explicit SetIgnoreMultiDamageDCCallback(const InitArg& arg);
    ~SetIgnoreMultiDamageDCCallback() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    uking::act::DamageCallback* m14() override;

    /* 0x30 */ Unk_7102451b30 _30;
    /* 0x58 */ const bool* mEnableCritical_s{};
    /* 0x60 */ const bool* mEnableSmallHit_s{};
    /* 0x68 */ const bool* mEnableMiddleHit_s{};
    /* 0x70 */ const bool* mEnableLargeHit_s{};
    /* 0x78 */ const bool* mEnableBlowOff_s{};
    /* 0x80 */ const bool* mEnableGust_s{};
};
KSYS_CHECK_SIZE_NX150(SetIgnoreMultiDamageDCCallback, 0x88);

}  // namespace uking::behavior
