#include "KingSystem/Resource/resUnk_710251A740.h"

namespace ksys::res {

bool Unk_710251A740::checkDerivedRuntimeTypeInfoStatic(
    const sead::RuntimeTypeInfo::Interface* typeInfo) {
    if (typeInfo == getRuntimeTypeInfoStatic())
        return true;
    return Resource::checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

}  // namespace ksys::res
