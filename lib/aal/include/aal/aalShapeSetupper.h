#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEndian.h>

namespace sead {
class Heap;
}

namespace aal {

class ShapeMgr;

/// Creates the shape templates of a ShapeMgr from the shape resource. TODO: only the constructor is modeled.
class ShapeSetupper {
public:
    explicit ShapeSetupper(ShapeMgr* shape_mgr);
    virtual ~ShapeSetupper() = default;

    /// 0x7100b9d40c / 0x7100b9d6f0 (declared only)
    void setup(const void* resource, sead::Heap* heap);

private:
    void setupOld_(const void* resource, sead::Endian::Types endian, sead::Heap* heap);

    ShapeMgr* mShapeMgr;
};

}  // namespace aal
