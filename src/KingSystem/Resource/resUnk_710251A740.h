#pragma once

#include "KingSystem/Resource/resResource.h"

namespace nn::g3d {
class ResFile;
}

namespace ksys::res {

// Resource carrying a ResFile pointer; vtable 0x710251a740, constructor 0x71012bad10.
class Unk_710251A740 : public Resource {
public:
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

    // Native factory alignment getter 0x7100FE2390 returns 4.
    static constexpr size_t cLoadDataAlignment = 4;

    Unk_710251A740();
    ~Unk_710251A740() override;
    bool needsParse() const override;

protected:
    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    nn::g3d::ResFile* _38 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_710251A740, 0x40);

}  // namespace ksys::res
