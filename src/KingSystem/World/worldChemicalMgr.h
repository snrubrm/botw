#pragma once

#include <container/seadPtrArray.h>
#include <container/seadObjList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::act {
class Actor;
class Chemical;
}

// Name from the CSV; partial declaration of ChemicalMgr's carried chemical-element pool.
// Constructor 0x71010c9074, vtable address point 0x710250c870, size 0x90.
class WorldMgrStruct0_8_a {
public:
    virtual ~WorldMgrStruct0_8_a();
    void sub_71010C9D00(ksys::act::Actor* actor);
    void sub_71010C9E48(ksys::act::Actor* actor);
    void sub_71010C9438();
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

namespace ksys::world {

// TODO
class ChemicalMgr : public Job {
public:
    ChemicalMgr();

    JobType getType() const override { return JobType::Chemical; }

    void initBeforeStageGen();
    void unload2();
    void sub_71010CC5AC();
    void sub_71010CC5B4();
    void sub_71010CE760();
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
    u8 _20[8];
    sead::CriticalSection mChemicalPairLock;
    sead::CriticalSection _68;
    u8 _a8[0x10];
    sead::FixedObjList<ChemicalPair, 64> mChemicalPairs;
    void* _ae8;  // chemical element holder (type incomplete), read by Manager::getElementHolderMaybe.
    u8 _af0[0xb10 - 0xaf0];
    u8 _b10;
    u8 _b11[0xc10 - 0xb11];
    sead::CriticalSection _c10;
    u8 _c50[0xc60 - 0xc50];
    sead::PtrArray<Unk_710250c698> _c60;
    sead::PtrArray<Unk_710250c698> _c70;
    u8 _c80[0xcf8 - 0xc80];
    WorldMgrStruct0_8_a _cf8;
    u8 _d88[0xdc0 - 0xd88];
};
KSYS_CHECK_SIZE_NX150(ChemicalMgr, 0xdc0);

}  // namespace ksys::world
