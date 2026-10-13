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
