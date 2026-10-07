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

    sead::CriticalSection mCS;
    u64 _48;
    u32 _50;
    s32 _54;
};

}  // namespace ksys::gfx
