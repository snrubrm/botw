#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadOffsetList.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include <thread/seadMutex.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class Constraint;

// Placeholder name (created by 0x71012a6844 in System::init; stored in System::_150). Keeps two mutex-guarded
// intrusive lists. TODO: incomplete (the TU 0x71012a605c - 0x71012a70xx is not decompiled).
// Its vtable is 0x7102519a68 (RTTI root; the destructor 0x71012a67c8 destroys the two mutexes).
class Unk_71012a6844 {
    SEAD_RTTI_BASE(Unk_71012a6844)
public:
    virtual ~Unk_71012a6844();

    // ItemA's own constructor 0x7100f70c24 installs the complete root table
    // 0x71024f66b8 and initializes its Constraint pointer and list node.
    struct ItemA {
        SEAD_RTTI_BASE(ItemA)
        explicit ItemA(Constraint* constraint);
        // Whole manager 0x71012a6bb0 reads slot 2 as bool, and passes pairs
        // of Vector3f output pointers to slots 3 and 4. These read the entry.
        virtual bool m0() const = 0;
        virtual void sub_7100F6EC20(sead::Vector3f* a, sead::Vector3f* b) const;
        virtual void sub_7100F6FF60(sead::Vector3f* a, sead::Vector3f* b) const;
        // D1 and D0 are slots 5 and 6, at 0x7100f70c40 / 0x7100f70c44.
        virtual ~ItemA();
        static void sub_7100F70C48(ItemA* item);

        Constraint* mConstraint;
        sead::ListNode mNode;
        bool isLinked() const { return mNode.isLinked(); }
    };
    KSYS_CHECK_SIZE_NX150(ItemA, 0x20);
    // Placeholder: a constraint snapshot written by sub_71012A6BB0 (0x40 bytes).
    struct Record {
        sead::Vector3f _0 = sead::Vector3f::zero;
        sead::Vector3f _c = sead::Vector3f::zero;
        sead::Vector3f _18 = sead::Vector3f::zero;
        sead::Vector3f _24 = sead::Vector3f::zero;
        Constraint* _30 = nullptr;
        bool _38 = false;
    };
    KSYS_CHECK_SIZE_NX150(Record, 0x40);

    // Placeholder: a consumer of the records (pointers to the records of the current step).
    struct ItemB {
        u8 _0[0x8];
        sead::Buffer<Record*> _8;
        sead::Atomic<s32> _18;
    };

    // 0x71012a69e0 / 0x71012a6a44: adds ItemA to / removes it from the list at +0x8 (guarded by the mutex at +0x48).
    void sub_71012A69E0(ItemA* item);
    void sub_71012A6A44(ItemA* item);
    // 0x71012a6aa4 / 0x71012a6af8: adds / removes an entry of the list at +0x20 (guarded by the mutex at +0x88).
    void sub_71012A6AA4(ItemB* item);
    void sub_71012A6AF8(ItemB* item);
    // 0x71012a6b48 / 0x71012a6bb0 (declared only; placeholder names): called by the System step functions
    // (0x71012a6b48 clears a counter of every list B entry under mMutexA).
    void sub_71012A6B48();
    void sub_71012A6BB0();

    /* 0x08 */ sead::OffsetList<ItemA> mListA;
    /* 0x20 */ sead::OffsetList<ItemB> mListB;
    /* 0x38 */ sead::Buffer<Record> mRecords;
    /* 0x48 */ sead::Mutex mMutexA;
    /* 0x88 */ sead::Mutex mMutexB;
    // Number of used mRecords (an atomic: reset by sub_71012A6B48, incremented by sub_71012A6BB0).
    /* 0xc8 */ sead::Atomic<s32> _c8;
};

}  // namespace ksys::phys
