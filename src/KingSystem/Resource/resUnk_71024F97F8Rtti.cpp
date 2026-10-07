#include "KingSystem/Resource/resUnk_71024F97F8.h"

namespace ksys::res {

bool Unk_71024F97F8::checkDerivedRuntimeTypeInfoStatic(
    const sead::RuntimeTypeInfo::Interface* typeInfo) {
    if (typeInfo == getRuntimeTypeInfoStatic())
        return true;
    return Resource::checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

}  // namespace ksys::res
