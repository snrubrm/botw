#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BossBgmDamaged : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BossBgmDamaged, ksys::act::ai::Behavior)
public:
    explicit BossBgmDamaged(const InitArg& arg);
    ~BossBgmDamaged() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m11() override {}
    virtual bool m14() { return false; }
    void m7() override;  // not decompiled yet (0x710061aaa0)

    /* 0x28 */ const int* mDieType_s{};
};
KSYS_CHECK_SIZE_NX150(BossBgmDamaged, 0x30);

}  // namespace uking::behavior
