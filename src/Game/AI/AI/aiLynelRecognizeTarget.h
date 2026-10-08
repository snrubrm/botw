#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act::acc {
class PlayerOrEnemy;
}

namespace uking::ai {

class LynelRecognizeTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelRecognizeTarget, ksys::act::ai::Ai)
public:
    explicit LynelRecognizeTarget(const InitArg& arg);
    ~LynelRecognizeTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x710049708c (placeholder name)
    void changeToReturn();
    // 0x7100496894 (placeholder name)
    void changeToNotice();
    // 0x71004966c4 (placeholder name)
    void changeToAlert();
    // 0x71004967ac (placeholder name)
    void changeToObserve();
    // 0x7100496d84 (placeholder name)
    void changeToStartBattle();
    // 0x7100497164 (placeholder name)
    void changeToForceStartBattle();
    // 0x7100497be8 (placeholder name): `actor` has a weapon (not of type 4) for which PlayerOrEnemy::sub_7100009AA8 is false.
    bool sub_7100497BE8(ksys::act::acc::PlayerOrEnemy* actor);
    // 0x71004963f8 (CSV placeholder, declared only): update _f0 from sub_710049759C (kept when
    // `flag & 1` and larger); blocked on checkIsFooledByDisguise's accessor/PlayerBase paradox.
    void sub_71004963F8(u32 flag);
    // 0x7100496564 (CSV lynelRecogniseTargetStuff): set flag 0x2000000, change to 戦闘, set _e84 bit.
    void sub_7100496564();

protected:
    // static_param at offset 0x38
    const int* mAttensionStartPoint_s{};
    // static_param at offset 0x40
    const int* mObserveEndPoint_s{};
    // static_param at offset 0x48
    const int* mDrawnWeaponPoint_s{};
    // static_param at offset 0x50
    const int* mWeaponAimPoint_s{};
    // static_param at offset 0x58
    const int* mAttackPoint_s{};
    // static_param at offset 0x60
    const int* mDashPoint_s{};
    // static_param at offset 0x68
    const int* mAppPoint_s{};
    // static_param at offset 0x70
    const int* mHorseRidePoint_s{};
    // static_param at offset 0x78
    const int* mDamagePoint_s{};
    // static_param at offset 0x80
    const int* mTrickedMaskPoint_s{};
    // static_param at offset 0x88
    const int* mBombPoint_s{};
    // static_param at offset 0x90
    const int* mAimPoint_s{};
    // static_param at offset 0x98
    const int* mNearDistPoint_s{};
    // static_param at offset 0xa0
    const int* mMiddleDistPoint_s{};
    // static_param at offset 0xa8
    const int* mTiredTime_s{};
    // static_param at offset 0xb0
    const int* mTiredPoint_s{};
    // static_param at offset 0xb8
    const int* mForceBattleStartTime_s{};
    // static_param at offset 0xc0
    const float* mNearDistance_s{};
    // static_param at offset 0xc8
    const float* mFarDistance_s{};
    // static_param at offset 0xd0
    const float* mAimAngle_s{};
    // map_unit_param at offset 0xd8
    const bool* mIsNearCreate_m{};
    // aitree_variable at offset 0xe0
    int* mLynelAIFlags_a{};
    // aitree_variable at offset 0xe8
    int* mLynelAreaAlarmPoint_a{};
    s32 _f0{};
    bool _f4{};
    f32 _f8 = 0;
    // An unidentified actor-time-scaled timer object {Actor*, f32 value, ...} (methods 0x7100d3bc4c, ...)
    ksys::act::Actor* _100 = mActor;
    f32 _108 = 0;
    u32 _10c;
    // Same type as _100
    ksys::act::Actor* _110 = mActor;
    f32 _118 = 0;
    u32 _11c;
};

}  // namespace uking::ai
