#pragma once

#include "Game/AI/Behavior/behaviorNoiseBase.h"
#include "KingSystem/ActorSystem/Awareness/actAITerror.h"

namespace uking::behavior {

class Noise : public NoiseBase {
    SEAD_RTTI_OVERRIDE(Noise, NoiseBase)
public:
    explicit Noise(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    ~Noise() override;
    // 0x710062df30
    void sub_710062DF30();

    /* 0x40 */ const float* mSensorRadius_s{};
    /* 0x48 */ ksys::act::AITerror _48{mActor};
};

}  // namespace uking::behavior
