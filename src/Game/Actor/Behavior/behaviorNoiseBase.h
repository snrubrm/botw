#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// CSV name: Noise_ (base of Noise and the NoSensor*Noise behaviors).
class NoiseBase : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(NoiseBase, ksys::act::ai::Behavior)
public:
    explicit NoiseBase(const InitArg& arg);
    void m7() override;
    void m8() override { _38 = false; }
    void m9() override;
    void loadParams() override;
    virtual f32 m14() { return *mNoiseValue_s; }
    // 0x710062e9f0
    void sub_710062E9F0();
    // 0x710062e9f8
    void sub_710062E9F8();

    /* 0x28 */ const float* mNoiseValue_s{};
    /* 0x30 */ const bool* mIsShock_s{};
    /* 0x38 */ bool _38 = false;
};

}  // namespace uking::behavior
