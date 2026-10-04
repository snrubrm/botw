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
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710043cb38 (4.5 KB, not decompiled).
    void m34(u32 kind, const sead::Vector3f& pos, ksys::act::BaseProcLink* link) override;
    // 0x710043dcdc (not decompiled: calls the unnamed 0x7100e804e4).
    bool m35(ksys::act::Unk_7100d78e50* entry, s32 idx) override;

protected:
    // static_param at offset 0x48
    const float* mNavMeshCharacterScaleAtPrecise_s{};
    sead::Vector3f _50{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
    std::numeric_limits<f32>::quiet_NaN()};
    f32 _5c = 0.0f;
    f32 _60 = 0.0f;
    u32 _64 = 0;
    f32 _68 = 0.0f;
    void* _70{};
    bool _78 = false;
};

}  // namespace uking::ai
