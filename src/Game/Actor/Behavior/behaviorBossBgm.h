#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BossBgm : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BossBgm, ksys::act::ai::Behavior)
public:
    explicit BossBgm(const InitArg& arg);
    ~BossBgm() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mBossType_s{};
};
KSYS_CHECK_SIZE_NX150(BossBgm, 0x30);

}  // namespace uking::behavior
