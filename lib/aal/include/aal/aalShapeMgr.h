#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace aal {

class Shape;
class ShapeTemplate;
struct ShapeParam;

/// Keeps track of all the live shapes (they register in `Shape::create` and unregister in `Shape::destroy`) and of
/// the shape templates. TODO: incomplete (only the shape list is modeled).
class ShapeMgr : public sead::hostio::Node {
public:
    ~ShapeMgr();

    /// Creates a shape template and adds it to the list; false if there is a template with that name already.
    bool createAndRegisterTemplate(const sead::SafeString& name, const ShapeParam& param, sead::Heap* heap);

    /// Adds the shape to the list; the list is kept sorted by the name of the shapes.
    void addShape(Shape* shape);
    void removeShape(Shape* shape);

private:
    sead::OffsetList<ShapeTemplate> mTemplates;
    sead::OffsetList<Shape> mShapes;
    sead::CriticalSection mCS;
    u8 _78[0x128 - 0x78];
};
static_assert(sizeof(ShapeMgr) == 0x128, "aal::ShapeMgr size mismatch");

}  // namespace aal
