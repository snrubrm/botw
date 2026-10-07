#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>

namespace ksys::map {
struct Unk_71012497f8Entry;
}

namespace ksys::act {

// TODO
class ClusteredRenderer {
public:
    void startThread();
    void requestDraw();
    // 0x7101244598 (declaration only; placeholder name)
    void sub_7101244598();
    // 0x7101243b70 (declaration only; placeholder name)
    void sub_7101243B70();
    // 0x71012497f8: calls `callback` for every cluster entry within `radius` of `pos`.
    void sub_71012497F8(const sead::Vector3f* pos, f32 radius, bool x,
                        sead::IDelegate1R<map::Unk_71012497f8Entry*, bool>* callback);

    u8 _0[0xc9c];
    u32 _c9c;
};

}  // namespace ksys::act
