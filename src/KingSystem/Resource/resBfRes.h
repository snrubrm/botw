#pragma once

#include <container/seadListImpl.h>
#include <container/seadOffsetList.h>
#include <container/seadTList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resResource.h"

namespace ksys::res {

class BfRes;
struct Unk_BfResNode;  // element type of the lists at 0x138 / 0x150 (unknown)

// Vtable 0x71024f9d68 (GOT 0x259ed88): abstract callback interface (D1 0x7100fe85a4 is a shared `ret`, D0 0x7100fe85a8,
// then three pure virtuals); the constructor 0x7100fe8584 sets {vptr, -1, -1} out of line. Placeholder name.
class Unk_71024f9d68 {
public:
    Unk_71024f9d68();
    virtual ~Unk_71024f9d68();
    virtual void m2(const void* arg) = 0;
    virtual void m3(const void* arg) = 0;
    virtual void m4(const void* arg) = 0;

    u64 _8;
    s32 _10;
};

// Vtable 0x71025149d0 (GOT 0x25a25d0), the callback object at BfRes + 0x168. Its m2 / m3 / m4 are 0x71012007b8,
// 0x71012007e4 and 0x710120086c (declared only); D0 0x7100001200908. The destructor is out of line (a shared `ret`).
class Unk_71025149d0 : public Unk_71024f9d68 {
public:
    explicit Unk_71025149d0(BfRes* owner) : mOwner(owner) {}
    ~Unk_71025149d0() override;
    void m2(const void* arg) override;
    void m3(const void* arg) override;
    void m4(const void* arg) override;

    BfRes* mOwner;
};

// The third base of BfRes (at +0x38, no destructor): its m2 / m3 forward to the object at `_58`. The member names
// are the BfRes offsets. Placeholder name.
class Unk_BfResBase3 {
public:
    virtual void m0() {}
    virtual void m1() {}
    virtual void m2() = 0;
    virtual void m3(const void* arg) = 0;

    u8 _40 = 1;
    u8 _41 = 0;
    void* _48 = nullptr;
    void* _50 = nullptr;
    void* _58 = nullptr;
};

// Placeholder name (vtable 0x71025148f8, typeinfo 0x71025b71c8; ctor 0x71011fe300, size 0x1a8): the bfres
// resource of the texture handle manager. Only the type is modelled (for DynamicCast).
// TODO: incomplete.
class BfRes : public Resource, public Unk_BfResBase3 {
    SEAD_RTTI_OVERRIDE(BfRes, Resource)
public:
    BfRes();
    ~BfRes() override;
    s32 getLoadDataAlignment() const override;
    bool needsParse() const override;
    bool m2_() override;
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    void onDestroy_() override;

    // Overriders of Unk_BfResBase3::m2 / m3 (CSV BfRes::h 0x71012005f8 and BfRes::i 0x7101200628, declared only; the
    // Thn56 thunks 0x7101200610 / 0x7101200680 hold inlined copies): `_58->vslot2()` and, after a call of
    // slot 7 of Unk_710260af28::sInstance, `_58->vslot3(arg)`.
    void m2() override;
    void m3(const void* arg) override;

    // 0x71011ffecc (declared only)
    void sub_71011FFECC();

    sead::TList<void*> _60;
    sead::CriticalSection _78{nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified};
    sead::CriticalSection _b8{nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified};
    sead::CriticalSection _f8{nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified};
    sead::OffsetList<Unk_BfResNode> _138;
    sead::OffsetList<Unk_BfResNode> _150;
    Unk_71025149d0 _168{this};
    // The node of ResourceMgrTask::mBfResList.
    sead::ListNode mListNode;
    void* _198;
    void* _1a0;
};

KSYS_CHECK_SIZE_NX150(BfRes, 0x1a8);

}  // namespace ksys::res
