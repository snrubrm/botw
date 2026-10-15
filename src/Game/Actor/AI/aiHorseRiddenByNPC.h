#pragma once

#include <limits>
#include <math/seadVector.h>
#include <prim/seadEnum.h>

#include "Game/Actor/aiFlagByte.h"
#include "Game/Actor/Horse/AI/aiHorseRiddenByNPCBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRiddenByNPC : public HorseRiddenByNPCBase {
    SEAD_RTTI_OVERRIDE(HorseRiddenByNPC, HorseRiddenByNPCBase)
public:
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5)
    explicit HorseRiddenByNPC(const InitArg& arg);
    ~HorseRiddenByNPC() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710043cb38 (4.5 KB, not decompiled).
    void m34(u32 kind, const sead::Vector3f& pos, ksys::act::BaseProcLink* link) override;
    // Whether an awareness entry of sensor idx is ignored.
    bool m35(ksys::act::Unk_7100d78e50* entry, s32 idx) override;

protected:
    // static_param at offset 0x48
    const float* mNavMeshCharacterScaleAtPrecise_s{};
    sead::Vector3f _50{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
    std::numeric_limits<f32>::quiet_NaN()};
    f32 _5c = 0.0f;
    f32 _60 = 0.0f;
    f32 _64 = 0.0f;
    f32 _68 = 0.0f;
    void* _70{};
    FlagByte<Flag> _78;
};

}  // namespace uking::ai
