#pragma once

#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"

namespace uking::act {
class Unk_71025ae680;
}  // namespace uking::act

namespace ksys::act {

class Unk_71006e45c4;
class Unk_71006ecc78;
class Unk_7102459df8;

// Placeholder name (ctor 0x71006dc134, inlined into DynamicActor::m36 0x71006dc16c): the argument
// m36 passes (by pointer) to the sead::IDelegate1 at _a70 (e.g. PriestBossIronBallRoot::_248).
struct Unk_71006dc134 {
    Unk_71006dc134(const sead::Vector3f& a1, const sead::Vector3f& a2,
                  ActorAtk::Unk_710079e64c::Unk1* info, bool a4, bool a5);
    sead::Vector3f _0;
    sead::Vector3f _c;
    ActorAtk::Unk_710079e64c::Unk1* _18;
    bool _20;
    bool _21;
};

// Placeholder (lane4 s50; vtable unknown): the object at DynamicActor::_a58. Slot 5 is polled by
// startPreparingForPreDelete_ (declared only).
struct Unk_DynamicActorA58 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual bool m5();
    virtual void m6(bool a1);
};

// TODO: incomplete. Factory size 0xb90 (DynamicActor::construct); the vtable has 163 slots.
class DynamicActor : public Actor {
    SEAD_RTTI_OVERRIDE(DynamicActor, Actor)
public:
    explicit DynamicActor(const CreateArg& arg);
    // CSV DynamicActor::construct: the actor factory function.
    static BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~DynamicActor() override;

protected:
    bool startPreparingForPreDelete_() override;
    void onDeleteRequested_(DeleteReason reason) override;
    void onSleepRequested_(SleepWakeReason reason) override;
    void onEnterDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg&) override;
    void preDelete2_(const PreDeleteArg& arg) override;
    IsSpecialJobTypeResult isSpecialJobType_(JobType type) override;
    // 0x71006dc5d4 (CSV DynamicActor::initField868): creates the ragdoll controller `_868` if the actor
    // has a ragdoll instance.
    bool initField868(sead::Heap* heap);
    bool constructActorAtk(sead::Heap* heap);
    bool initField858(sead::Heap* heap);
    bool initDropData(sead::Heap* heap);

public:
    Actor* m31() override;
    void m36(const sead::Vector3f& a1, const sead::Vector3f& a2, bool a3, bool a4, bool a5) override;
    Actor* m48() override;
    bool m53() override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m73() override;
    void m76(VFR::ScopedDeltaSetter* setter) override;
    bool m81(const Message& message) override;
    s32* getLife() override;
    Unk_7100e4e084* m100() override;
    int getExtraHeapSize() override;
    Unk_71025ae640* getAtk() override;
    Unk_71025b08f8* m126() override;
    uking::dmg::DamageManagerBase* getDamageMgr() override;
    Unk_71006e45c4* m128() override;
    Unk_71025ae620* getDropData() override;
    Unk3* m135() override;

    // FIXME: figure out return types, parameters and names
    virtual f32 m148() { return _860; }
    virtual void m149(int) {}
    virtual void m150() {}
    // Test a bit / a mask of the BitFlag16 at +8 of the object returned by m159.
    virtual bool m151(u16 bit) { return false; }
    virtual bool m152(u16 mask) { return false; }
    virtual f32 m153() { return 1.0f; }
    virtual bool m154() { return false; }
    virtual bool m155() { return false; }
    virtual void m156();
    // Slot 157: initialize damage manager using the supplied heap (6DC8F0 / Player 85DD3C).
    virtual bool m157(sead::Heap* heap);
    virtual void m158();
    virtual uking::act::Unk_71025ae680* m159() { return nullptr; }
    virtual void m160();
    virtual void m161() {}
    virtual bool m162() { return false; }

    // 0x71006dd92c: forwards to the object at _868 (a different routine for true / false).
    void sub_71006DD92C(bool enable);
    // 0x71006dd21c (CSV DynamicActor::m69_xxx, 796 B; declaration only, lane4 s50): called by calcMaybe.
    void sub_71006DD21C();
    // 0x71006dc81c / 0x71006dc864: release the owned actor attack / ragdoll handlers.
    void sub_71006DC81C();
    void sub_71006DC864();
    // 0x71006dc89c (placeholder name): deletes the drop data (`_a60`) and clears it.
    void sub_71006DC89C();
    // 0x71006de274 (lane4 s64; placeholder name): sets / clears bit 0 of the drop data's flags `_c` (if there is drop data).
    void sub_71006DE274(bool on);
    // 0x71006dd908 (declared only): forwards to _868 (Unk_71006ecc78::sub_71006EE128(out)) if it exists.
    void sub_71006DD908(sead::Vector3f* out);

public:
    // Members are public: AI and action code read them directly.
    /* 0x840 */ uking::dmg::DamageManagerBase* mDamageMgr = nullptr;
    /* 0x848 */ s32 mLife = 1;
    /* 0x850 */ ActorAtk* _850 = nullptr;  // created by ActorAtk::makeForActor
    /* 0x858 */ Unk_7102459df8* _858 = nullptr;  // DynamicActor::initField858 (CSV)
    /* 0x860 */ f32 _860 = 0.0;
    /* 0x868 */ Unk_71006ecc78* _868 = nullptr;  // ragdoll handler (initField868)
    /* 0x870 */ Unk_7100e4e084 _870{this};  // m100
    /* 0xa50 */ Unk_71006e45c4* _a50 = nullptr;  // m128
    /* 0xa58 */ Unk_DynamicActorA58* _a58 = nullptr;
    /* 0xa60 */ DropData* _a60 = nullptr;  // created by Actor::makeDropData (CSV); getDropData
    /* 0xa68 */ u8 _a68 = 0;  // flags (byte accesses from AI/action code)
    /* 0xa69 */ u8 _a69 = 0;
    /* 0xa70 */ sead::IDelegate1<Unk_71006dc134*>* _a70 = nullptr;
    /* 0xa78 */ Unk3 _a78;  // m135
    /* 0xa80 */ BaseProcLink _a80;
    /* 0xa90 */ u8 _a90[0xb90 - 0xa90];
};
KSYS_CHECK_SIZE_NX150(DynamicActor, 0xb90);

// Placeholder name (after its out-of-line setter 0x71006e4478 in the DynamicActor TU; no ctor of its
// own): a target snapshot (link, matrix, velocity, previous position). Enemy embeds one at 0xe08,
// NPC at 0xe30.
struct Unk_71006e4478 {
    // 0x71006e4478: copies `link` / `mtx` and the linked actor's velocity / previous position; for
    // Arrow-tagged actors the translation and the previous position are moved back by the
    // velocity (and _5d is set).
    void sub_71006E4478(BaseProcLink* link, const sead::Matrix34f& mtx);

    /* 0x00 */ BaseProcLink _0;
    /* 0x10 */ sead::Matrix34f _10 = sead::Matrix34f::ident;
    /* 0x40 */ sead::Vector3f _40 = sead::Vector3f::zero;  // velocity
    /* 0x4c */ sead::Vector3f _4c = sead::Vector3f::zero;  // previous position
    /* 0x58 */ u32 _58 = 0;
    /* 0x5c */ bool _5c = false;
    /* 0x5d */ bool _5d = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71006e4478, 0x60);

}  // namespace ksys::act
