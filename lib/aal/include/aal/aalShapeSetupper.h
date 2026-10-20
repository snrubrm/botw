#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEndian.h>

namespace sead {
class Heap;
}

namespace aal {

class ShapeMgr;

/// Creates the shape templates of a ShapeMgr from the shape resource.
class ShapeSetupper {
public:
    explicit ShapeSetupper(ShapeMgr* shape_mgr);
    virtual ~ShapeSetupper() = default;

    /// Reads the SHST resource and creates each named shape template.
    bool setup(const void* resource, sead::Heap* heap);

private:
    bool setupOld_(const void* resource, sead::Endian::Types endian, sead::Heap* heap);

    ShapeMgr* mShapeMgr;
};

}  // namespace aal
