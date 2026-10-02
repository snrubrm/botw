#pragma once

#include "Game/AI/Behavior/behaviorTerrorBehavior.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

class CanRideAnimalTerror : public TerrorBehavior {
    SEAD_RTTI_OVERRIDE(CanRideAnimalTerror, TerrorBehavior)
public:
    explicit CanRideAnimalTerror(const InitArg& arg);
    ~CanRideAnimalTerror() override;
    bool m6(sead::Heap* heap) override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x710061b920)
    void m8() override;  // not decompiled yet (0x710061b8ec)

    /* 0x158 */ const int* mLevelForRiddenPlayer_s{};
    /* 0x160 */ ksys::Timer _160{};
    /* 0x16c */ bool _16c = false;
};
KSYS_CHECK_SIZE_NX150(CanRideAnimalTerror, 0x170);

}  // namespace uking::behavior
