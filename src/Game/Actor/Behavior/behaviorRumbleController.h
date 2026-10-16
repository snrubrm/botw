#pragma once

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

    /* 0x28 */ const float* mReduceDist_s{};
};
KSYS_CHECK_SIZE_NX150(RumbleController, 0x30);

}  // namespace uking::behavior
