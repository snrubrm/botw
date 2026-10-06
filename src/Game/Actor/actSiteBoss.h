#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/Event/evtResidentEvent.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace ksys::map {
class Rail;
}

namespace uking::act {

class SiteBoss;

// Placeholder name (vtable 0x71023d04f8; inherits DamageCallback's RTTI; `call` 0x71002d03e8).
// SiteBoss::_14c8. `call` reads and clears bits of _30.
// TODO: incomplete.
class Unk_71023d04f8 : public dmg::DamageCallback {
public:
    explicit Unk_71023d04f8(SiteBoss* boss) : mBoss(boss) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    /* 0x28 */ SiteBoss* mBoss;
    /* 0x30 */ sead::BitFlag16 _30;  // read by many SiteBoss AI functions (SiteBoss + 0x14f8)
    /* 0x34 */ u32 _34 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71023d04f8, 0x38);

// Name from the CSV (SiteBoss::*): the four blight Ganons. vtable 0x71023cfef0 (181 slots, no new
// virtuals), RTTI static 0x71025b0a10 (parent: Enemy). Factory 0x71002cf134 (CSV SiteBoss::construct,
// which inlines the ctor): new(0x2988).
// TODO: incomplete. Members are public: AI code reads them directly.
class SiteBoss : public Enemy {
    SEAD_RTTI_OVERRIDE(SiteBoss, Enemy)
public:
    void sub_71002D23F0();
    void sub_71002D2420();
    void sub_71002D2390();
    void sub_71002D22B8();

    explicit SiteBoss(const CreateArg& arg);
    ~SiteBoss() override;

protected:
    bool startPreparingForPreDelete_() override;

public:
    s32 getMaxLife() override;
    void m63() override;
    void initMaybe() override;
    void m73() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void m117(ksys::act::Unk117* arg) override;
    bool isGuard() override;
    bool isGuardJust() override;
    Unk_71025ae680* m178(sead::Heap* heap) override;

    // Placeholder names (CSV x_N where it had one); called by SiteBoss AI functions.
    void x_0();
    void x_1(bool a1, bool a2, bool skip_flag);
    // 0x71002d20b8 (CSV SiteBoss::x_3; declared only; lane1 s25): called with no arguments by
    // LastBossBeamAttackRoot::enter_.
    void sub_71002D20B8();
    void x_5(bool on);
    void x_6(bool on);
    bool sub_71002D33D0(f32 value) const;
    void sub_71002D1B18(bool on);
    void sub_71002D38EC(const sead::SafeString& name);
    void sub_71002D3944();
    // 0x71002d39d8 (declaration only; LastBossNormalWarpRoot::m38).
    void sub_71002D39D8();
    // Declaration only.
    void sub_71002D28BC();
    // Declaration only: SiteBossBowBlowOff::leave_ passes false.
    void sub_71002CFD04(bool on);

    // Called with a possibly null boss: iterate / query the actor parts (Enemy::_1128).
    // x_2 / sub_71002D3498 take the DynamicCast<Enemy> result of their callers.
    static void x_2(Enemy* boss, ksys::act::Actor* sender);
    static void sub_71002D3498(Enemy* boss, ksys::act::Actor* sender);
    static void sub_71002D3624(SiteBoss* boss, const sead::SafeString& part);
    static bool sub_71002D3804(ksys::act::Actor* actor, const sead::SafeString& part);

