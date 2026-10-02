#pragma once

#include <container/seadRingBuffer.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class EnemySearchHorse : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemySearchHorse, ksys::act::ai::Ai)
public:
    explicit EnemySearchHorse(const InitArg& arg);
    ~EnemySearchHorse() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool sub_71003B9914();

protected:
    // static_param at offset 0x38
    const int* mRepathTime_s{};
    // static_param at offset 0x40
    const float* mSearchDist_s{};
    // static_param at offset 0x48
    const float* mRideRadius_s{};
    // static_param at offset 0x50
    const bool* mNoWeaponRiding_s{};
    ksys::act::BaseProcLink _58;
    sead::FixedRingBuffer<ksys::act::BaseProcLink, 8> _68;
    ksys::Timer _100;
    ksys::act::BaseProcLink _110;
};
KSYS_CHECK_SIZE_NX150(EnemySearchHorse, 0x120);

}  // namespace uking::ai
