#pragma once

#include <aal/aalHandle.h>
#include <container/seadObjList.h>
#include <container/seadSafeArray.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::snd {

// Vtable 0x710251b2e8 (no RTTI; 0x4d0 bytes): SoundMgr::_b0, created by 0x71011fab7c. Keeps the playing sounds of
// 11 kinds (the kind is custom param 9 of the asset, see Unk_710251b7a0::eventCalced) in two lists each, sized from
// the table 0x710251b308.
class Unk_710251b2e8 {
public:
    struct Item {
        Item() {}

        aal::Handle handle;
        f32 distance = 0.0f;
        u8 _14[0x20 - 0x14];
    };

    struct Entry {
        sead::ObjList<Item> mList1;
        sead::ObjList<Item> mList2;
        s32 _60;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x68);

    // The list sizes of each kind (the other fields are read by 0x71012c7f8c).
    struct KindInfo {
        s32 num1;
        s32 _4;
        s32 _8;
        s32 num2;
        s32 _10;
        s32 _14;
        s32 _18;
    };

    Unk_710251b2e8();
    virtual ~Unk_710251b2e8();

    // 0x71012c77f0: allocates the lists.
    void init(sead::Heap* heap, sead::Heap* heap2);
    // 0x71012c7a08 (declared only): per-frame update of the lists.
    void calc();

    /* 0x008 */ bool mInitialized = false;
    /* 0x010 */ sead::SafeArray<Entry, 11> mEntries;
    /* 0x488 */ sead::CriticalSection mCS;
    /* 0x4c8 */ sead::Heap* mHeap = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b2e8, 0x4d0);

}  // namespace ksys::snd
