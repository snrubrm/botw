#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ForceSealSilentKill : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ForceSealSilentKill, ksys::act::ai::Behavior)
public:
    explicit ForceSealSilentKill(const InitArg& arg);
    ~ForceSealSilentKill() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ int* mForceSealSilentKillCount_a{};
};
KSYS_CHECK_SIZE_NX150(ForceSealSilentKill, 0x30);

}  // namespace uking::behavior
