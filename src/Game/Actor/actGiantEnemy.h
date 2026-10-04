#pragma once

#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::act {

// Placeholder name (vtable 0x710235a050; inherits DamageCallback's RTTI; D1 0x710002ab28, `call`
// 0x710002b994). GiantEnemy::_1510.
class Unk_710235a050 : public dmg::DamageCallback {
public:
    ~Unk_710235a050() override;
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

// Placeholder name (the object at GiantEnemy::_1558, created by the unnamed factories 0x7100302d0 / 0x71002d99c; only
// the virtual slots that GiantEnemy calls are declared: slot 2 / 3 / 5 / 8, slots 0 and 1 are the destructors).
class Unk_71002d99c {
public:
    virtual ~Unk_71002d99c();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void* m8();
};

// Name from the CSV (GiantEnemy::*): Hinox / Stalnox / Talus / Molduga-sized enemies. vtable
// 0x7102359a48 (181 slots, no new virtuals), RTTI static 0x71025af110 (parent: Enemy). Factory
// 0x710002a150 (CSV GiantEnemy::construct, which inlines the ctor): new(0x1588).
// TODO: incomplete. Members are public: AI code reads them directly.
class GiantEnemy : public Enemy {
    SEAD_RTTI_OVERRIDE(GiantEnemy, Enemy)
public:
    // Object at 0x14c8 (owner + four links); m76 calls sub_710002A94C(this) on it.
    struct Unk1 {
        explicit Unk1(Actor* owner) : mOwner(owner) {}
        void sub_710002A94C(Actor* actor);
        // 0x710002a828: forwards the request to the four linked actors (Actor::x_17).
        void sub_710002A828(ksys::act::Unk117* arg);
        // Declaration only: dispatches sleep / wake / delete to the four linked actors.
        void sub_710002A544(ksys::act::BaseProc::SleepWakeReason reason);
        void sub_710002A63C(ksys::act::BaseProc::SleepWakeReason reason);
        void sub_710002A734();

        /* 0x00 */ Actor* mOwner;
        /* 0x08 */ ksys::act::BaseProcLink _8[4];  // iterated as an array
    };

    explicit GiantEnemy(const CreateArg& arg);
    ~GiantEnemy() override;

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    void onDeleteRequested_(DeleteReason reason) override;
    void onSleepRequested_(SleepWakeReason reason) override;
    void onWakeUpRequested_(SleepWakeReason reason) override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    void m44() override;
    void killWithDropsAndEffects(int a1) override;
    void m56(sead::Vector3f* pos) override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void m79() override;
    void m110(f32* a1, s32* a2) override;
    void m111(f32* a1, s32* a2) override;
    void m112(f32* a1, s32* a2) override;
    void m113(f32* a1, s32* a2) override;
    void m117(ksys::act::Unk117* arg) override;
    void* m119() override;
    void m145() override;
    bool m146() override;
    bool weaponDroppedByEnemy() override;
    Unk_71025ae680* m178(sead::Heap* heap) override;
    // Not declared: slot 180 (writes &_1538 to its pointer argument's +0x30 when _1550 is set; Enemy
    // declares `void m180()`).

    /* 0x14c8 */ Unk1 _14c8{this};
    /* 0x1510 */ Unk_710235a050 _1510;
    /* 0x1538 */ ksys::phys::MaterialMask _1538;
    /* 0x1550 */ u8 _1550 = 0;
    /* 0x1558 */ Unk_71002d99c* _1558 = nullptr;
    /* 0x1560 */ ksys::phys::RigidBody* _1560 = nullptr;  // set by the ForestGiant / StalGiantEnemy / Golem root AIs (m56)
    /* 0x1568 */ u8 _1568 = 0;  // written by several giant AIs
    // object with vtable 0x7102357908 (owner = this); m79 forwards to 0x71006cef08 on it
    /* 0x1570 */ u8 _1570[0x1588 - 0x1570];
};
KSYS_CHECK_SIZE_NX150(GiantEnemy, 0x1588);

}  // namespace uking::act
