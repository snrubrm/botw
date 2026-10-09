#pragma once

#include <container/seadListImpl.h>
#include <container/seadOffsetList.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadMutex.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class Constraint;

// Placeholder name (created by 0x71012a6844 in System::init; stored in System::_150). Keeps two mutex-guarded
// intrusive lists. TODO: incomplete (the TU 0x71012a605c - 0x71012a70xx is not decompiled).
class Unk_71012a6844 {
public:
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
    struct ItemB {};

    // 0x71012a69e0 / 0x71012a6a44: adds ItemA to / removes it from the list at +0x8 (guarded by the mutex at +0x48).
    void sub_71012A69E0(ItemA* item);
    void sub_71012A6A44(ItemA* item);
    // 0x71012a6aa4 / 0x71012a6af8: adds / removes an entry of the list at +0x20 (guarded by the mutex at +0x88).
    void sub_71012A6AA4(ItemB* item);
    void sub_71012A6AF8(ItemB* item);

    /* 0x00 */ u8 _0[0x8];
    /* 0x08 */ sead::OffsetList<ItemA> mListA;
    /* 0x20 */ sead::OffsetList<ItemB> mListB;
    /* 0x38 */ u8 _38[0x48 - 0x38];
    /* 0x48 */ sead::Mutex mMutexA;
    /* 0x88 */ sead::Mutex mMutexB;
};

}  // namespace ksys::phys
