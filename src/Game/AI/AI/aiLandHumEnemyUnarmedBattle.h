#pragma once

#include <container/seadObjList.h>
#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumEnemyUnarmedBattle : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(LandHumEnemyUnarmedBattle, UnarmedEnemySearch)
public:
    explicit LandHumEnemyUnarmedBattle(const InitArg& arg);
    ~LandHumEnemyUnarmedBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m35(const sead::Vector3f& target) override;
    void m36() override {}
    void m42() override;

    // 0x71004703e8 (placeholder name): tells the actor of _118 that we let go (0x80000c3), unlinks it from the Enemy
    // and resets _118.
    void sub_71004703E8();
    // 0x710046fd74 (placeholder name)
    void changeToAvoidDanger();
    // 0x710046fa70 (placeholder name)
    void changeToFindItem();
    // 0x710046fc10 (declaration only; placeholder name): called by m35.
    void sub_710046FC10();
    // 0x710046ec44 (placeholder name; CSV landHumEnemyStuff): tells the actor of _118 that we let go and starts the
    // "戦闘" child.
    void changeToBattle();
    // 0x7100470ed4 (placeholder name): true if `link` is already handled or its actor is within the reach distance.
    bool sub_7100470ED4(ksys::act::BaseProcLink& link) const;
    // 0x7100470d54 (placeholder name): the "Grab" attention client of the actor of `link` accepts a grab at the actor's
    // matrix moved by AttOffset (scaled by the actor's scale) within GrabCheckRadius.
    bool sub_7100470D54(ksys::act::BaseProcLink* link, bool a2);

protected:
    struct Params {
        // static_param at offset 0x68
        const int* mEquipItemSearchIdx_s{};
        // static_param at offset 0x70
        const int* mLostTimer_s{};
        // static_param at offset 0x78
        const float* mSearchWeaponDist_s{};
        // static_param at offset 0x80
        const float* mSearchBaseWeaponDist_s{};
        // static_param at offset 0x88
        const float* mSearchObjectDist_s{};
        // static_param at offset 0x90
        const float* mSearchWeaponTargetDist_s{};
        // static_param at offset 0x98
        const float* mSearchBowTargetDist_s{};
        // static_param at offset 0xa0
        const float* mGrabCheckRadius_s{};
        // static_param at offset 0xa8
        const float* mItemChaseableSpd_s{};
        // static_param at offset 0xb0
        const sead::Vector3f* mAttOffset_s{};
        // static_param at offset 0xb8
        const bool* mCanGrabHeavy_s{};
        // static_param at offset 0xc0
        const int* mRepathTime_s{};
        // static_param at offset 0xc8
        const float* mExplosivesAvoidDist_s{};
        // static_param at offset 0xd0
        const float* mExplosivesAvoidSpeed_s{};
        // static_param at offset 0xd8
        const float* mExplosivesAvoidAng_s{};
        // static_param at offset 0xe0
        const float* mLostVMin_s{};
        // static_param at offset 0xe8
        const float* mLostVMax_s{};
        // static_param at offset 0xf0
        const float* mLostRange_s{};
        // static_param at offset 0xf8
        const float* mOnCoHitAllowGrabAngle_s{};
        // dynamic_param at offset 0x100
        sead::Vector3f* mTargetPos_d{};
    };
    Params mParams;
    ksys::act::BaseProcLink _108;
    ksys::act::BaseProcLink _118;
    ksys::act::BaseProcLink _128;
    ksys::act::BaseProcLink _138;
    s32 _148 = -1;
    sead::FixedObjList<ksys::act::Unk_7100d78e50, 8> _150;
    u64 _780 = 0;
    f32 _788 = -1.0f;
    s32 _78c = 0;
    u64 _790 = 0;
    bool _798 = true;
    bool _799 = true;
};
KSYS_CHECK_SIZE_NX150(LandHumEnemyUnarmedBattle, 0x7a0);

}  // namespace uking::ai
