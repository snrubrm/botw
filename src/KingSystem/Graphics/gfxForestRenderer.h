#pragma once

#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>

namespace ksys::map {
class PlacementMgr;
}

namespace ksys::gfx {

// TODO: incomplete
class ForestRenderer : public sead::hostio::Node {
public:
    virtual ~ForestRenderer();

    s32 x_7(const sead::Vector3f& vec);
    // 0x7100f06798 (CSV x_8; declaration only)
    void x_8(s32 idx, bool a, bool b);
    // 0x7100f03c18 (declaration only; placeholder name)
    void sub_710F03C18(const sead::Vector3f* pos);
    // 0x7100f06904 (declaration only; placeholder name)
    void sub_710F06904(map::PlacementMgr* mgr, bool a);
    bool x_9();
    // 0x7100f03af0 (CSV ForestRenderer::stopped): true unless the renderer has reached state 5 with _220 set in
    // a non-debug, non-dungeon stage (or the final trial); in state 6 it is true if bit 0 of _50 is set and
    // _60 > 3.
    bool stopped();

    sead::CriticalSection mCS;
    u64 _48;
    u32 _50;
    s32 _54;
    u8 _58[0x60 - 0x58];
    s32 _60;
    u8 _64[0x220 - 0x64];
    u32 _220;
};

}  // namespace ksys::gfx
