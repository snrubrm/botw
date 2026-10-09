#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
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
    bool areResourcesReady();
    void sub_7100920200();
    void initBeforeStageGen();

private:
    u8 _20[0x20a8 - 0x20];
    ksys::res::Handle _20a8;
    sead::SafeArray<ksys::res::Handle, 9> _20f8;
    ksys::act::BaseProc* _23c8;
    sead::SafeArray<ksys::res::Handle, 9> _23d0;
    ksys::res::Handle _26a0;
    u8 _26f0[0x26fc - 0x26f0];
    bool _26fc;
};
KSYS_CHECK_SIZE_NX150(TipsMgr, 0x2700);
