#pragma once

#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <container/seadObjList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::act {
class Actor;
class Chemical;
class Unk_71024dd490;
}

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
// vtable header 0x710250c698); remaining fields and virtuals are not recovered.
class Unk_710250c698 {
public:
    virtual ~Unk_710250c698();
    u32 _8;
    u8 _c[0x38 - 0xc];
};
KSYS_CHECK_SIZE_NX150(Unk_710250c698, 0x38);

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
public:
    ChemicalMgr();
    ~ChemicalMgr() override;

    // m3: sets the position of the actor at `_d88`; m4: `_b10 = 0`; m2: forwards `arg` to
    // sub_71010CBF7C with the element holder `_ae8` (null without one).
    void m3(const sead::Vector3f* pos) override;
    void m4() override;
    void* m2(void* arg) override;

    JobType getType() const override { return JobType::Chemical; }

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
    u8 _b11[0xc10 - 0xb11];
    sead::CriticalSection _c10;
    u8 _c50[0xc60 - 0xc50];
    sead::PtrArray<Unk_710250c698> _c60;
    sead::PtrArray<Unk_710250c698> _c70;
    u8 _c80[0xcf8 - 0xc80];
    WorldMgrStruct0_8_a _cf8;
    // The actor whose chemical state is put to sleep on unload (acquireActor in unload2).
    act::BaseProcLink _d88;
    u8 _d98[0xdc0 - 0xd98];
};
KSYS_CHECK_SIZE_NX150(ChemicalMgr, 0xdc0);

// 0x71010cbf7c (declaration only): called by ChemicalMgr::m2 with (`_ae8`, {arg, `_ae8`}).
struct Unk_ChemicalMgrM2Arg {
    void* arg;
    act::Unk_71024dd490* holder;
};
void* sub_71010CBF7C(act::Unk_71024dd490* holder, Unk_ChemicalMgrM2Arg* arg);

}  // namespace ksys::world
