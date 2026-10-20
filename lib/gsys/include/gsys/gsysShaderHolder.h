#pragma once

#include <common/aglShaderProgramArchive.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace sead {
class ArchiveRes;
class Heap;
}  // namespace sead

namespace gsys {

// createInstance 0x7100c6be38 allocates 0xe8 bytes: vtable, singleton disposer and the shader
// program archive at +0x28.
class ShaderHolder : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ShaderHolder)
public:
    ShaderHolder() = default;
    virtual ~ShaderHolder();

    void initialize(sead::ArchiveRes* archive, sead::Heap* heap, sead::Heap* debug_heap);

private:
    agl::ShaderProgramArchive mProgramArchive;
};
static_assert(sizeof(ShaderHolder) == 0xe8);

}  // namespace gsys
