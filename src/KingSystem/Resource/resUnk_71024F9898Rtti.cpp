#include "KingSystem/Resource/resUnk_71024F9898.h"

namespace ksys::res {

bool Unk_71024F9898::checkDerivedRuntimeTypeInfoStatic(
    const sead::RuntimeTypeInfo::Interface* typeInfo) {
    if (typeInfo == getRuntimeTypeInfoStatic())
        return true;
    return Resource::checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

}  // namespace ksys::res
