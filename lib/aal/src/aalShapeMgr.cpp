#include "aal/aalShapeMgr.h"
#include <prim/seadScopedLock.h>
#include "aal/aalShape.h"
#include "aal/aalShapeTemplate.h"

namespace aal {

// The body keeps the vtable pointer store of the destructor (a defaulted or empty destructor does not store it).
// 0x7100b9c8cc
ShapeMgr::~ShapeMgr() {
    mTemplates.clear();
}

// 0x7100b9cbac
bool ShapeMgr::createAndRegisterTemplate(const sead::SafeString& name, const ShapeParam& param, sead::Heap* heap) {
    for (ShapeTemplate& shape_template : mTemplates) {
        if (shape_template.getObjName() == name)
            return false;
    }

    ShapeTemplate* shape_template = new (heap, 8) ShapeTemplate;
    shape_template->initialize(name, param);
    mTemplates.pushBack(shape_template);
    return true;
}

// NON_MATCHING: the original only tests the sign of the character difference of the name comparison; here the
// -1 / 1 result of SafeString::compare is computed and compared.
// 0x7100b9c904
void ShapeMgr::addShape(Shape* shape) {
    if (!shape)
        return;

    auto lock = sead::makeScopedLock(mCS);
    mShapes.pushBack(shape);
    mShapes.insertionSort([](const Shape* lhs, const Shape* rhs) {
        return lhs->getObjName().compare(rhs->getObjName()) > 0;
    });
    for (Shape& s : mShapes) {
    }
}

// 0x7100b9cb48
void ShapeMgr::removeShape(Shape* shape) {
    if (!shape)
        return;

    auto lock = sead::makeScopedLock(mCS);
    mShapes.erase(shape);
}

}  // namespace aal
