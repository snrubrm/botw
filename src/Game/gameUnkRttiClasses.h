#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadDelegate.h>
#include "Game/Actor/actCameraUtil.h"

namespace uking::action {
class CameraLockOnBase;
}
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskData.h"

namespace sead {
class Heap;
}

namespace uking {
class Stage;
class StageBinder;
}

// Placeholder classes (lane4 s47) for vtables of the original that have no name: every class here has only trivial
// virtual functions (the destructor is empty, the other slots are constant results). The name is the address of
// the vtable; the class is only defined so that its RTTI functions, destructors and stubs can be matched.

// vtable 0x71023f3710 (4 slots)
// The destructor is defaulted on its first declaration (virtual but trivial): the
// original's D0 is just `b operator delete` with no D1 call, so subclasses keep no D1
// of their own (their D1 slot is the base's). The two RTTI virtuals are therefore
// declared here and defined out of line in gameUnkRttiClasses.cpp (instead of using
// SEAD_RTTI_BASE, whose inline virtuals would leave no key function): the first one is
// the key function that emits the vtable. Bodies are the macro's. Do not move the
// destructor out of line.
class Unk_71023f3710 {
public:
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Root typeInfo;
        return &typeInfo;
    }

    static bool checkDerivedRuntimeTypeInfoStatic(
        const sead::RuntimeTypeInfo::Interface* typeInfo) {
        const sead::RuntimeTypeInfo::Interface* clsTypeInfo =
            Unk_71023f3710::getRuntimeTypeInfoStatic();
        return typeInfo == clsTypeInfo;
    }

    virtual bool checkDerivedRuntimeTypeInfo(
        const sead::RuntimeTypeInfo::Interface* typeInfo) const;
    virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;
    virtual ~Unk_71023f3710() = default;
};

// vtable 0x710245a498 (4 slots)
class Unk_710245a498 {
    SEAD_RTTI_BASE(Unk_710245a498)
public:
    virtual ~Unk_710245a498();
};

// vtable 0x710245a4c8 (4 slots)
class Unk_710245a4c8 {
    SEAD_RTTI_BASE(Unk_710245a4c8)
public:
    virtual ~Unk_710245a4c8();
};

// vtable 0x710245a4f8 (4 slots)
class Unk_710245a4f8 {
    SEAD_RTTI_BASE(Unk_710245a4f8)
public:
    virtual ~Unk_710245a4f8();
};

// vtable 0x710245a578 (4 slots)
class Unk_710245a578 {
    SEAD_RTTI_BASE(Unk_710245a578)
public:
    virtual ~Unk_710245a578();
};

// Vtable 0x710245bee0 (4 slots). StageBinder::createStage at 7CBC5C constructs this request;
// StageFactory::create at 7CBEAC reads its heap/binder and writes the stage output.
class Unk_710245bee0 {
    SEAD_RTTI_BASE(Unk_710245bee0)
public:
    virtual ~Unk_710245bee0();

    /* 0x08 */ bool _8;
    /* 0x10 */ sead::Heap* mHeap;
    /* 0x18 */ uking::Stage** mStage;
    /* 0x20 */ uking::StageBinder* mBinder;
};
static_assert(sizeof(Unk_710245bee0) == 0x28);

// vtable 0x710245c6b8 (4 slots)
class Unk_710245c6b8 {
    SEAD_RTTI_BASE(Unk_710245c6b8)
public:
    virtual ~Unk_710245c6b8();
};

// vtable 0x710245c858 (4 slots)
class Unk_710245c858 {
    SEAD_RTTI_BASE(Unk_710245c858)
public:
    virtual ~Unk_710245c858();
};

// vtable 0x710246c330 (4 slots)
class Unk_710246c330 {
    SEAD_RTTI_BASE(Unk_710246c330)
public:
    virtual ~Unk_710246c330();
};

// vtable 0x710246c360 (4 slots)
class Unk_710246c360 {
    SEAD_RTTI_BASE(Unk_710246c360)
public:
    virtual ~Unk_710246c360();
};

// vtable 0x710246cec8 (4 slots)
class Unk_710246cec8 {
    SEAD_RTTI_BASE(Unk_710246cec8)
public:
    virtual ~Unk_710246cec8();
};

// vtable 0x71024dcf80 (4 slots)
class Unk_71024dcf80 {
    SEAD_RTTI_BASE(Unk_71024dcf80)
public:
    virtual ~Unk_71024dcf80();
};

