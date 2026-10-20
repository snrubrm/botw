#include <gsys/gsysLayer3D.h>

namespace gsys {
bool Layer::checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* type) const {
    return checkDerivedRuntimeTypeInfoStatic(type);
}
const sead::RuntimeTypeInfo::Interface* Layer::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}
bool Layer3D::checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* type) const {
    return checkDerivedRuntimeTypeInfoStatic(type);
}
const sead::RuntimeTypeInfo::Interface* Layer3D::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}
}
