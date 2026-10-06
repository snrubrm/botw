#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include <resource/seadResource.h>

namespace ksys::phys {

class ClothResource : public sead::DirectResource {
public:
    ClothResource();
    ~ClothResource() override;

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

    // 0x710121cea0 (lane4 s48; placeholder name): 1 if bit 0 of `_48` is set, 2 for bit 2, 3 for bit 3, 4 for bit 4,
    // 5 for bit 5, else 0.
    s32 sub_710121CEA0() const;
    // The file path ("Physics/Cloth/<name>") InstanceSet::sub_7100FBF368 copies into the resource (`_50`).
    sead::BufferedSafeString& getPath() { return _50; }

private:
    // TODO: rename
    struct Unk2 {
        ~Unk2() { _8.freeBuffer(); }

        void* _0;
        sead::Buffer<u8> _8;
        void* _18;
    };

    // TODO: rename
    struct Unk1 {
        ~Unk1() { _8.freeBuffer(); }

        hkRefPtr<hkReferencedObject> _0;
        sead::Buffer<Unk2> _8;
    };

    u8* _20{};
    sead::Buffer<Unk1> _28;
    int _38{};
    void* _40{};
    u8 _48{};
    sead::FixedSafeString<128> _50;
};

}  // namespace ksys::phys
