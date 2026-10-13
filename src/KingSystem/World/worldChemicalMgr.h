#pragma once

#include <container/seadPtrArray.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <container/seadObjList.h>
#include <thread/seadCriticalSection.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Chemical/chmRoot.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::phys {
class RigidBody;
}

namespace ksys::act {
class Actor;
class Chemical;
class Unk_71024dd490;
}

// Concrete shape/root adapters embedded at +A0 / +98 in the E0-byte records built by 10C9274.
// The signed shape index is read by 10C8658; the next record field at +B0 is a map object.
class Unk_710250c880 : public ksys::chm::IShape {
public:
    const sead::SafeString& getResTypeId() const override;
    const sead::SafeString& getName() const override;
    f32 getVolumeOccupancy() const override;
    f32 getElementOcclusion() const override;

    s32 _8 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710250c880, 0x10);

// Complete 23-slot table at 250C8B0. getShape returns this + 8; all other slots are constants.
class Unk_710250c8b0 : public ksys::chm::IRoot {
public:
    int getNumShapes() const override { return 1; }
    const ksys::chm::IShape& getShape(int idx) const override;
    bool isRigidAttribute0Set(int idx) const override { return false; }
    bool isRigidAttribute1Set(int idx) const override { return false; }
    const sead::SafeString& getRigidSetName(int idx) const override {
        return sead::SafeString::cEmptyString;
    }
    bool isRigidAttribute2Set(int idx) const override { return false; }
    const sead::SafeString& getRigidName(int idx) const override {
        return sead::SafeString::cEmptyString;
    }
    bool rigidHasBurnOutTime(int idx) const override { return false; }
    f32 getRigidBurnOutTime(int idx) const override { return 0.0f; }
    bool isRigidAttribute3Set(int idx) const override { return true; }
    bool isRigidAttribute15Set(int idx) const override { return false; }
    f32 getRigidVolume(int idx) const override { return 1.0f; }
    bool isRigidAttribute9Set(int idx) const override { return true; }
    bool isRigidAttribute10Set(int idx) const override { return false; }
    f32 getRigidMass(int idx) const override { return 1.0f; }
    bool isRigidAttribute6Or14Set(int idx) const override { return false; }
    bool isRigidAttribute5Set(int idx) const override { return false; }
    bool isRigidAttribute4Set(int idx) const override { return false; }
    bool isRigidAttribute11Set(int idx) const override { return false; }
    bool isRigidAttribute12Set(int idx) const override { return false; }
    bool isRigidAttribute13Set(int idx) const override { return false; }
    bool isRigidAttribute14Set(int idx) const override { return false; }
    bool isRigidAttribute16Set(int idx) const override { return false; }

    Unk_710250c880 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_710250c8b0, 0x18);

// Name from the CSV; partial declaration of ChemicalMgr's carried chemical-element pool.
// Constructor 0x71010c9074, vtable address point 0x710250c870, size 0x90.
class WorldMgrStruct0_8_a {
public:
    virtual ~WorldMgrStruct0_8_a();
    void sub_71010C9D00(ksys::act::Actor* actor);
    void sub_71010C9E48(ksys::act::Actor* actor);
    void sub_71010C9438();
    void sub_71010C9B48();
    // Pool reset forwarder (0x71010c9cfc); defined in its own TU so callers keep the call.
    void sub_71010C9CFC();
    sead::CriticalSection _8;
    u8 _48[0x90 - 0x48];
};
KSYS_CHECK_SIZE_NX150(WorldMgrStruct0_8_a, 0x90);

// Address placeholder for the 0x38-byte pooled entry (ctor 0x71010c5d04,
// vtable header 0x710250c698). The complete two-slot table contains only the destructors.
class Unk_710250c698 {
public:
    Unk_710250c698();
    virtual ~Unk_710250c698();
    u32 _8 = 0;
    // Full 10C5F2C uses this as a carried radial-wind element; pointee interface remains opaque.
    void* _10 = nullptr;
    ksys::phys::RigidBody* _18 = nullptr;
    u8 _20[0x2c - 0x20];
    // Constructor defaults; full update 10C5F2C reads both as floats and passes _30 to setRadius.
    f32 _2c = 10.0f;
    f32 _30 = 5.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_710250c698, 0x38);

// Complete 0x70 pool at ChemicalMgr +C10: constructor10CA1C0, init10CA680 and lifetime10CA33C.
struct Unk_71010cb1f0 {
    void sub_71010CB1F0(s32 count, sead::Heap* heap);

