#pragma once

#include <hostio/seadHostIONode.h>

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

private:
    nn::g3d::ResShape* mResShape;
    u8 _10[0x1190 - 0x10];
};
static_assert(sizeof(G3dResShapeEx) == 0x1190);
}  // namespace gsys
