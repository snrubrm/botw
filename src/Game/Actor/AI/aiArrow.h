#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::map {
class Object;
}

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
    // 0x7100468028 (placeholder name): kills the ELink events and fades the SLink events of _f0 and _110.
    void sub_7100468028();
    // 0x7100466c48 (placeholder name): whether the arrow should be released (m40): while flying (発射 / ホーミング /
    // 上空撃ち) beyond 10 * _e8 from the player (XZ) when not visible, or within it when below the ground; after
    // 刺さる / 跳ね返る / 接地 beyond that range.
    bool sub_7100466C48();
    // 0x7100469628 (placeholder name): once _d8 is set (the parent of the actor of _c8 is in the calc state),
    // casts a ground ray along the actor's front axis and returns whether the hit is within 1.3 of height _e0
    // (true without a hit).
    bool sub_7100469628();
    // 0x710046a7bc (placeholder name): the damage of the shot: the connected Weapon's effective attack power plus
    // Arrow ExtraDamage * Weapon::sub_71002EA21C, scaled by the shooter's PlayerBase::m232 rate (depending on tag
    // 0x5e27ef10), times _d04 (1 with m38()).
    f32 sub_710046A7BC();
    // 0x71004693a0 (placeholder name): sticks into the map object _190 (刺さる with StickPos / StickPosDiv /
    // StickActor / StickBodyName), disables the att clients while burning (or _b9), otherwise enables them and
    // follows the object's actor when it has tag 0x170cf1e2; without an object: m40(mActor).
    void sub_71004693A0();
    // 0x7100469074 (placeholder name): lands on the ground (接地): delete timer _6c from the Arrow GParam
    // DeleteTime(WithChemical) (GroundHitTime when 0), clears chemical / LOD / bullet state, then the att clients as
    // in sub_71004693A0.
    void sub_7100469074();
    // 0x71004692fc (placeholder name): the linked weapon's parent actor is the player.
    bool sub_71004692FC();
    // 0x7100467d20 / 0x7100467e24 / 0x7100467f28 (placeholder names): the Weapon the arrow is connected to as a
    // calc parent has `_d54` 1 / `_d54` 2 / bit 12 of its flags.
    bool sub_7100467D20();
    bool sub_7100467E24();
    // 0x7100467b40 (placeholder name): the charge xlink events ("ArrowCharge" until the bow is fully
    // charged unless `complete`, then "ArrowCharge_Complete" and fade the first).
    void sub_7100467B40(bool complete);
    bool sub_7100467F28();
    // 0x710046757c (placeholder names): the connected Weapon has a pending request of type 6 or 7 /
    // returns its `_d0c` (1 without a weapon) / forwards to Weapon::sub_71002EE7E8.
    bool sub_710046757C();
    // 0x710046a9ec (placeholder name): attack flags from the connected Weapon (the pending request's,
    // `_cf4` or `_c20._4`) plus 0x8, 0x200 and 0x8000000 from the weapon / chemical / tag state.
    u32 sub_710046A9EC();
    // 0x7100469958 (placeholder name): the connected Weapon's `_d04` range, scaled by the holder's
    // BowAttackRangeRatio (when m142) and Weapon::sub_71002ED434; 0 without a Weapon.
    f32 sub_7100469958();
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
    sead::Vector3f _dc{0, 0, 0};  // position of the stick target (sub_71004693A0); its height is checked by sub_7100469628
    f32 _e8 = 0;  // range (sub_7100466C48 uses 10 * _e8)
    bool _ec = false;
    Unk_71012419b4 _f0;
    Unk_71012419b4 _110;
    Unk_71012419b4 _130;
    Unk_71012419b4 _150;
    Unk_71012419b4 _170;
    ksys::map::Object* _190;
    ksys::act::BaseProcLink _198;
    ksys::act::BaseProcHandle _1a8;
    Unk_71024013b8 _1b8{mActor, 0x80000bb};
    u32 _1d0 = 0;
    u32 _1d4 = 0;
};
KSYS_CHECK_SIZE_NX150(Arrow, 0x1d8);

}  // namespace uking::ai
