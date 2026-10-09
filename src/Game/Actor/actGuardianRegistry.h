#pragma once

#include <container/seadSafeArray.h>
#include <container/seadTList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

class Unk_710243c250;

// DamageInfoMgr +0xb90: constructor 66E194 constructs three 0x68-byte buckets.
class Unk_710243c2a0 {
public:
    virtual ~Unk_710243c2a0();

    /* 0x08 */ sead::TList<Unk_710243c250*> mEntries;
    /* 0x20 */ sead::CriticalSection mLock;
    /* 0x60 */ u32 mSequence = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710243c2a0, 0x68);

class Unk_710243c280 {
public:
    Unk_710243c280();
    virtual ~Unk_710243c280();

    /* 0x008 */ sead::SafeArray<Unk_710243c2a0, 3> mBuckets;
    /* 0x140 */ u32 mSequence = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710243c280, 0x148);
