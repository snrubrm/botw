#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ForceFallCliffEdgeChanger : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ForceFallCliffEdgeChanger, ksys::act::ai::Behavior)
public:
    explicit ForceFallCliffEdgeChanger(const InitArg& arg);
    ~ForceFallCliffEdgeChanger() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const bool* mState_s{};
    /* 0x30 */ bool _30 = false;
};
KSYS_CHECK_SIZE_NX150(ForceFallCliffEdgeChanger, 0x38);

}  // namespace uking::behavior
