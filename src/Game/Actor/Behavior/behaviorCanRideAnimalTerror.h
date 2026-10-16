#pragma once

#include "Game/Actor/Behavior/behaviorTerrorBehavior.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

class CanRideAnimalTerror : public TerrorBehavior {
    SEAD_RTTI_OVERRIDE(CanRideAnimalTerror, TerrorBehavior)
public:
    explicit CanRideAnimalTerror(const InitArg& arg);
    ~CanRideAnimalTerror() override;
    bool init_(sead::Heap* heap) override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void calc() override;

    void sub_710061B944();

    /* 0x158 */ const int* mLevelForRiddenPlayer_s{};
    /* 0x160 */ ksys::Timer _160{};
    /* 0x16c */ bool _16c = false;
};
KSYS_CHECK_SIZE_NX150(CanRideAnimalTerror, 0x170);

}  // namespace uking::behavior
