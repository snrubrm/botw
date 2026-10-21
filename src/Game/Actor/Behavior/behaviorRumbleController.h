#pragma once

#include "Game/gameRumble.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class RumbleController : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(RumbleController, ksys::act::ai::Behavior)
public:
    explicit RumbleController(const InitArg& arg);
    ~RumbleController() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    // The patterns come in the two groups 0-2 (event 86) and 3-5 (event 50); calc() lowers the pattern by the
    // distance to the player measured in units of ReduceDist, but never below the lowest pattern of its group.
    /* 0x28 */ const float* mReduceDist_s{};
};
KSYS_CHECK_SIZE_NX150(RumbleController, 0x30);

}  // namespace uking::behavior
