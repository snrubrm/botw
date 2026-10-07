#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class Arrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Arrow, ksys::act::ai::Ai)
public:
    explicit Arrow(const InitArg& arg);
    ~Arrow() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual bool m38();
    virtual void m39();
    virtual void m40(ksys::act::BaseProc* proc);

    void sub_7100463940();
    // 0x7100463f68 / 0x71004640b0 (placeholder names): 0x463f68 clears the Bullet's flag 0x80, starts the chemical of the
    // arrow (when it has one) and changes to "所持前"; 0x4640b0 is declared only (not decompiled).
    void sub_7100463F68();
    void sub_71004640B0();
    // 0x71004682cc: kills the ELink event of _170 (if it is still the one that was emitted).
    void sub_71004682CC();
    // 0x71004692fc (placeholder name): the linked weapon's parent actor is the player.
    bool sub_71004692FC();
    // 0x7100467d20 / 0x7100467e24 / 0x7100467f28 (placeholder names): the Weapon the arrow is connected to as a
    // calc parent has `_d54` 1 / `_d54` 2 / bit 12 of its flags.
    bool sub_7100467D20();
    bool sub_7100467E24();
    bool sub_7100467F28();
    // 0x710046757c (placeholder names): the connected Weapon has a pending request of type 6 or 7 /
    // returns its `_d0c` (1 without a weapon) / forwards to Weapon::sub_71002EE7E8.
    bool sub_710046757C();
    s32 sub_710046ABA8();
    bool sub_710046ACA4(ksys::act::BaseProcLink* out);
    // 0x7100469850 (placeholder name): makes the arrow's body dynamic again and bounces ("跳ね返る").
    void sub_7100469850();
    void spawnElectricWaterBall();  // CSV name (aiArrowSpawnElectricWaterBall)

protected:
    sead::Vector3f _38{0, 0, 0};
    u32 _44 = 0;
    u64 _48 = 0;
    sead::SafeString _50 = sead::SafeString::cEmptyString;
    ksys::Timer _60{0, 0};
    ksys::Timer _6c{0, 0};
    ksys::Timer _78{0, 0};
    ksys::Timer _84{0.1f, 0.1f};
    ksys::Timer _90{0, 0};
    ksys::phys::ContactLayer _9c = ksys::phys::ContactLayer::EntityNoHit;
    const f32* mStickTime_s = nullptr;
    const f32* mGroundHitTime_s = nullptr;
    const s32* mKillFireTime_s = nullptr;
    bool _b8 = false;
    bool _b9 = false;
    bool _ba = false;
    bool _bb = false;
    bool _bc = false;
    bool _bd = false;
    bool _be = false;
    f32 _c0 = 1.0f;
    ksys::act::BaseProcLink _c8;
    bool _d8 = false;
    u32 _dc = 0;
    u32 _e0 = 0;
    u32 _e4 = 0;
    u32 _e8 = 0;
    bool _ec = false;
    Unk_71012419b4 _f0;
    Unk_71012419b4 _110;
    Unk_71012419b4 _130;
    Unk_71012419b4 _150;
    Unk_71012419b4 _170;
    void* _190;
    ksys::act::BaseProcLink _198;
    ksys::act::BaseProcHandle _1a8;
    Unk_71024013b8 _1b8{mActor, 0x80000bb};
    u32 _1d0 = 0;
    u32 _1d4 = 0;
};
KSYS_CHECK_SIZE_NX150(Arrow, 0x1d8);

}  // namespace uking::ai
