#pragma once

#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71025b2aa8.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/Event/evtResidentEvent.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace ksys::act {
class ActorLinkConstDataAccess;
class InstParamPack;
}
namespace ksys::map {
class Rail;
}

namespace uking::act {

class SiteBoss;

// Placeholder name (vtable 0x71023d04f8; inherits DamageCallback's RTTI; `call` 0x71002d03e8).
// SiteBoss::_14c8. `call` reads and clears bits of _30.
// TODO: incomplete.
class Unk_71023d04f8 : public act::DamageCallback {
public:
    explicit Unk_71023d04f8(SiteBoss* boss) : mBoss(boss) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) override;

    /* 0x28 */ SiteBoss* mBoss;
    /* 0x30 */ sead::BitFlag16 _30;  // read by many SiteBoss AI functions (SiteBoss + 0x14f8)
    /* 0x34 */ s32 _34 = 0;  // compared as an s32 with SiteBoss::_1500 (SiteBossBowBlowOff::m36)
};
KSYS_CHECK_SIZE_NX150(Unk_71023d04f8, 0x38);

// Placeholder name (ctor 0x7100722420(this + 0x2390, boss), dtor 0x71007224cc; size 0x258): SiteBoss::_2390. Wraps a
// Unk_71025b2aa8Data at +0x240. TODO: incomplete (not modelled).
struct Unk_7100722420 {
    // 0x7100722420 (declared only).
    explicit Unk_7100722420(ksys::act::Actor* actor);
    // 2026-10-07: original 0x71007224cc closes the embedded dialog at +0x240.
    ~Unk_7100722420();
    // 0x71007224d4 (declared only; lane5 s5): forwards to the Unk_71025b2aa8Data at +0x240 (sub_7100721EFC).
    void sub_71007224D4();
    // 2026-10-07: original 0x71007224dc receives three signed configuration values.
    void sub_71007224DC(s32 a1, s32 a2, s32 a3);
    // 722764 updates this dialog owner; SiteBoss::m73 passes its existing member.
    void sub_7100722764();
    // 0x7100723418: enables the pending dialog after the given delay.
    void sub_7100723418(f32 delay);

