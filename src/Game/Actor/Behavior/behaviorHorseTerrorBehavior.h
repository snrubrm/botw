#pragma once

#include "Game/Actor/Behavior/behaviorTerrorBehavior.h"

namespace uking::behavior {

class HorseTerrorBehavior : public TerrorBehavior {
    SEAD_RTTI_OVERRIDE(HorseTerrorBehavior, TerrorBehavior)
public:
    explicit HorseTerrorBehavior(const InitArg& arg);
    ~HorseTerrorBehavior() override;
    bool init_(sead::Heap* heap) override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void calc() override;

    /* 0x158 */ const int* mGear1Level_s{};
    /* 0x160 */ const int* mGear2Level_s{};
    /* 0x168 */ const int* mGear3Level_s{};
    /* 0x170 */ const int* mGearTopLevel_s{};
    /* 0x178 */ const float* mOffsetDistanceSec_s{};
};
KSYS_CHECK_SIZE_NX150(HorseTerrorBehavior, 0x180);

}  // namespace uking::behavior
