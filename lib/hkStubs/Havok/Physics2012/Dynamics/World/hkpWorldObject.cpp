#include <Havok/Physics2012/Dynamics/World/hkpWorldObject.h>

hkWorldOperation::Result hkpWorldObject::setShape(const hkpShape* shape) {
    return hkWorldOperation::DONE;
}

hkWorldOperation::Result hkpWorldObject::updateShape(hkpShapeModifier* shapeModifier) {
    return hkWorldOperation::DONE;
}
