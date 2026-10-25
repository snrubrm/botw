#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <time/seadDateTime.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class BaseProc;
}

// Name from the native TipsMgr function family. Singleton 0x71025d23d0; constructor 0x710091de54.
// Only the resource and actor members used by the readiness / stage callbacks are recovered.
class TipsMgr {
    SEAD_SINGLETON_DISPOSER(TipsMgr)
    TipsMgr();
    ~TipsMgr();

public:
    void init(sead::Heap* heap);
    bool areResourcesReady();
    // 91E158 loads resources using only the receiver; its final call destroys a load request.
    void loadTipFiles();
    void sub_7100920200();
    void initBeforeStageGen();
    // 0x71009200b4 (placeholder name): stamps every queued tip with the running index, the hour
    // and the current time.
    void sub_71009200B4();

private:
    // A queued tip; only the fields 0x71009200b4 writes are known.
    struct Tip {
        u8 _0[0x40];
        /* 0x40 */ s32 _40;
        /* 0x44 */ s32 _44;
        /* 0x48 */ s32 _48;
        u8 _4c[4];
        /* 0x50 */ u64 _50;
    };
    static_assert(sizeof(Tip) == 0x58);

    // 91E0E0 creates the Tips ExpHeap here; the complete destructor only destroys
    // the resource handles, leaving this heap's lifetime to the parent heap.
    sead::Heap* _20;
    u8 _28[0x150 - 0x28];
    /* 0x150 */ sead::PtrArray<Tip> mTips;
    u8 _160[0x20a0 - 0x160];
    /* 0x20a0 */ s32 _20a0;
    u8 _20a4[4];
    ksys::res::Handle _20a8;
    sead::SafeArray<ksys::res::Handle, 9> _20f8;
    ksys::act::BaseProc* _23c8;
    sead::SafeArray<ksys::res::Handle, 9> _23d0;
    ksys::res::Handle _26a0;
    u8 _26f0[0x26fc - 0x26f0];
    bool _26fc;
};
KSYS_CHECK_SIZE_NX150(TipsMgr, 0x2700);
