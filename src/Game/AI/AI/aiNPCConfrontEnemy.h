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

class NPCConfrontEnemy : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCConfrontEnemy, ksys::act::ai::Ai)
public:
    explicit NPCConfrontEnemy(const InitArg& arg);
    ~NPCConfrontEnemy() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71004c8ddc: starts the "気絶前振り向き" child (timer _98[1] = 600)
    void sub_71004C8DDC(const sead::Vector3f& pos);
    // 0x71004c82d0: starts the "お礼" child (timer _98[0] = 5)
    void sub_71004C82D0();
    // 0x71004c83dc: false if any linked actor is closer than ReleaseDistance
    bool sub_71004C83DC();
    // static_param at offset 0x38
    const float* mReleaseDistance_s{};
    // static_param at offset 0x40
    const float* mReleaseTime_s{};
    // static_param at offset 0x48
    const float* mRewardDistance_s{};
    // static_param at offset 0x50
    const float* mTerrorDistAfterPlayerRescue_s{};
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
    // map_unit_param at offset 0x80
    const float* mTerritoryArea_m{};
    act::NPC* _88{};
    u32 _90 = 0;
    bool _94 = false;
    // Five timers (the confront / thank / faint states use the entries 0 and 1); zeroed together by one memset.
    ksys::Timer _98[5];
    ksys::act::BaseProcLink _d8;
    sead::SafeArray<ksys::act::BaseProcLink, 10> _e8;
    LockedProcLinkMaybe _188;
};
KSYS_CHECK_SIZE_NX150(NPCConfrontEnemy, 0x1e0);

}  // namespace uking::ai
