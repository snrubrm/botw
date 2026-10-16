#pragma once

#include <hostio/seadHostIONode.h>

namespace agl::g3d {
class ModelShaderAttribute;
}

namespace nn::g3d {
class ResShape;
}

namespace gsys {

// C6DD78 allocates arrays with stride 0x1190. Native table 24D0D50 has
// Node::getNodeClassType followed by the class's own D1/D0.
class G3dResShapeEx : public sead::hostio::Node {
public:
    G3dResShapeEx();
    virtual ~G3dResShapeEx();

    // Inline-only in the original; name is a guess. C6F3CC stores the resource
    // and independently formats its name, also consumed by callback 1200AC0.
    const nn::g3d::ResShape* getResShape() const { return mResShape; }

    // Inline-only in the original; name is a guess. ksys::tera 0x71011413b4 reads the attribute of
    // each of the 15 passes at +0x30 + pass * 0x100.
    agl::g3d::ModelShaderAttribute* getShaderAttribute(s32 pass) const {
        return mPasses[pass].attribute;
    }

private:
    struct Pass {
        agl::g3d::ModelShaderAttribute* attribute;
        u8 _8[0x100 - 0x8];
    };

    nn::g3d::ResShape* mResShape;
    u8 _10[0x30 - 0x10];
    Pass mPasses[15];
    u8 _f30[0x1190 - 0xf30];
};
static_assert(sizeof(G3dResShapeEx) == 0x1190);
}  // namespace gsys
