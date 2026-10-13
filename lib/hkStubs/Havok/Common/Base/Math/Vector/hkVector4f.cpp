#include <Havok/Common/Base/hkBase.h>

void hkVector4f::setRotatedDir(const hkMatrix3f& rotation, hkVector4fParameter direction) {
    _setRotatedDir(rotation, direction);
}

void hkVector4f::setRotatedDir(hkQuaternionfParameter rotation, hkVector4fParameter direction) {
    _setRotatedDir(rotation, direction);
}

void hkVector4f::setRotatedInverseDir(hkQuaternionfParameter rotation,
                                    hkVector4fParameter direction) {
    _setRotatedInverseDir(rotation, direction);
}

void hkVector4f::setTransformedPos(const hkQsTransformf& transform, hkVector4fParameter position) {
    hkVector4f scaled;
    scaled.setMul(position, transform.getScale());
    hkVector4f rotated;
    rotated.setRotatedDir(transform.getRotation(), scaled);
    setAdd(transform.getTranslation(), rotated);
}

void hkVector4f::setTransformedInversePos(const hkQsTransformf& transform,
                                        hkVector4fParameter position) {
    hkVector4f translated;
    translated.setSub(position, transform.getTranslation());
    hkVector4f rotated;
    rotated.setRotatedInverseDir(transform.getRotation(), translated);
    hkVector4f inverseScale;
    inverseScale.setReciprocal(transform.getScale());
    setMul(inverseScale, rotated);
}
