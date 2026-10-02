#pragma once

#include <math/seadVector.h>
#include "Game/AI/AI/aiAnimalRoam.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalRoamCheckWater : public AnimalRoam {
    SEAD_RTTI_OVERRIDE(AnimalRoamCheckWater, AnimalRoam)
public:
    explicit AnimalRoamCheckWater(const InitArg& arg);
    ~AnimalRoamCheckWater() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool m39() override;
    bool m40(sead::Vector3f* pos) override;

protected:
    // static_param at offset 0xf8
    const float* mWaterLevelLimitLower_s{};
    // static_param at offset 0x100
    const float* mWaterLevelLimitUpper_s{};
    bool _108 = false;
    sead::Vector3f _10c;
};
KSYS_CHECK_SIZE_NX150(AnimalRoamCheckWater, 0x118);

}  // namespace uking::ai
