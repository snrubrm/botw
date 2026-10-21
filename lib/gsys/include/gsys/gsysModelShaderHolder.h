#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace sead {
class Heap;
}

namespace gsys {

class ModelShader;

// Only the members ModelShaderHolder uses are declared (constructor 0x7100c3cc14 builds 0x58 bytes).
class ModelShaderArchive {
public:
    ModelShaderArchive();
    virtual ~ModelShaderArchive();

    void setBinary(void* binary);
    void setup(sead::Heap* heap, sead::Heap* debug_heap);
    const ModelShader* getModelShader(int index) const;
    // 0x7100c3d244 (declared only; the CSV had an nn::g3d name, but it takes a sead::SafeString and
    // sits in this class's TU).
    const ModelShader* searchModelShader(const sead::SafeString& name) const;
    // ModelShaderHolder::searchModelShader 0x7100c6a768 compares this name.
    const sead::SafeString& getName() const { return mName; }

private:
    u8 _8[0x40 - 0x8];
    sead::SafeString mName;
    u8 _50[0x58 - 0x50];
};
static_assert(sizeof(ModelShaderArchive) == 0x58);

// Constructor 0x7100c6a64c: the archive list at +0x8 and the fallback archive at +0x18.
class ModelShaderHolder : public sead::hostio::Node {
public:
    ModelShaderHolder();
    virtual ~ModelShaderHolder();

    void initialize(sead::Heap* heap, sead::Heap* debug_heap);
    ModelShaderArchive* addModelShaderArchive(void* binary, sead::Heap* heap, sead::Heap* debug_heap);
    void setInvalidModelShaderArchive(ModelShaderArchive* archive);
    const ModelShader* searchModelShader(const sead::SafeString& archive_name,
                                         const sead::SafeString& shader_name) const;
    ModelShaderArchive* getInvalidModelShaderArchive() const { return mInvalidArchive; }

private:
    sead::PtrArray<ModelShaderArchive> mArchives;
    ModelShaderArchive* mInvalidArchive = nullptr;
};
static_assert(sizeof(ModelShaderHolder) == 0x20);

}  // namespace gsys
