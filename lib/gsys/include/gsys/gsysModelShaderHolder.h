#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace sead {
class Heap;
}

namespace nn::g3d {
class ResMaterial;
class ResModel;
}  // namespace nn::g3d

namespace gsys {

class ModelShader;

// The shader-variation attribute names ModelShaderVariationKey uses are static lookups on this
// class. Only those are declared here; the instance layout is not modelled yet.
class ModelShader {
public:
    static const char* getAssignID();
    static const char* getAssignVariationID();
    static const char* getVtxSkinWeightName();
    // 0x7100c3c258
    void clearShaderOption();

private:
    u8 _0[0xc8];
    /* 0xc8 */ u32 mShaderOption;
};

// A relocated shading-model record of the shader archive.
class ModelShaderRecord {
public:
    u8 _0[0xc0];
};
static_assert(sizeof(ModelShaderRecord) == 0xc0);

// Only the members ModelShaderHolder uses are declared (constructor 0x7100c3cc14 builds 0x58 bytes).
class ModelShaderArchive {
public:
    ModelShaderArchive();
    virtual ~ModelShaderArchive();

    void setBinary(void* binary);
    void setup(sead::Heap* heap, sead::Heap* debug_heap);
    // 0x7100c3d3a0: the relocated shading-model record at index. The original return type is not
    // recovered; the call sites treat it as opaque.
    const ModelShaderRecord* getModelShader(int index) const;
    // 0x7100c3d244 (declared only; the CSV had an nn::g3d name, but it takes a sead::SafeString and
    // sits in this class's TU).
    const ModelShaderRecord* searchModelShader(const sead::SafeString& name) const;
    // 0x7100c3d3b4 (declared only)
    const ModelShaderRecord* searchModelShader(const nn::g3d::ResModel* model,
                                               const nn::g3d::ResMaterial* material) const;
    // ModelShaderHolder::searchModelShader 0x7100c6a768 compares this name.
    const sead::SafeString& getName() const { return mName; }

private:
    // The relocated shader archive (0x30 is set from ResCast(binary) + 0x20 and passed to
    // nn::g3d::ResShaderArchive::Setup). Each shading-model record is 0xc0 bytes.
    struct ShaderArchive {
        u8 _0[0x10];
        ModelShaderRecord* mRecords;
    };

    u8 _8[0x30 - 0x8];
    ShaderArchive* mShaderArchive;  // 30
    u32 _38;
    u8 _3c[0x40 - 0x3c];
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
    const ModelShaderRecord* searchModelShader(const sead::SafeString& archive_name,
                                               const sead::SafeString& shader_name) const;
    ModelShaderArchive* getInvalidModelShaderArchive() const { return mInvalidArchive; }

private:
    sead::PtrArray<ModelShaderArchive> mArchives;
    ModelShaderArchive* mInvalidArchive = nullptr;
};
static_assert(sizeof(ModelShaderHolder) == 0x20);

}  // namespace gsys
