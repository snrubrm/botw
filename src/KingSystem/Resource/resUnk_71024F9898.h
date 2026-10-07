#pragma once

#include "KingSystem/Resource/resResource.h"
#include <cstddef>

namespace gsys {
class ModelResource;
class CameraAnimation;
}

namespace ksys::res {

// Resource carrying a model and camera animation; vtable 0x71024f9898, constructor 0x7100fdc9f8.
class Unk_71024F9898 : public Resource {
public:
    // The original virtual check tail-calls the separate static check at 0x7100fdccb8.
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

    Unk_71024F9898();
    ~Unk_71024F9898() override;
    static constexpr size_t cLoadDataAlignment = 0x2000;
    s32 getLoadDataAlignment() const override;
    bool needsParse() const override;
    bool m2_() override;

protected:
    void doCreate_(u8* data, u32 size, sead::Heap* heap) override {}
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    void onDestroy_() override;
    void m8_() override {}

    gsys::ModelResource* _38 = nullptr;
    gsys::CameraAnimation* _40 = nullptr;
    void* _48 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_71024F9898, 0x50);

}  // namespace ksys::res
