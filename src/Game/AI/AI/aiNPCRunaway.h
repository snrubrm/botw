#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "Game/Actor/actNPC.h"
#include "Game/AI/aiLockedProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class NPCRunaway : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCRunaway, ksys::act::ai::Ai)
public:
    explicit NPCRunaway(const InitArg& arg);
    ~NPCRunaway() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71004dd654: finds the first NPC among the linked map objects and acquires it into `link` (the same body as NPCConfrontEnemy::sub_71004C69B0)
    bool sub_71004DD654(ksys::act::BaseProcLink* link);
    // 0x71004de978: the first entry of the third awareness sensor whose actor is targeting this actor; its link goes to `link` (if given)
    bool sub_71004DE978(ksys::act::BaseProcLink* link);
    // 0x71004deba0: false if any linked actor is closer than ReleaseDistance
    bool sub_71004DEBA0();
    // 0x71004df1d0: starts the "立ち上がる" child (timer _90[4] = StandingTime * 30)
    void sub_71004DF1D0();
    // 0x71004df0b0: starts the "気絶前振り向き" child (timer _90[5] = 600)
    void sub_71004DF0B0(const sead::Vector3f& pos);
    // 0x71004dec8c: starts the "お礼" child (timer _90[2] = 5)
    void sub_71004DEC8C();
    // 0x71004dea74: starts the "逃走" child
    void sub_71004DEA74();
    // 0x71004dd700: starts the "待機" child (timer _90[1] = 300)
    void sub_71004DD700();
    // static_param at offset 0x38
    const float* mReleaseDistance_s{};
    // static_param at offset 0x40
    const float* mCorneredDistance_s{};
    // static_param at offset 0x48
    const float* mStandRateTime_s{};
    // static_param at offset 0x50
    const float* mStandingTime_s{};
    // dynamic_param at offset 0x58
    int* mTerrorLevel_d{};
    // dynamic_param at offset 0x60
    int* mTerrorLayer_d{};
    // dynamic_param at offset 0x68
    bool* mIsReturnFromDemo_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetVel_d{};
    act::NPC* _80{};
    s32 _88 = 30;
    bool _8c = false;
    bool _8d = false;
    // Six timers (the functions of the "escape" states use the entries 1 / 2 / 4 / 5); zeroed together by one memset.
    ksys::Timer _90[6];
    ksys::act::BaseProcLink _d8;
    sead::SafeArray<ksys::act::BaseProcLink, 10> _e8;
    LockedProcLinkMaybe _188;
};
KSYS_CHECK_SIZE_NX150(NPCRunaway, 0x1e0);

}  // namespace uking::ai
