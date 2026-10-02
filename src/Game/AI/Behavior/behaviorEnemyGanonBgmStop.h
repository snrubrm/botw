#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EnemyGanonBgmStop : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EnemyGanonBgmStop, ksys::act::ai::Behavior)
public:
    explicit EnemyGanonBgmStop(const InitArg& arg);
    ~EnemyGanonBgmStop() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyGanonBgmStop, 0x30);

}  // namespace uking::behavior
