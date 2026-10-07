#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace nn::g3d {
class ResFile;
}

namespace gsys {
class IModelResourceCallback;
class ModelShaderArchive;

// Constructor c0b778 and the secondary host-I/O vtable establish these bases.
// Only the independently recovered resource prefix is modeled here.
class ModelResource : public sead::IDisposer, public sead::hostio::Node {
public:
    struct CreateArg {
        explicit CreateArg(void* file);
        void* file;
        // c0b778 consumes this array as ModelShaderArchive pointers.
        sead::FixedPtrArray<ModelShaderArchive, 256> shader_archives;
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

private:
    // ModelResourceMgr c0c80c records the intrusive node offset as +28.
    sead::ListNode mResourceListNode;
    nn::g3d::ResFile* mResFile;
};
}  // namespace gsys
