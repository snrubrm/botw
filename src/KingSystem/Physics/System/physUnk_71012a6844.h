#pragma once

#include <container/seadListImpl.h>
#include <container/seadOffsetList.h>
#include <thread/seadMutex.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Placeholder name (created by 0x71012a6844 in System::init; stored in System::_150). Keeps two mutex-guarded
// intrusive lists. TODO: incomplete (the TU 0x71012a605c - 0x71012a70xx is not decompiled).
class Unk_71012a6844 {
public:
    // List entry types are unknown; ItemA has its list node at +0x10, ItemB's offset is only known at run time.
    struct ItemA {
        u8 _0[0x10];
        sead::ListNode mNode;
        bool isLinked() const { return mNode.isLinked(); }
    };
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
