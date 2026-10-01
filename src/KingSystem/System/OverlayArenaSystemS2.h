#pragma once

#include <basis/seadTypes.h>
#include <prim/seadDelegate.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class OverlayArenaSystemS1;
class SystemPauseMgr;

// FIXME: incomplete
class OverlayArenaSystemS2 {
public:
    struct InitArg {
        OverlayArenaSystemS1* s1;
        SystemPauseMgr* system_pause_mgr;
    };

    OverlayArenaSystemS2();

    void init(const InitArg& arg);
    bool x_a() const;

private:
    bool sub_71012BBA50(void* userdata);

    u32 _0 = 0;
    sead::Delegate1R<OverlayArenaSystemS2, void*, bool> mDelegate{
        this, &OverlayArenaSystemS2::sub_71012BBA50};
    u32 _28 = 1;
    void* _30 = nullptr;
    void* _38 = nullptr;
};
KSYS_CHECK_SIZE_NX150(OverlayArenaSystemS2, 0x40);

}  // namespace ksys
