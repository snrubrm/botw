#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

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
    void m31() override;
    void m36() override;
    void m48() override;
    bool m53() override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m73() override;
    void m76() override;
    void m81() override;
    s32* getLife() override;
    void m100() override;
    int getExtraHeapSize() override;
    Unk_71025ae640* getAtk() override;
    Unk_71025b08f8* m126() override;
    uking::dmg::DamageManagerBase* getDamageMgr() override;
    void m128() override;
    Unk_71025ae620* getDropData() override;
    void m135() override;

    // FIXME: figure out return types, parameters and names
    virtual f32 m148() { return _860; }
    virtual void m149(int) {}
    virtual void m150() {}
    virtual void m151();
    virtual void m152();
    virtual f32 m153() { return 1.0f; }
    virtual bool m154() { return false; }
    virtual bool m155() { return false; }
    virtual void m156();
    virtual void m157();
    virtual void m158();
    virtual void m159();
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
    /* 0x870 */ Actor* _870 = this;
    /* 0x878 */ sead::CriticalSection _878;
    /* 0x8b8 */ sead::FixedSafeString<32> _8b8;
    /* 0x8f0 */ u8 _8f0[0x92c - 0x8f0];
    /* 0x92c */ bool _92c = false;
    /* 0x930 */ sead::CriticalSection _930;
    /* 0x970 */ u8 _970[0x9a0 - 0x970];
    /* 0x9a0 */ sead::CriticalSection _9a0;
    /* 0x9e0 */ BaseProcLink _9e0;
    /* 0x9f0 */ sead::CriticalSection _9f0;
    /* 0xa30 */ f32 _a30 = -1.0;
    /* 0xa38 */ u8 _a38[0xa60 - 0xa38];
    /* 0xa60 */ DropData* _a60 = nullptr;  // created by Actor::makeDropData (CSV); getDropData
    /* 0xa68 */ u8 _a68[0xa80 - 0xa68];
    /* 0xa80 */ BaseProcLink _a80;
    /* 0xa90 */ u8 _a90[0xb90 - 0xa90];
};
KSYS_CHECK_SIZE_NX150(DynamicActor, 0xb90);

}  // namespace ksys::act
