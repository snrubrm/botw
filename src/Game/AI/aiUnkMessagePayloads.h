#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include <prim/seadScopedLock.h>
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
    sead::Vector3f _0 = sead::Vector3f::zero;
    u32 _c = 0;
    bool _10 = false;
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
        u8 _34 = 0;  // set to 2 by BasicSignalEnemyForceNotice
    };

    Data mData;
    sead::JobQueueLock mLock;
};

// Message 0x8000010 (sender unknown; placeholder name = listener vtable)
struct Unk_71024504c8_Payload {
    ksys::act::BaseProcLink _0;
    ksys::act::BaseProcLink _10;
    sead::Vector3f _20 = sead::Vector3f::zero;
    sead::Vector3f _2c = sead::Vector3f::zero;
    sead::JobQueueLock mLock;
};

// Message 0x80000a4 (sender Unk_7102410070)
struct Unk_7102410070_Payload {
    ksys::act::BaseProcLink mLink;
    sead::Vector3f _10;
    sead::Vector3f _1c;
    sead::JobQueueLock mLock;
};

// Message 0x8000007 (sender Unk_710236f520)
struct Unk_710236f520_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        mLink.acquire(proc, false);
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x8000008 (sender Unk_7102372510)
struct Unk_7102372510_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000d3 (sender Unk_7102413398)
struct Unk_7102413398_Payload {
    // Inline only (PriestBossFormation::m35); placeholder name.
    void y(u32 value, ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        _0 = value;
        mLink.acquire(proc, false);
    }

    u32 _0 = 0;
    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000da (sender Unk_7102409958)
struct Unk_7102409958_Payload {
    u32 _0 = 0;
    u32 _4;
    u32 _8;
    u32 _c;
    sead::JobQueueLock mLock;
    u32 _14 = 0;
    ksys::act::BaseProcLink mLink;
};

// Message 0x80000db (sender unknown; placeholder name = listener vtable)
struct Unk_71024508e8_Payload {
    u32 _0;
    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000dc (sender Unk_7102411178)
struct Unk_7102411178_Payload {
    u32 _0 = 0;
    u32 _4 = 0;
    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000d5 (sender Unk_71023b1860)
struct Unk_71023b1860_Payload {
    u32 _0 = 0;
    ksys::act::BaseProcLink mLink;
    bool _18 = false;
    sead::JobQueueLock mLock;
};

// Message 0x80000a5 (sender Unk_7102379de0)
struct Unk_7102379de0_Payload {
    ksys::act::BaseProcLink mLink;
    u32 _10;
    sead::JobQueueLock mLock;
};

// Message 0x8000047 (sender unknown; placeholder name = listener vtable)
struct Unk_7102450738_Payload {
    u32 _0 = 0;
    sead::JobQueueLock mLock;
};

// Message 0x8000017 (sender Unk_71023eaec8)
struct Unk_71023eaec8_Payload {
    ksys::act::BaseProcLink _0;
    ksys::act::BaseProcLink _10;
    sead::Matrix34f _20 = sead::Matrix34f::ident;
    sead::JobQueueLock mLock;
};

// Message 0x80000d8 (sender Unk_7102411f48)
struct Unk_7102411f48_Payload {
    bool _0;
    u32 _4;
    sead::JobQueueLock mLock;
};

// Message 0x80000d4 (sender Unk_7102415df0; placeholder name = listener vtable)
struct Unk_7102450978_Payload {
    u32 _0 = 0;
    ksys::act::BaseProcLink _8;
    ksys::act::BaseProcLink _18;
    u32 _28;
    u32 _2c;
    u32 _30;
    sead::JobQueueLock mLock;
    u32 _38 = 0;
};

// Message 0x80000d7 (sender Unk_71023dbd40)
struct Unk_71023dbd40_Payload {
    u32 _0 = 0;
    u32 _4 = 0;
    u32 _8 = 0;
    bool _c = false;
    sead::JobQueueLock mLock;
};

// Message 0x800005d (sender unknown; placeholder name = listener vtable)
struct Unk_7102450a38_Payload {
    sead::Matrix34f _0;
    u32 _30;
    sead::JobQueueLock mLock;
};

// Message 0x8000029 (sender unknown; placeholder name = listener vtable)
struct Unk_7102450a98_Payload {
    ksys::act::BaseProcLink _0;
    ksys::act::BaseProcLink _10;
    sead::JobQueueLock mLock;
};

// Message 0x800001f (sender Unk_7102396ae0)
struct Unk_7102396ae0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000de (sender Unk_7102413c08; sender method Unk_7102413c08::sub_710070E2BC)
struct Unk_7102413c08_Payload {
    void sub_710070E270(Unk_7102413c08_Payload* out);

