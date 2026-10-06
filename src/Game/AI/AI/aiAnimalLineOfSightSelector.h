#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AnimalLineOfSightSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalLineOfSightSelector, ksys::act::ai::Ai)
public:
    explicit AnimalLineOfSightSelector(const InitArg& arg);
    ~AnimalLineOfSightSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100307530 (placeholder name): starts the child of the given gear (1-4) and restarts the gear-up restriction timer.
    void changeToGear(s32 gear);
    // 0x710030732c / 0x7100307430 (placeholder names): gear down / up within [MinGear, MaxGear].
    void gearDown();
    void gearUp();

protected:
    // static_param at offset 0x38
    const int* mStartGear_s{};
    // static_param at offset 0x40
    const int* mMinGear_s{};
    // static_param at offset 0x48
    const int* mMaxGear_s{};
    // static_param at offset 0x50
    const float* mGearUpRestrictionFrames_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _60;
    bool _6c = true;
    int _70{};
};

}  // namespace uking::ai
