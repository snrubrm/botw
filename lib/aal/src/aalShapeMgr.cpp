#include "aal/aalShapeMgr.h"
#include <prim/seadScopedLock.h>
#include "aal/aalShape.h"

namespace aal {

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