    sead::JobQueueLock mLock;
    u32 _4 = 1;
    s32 _8 = -1;
};

// Message 0x80000dd (sender Unk_7102415900). Filled by the sender's non-virtual 0x710070e254 (a
// 0x18-byte copy) from the struct getLifeRecoverParams (0x7100d68598) writes; field types unknown.
struct Unk_7102415900_Payload {
    u64 _0 = 0;
    u64 _8 = 0;
    u64 _10 = 0;
};

// Message 0x8000040 (sender Unk_710235aba0)
struct Unk_710235aba0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000a9 (sender unknown; placeholder name = listener vtable)
struct Unk_7102450a68_Payload {
    ksys::act::BaseProcLink _0;
    sead::Vector3f _10;
    sead::JobQueueLock mLock;
};

// Message 0x8000037 (sender unknown; placeholder name = listener vtable)
struct Unk_7102450be8_Payload {
    ksys::act::BaseProcLink _0;
    ksys::act::BaseProcLink _10;
    sead::Vector3f _20 = sead::Vector3f::zero;
    sead::Vector3f _2c;
    sead::Vector3f _38;
    s32 _44 = 0;
    u32 _48 = 0;
    u32 _4c = 0;
    sead::JobQueueLock mLock;
};

// Message 0x800009c (sender unknown; placeholder name = listener vtable)
struct Unk_71023e7c38_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x800009d (sender unknown; placeholder name = listener vtable)
struct Unk_71023e7c68_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x800009e (sender Unk_7102379988)
struct Unk_7102379988_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000a1 (sender Unk_71023e78b0)
struct Unk_71023e78b0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000a2 (sender unknown; placeholder name = listener vtable)
struct Unk_71023e7cf8_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000b3 (sender unknown; placeholder name = listener vtable)
struct Unk_71023e8ff8_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000bf (sender unknown; placeholder name = listener vtable)
struct Unk_71023e9028_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000c0 (sender unknown; placeholder name = listener vtable)
struct Unk_71023e7d28_Payload {
    sead::Vector3f _0;  // EnemyNormal: a position within its home radius (sub_710039FAA4)
    sead::JobQueueLock mLock;
};

// Message 0x800006e (sender unknown; placeholder name = listener vtable)
struct Unk_7102358dc0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x8000041 (sender Unk_71023e7bc0)
struct Unk_71023e7bc0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        mLink.acquire(proc, false);
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000a3 (sender unknown; placeholder name = listener vtable)
struct Unk_71023799b0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x800009f (sender unknown; placeholder name = listener vtable)
struct Unk_7102379b00_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000a0 (sender unknown; placeholder name = listener vtable)
struct Unk_7102379b30_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000ab (sender Unk_71023d4bb0)
struct Unk_71023d4bb0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    // Inline only (AncientNecklaceBall ctor and init_); placeholder name.
    void y(ksys::act::BaseProc* proc) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        mLink.acquire(proc, false);
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x8000018 (sender unknown; placeholder name = listener vtable)
struct Unk_7102404060_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x8000042 (sender unknown; placeholder name = listener vtable)
struct Unk_710240dd68_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000b8 (sender Unk_71023c5480)
struct Unk_71023c5480_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000cc (sender unknown; placeholder name = listener vtable)
struct Unk_710244e760_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x80000ac (sender unknown; placeholder name = listener vtable)
struct Unk_71024056a8_Payload {
    u32 _0;
    sead::JobQueueLock mLock;
};

// Message 0x80000cf (sender unknown; placeholder name = listener vtable)
struct Unk_710244e7f0_Payload {
    bool _0;
    sead::JobQueueLock mLock;
};

// Message 0x5800000 (sender Unk_71024512c0)
struct Unk_71024512c0_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProcLink* out) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        *out = mLink;
    }

    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// Message 0x800001d (sender Unk_7102399748)
struct Unk_7102399748_Payload {
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(ksys::act::BaseProc* proc, f32 value) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        mLink.acquire(proc, false);
        _10 = value;
    }

    ksys::act::BaseProcLink mLink;
    f32 _10 = 0;
    sead::JobQueueLock mLock;
};

// Message 0x8000037 (sender Unk_7102368740: AssassinBossRoot, AssassinBossFirstBattle and the
// AssassinBossIron* actions); the owners fill it under the lock.
struct Unk_7102368740_Payload {
    ksys::act::BaseProcLink _0;
    ksys::act::BaseProcLink _10;
    sead::Vector3f _20 = sead::Vector3f::zero;
    sead::Vector3f _2c;
    sead::Vector3f _38;
    s32 _44 = 0;
    s32 _48 = 0;
    u32 _4c = 0;
    sead::JobQueueLock mLock;
};

// Message 0x8000083 (sender Unk_71023b0898; the listener at 0x7100903408 copies _0, _8 and _10)
struct Unk_71023b0898_Payload {
    struct Data {
        // 0x71009033fc (in the listener's TU, where the listener inlines it); placeholder name.
        void sub_71009033FC(const Data& other);

        s32 _0 = -1;
        ksys::act::BaseProcLink _8;
    };

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(const Data& data) {
        sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
        _0 = true;
        _8.sub_71009033FC(data);
    }

    bool _0 = true;
    u32 _4;
    Data _8;
    sead::JobQueueLock mLock;
};