    /* 0x14c8 */ Unk_71023d04f8 _14c8{this};
    /* 0x1500 */ f32 _1500 = 0;
    /* 0x1504 */ f32 _1504 = 0;
    /* 0x1508 */ f32 _1508 = 0;
    /* 0x150c */ u32 _150c = 0;
    /* 0x1510 */ s32 _1510 = -1;
    /* 0x1514 */ f32 _1514 = 1.0;
    /* 0x1518 */ u32 _1518 = 0;
    /* 0x151c */ s32 _151c = 3;
    /* 0x1520 */ u64 _1520 = 0;
    /* 0x1528 */ u32 _1528 = 0;
    /* 0x152c */ u32 _152c;  // not initialised by the ctor
    /* 0x1530 */ u32 _1530 = 0;
    /* 0x1534 */ s32 _1534 = 12;  // kind (bits 2-3: 4 / 8 compared by getMaxLife and m73)
    /* 0x1538 */ s32 _1538 = 0;  // set from vtable slot 30 (getMaxLife) by m63
    /* 0x153c */ u32 _153c = 0;
    /* 0x1540 */ u8 _1540 = 0;
    /* 0x1544 */ s32 _1544 = 4;
    /* 0x1548 */ u64 _1548 = 0;
    /* 0x1550 */ f32 _1550 = 0;
    /* 0x1554 */ f32 _1554 = 0;  // = 1000.0 by m63
    /* 0x1558 */ sead::BitFlag32 _1558;
    // object with ctor 0x71002cf2ac(this + 0x1560, this) and dtor 0x710066b9b8; its methods are in
    // the TU at 0x710066b9b8 (actUnk_71002cf2ac.cpp). Manages up to 20 bound actors (_1e0) and
    // sends them messages (sub_710066C164; per-actor MesTransceiverId at 0x530 / payload at 0x710,
    // stride 0x18 / 0x28; spin lock at 0xdb0).
    // TODO: incomplete.
    struct Unk_71002cf2ac {
        // 0x710066c164: sends `type` to bound actor `idx` (every bound actor when idx >= 20).
        void sub_710066C164(ksys::act::Actor* owner, ksys::act::BaseProcLink* target,
                            ksys::MessageType type, int idx, u32 flags, ksys::map::Rail* rail);
        // Wrappers of sub_710066C164 (message type in the comment).
        void sub_710066C13C(ksys::act::BaseProcLink* target, int idx);  // 0x800004d
        void sub_710066C518(ksys::act::BaseProcLink* target, int idx);  // 0x800004e
        void sub_710066C540(ksys::act::BaseProcLink* target, int idx);  // 0x800004f
        void sub_710066C568(ksys::act::BaseProcLink* target, int idx);  // 0x8000050
        void sub_710066C590(ksys::act::BaseProcLink* target, int idx);  // 0x8000051
        void sub_710066C5B8(ksys::act::BaseProcLink* target, int idx);  // 0x8000052
        void sub_710066C5E0(ksys::act::BaseProcLink* target, int idx,
                            ksys::map::Rail* rail);  // 0x8000053
        void sub_710066C60C(ksys::act::BaseProcLink* target, int idx);  // 0x8000054
        void sub_710066C70C(ksys::act::BaseProcLink* target, int idx, bool flag,
                            ksys::map::Rail* rail);  // 0x8000055
        void sub_710066CBD4(int idx);                // 0x800005c, no target
        // 0x710066cc64: deletes bound actor `idx`.
        void sub_710066CC64(int idx);
        // 0x710066cbf8: puts bound actor `idx` to sleep (index >= 20 is treated as 0).
        void sub_710066CBF8(int idx);
        // 0x710066bc04 (declared only; placeholder name): deletes every bound actor that is still alive (the links
        // at 0x320 - 0x3a0 and _3b0); called by the destructors of SiteBoss*Root.
        void sub_710066BC04();
        // 0x710066c074: number of bound actors that are in the calc state.
        s32 sub_710066C074();
        // 0x710066c738 (declared only; 200 B): `pos`, then two floats (SiteBossMoveAndAttack passes 0.8 / 0.4); looks for a
        // free actor handle at 0xa0 + 0x10 * i and continues in 0x710066c800.
        void sub_710066C738(sead::Vector3f* pos, f32 a, f32 b);
        // 0x710066d9b8 (declaration only; 124 B): if the message of bound actor `idx` is still pending, sends it and returns true.
        bool sub_710066D9B8(s32 idx);
        // 0x710066dabc (declaration only).
        void sub_710066DABC(ksys::act::BaseProc* proc, s32 idx);
        void sub_710066D708(s32 idx);
        // 0x710066db98: replaces the actor linked at _360 with `proc` (deleting the old one).
        void sub_710066DB98(ksys::act::BaseProc* proc, int idx);
        // 0x710066de24: &_3b0[idx] (out-of-line).
        ksys::act::BaseProcLink* sub_710066DE24(int idx);

