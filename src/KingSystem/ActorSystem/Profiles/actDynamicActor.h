#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"

namespace uking::act {
class Unk_71025ae680;
}  // namespace uking::act

namespace ksys::act {

class Unk_71006e45c4;
class Unk_7102459df8;

// Placeholder name (ctor 0x71006dc134, inlined into DynamicActor::m36 0x71006dc16c): the argument
// m36 passes (by pointer) to the sead::IDelegate1 at _a70 (e.g. PriestBossIronBallRoot::_248).
struct Unk_71006dc134 {
    sead::Vector3f _0;
    sead::Vector3f _c;
    void* _18;
    bool _20;
    bool _21;
};

// TODO: incomplete. Factory size 0xb90 (DynamicActor::construct); the vtable has 163 slots.
class DynamicActor : public Actor {
    SEAD_RTTI_OVERRIDE(DynamicActor, Actor)
public:
    explicit DynamicActor(const CreateArg& arg);
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

public:
    Actor* m31() override;
    void m36() override;
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
    virtual void m157();
    virtual void m158();
    virtual uking::act::Unk_71025ae680* m159() { return nullptr; }
    virtual void m160();
    virtual void m161() {}
    virtual bool m162() { return false; }

public:
    // Members are public: AI and action code read them directly.
    /* 0x840 */ uking::dmg::DamageManagerBase* mDamageMgr = nullptr;
    /* 0x848 */ s32 mLife = 1;
    /* 0x850 */ ActorAtk* _850 = nullptr;  // created by ActorAtk::makeForActor
    /* 0x858 */ Unk_7102459df8* _858 = nullptr;  // DynamicActor::initField858 (CSV)
    /* 0x860 */ f32 _860 = 0.0;
    /* 0x868 */ void* _868 = nullptr;
    /* 0x870 */ Unk_7100e4e084 _870{this};  // m100
    /* 0xa50 */ Unk_71006e45c4* _a50 = nullptr;  // m128
    /* 0xa58 */ void* _a58 = nullptr;
    /* 0xa60 */ DropData* _a60 = nullptr;  // created by Actor::makeDropData (CSV); getDropData
    /* 0xa68 */ u8 _a68 = 0;  // flags (byte accesses from AI/action code)
    /* 0xa69 */ u8 _a69 = 0;
    /* 0xa70 */ void* _a70 = nullptr;
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
