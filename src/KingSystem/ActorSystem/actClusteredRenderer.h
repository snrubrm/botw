#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {

// TODO
class ClusteredRenderer {
public:
    void startThread();
    void requestDraw();

    u8 _0[0xc9c];
    u32 _c9c;
};

}  // namespace ksys::act