        // 0x710066c634: sub_710066C164(.., 0x8000054, .., flags = 1) + the same message to the
        // actors in _3b0.
        void sub_710066C634(ksys::act::BaseProcLink* target, int idx);

        // Message payload (sendMessage's void* argument); 0x710066c164 fills it.
        struct Payload {
            ksys::act::Actor* owner;
            ksys::act::BaseProcLink* target;
            sead::Vector3f pos;  // average of the rail points (zero without a rail)
            s32 idx;
            u32 flags;
        };

        /* 0x000 */ ksys::act::Actor* mOwner;
        /* 0x008 */ u8 _8[0x9c - 0x8];
        /* 0x09c */ u32 _9c;  // bit idx: bound actor idx (cleared by SiteBossChemicalProjectile)
        /* 0x0a0 */ u8 _a0[0x1e0 - 0xa0];
        /* 0x1e0 */ sead::SafeArray<ksys::act::BaseProcLink, 20> _1e0;
        /* 0x320 */ u8 _320[0x360 - 0x320];
        /* 0x360 */ ksys::act::BaseProcLink _360;
        /* 0x370 */ u8 _370[0x3b0 - 0x370];
        /* 0x3b0 */ sead::SafeArray<ksys::act::BaseProcLink, 24> _3b0;
        /* 0x530 */ u8 _530[0x710 - 0x530];  // MesTransceiverId x 20 (stride 0x18)
        /* 0x710 */ Payload _710[24];
        /* 0xad0 */ u8 _ad0[0xdb0 - 0xad0];
        /* 0xdb0 */ sead::JobQueueLock _db0;
    };
    /* 0x1560 */ Unk_71002cf2ac _1560;
    /* 0x2318 */ sead::Vector3f _2318;  // home position (m63)
    /* 0x2324 */ u8 _2324[0x2328 - 0x2324];
    /* 0x2328 */ sead::SafeString _2328;
    /* 0x2338 */ u64 _2338 = 0;
    /* 0x2340 */ u32 _2340 = 0;
    /* 0x2348 */ u64 _2348 = 0;
    /* 0x2350 */ u32 _2350 = 0;
    /* 0x2358 */ u64 _2358 = 0;
    /* 0x2360 */ u32 _2360 = 0;
    /* 0x2368 */ u64 _2368 = 0;
    /* 0x2370 */ u32 _2370 = 0;
    /* 0x2374 */ u32 _2374;  // not initialised by the ctor
    /* 0x2378 */ u8 _2378 = 0;
    /* 0x2379 */ u8 _2379 = 0;
    /* 0x237a */ u8 _237a = 0;
    /* 0x237b */ u8 _237b;  // not initialised by the ctor
    /* 0x237c */ u32 _237c = 0;
    /* 0x2380 */ u32 _2380 = 0;
    /* 0x2384 */ u32 _2384 = 0;
    /* 0x2388 */ u32 _2388 = 0;
    // object with ctor 0x7100722420(this + 0x2390, this) and dtor 0x71007224cc
    /* 0x2390 */ u8 _2390[0x25e8 - 0x2390];
    /* 0x25e8 */ ksys::evt::ResidentEvent _25e8;
    /* 0x27b8 */ ksys::evt::ResidentEvent _27b8;
};
KSYS_CHECK_SIZE_NX150(SiteBoss, 0x2988);

}  // namespace uking::act

// 0x71002d02ac / 0x71002d0310 (CSV names; namespace unknown): number of Die_PGanon* / Clear_Remains*
// game data flags that are set (0-4).
int getNumberOfDeadBlights();
int getNumberOfClearedRemains();
