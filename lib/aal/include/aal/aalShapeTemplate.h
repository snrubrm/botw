#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <math/seadVector.h>
#include "aal/aalNamedObj.h"

namespace aal {

/// The parameters of a shape (what a shape template creates its shapes with). TODO: the meanings of the fields are not
/// known.
struct ShapeParam {
    u32 _0 = 0;
    sead::Vector3f _4 = sead::Vector3f::zero;
    sead::Vector3f _10 = sead::Vector3f::zero;
    sead::Vector3f _1c = sead::Vector3f::zero;
    u32 _28 = 0;
    bool _2c = true;
    bool _2d = true;
    bool _2e = false;
};
static_assert(sizeof(ShapeParam) == 0x30, "aal::ShapeParam size mismatch");

/// A named set of shape parameters that is kept in the list of the ShapeMgr.
class ShapeTemplate : public FixedNamedObj<32> {
public:
    ShapeTemplate();
    ~ShapeTemplate() override = default;

    void initialize(const sead::SafeString& name, const ShapeParam& param);

    /// The node in the list of the shape templates of the ShapeMgr.
    sead::ListNode mListNode;

private:
    ShapeParam mParam;
};
static_assert(sizeof(ShapeTemplate) == 0x90, "aal::ShapeTemplate size mismatch");

}  // namespace aal
