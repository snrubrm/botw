#include <Havok/Common/Base/hkBase.h>

void hkVector4f::setRotatedDir(const hkMatrix3f& rotation, hkVector4fParameter direction) {
    _setRotatedDir(rotation, direction);
}
