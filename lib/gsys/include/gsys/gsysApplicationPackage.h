#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "gsys/gsysModelSceneConfig.h"
#include "gsys/gsysModelShaderHolder.h"
#include "gsys/gsysParticleConfig.h"

namespace sead {
class ArchiveRes;
class Heap;
}  // namespace sead

namespace gsys {

class ModelShader;

// createInstance 0x7100c682a8 allocates 0x38 bytes: vtable, singleton disposer, the package at
// +0x28 and the system model shader archive at +0x30.
class ApplicationPackage : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ApplicationPackage)
public:
    // Only the members the ApplicationPackage accessors use are placed. The destructor
    // 0x7100c68bac also shows a second base at +0x8 (not modelled).
    class Package : public sead::hostio::Node {
    public:
        virtual ~Package();

        void initialize(sead::ArchiveRes* archive, sead::ArchiveRes* system_archive,
                        sead::Heap* heap, sead::Heap* debug_heap);
        bool searchAglShaderFile(void** binary, void** source, const sead::SafeString& name);

        u8 _8[0x4e0 - 0x8];
        ModelSceneConfigList mModelSceneConfigList;
        u8 _pad[0x54648 - 0x4e0 - sizeof(ModelSceneConfigList)];
        ModelShaderHolder mModelShaderHolder;
        ParticleConfig mParticleConfig;
    };

    ApplicationPackage() = default;
    virtual ~ApplicationPackage();

    void initialize(sead::Heap* heap, sead::Heap* debug_heap);
    void setApplicationPackage(sead::ArchiveRes* archive, sead::Heap* heap, sead::Heap* debug_heap);
    const ModelShader* searchModelShader(const sead::SafeString& archive_name,
                                         const sead::SafeString& shader_name) const;
    const ModelShader* getInvalidModelShader() const;
    ParticleConfig* getParticleConfig() const;
    bool searchAglShaderFile(void** binary, void** source, const sead::SafeString& name);
    void setSystemModelShader(sead::ArchiveRes* archive);
    void setupModelSceneConfig(const sead::SafeString& config_name);

private:
    Package* mPackage = nullptr;
    sead::ArchiveRes* mSystemModelShader = nullptr;
};
static_assert(sizeof(ApplicationPackage) == 0x38);

}  // namespace gsys
