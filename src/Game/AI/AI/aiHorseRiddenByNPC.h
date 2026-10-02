#pragma once

#include <limits>
#include <math/seadVector.h>

#include "Game/AI/AI/aiHorseRiddenByNPCBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRiddenByNPC : public HorseRiddenByNPCBase {
    SEAD_RTTI_OVERRIDE(HorseRiddenByNPC, HorseRiddenByNPCBase)
public:
    explicit HorseRiddenByNPC(const InitArg& arg);
    ~HorseRiddenByNPC() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x48
    const float* mNavMeshCharacterScaleAtPrecise_s{};
    sead::Vector3f _50{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
    std::numeric_limits<f32>::quiet_NaN()};
    f32 _5c = 0.0f;
    f32 _60 = 0.0f;
    u32 _64 = 0;
    u32 _68 = 0;
    void* _70{};
    bool _78 = false;
};

}  // namespace uking::ai
