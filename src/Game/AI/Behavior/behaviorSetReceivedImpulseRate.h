#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// TODO: `_30` is a sead::Delegate1 (vtable 0x7102439f70) bound to this and 0x710063e528, whose argument type
// (an impulse info struct) is not declared yet.
class SetReceivedImpulseRate : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetReceivedImpulseRate, ksys::act::ai::Behavior)
public:
    explicit SetReceivedImpulseRate(const InitArg& arg);
    ~SetReceivedImpulseRate() override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710063e5c0)

    /* 0x28 */ const float* mImpulseRate_s{};
    /* 0x30 */ u8 _30[0x20];
};
KSYS_CHECK_SIZE_NX150(SetReceivedImpulseRate, 0x50);

}  // namespace uking::behavior
