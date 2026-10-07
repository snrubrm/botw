#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resUnk_71024F97F8.h"
#include "KingSystem/Resource/resUnk_71024F9898.h"

namespace ksys::res {

bool EntryFactoryBase::checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* typeInfo) {
    const sead::RuntimeTypeInfo::Interface* clsTypeInfo = EntryFactoryBase::getRuntimeTypeInfoStatic();
    if (typeInfo == clsTypeInfo)
        return true;

    return sead::DirectResourceFactoryBase::checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

static EntryFactory<Resource> sDefaultEntryFactory;

template class EntryFactory<Unk_71024F97F8>;
template class EntryFactory<Unk_71024F9898>;

u32 EntryFactoryBase::getResourceSize() const {
    KSYS_CHECK_SIZE_NX150(sead::DirectResource, 0x20);
    return sizeof(sead::DirectResource);
}

u32 EntryFactoryBase::getLoadDataAlignment() const {
    return sizeof(void*);
}

EntryFactory<Resource>& getDefaultResourceFactory() {
    return sDefaultEntryFactory;
}

}  // namespace ksys::res
