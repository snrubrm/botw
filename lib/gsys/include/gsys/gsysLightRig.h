#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace gsys {

class Model;

// The base of the light rigs. release_ 0x7100c578c0 / 0x7100c62588 / 0x7100c7c224 only clears the
// pointer at +0x498; the rest of the rig record is not modelled.
template <typename T>
class LightRig {
public:
    // 0x7100c58704 / 0x7100c633c8 / 0x7100c7cd00: the base update hook does nothing.
    virtual void updateObj_(T* obj, const sead::Matrix34f& view, const sead::Color4f& color_a,
                            const sead::Color4f& color_b, const sead::Vector3f& position, f32 a,
                            f32 b) const {}

    void release_(Model*, int) { mScene = nullptr; }

private:
    u8 _0[0x490];
    /* 0x498 */ void* mScene;
};

}  // namespace gsys