// vtable 0x71024dd5c8 (4 slots)
class Unk_71024dd5c8 {
    SEAD_RTTI_BASE(Unk_71024dd5c8)
public:
    virtual ~Unk_71024dd5c8();

    // 0x7100d9e148 (placeholder name): always true.
    bool sub_7100D9E148();
};

// vtable 0x71024e8128 (4 slots)
class Unk_71024e8128 {
    SEAD_RTTI_BASE(Unk_71024e8128)
public:
    virtual ~Unk_71024e8128();
};

// vtable 0x71024e80e0 (4 slots)
class Unk_71024e80e0 : public Unk_71024e8128 {
    SEAD_RTTI_OVERRIDE(Unk_71024e80e0, Unk_71024e8128)
public:
    ~Unk_71024e80e0() override;
};

// vtable 0x71024efd58 (11 slots)
class Unk_71024efd58 {
    SEAD_RTTI_BASE(Unk_71024efd58)
public:
    virtual ~Unk_71024efd58();
    virtual bool m4() { return true; }
    virtual void m5() {}
    virtual void m6() {}
    virtual void m7() {}
    virtual void m8() {}
    virtual void m9() {}
    virtual void m10() {}
};

// vtable 0x710250dcd8 (4 slots)
class Unk_710250dcd8 {
    SEAD_RTTI_BASE(Unk_710250dcd8)
public:
    virtual ~Unk_710250dcd8();

    // 0x710110dd20: sets (or clears) bit 2 of the flags. Placeholder name.
    void sub_710110DD20(bool on);
    // 0x710110dd3c: clears bit 3 of the flags, destroys the sampler / texture pair at `_10` and nulls it.
    // Placeholder name.
    void sub_710110DD3C();

private:
    // Sampler (+0) and texture (+0x68) wrapper of the object at `_10` (defined in the .cpp).
    struct Unk1;

    u32 _8;
    Unk1* _10;
};

// vtable 0x7102518b60 (4 slots)
class Unk_7102518b60 {
    SEAD_RTTI_BASE(Unk_7102518b60)
public:
    virtual ~Unk_7102518b60();
};

// vtable 0x710251b678 (6 slots)
class Unk_710251b678 {
    SEAD_RTTI_BASE(Unk_710251b678)
public:
    virtual ~Unk_710251b678();
    virtual void m4() {}
    virtual void m5() {}
};

// vtable 0x71023d0d70 (11 slots)
class Unk_71023d0d70 {
    SEAD_RTTI_BASE(Unk_71023d0d70)
public:
    virtual ~Unk_71023d0d70();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
};

// vtable 0x71023d0d08 (11 slots)
class Unk_71023d0d08 : public Unk_71023d0d70 {
    SEAD_RTTI_OVERRIDE(Unk_71023d0d08, Unk_71023d0d70)
public:
    ~Unk_71023d0d08() override;
};

// vtable 0x71023d0e08 (11 slots)
class Unk_71023d0e08 : public Unk_71023d0d70 {
    SEAD_RTTI_OVERRIDE(Unk_71023d0e08, Unk_71023d0d70)
public:
    ~Unk_71023d0e08() override;
    void m4() override;
    void m6() override;
    void m7() override;
    void m8() override;
    void m10() override;
};

// vtable 0x7102457a80 (6 slots)
class Unk_7102457a80 {
    SEAD_RTTI_BASE(Unk_7102457a80)
public:
    struct InitArg {
        SEAD_RTTI_BASE(InitArg)
        explicit InitArg(uking::action::CameraLockOnBase* owner) : _8(owner) {}
        uking::action::CameraLockOnBase* _8;
    };

    virtual ~Unk_7102457a80();
    // Native 0x7100786d08 copies the owner from this typed context when it is non-null.
    virtual void m4(const InitArg* arg);
    virtual void m5() {}

    // Native 0x7100786d18 and the camera array readers establish these fields.
    uking::action::CameraLockOnBase* _8 = nullptr;
    uking::act::Unk_71009214b8 _10;
};

// vtable 0x7102457ac0 (6 slots)
class Unk_7102457ac0 : public Unk_7102457a80 {
    SEAD_RTTI_OVERRIDE(Unk_7102457ac0, Unk_7102457a80)
public:
    struct InitArg : Unk_7102457a80::InitArg {
        SEAD_RTTI_OVERRIDE(InitArg, Unk_7102457a80::InitArg)
        InitArg(uking::action::CameraLockOnBase* owner,
                sead::IDelegate1<uking::act::Unk_71009214b8*>* callback)
            : Unk_7102457a80::InitArg(owner), _10(callback) {}
        sead::IDelegate1<uking::act::Unk_71009214b8*>* _10;
    };

