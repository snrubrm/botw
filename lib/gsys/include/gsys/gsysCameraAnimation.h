#pragma once

#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

namespace gsys {
class ModelResource;

// The original vtable has Node::getNodeClassType before the own destructors.
// Size from the create factory (0x71014090b4 allocates 0xa0 bytes with alignment 8); only the
// matrix at +0x70 is recovered. The constructor zeroes the 0x44 bytes at +0x2c, stores two -1
// values at +0x20 and -2.0f at +0x28, and copies Matrix34f::ident to +0x70 (three 16-byte stores
// at +0x70 / +0x80 / +0x90, the same sequence evt::CameraSystem::sub_7100DA44EC writes on its
// camera-animation resource). initialize_ (0x7101409154) fills a 0x18-byte-element buffer whose
// count / buffer live at +0x08 / +0x10 and stores the scene animation pointer at +0x18.
class CameraAnimation : public sead::hostio::Node {
public:
    virtual ~CameraAnimation();
    static CameraAnimation* create(ModelResource* resource, const sead::SafeString& name,
                                   sead::Heap* heap);
    static void sub_71014092F8(CameraAnimation* animation);

private:
    u8 _8[0x70 - 0x8];

public:
    sead::Matrix34f mMatrix;
};
static_assert(sizeof(CameraAnimation) == 0xa0);

}  // namespace gsys
