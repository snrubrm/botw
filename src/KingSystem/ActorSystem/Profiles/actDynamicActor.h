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

protected:
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
    /* 0xa68 */ u8 _a68[0xa78 - 0xa68];
    /* 0xa78 */ Unk3 _a78;  // m135
    /* 0xa80 */ BaseProcLink _a80;
    /* 0xa90 */ u8 _a90[0xb90 - 0xa90];
};
KSYS_CHECK_SIZE_NX150(DynamicActor, 0xb90);

}  // namespace ksys::act
