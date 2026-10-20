#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace sead {
class Heap;
}

namespace gsys {

// Only the members ModelShaderHolder uses are declared (constructor 0x7100c3cc14 builds 0x58 bytes).
class ModelShaderArchive {
public:
    ModelShaderArchive();
    virtual ~ModelShaderArchive();

    void setBinary(void* binary);
    void setup(sead::Heap* heap, sead::Heap* debug_heap);

private:
    u8 _8[0x58 - 0x8];
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

private:
    sead::PtrArray<ModelShaderArchive> mArchives;
    ModelShaderArchive* mInvalidArchive = nullptr;
};
static_assert(sizeof(ModelShaderHolder) == 0x20);

}  // namespace gsys