    // 2026-10-07: ctor 0x7100722420 stores its Actor* argument here, not a vtable.
    ksys::act::Actor* _0;
    /* 0x08 */ bool _8;  // cleared by SiteBossDie::leave_
    u8 _9[0x23c - 9];
    /* 0x23c */ f32 _23c;
    /* 0x240 */ Unk_71025b2aa8Data _240;
};
KSYS_CHECK_SIZE_NX150(Unk_7100722420, 0x258);

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
    // 0x71002d223c (declared only; lane5 s5): called by SiteBossSwordChemicalPlus::sub_7100268FCC.
    void sub_71002D223C();
    // lane4 s46 (placeholder names): 0x71002d2a5c: AS list x_2(0x42, bit, on, false). 0x71002d2a1c: AS list
    // goLimpFromHeadShotMaybe(0x2f, name, 0).
    void sub_71002D2A5C(s32 bit, bool on);
    void sub_71002D2A1C(const char* name);

    explicit SiteBoss(const CreateArg& arg);
    ~SiteBoss() override;
    // 0x71002cf134 (CSV SiteBoss::construct; the ctor is inlined there).
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

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
    // 0x71002d3740 (CSV x; SiteBossDie::enter_ calls it first): deleteLater on every part actor in its calc state with tag 0xb0c0f649, then
    // _1560.sub_710066BC04(). 0x71002d38f8 (CSV x_0): unloads the resident events _25e8 / _27b8.
    void x();
    void x_0();
    // CSV names. 0x71002d27a4: loads the HP demo resident events _25e8 / _27b8 (event `event`, entry points `entry1` /
    // `entry2`) once (bit 25 of _1558). 0x71002d24f8: calls one of them when the life drops to `rate` of the max.
    void playHPDemoIfNeededInitEvents(const sead::SafeString& event, const sead::SafeString& entry1,
                                      const sead::SafeString& entry2);
    bool playHPDemoIfNeeded(f32 rate, const sead::SafeString& event, const sead::SafeString& entry1,
                            const sead::SafeString& entry2);
    // 0x71002d2958 (placeholder name): puts the untagged part actors to sleep, then _1560.sub_710066D094().
    void sub_71002D2958();
    void x_1(bool a1, bool a2, bool skip_flag);
    // 0x71002d20b8 (CSV SiteBoss::x_3; lane1 s25): fades the Elec_Sword / Elec_Shield effects (bits 4 / 5 of _1558);
    // called with no arguments by LastBossBeamAttackRoot::enter_.
    void sub_71002D20B8();
    // 0x71002d1fd4 (declared only; placeholder name, 228 B): fades the xlink event of the handle at +0x2348.
    void sub_71002D1FD4();
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
    void sub_71002D1740(s32 value);
    bool sub_71002D2AE0(f32 rate, s32 a, s32 b);
    static SiteBoss* sub_71002D3B20(const ksys::act::ActorLinkConstDataAccess& accessor);
    static bool sub_71002D3A68(const ksys::act::ActorLinkConstDataAccess& accessor);
    static bool sub_71002D3C14(const ksys::act::ActorLinkConstDataAccess& accessor);
    // Declaration only: SiteBossBowBlowOff::leave_ passes false.
    void sub_71002CFD04(bool on);

    // Called with a possibly null boss: iterate / query the actor parts (Enemy::_1128).
    // x_2 / sub_71002D3498 take the DynamicCast<Enemy> result of their callers.
    static void x_2(Enemy* boss, ksys::act::Actor* sender);
    static void sub_71002D3498(Enemy* boss, ksys::act::Actor* sender);
    // 0x71002d355c (declared only; placeholder name, 200 B): works on the part `part` of `boss` (null-checked).
    static void sub_71002D355C(Enemy* boss, ksys::act::Actor* sender, const sead::SafeString& part);
    static void sub_71002D3624(SiteBoss* boss, const sead::SafeString& part);
    static bool sub_71002D3804(ksys::act::Actor* actor, const sead::SafeString& part);

    /* 0x14c8 */ Unk_71023d04f8 _14c8{this};
    /* 0x1500 */ s32 _1500 = 0;
    /* 0x1504 */ s32 _1504 = 0;
    /* 0x1508 */ s32 _1508 = 0;
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
    /* 0x1548 */ f32 _1548 = 0;  // read by SiteBossSwordAttackRoot::sub_7100596400
    /* 0x154c */ f32 _154c = 0;
    /* 0x1550 */ f32 _1550 = 0;
    /* 0x1554 */ f32 _1554 = 0;  // = 1000.0 by m63
    /* 0x1558 */ sead::BitFlag32 _1558;
    // object with ctor 0x71002cf2ac(this + 0x1560, this) and dtor 0x710066b9b8; its methods are in
    // the TU at 0x710066b9b8 (actUnk_71002cf2ac.cpp). Manages up to 20 bound actors (_1e0) and
    // sends them messages (sub_710066C164; per-actor MesTransceiverId at 0x530 / payload at 0x710,
    // stride 0x18 / 0x28; spin lock at 0xdb0).
    // TODO: incomplete.
    struct Unk_71002cf2ac {
        // 0x71002cf2ac (declared only).
        explicit Unk_71002cf2ac(SiteBoss* boss);
        // 2026-10-07: real original D1 0x710066b9b8 called by SiteBoss::~SiteBoss.
        ~Unk_71002cf2ac();
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
        // 0x710066cd7c (declared only): stores `value` at +0x94 and deletes every bound actor (`_1e0`).
        void sub_710066CD7C(u32 value);
        // 0x710066cc64: deletes bound actor `idx`.
        void sub_710066CC64(int idx);
        // 0x710066cbf8: puts bound actor `idx` to sleep (index >= 20 is treated as 0).
        void sub_710066CBF8(int idx);
        // 0x710066df44 (placeholder name): the next bound-actor index after `index`
        // stepping by `step` (wrapping within 0-19, skipping `skip`), stopping at the first slot whose
        // link has a proc (at most 20 tries).
        s32 sub_710066DF44(s32 index, s32 step, s32 skip);
        // 0x710066bc04 (declared only; placeholder name): deletes every bound actor that is still alive (the links
        // at 0x320 - 0x3a0 and _3b0); called by the destructors of SiteBoss*Root.
        void sub_710066BC04();
        // 0x710066c028: deletes every bound actor handle in _a0 and clears _8.
        void sub_710066C028();
        // 0x710066ccd0 (placeholder name): the same handle cleanup, then deletes the actor behind every
        // link in _1e0.
        void sub_710066CCD0();
        // 0x710066da34: binds `proc` to link `idx` and copies its message transceiver id.
        void sub_710066DA34(ksys::act::Actor* proc, s32 idx);
        // 0x710066dc34: binds `proc` to one of the four _370 links, deleting the old actor first.
        void sub_710066DC34(ksys::act::Actor* proc, s32 idx);
        // 0x710066bfec: requests the named actor in the existing handle slot.
        bool sub_710066BFEC(s32 index, const char* name, ksys::act::InstParamPack* params,
                           bool flag);
        // 0x710066d094 (placeholder name): called by SiteBoss::sub_71002D2958.
        void sub_710066D094();
        // 0x710066d3a4 (declared only; placeholder name): the bound-actor update and respawn tick.
        void sub_710066D3A4(f32 dt);
        // 0x710066c074: number of bound actors that are in the calc state.
        s32 sub_710066C074();
        // 0x710066c738: `pos`, then two floats (SiteBossMoveAndAttack passes 0.8 / 0.4); looks for a
        // free actor handle at 0xa0 + 0x10 * i and continues in 0x710066c800.
        void sub_710066C738(sead::Vector3f* pos, f32 a, f32 b);
        // 0x710066c800 (declaration only; 980 B): the continuation of sub_710066C738 for handle `index`.
        void sub_710066C800(sead::Vector3f* pos, s32 index, f32 a, f32 b);
        // 0x710066d9b8 (declaration only; 124 B): if the message of bound actor `idx` is still pending, sends it and returns true.
        bool sub_710066D9B8(s32 idx);
        // 0x710066dabc (declaration only).
        void sub_710066DABC(ksys::act::BaseProc* proc, s32 idx);
        // 0x710066dd10 (declared only; placeholder name): binds `proc` to one of the _3b0 links.
        void sub_710066DD10(ksys::act::Actor* proc, int idx);
        // 0x710066de3c (declared only; placeholder name): picks a bound-actor link that has a proc.
        ksys::act::BaseProcLink* sub_710066DE3C(s32 start);
        void sub_710066D708(s32 idx);
        // 0x710066db98: replaces the actor linked at _360 with `proc` (deleting the old one).
        void sub_710066DB98(ksys::act::BaseProc* proc, int idx);
        // 0x710066de24: &_3b0[idx] (out-of-line).
        ksys::act::BaseProcLink* sub_710066DE24(int idx);
        // 0x710066de04 / 0x710066ddec / 0x710066de0c (placeholder names): `&_360`, `&_320[idx]`, `&_370[idx]`.
        ksys::act::BaseProcLink* sub_710066DE04(int unused);
        ksys::act::BaseProcLink* sub_710066DDEC(int idx);
        ksys::act::BaseProcLink* sub_710066DE0C(int idx);

        // 0x710066c634: sub_710066C164(.., 0x8000054, .., flags = 1) + the same message to the
        // actors in _3b0.
        void sub_710066C634(ksys::act::BaseProcLink* target, int idx);

        // 0x710066cdf8 (declared only; 668 B): binds / spawns the actor `idx` at the pose `mtx`.
        struct SpawnArg {
            u64 _0 = 0;
            sead::Vector3f pos;
            f32 _14 = 0;
            bool _18 = false;
            bool _19 = false;
            bool _1a = false;
            bool _1b = false;
        };
        void sub_710066CDF8(ksys::act::Actor* owner, const sead::Matrix34f& mtx, int idx,
                            const SpawnArg& arg);

        // Message payload (sendMessage's void* argument); 0x710066c164 fills it.
        struct Payload {
            ksys::act::Actor* owner = nullptr;
            ksys::act::BaseProcLink* target = nullptr;
            sead::Vector3f pos = sead::Vector3f::zero;  // average of the rail points (zero without a rail)
            s32 idx = 0;
            u32 flags = 0;
        };

        // 0x710066cdf8 fills this for bound actor `idx` once its link is live.
        struct SpawnInfo {
            ksys::act::Actor* owner = nullptr;
            sead::Vector3f pos;
            f32 _14 = 0;
            bool _18 = false;
            bool _19 = false;
            bool _1a = false;
            bool _1b = false;
            u8 _1c[4] = {};  // padding to the 0x20 stride
        };
        static_assert(sizeof(SpawnInfo) == 0x20);

        /* 0x000 */ ksys::act::Actor* mOwner = nullptr;
        // 0x008-0x094: fire ball spawn parameters (SiteBossLswordFirstCreateFBall::enter_).
        /* 0x008 */ bool _8 = false;
        /* 0x00c */ f32 _c = 0;
        /* 0x010 */ f32 _10 = 0;  // spawn retry timer
        /* 0x018 */ sead::FixedSafeString<64> _18;  // actor name
        /* 0x070 */ s32 _70 = 0;
        /* 0x074 */ f32 _74 = 0;
        /* 0x078 */ f32 _78 = 0;
        /* 0x07c */ f32 _7c = 0;
        /* 0x080 */ f32 _80 = 0;
        /* 0x084 */ s32 _84 = 0;
        /* 0x088 */ sead::Vector3f _88;
        /* 0x094 */ u32 _94 = 0;
        /* 0x098 */ u8 _98 = 0;
        // 2026-10-07: SiteBossSwordRoot::init_ 0x710059881c sets this from _1534 bits 2/3.
        /* 0x099 */ bool _99 = false;
        /* 0x09a */ u8 _9a[2] = {};
        /* 0x09c */ u32 _9c = 0;  // bit idx: bound actor idx (cleared by GanonFlameBall)
        /* 0x0a0 */ sead::SafeArray<ksys::act::BaseProcHandle, 20> _a0;
        /* 0x1e0 */ sead::SafeArray<ksys::act::BaseProcLink, 20> _1e0;
        /* 0x320 */ sead::SafeArray<ksys::act::BaseProcLink, 4> _320;
        /* 0x360 */ ksys::act::BaseProcLink _360;
        /* 0x370 */ sead::SafeArray<ksys::act::BaseProcLink, 4> _370;
        /* 0x3b0 */ sead::SafeArray<ksys::act::BaseProcLink, 24> _3b0;
        /* 0x530 */ sead::SafeArray<ksys::MesTransceiverId, 20> _530;
        /* 0x710 */ sead::SafeArray<Payload, 24> _710;
        // 0x710066cdf8 stores the owner and the spawn argument for bound actor `idx` here.
        /* 0xad0 */ sead::SafeArray<SpawnInfo, 20> _ad0{};
        // 2026-10-07: sub_710066D9B8 tests, sends and clears a 24-entry message-type array.
        /* 0xd50 */ sead::SafeArray<ksys::MessageType, 24> mPendingMessages{};
        /* 0xdb0 */ sead::JobQueueLock _db0;
    };
    /* 0x1560 */ Unk_71002cf2ac _1560{this};
    /* 0x2318 */ sead::Vector3f _2318;  // home position (m63)
    /* 0x2324 */ u8 _2324[0x2328 - 0x2324];
    /* 0x2328 */ sead::SafeString _2328;
    /* 0x2338 */ xlink2::HandleELink _2338;  // "Elec_Sword" (sub_71002D223C)
    /* 0x2348 */ xlink2::HandleELink _2348;  // "Elec_Shield"
    /* 0x2358 */ xlink2::HandleELink _2358;  // "LightShield" (sub_71002D2390)
    /* 0x2368 */ xlink2::HandleSLink _2368;
    /* 0x2378 */ u8 _2378 = 0;
    /* 0x2379 */ u8 _2379 = 0;
    /* 0x237a */ u8 _237a = 0;
    /* 0x237b */ u8 _237b = 0;  // zeroed by the ctor (8-byte store at 0x2378)
    /* 0x237c */ u32 _237c = 0;
    /* 0x2380 */ u32 _2380 = 0;
    /* 0x2384 */ u32 _2384 = 0;
    /* 0x2388 */ u32 _2388 = 0;
    // object with ctor 0x7100722420(this + 0x2390, this) and dtor 0x71007224cc
    /* 0x2390 */ Unk_7100722420 _2390{this};
    /* 0x25e8 */ ksys::evt::ResidentEvent _25e8;
    /* 0x27b8 */ ksys::evt::ResidentEvent _27b8;
};
KSYS_CHECK_SIZE_NX150(SiteBoss, 0x2988);

}  // namespace uking::act

// 0x71002d02ac / 0x71002d0310 (CSV names; namespace unknown): number of Die_PGanon* / Clear_Remains*
// game data flags that are set (0-4).
int getNumberOfDeadBlights();
int getNumberOfClearedRemains();

// 0x71002d17d4 (placeholder name): tests a target against the home-relative chase range.
bool sub_71002D17D4(ksys::act::Actor* actor, const sead::Vector3f* home,
                  const sead::Vector3f* target, const sead::Vector3f* distance,
                  const sead::Vector3f* offset, bool special);

// 0x71002d2d9c: computes the avoidance vector and interpolation flag.
bool sub_71002D2D9C(sead::Vector3f* out, bool* out_flag, ksys::act::Actor* actor,
                  const sead::Vector3f& target, bool side, f32 distance);
