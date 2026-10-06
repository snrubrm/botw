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
    void calc_() override;
    void loadParams_() override;

    bool sub_71003B9914();

protected:
    // 0x71003ba1c4 (declared only): searches a rideable horse into `link` (false without one).
    bool sub_71003BA1C4(ksys::act::BaseProcLink* link);
    void sub_71003B9624();
    void sub_71003B977C();
    void sub_71003B9A48();
    // 0x71003ba088 (placeholder name)
    void changeToStraightMove();

    struct Params {
        // static_param at offset 0x38
        const int* mRepathTime_s{};
        // static_param at offset 0x40
        const float* mSearchDist_s{};
        // static_param at offset 0x48
        const float* mRideRadius_s{};
        // static_param at offset 0x50
        const bool* mNoWeaponRiding_s{};
    };
    Params mParams;
    ksys::act::BaseProcLink _58;
    sead::FixedRingBuffer<ksys::act::BaseProcLink, 8> _68;
    ksys::Timer _100;
    ksys::act::BaseProcLink _110;
};
KSYS_CHECK_SIZE_NX150(EnemySearchHorse, 0x120);

}  // namespace uking::ai
