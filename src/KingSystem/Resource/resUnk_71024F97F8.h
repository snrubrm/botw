#pragma once

#include "KingSystem/Resource/resResource.h"
#include <utility/aglResParameter.h>

namespace ksys::res {

// Resource with a parameter archive; vtable 0x71024f97f8, constructor 0x7100fdc738.
class Unk_71024F97F8 : public Resource {
public:
    // The original virtual check tail-calls the separate static check at 0x7100fdc884.
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<Resource> typeInfo;
        return &typeInfo;
    }
    static bool checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* typeInfo);
    bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const override {
        return checkDerivedRuntimeTypeInfoStatic(typeInfo);
    }
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override {
        return getRuntimeTypeInfoStatic();
    }

    Unk_71024F97F8();
    ~Unk_71024F97F8() override;
    bool needsParse() const override;
    bool m2_() override;

protected:
    void doCreate_(u8* data, u32 size, sead::Heap* heap) override {}
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    agl::utl::ResParameterArchive mArchive;
};
KSYS_CHECK_SIZE_NX150(Unk_71024F97F8, 0x40);

}  // namespace ksys::res
