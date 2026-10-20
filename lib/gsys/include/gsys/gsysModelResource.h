#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace nn::g3d {
class ResFile;
}

namespace gsys {
class ModelShaderArchive;
class ModelShaderVariationKey;
class G3dResModelEx;
class G3dResMaterialEx;
class G3dResShapeEx;
class G3dResAnimationEx;
namespace ModelEnum {
enum class ShaderAssignType;
}
enum class MaterialAnmType;

// BfRes +38 is a borrowed callback receiver (11FE614); its constructor and
// destructor install four-slot tables with no virtual destructor slots.
class IModelResourceCallback {
public:
    // Reconstructed names for native argument records. ResourceArg and
    // MaterialArg remain opaque.
    // C0B778/C0C024 produce {ResFile*, ModelResource*} for slots 0/1.
    struct ResourceArg;
    // C6F5EC produces a variation key, two selectors, model, material and shape
    // for slot 2; 1200AC0 consumes the same record.
    struct ShaderAssignArg {
        ModelShaderVariationKey* variation_key;
        ModelEnum::ShaderAssignType assign_type;
        s32 variation;
        const G3dResModelEx* model;
        const G3dResMaterialEx* material;
        const G3dResShapeEx* shape;
    };
    static_assert(sizeof(ShaderAssignArg) == 0x28);
    // C811C0 produces {G3dResMaterialEx*, render-info receiver} for slot 3.
    struct MaterialArg;

    virtual void m0(const ResourceArg& arg, sead::Heap* heap) {}
    virtual void m1(const ResourceArg& arg) {}
    virtual void m2(const ShaderAssignArg& arg);
    virtual void m3(const MaterialArg& arg);
};

// Constructor c0b778 and the secondary host-I/O vtable establish these bases.
// Only the independently recovered resource prefix is modeled here.
class ModelResource : public sead::IDisposer, public sead::hostio::Node {
public:
    struct CreateArg {
        explicit CreateArg(void* file);
        void* file;
        // c0b778 consumes this array as ModelShaderArchive pointers.
        sead::FixedPtrArray<ModelShaderArchive, 256> shader_archives;
        // 0x7100c0a9b8: appends when the array has room.
        void pushBack(ModelShaderArchive* archive);
        bool _818;
        u8 _819;
        bool _81a;
        bool _81b;
        bool _81c;
        s32 buffer_count;
        IModelResourceCallback* callback;
    };

    ModelResource(const CreateArg& arg, sead::Heap* heap, sead::Heap* resource_heap);
    ~ModelResource() override;
    static ModelResource* create_(const CreateArg& arg, sead::Heap* heap);
    static void sub_7100C0B764(ModelResource* resource);
    size_t getResFileSize() const;

    // inline-only in the original; name is a guess. Resource creation c0b8ec stores +38;
    // model creation bf66b0 and getResFileSize c0c264 independently read it.
    nn::g3d::ResFile* getResFile() const { return mResFile; }
    // 0x7100c0c26c (name is a guess): the G3dResModelEx of model `index` (array at +0x40, stride 0x3f0;
    // ksys::tera 0x71011413b4 passes a ResFile::FindModelIndex result).
    G3dResModelEx* getResModelEx(s32 index) const;
    // 0x7100c0c27c / 0x7100c0c28c: the 0x18-byte skeletal animation records at +0x50 and, per
    // material-animation type, the record array at +0x58 + type * 8.
    G3dResAnimationEx* getG3dResSkeletalAnmEx(s32 index);
    G3dResAnimationEx* getG3dResMaterialAnmEx(MaterialAnmType type, s32 index);

private:
    // ModelResourceMgr c0c80c records the intrusive node offset as +28.
    sead::ListNode mResourceListNode;
    nn::g3d::ResFile* mResFile;
    G3dResModelEx* mResModelExs;
    u8 _48[8];
    G3dResAnimationEx* mSkeletalAnms;
    // Inline array indexed by MaterialAnmType (0x7100c0c28c adds type * 8 to this and loads
    // +0x58); the enum's extent is unproved, so eight slots are reserved.
    G3dResAnimationEx* mMaterialAnms[8];
};
}  // namespace gsys
