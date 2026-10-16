#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EnemyGanonBgmStop : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EnemyGanonBgmStop, ksys::act::ai::Behavior)
public:
    explicit EnemyGanonBgmStop(const InitArg& arg);
    ~EnemyGanonBgmStop() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyGanonBgmStop, 0x30);

}  // namespace uking::behavior
