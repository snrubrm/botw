#pragma once

#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace gsys {
class ModelResource;

// The original vtable has Node::getNodeClassType before the own destructors.
// Members and complete allocation extent remain unrecovered.
class CameraAnimation : public sead::hostio::Node {
public:
    virtual ~CameraAnimation();
    static CameraAnimation* create(ModelResource* resource, const sead::SafeString& name,
                                   sead::Heap* heap);
    static void sub_71014092F8(CameraAnimation* animation);
};
}  // namespace gsys
