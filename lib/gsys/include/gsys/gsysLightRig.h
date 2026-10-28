#pragma once

#include <basis/seadTypes.h>

namespace gsys {

class Model;

// The base of the light rigs. release_ 0x7100c578c0 / 0x7100c62588 / 0x7100c7c224 only clears the
// pointer at +0x498; the rest of the rig record is not modelled.
template <typename T>
class LightRig {
public:
    void release_(Model*, int) { mScene = nullptr; }

private:
    u8 _0[0x498];
    /* 0x498 */ void* mScene;
};

}  // namespace gsys