    sead::CriticalSection lock;
    sead::Buffer<Unk_710250c698> entries;
    sead::PtrArray<Unk_710250c698> free;
    sead::PtrArray<Unk_710250c698> used;
};
KSYS_CHECK_SIZE_NX150(Unk_71010cb1f0, 0x70);

// Interface at ChemicalMgr + 0x20. Vtable 0x710250cac8 (GOT 0x25a0c20): D1 (stores the vptr only), D0, then
// m2 (returns null), m3 and m4 (empty). ChemicalMgr overrides m2 / m3 / m4; as the overriders of this
// non-primary base they also get slots 13 - 15 of ChemicalMgr's own vtable (in declaration order m3, m4, m2),
// and the vtable group at +0x20 holds this-adjusting thunks with those bodies inlined.
class Unk_710250cac8 {
public:
    virtual ~Unk_710250cac8();
    virtual void* m2(void* arg) { return nullptr; }
    virtual void m3(const sead::Vector3f* pos) {}
    virtual void m4() {}
};

namespace ksys::world {

// TODO
class ChemicalMgr : public Job, public Unk_710250cac8 {
    SEAD_RTTI_OVERRIDE(ChemicalMgr, Job)
public:
    ChemicalMgr();
    ~ChemicalMgr() override;

    // m3: sets the position of the actor at `_d88`; m4: `_b10 = 0`; m2: forwards `arg` to
    // sub_71010CBF7C with the element holder `_ae8` (null without one).
    void m3(const sead::Vector3f* pos) override;
    void m4() override;
    void* m2(void* arg) override;

    JobType getType() const override { return JobType::Chemical; }

    void init_(sead::Heap* heap) override;
    void calc_() override {}
    void calcType1_() override {}
    void calcType2_() override {}
    void m9() override {}
    void m10() override {}
    void m11() override {}

    void initBeforeStageGen();
    void sub_71010CB39C();
    void unload2();
    void sub_71010CC5AC();
    void sub_71010CC5B4();
    void sub_71010CE760();
    // Pair-processing helper at 0x71010CE7DC consumes the current VFR delta frame.
    void sub_71010CE7DC(f32 delta_frame);
    void sub_71010CB5C0();
    // Original 0x71010cbdcc: enqueue a unique chemical pair and event type under the pool lock.
    void sub_71010CBDCC(act::Chemical* first, act::Chemical* second, s32 type);
    void sub_71010CBEAC(act::Chemical* chemical);
    bool x_4() const;
    void x_5(ksys::act::Actor* actor);
    void x_7(ksys::act::Actor* actor);
    Unk_710250c698* x_8();
    bool x_9(Unk_710250c698* entry);

    // Constructor 10CA1C0 sets up 64 records at stride28; remove10CBEAC confirms both pointers.
    struct ChemicalPair {
        act::Chemical* first;
        act::Chemical* second;
        u8 type;
    };
    static_assert(sizeof(ChemicalPair) == 0x18);
    sead::CriticalSection mChemicalPairLock;
    sead::CriticalSection _68;
    u8 _a8[0x10];
    sead::FixedObjList<ChemicalPair, 64> mChemicalPairs;
    act::Unk_71024dd490* _ae8;  // Actual Element holder created by sub_7100D9A1D0.
    u8 _af0[0xb10 - 0xaf0];
    u8 _b10;
    u8 _b11[3];
    sead::BitFlag32 _b14;
    u8 _b18[0xc10 - 0xb18];
    Unk_71010cb1f0 _c10;
    u8 _c80[0xcf8 - 0xc80];
    WorldMgrStruct0_8_a _cf8;
    // The actor whose chemical state is put to sleep on unload (acquireActor in unload2).
    act::BaseProcLink _d88;
    u8 _d98[4];
    u16 _d9c;
    u8 _d9e[0xdc0 - 0xd9e];
};
KSYS_CHECK_SIZE_NX150(ChemicalMgr, 0xdc0);

// 0x71010cbf7c (declaration only): called by ChemicalMgr::m2 with (`_ae8`, {arg, `_ae8`}).
struct Unk_ChemicalMgrM2Arg {
    void* arg;
    act::Unk_71024dd490* holder;
};
void* sub_71010CBF7C(act::Unk_71024dd490* holder, Unk_ChemicalMgrM2Arg* arg);

}  // namespace ksys::world
