#pragma once

#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadPtrArray.h>
#include <container/seadTList.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace nn::gfx {
class ResTexture;
}

namespace gsys {
class ModelNW;
class Model;
}

namespace ksys::res {

class BfRes;
class Unk_71024f9a70;

// Placeholder classes of the res TU at 0x7100fdc2a4 - 0x7100fddb70 (CSV StructB / StructA).
// They are the members at ActorData + 0x58 and ActorData + 0x20 (constructed by PlacementActors' ctor, destroyed
// by its D1 and by PlacementActors::deleteActorData).

// Vtable 0x71024f9938 (GOT 0x259eb88): ctor 0x7100fdce2c, D1 0x7100fdce48, D0 0x7100fdcfe8.
class Unk_71024f9938 {
public:
    Unk_71024f9938();
    virtual ~Unk_71024f9938();
    struct InitArg {
        s32 capacity;
        sead::Heap* heap;
        BfRes* resource;
    };
    bool sub_7100FDD00C(const InitArg& arg);
    bool sub_7100FDD0F0() const;
    nn::gfx::ResTexture* sub_7100FDD100(const sead::SafeString& name, Unk_71024f9a70* loader);
    // 0x7100fdcf20 (CSV StructB::x): releases texture hashes and resets the pool.
    void sub_7100FDCF20();

private:
    // FDD00C allocates capacity * 16 bytes: free-list nodes, followed by pointer-array storage.
    BfRes* _8 = nullptr;
    sead::PtrArray<u32> _10;
    sead::FreeList _20;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9938, 0x30);

// Vtable 0x71024f9958 (GOT 0x259eb90): ctor 0x7100fdd21c, D1 0x7100fdd250, D0 0x7100fdd474.
class Unk_71024f9958 {
public:
    struct InitArg {
        InitArg();
        ~InitArg();
        sead::Heap* heap = nullptr;
        BfRes* resource = nullptr;
        const sead::PtrArray<BfRes>* resources = nullptr;
        gsys::Model* model = nullptr;
        gsys::ModelNW* unit = nullptr;
        const sead::PtrArray<gsys::ModelNW>* units = nullptr;
        sead::SafeString name;
    };

    Unk_71024f9958();
    bool sub_7100FDD4A8(const InitArg& arg);
    virtual ~Unk_71024f9958();
    // Nonvirtual cleanup: native D1/D0 call 0x7100fdd264 directly; no vtable slot.
    void sub_7100FDD264();
    // BfRes calls this with a texture resource or null; native body invalidates all model textures.
    void sub_7100FDD9C0(const nn::gfx::ResTexture* texture);
    void sub_7100FDDA60(const sead::PtrArray<nn::gfx::ResTexture>* textures);

private:
    // FDD4A8 allocates these buffers; FDD264 frees them under the allocation heap.
    sead::Heap* _8 = nullptr;
    sead::Buffer<sead::TListNode<Unk_71024f9958*>>* _10 = nullptr;
    // The producer RTTI-casts model units to ModelNW before storing these pointers.
    sead::Buffer<gsys::ModelNW*>* _18 = nullptr;
    sead::Buffer<BfRes*>* _20 = nullptr;
    sead::SafeString _28;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9958, 0x38);

}  // namespace ksys::res