    Unk_7102457ac0();
    ~Unk_7102457ac0() override;
    void m4(const Unk_7102457a80::InitArg* arg) override;
    void m5() override;

    // Set by m4 at 0x7100786e00 and invoked with &_10 by m5.
    sead::IDelegate1<uking::act::Unk_71009214b8*>* _48 = nullptr;
};

// vtable 0x7102499a68 (6 slots)
class Unk_7102499a68 {
    SEAD_RTTI_BASE(Unk_7102499a68)
public:
    virtual ~Unk_7102499a68();
    virtual void m4();
    virtual void m5() {}
};

// vtable 0x7102499968 (6 slots)
class Unk_7102499968 : public Unk_7102499a68 {
    SEAD_RTTI_OVERRIDE(Unk_7102499968, Unk_7102499a68)
public:
    ~Unk_7102499968() override;
    void m4() override;
    void m5() override;
};

// vtable 0x71024999a8 (6 slots)
class Unk_71024999a8 : public Unk_7102499a68 {
    SEAD_RTTI_OVERRIDE(Unk_71024999a8, Unk_7102499a68)
public:
    ~Unk_71024999a8() override;
    void m4() override;
    void m5() override;
};

// vtable 0x71024999e8 (6 slots)
class Unk_71024999e8 : public Unk_7102499a68 {
    SEAD_RTTI_OVERRIDE(Unk_71024999e8, Unk_7102499a68)
public:
    ~Unk_71024999e8() override;
    void m4() override;
    void m5() override;
};

// vtable 0x710249a1a0 (6 slots)
class Unk_710249a1a0 {
    SEAD_RTTI_BASE(Unk_710249a1a0)
public:
    virtual ~Unk_710249a1a0();
    virtual void m4();
    virtual void m5() {}
};

// vtable 0x710249a0a0 (6 slots)
class Unk_710249a0a0 : public Unk_710249a1a0 {
    SEAD_RTTI_OVERRIDE(Unk_710249a0a0, Unk_710249a1a0)
public:
    ~Unk_710249a0a0() override;
    void m4() override;
    void m5() override;
};

// vtable 0x710249a0e0 (6 slots)
class Unk_710249a0e0 : public Unk_710249a1a0 {
    SEAD_RTTI_OVERRIDE(Unk_710249a0e0, Unk_710249a1a0)
public:
    ~Unk_710249a0e0() override;
    void m4() override;
    void m5() override;
};

// vtable 0x710249a120 (6 slots)
class Unk_710249a120 : public Unk_710249a1a0 {
    SEAD_RTTI_OVERRIDE(Unk_710249a120, Unk_710249a1a0)
public:
    ~Unk_710249a120() override;
    void m4() override;
    void m5() override;
};

// vtable 0x710251d230 (7 slots)
class Unk_710251d230 {
    SEAD_RTTI_BASE(Unk_710251d230)
public:
    virtual ~Unk_710251d230();
    virtual void m4();
    virtual void m5();
    virtual void m6();
};

// vtable 0x71024f9bb8 (4 slots): derives from ksys::util::TaskRequest.
class Unk_71024f9bb8 : public ksys::util::TaskRequest {
    SEAD_RTTI_OVERRIDE(Unk_71024f9bb8, ksys::util::TaskRequest)
public:
    ~Unk_71024f9bb8() override;

    // TextureHandleMgr::clearAllCache (0x7100fe5fcc) and invalidateUser (0x7100fe5b44)
    // initialize this 0xc8-byte request, including three additional SafeStrings.
    u32 _50 = 0x01000001;
    bool _54 = false;
    void* _58 = nullptr;
    void* _60 = nullptr;
    void* _68 = nullptr;
    sead::SafeString _70;
    u32 _80 = 0;
    sead::SafeString _88;
    u32 _98 = 0;
    void* _a0 = nullptr;
    void* _a8 = nullptr;
    void* _b0 = nullptr;
    sead::SafeString _b8;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9bb8, 0xc8);

// vtable 0x71024f9e28 (4 slots): derives from ksys::util::TaskData.
class Unk_71024f9e28 : public ksys::util::TaskData {
    SEAD_RTTI_OVERRIDE(Unk_71024f9e28, ksys::util::TaskData)
public:
    ~Unk_71024f9e28() override;
};
