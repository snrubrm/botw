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

// NON_MATCHING: existing getRows uses scalar row construction rather than the native packed transpose.
void hkVector4f::setRotatedInverseDir(const hkMatrix3f& rotation, hkVector4fParameter direction) {
    hkMatrix3f inverse;
    rotation.getRows(inverse.m_col0, inverse.m_col1, inverse.m_col2);
    _setRotatedDir(inverse, direction);
}
