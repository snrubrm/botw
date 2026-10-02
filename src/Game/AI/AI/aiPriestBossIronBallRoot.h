#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadEnum.h>
#include "Game/AI/AI/aiPriestBossMode.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class PriestBossIronBallRoot : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossIronBallRoot, PriestBossMode)
public:
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9)

    explicit PriestBossIronBallRoot(const InitArg& arg);
    ~PriestBossIronBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38(bool for_player);
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43(s32 command, const sead::Vector3f& base_pos, s32 wait_time);

    void sub_7100520874(ksys::act::Unk_71006dc134* arg);
    void sub_71005221EC(bool value);

protected:
    // static_param at offset 0x40
    const int* mAttackPower_s{};
    // static_param at offset 0x48
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x50
    const int* mAtMinDamage_s{};
    // static_param at offset 0x58
    const int* mMagneLightningTime_s{};
    // map_unit_param at offset 0x60
    sead::SafeString mActorName_m{};
    /* 0x070 */ ksys::act::BaseProcLink _70;  // the actor created from ActorName
    /* 0x080 */ sead::BitFlag16 _80;
    /* 0x084 */ ksys::Timer _84;
    /* 0x090 */ Unk_7102450be8 _90;
    /* 0x120 */ Unk_7102450588 _120;
    /* 0x170 */ Unk_71024508b8 _170;
    /* 0x1d0 */ Unk_7102409958 _1d0{mActor, 0x80000da};
    /* 0x210 */ Unk_7102413c08 _210{mActor, 0x80000de};
    /* 0x238 */ ksys::act::BaseProcLink _238;
    /* 0x248 */ sead::Delegate1<PriestBossIronBallRoot, ksys::act::Unk_71006dc134*> _248{
        this, &PriestBossIronBallRoot::sub_7100520874};
    /* 0x268 */ f32 _268 = -1.0f;  // mass of the main body
    /* 0x26c */ bool _26c;
    /* 0x270 */ f32 _270 = 0;
    /* 0x274 */ f32 _274 = 0;
    /* 0x278 */ f32 _278 = 0;
    /* 0x27c */ u32 _27c = 0;
};
KSYS_CHECK_SIZE_NX150(PriestBossIronBallRoot, 0x280);

}  // namespace uking::ai
