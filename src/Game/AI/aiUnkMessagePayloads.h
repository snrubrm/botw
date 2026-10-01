#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class BaseProc;
}

// Message payloads (the user data of messages sent by the Unk_7102357d20 sender family and copied by
// the Unk_7102357210 listener family). Each payload is guarded by a sead::JobQueueLock. Placeholder
// names are Unk_<sender vtable>_Payload (Unk_<listener vtable>_Payload when no sender is known);
// unnamed non-virtual functions are named by address (sub_<addr>).

// Message 0x800001e (sender Unk_710237ecc0)
struct Unk_710237ecc0_Payload {
    Unk_710237ecc0_Payload();

    void sub_710070E194(ksys::act::BaseProcLink* out);
    void sub_710070E1F8(ksys::act::BaseProc* proc);

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x8000021 (sender Unk_71023f83e8)
struct Unk_71023f83e8_Payload {
    sead::Vector3f _0;
    u32 _c;
    bool _10;
    sead::JobQueueLock mLock;
};

// Message 0x800001b (sender Unk_71023b1608)
struct Unk_71023b1608_Payload {
    Unk_71023b1608_Payload();

    void sub_710070E374(ksys::act::BaseProcLink* out);
    void sub_710070E3D8(ksys::act::BaseProc* proc);

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x8000006 (sender Unk_710235abc8)
struct Unk_710235abc8_Payload {
    struct Data {
        ksys::act::BaseProcLink _0;
        ksys::act::BaseProcLink _10;
        s32 _20 = 0x7fffffff;
        u32 _24 = 0;
        sead::Vector3f _28 = sead::Vector3f::zero;
        bool _34 = false;
    };

    Data mData;
    sead::JobQueueLock mLock;
};

// Message 0x8000010 (sender unknown; placeholder name = listener vtable)
struct Unk_71024504c8_Payload {
    ksys::act::BaseProcLink _0;
    ksys::act::BaseProcLink _10;
    u32 _20;
    u32 _24;
    sead::Vector3f _28;
    u32 _34;
    sead::JobQueueLock mLock;
};

// Message 0x80000a4 (sender Unk_7102410070)
struct Unk_7102410070_Payload {
    ksys::act::BaseProcLink mLink;
    sead::Vector3f _10;
    sead::Vector3f _1c;
    sead::JobQueueLock mLock;
};
