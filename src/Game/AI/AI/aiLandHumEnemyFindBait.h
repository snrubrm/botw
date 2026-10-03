#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class LandHumEnemyFindBait : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(LandHumEnemyFindBait, UnarmedEnemySearch)
public:
    explicit LandHumEnemyFindBait(const InitArg& arg);
    ~LandHumEnemyFindBait() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x710045ed68: starts the "気づき" child towards the bait (TargetPos = its position, or zero).
    void sub_710045ED68();
    // 0x710045f29c (placeholder name)
    void sub_710045F29C();

protected:
    // static_param at offset 0x68
    const int* mRepathTime_s{};
    // dynamic_param at offset 0x70
    ksys::act::BaseProcLink* mTargetBait_d{};
    // static_param at offset 0x78
    const bool* mIsDropWeapon_s{};
    // static_param at offset 0x80
    const bool* mIsValidForceNeck_s{};
    // dynamic_param at offset 0x88
    bool* mIsNotice_d{};
    ksys::Timer _90{0, 0};
    ksys::act::BaseProcLink _a0;
    f32 _b0 = 0;
    s32 _b4 = 0;
    s32 _b8 = 0;
    f32 _bc = 0;
    f32 _c0 = 0;
};
KSYS_CHECK_SIZE_NX150(LandHumEnemyFindBait, 0xc8);

}  // namespace uking::ai
