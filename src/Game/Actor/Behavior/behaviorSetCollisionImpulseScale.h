#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetCollisionImpulseScale : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetCollisionImpulseScale, ksys::act::ai::Behavior)
public:
    explicit SetCollisionImpulseScale(const InitArg& arg);
    ~SetCollisionImpulseScale() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const float* mScale_s{};
    /* 0x30 */ f32 _30 = 1.0f;
};
KSYS_CHECK_SIZE_NX150(SetCollisionImpulseScale, 0x38);

}  // namespace uking::behavior
