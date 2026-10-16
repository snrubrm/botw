#pragma once

#include <nn/gfx/detail/gfx_CommandBuffer-api.nvn.8.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_GpuAddress.h>
#include <thread/seadMutex.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::eft {

// Small helper classes of the Effect TU (functions 0x71011b8e5c .. 0x71011b9220). None of them has RTTI; the
// names are placeholders (vtable addresses).

// vtable 0x71025125c8 (13 slots, no destructor slot): an indexed triangle mesh. Two of them are embedded in each
// 0x150-byte record of the Effect array at +0x1840 (at +0x10 and +0xb8; the Effect constructor 0x71011b403c
// zeroes _8 and _c..0x50).
class Unk_71025125c8 {
public:
    using CommandBuffer = nn::gfx::detail::CommandBufferImpl<nn::gfx::DefaultApi>;

    virtual u32 getVertexCountMaybe() const;
    virtual u32 getIndexCount() const;
    virtual void* get18() const;
    virtual void* get20() const;
    virtual void getVertexAddress(nn::gfx::GpuAddress* out) const;
    virtual const nn::gfx::GpuAddress& getIndexAddress() const;
    virtual bool m6() const;
    virtual bool m7() const;
    virtual s32 m8() const;
    virtual nn::gfx::IndexFormat getIndexFormat() const;
    virtual void* get50(u32 idx) const;
    // Triangle list with the index buffer of getIndexAddress / getIndexCount / getIndexFormat.
    virtual void draw(CommandBuffer* buffer, s32 num_instances);
    virtual void draw(CommandBuffer* buffer, s32 num_instances, s32 base_instance);

    bool _8;
    u32 _c;
    u32 _10;
    u32 _14;
    void* _18;
    void* _20;
    u8 _28[8];
    nn::gfx::GpuAddress _30;
    nn::gfx::GpuAddress _40;
    void* _50[9];
};
KSYS_CHECK_SIZE_NX150(Unk_71025125c8, 0x98);

// vtable 0x7102512640 (1 slot): resets three floats.
class Unk_7102512640 {
public:
    virtual void reset();

    f32 _8;
    f32 _c;
    f32 _10;
};

// vtable 0x7102512658 (1 slot): resets its parameters.
class Unk_7102512658 {
public:
    virtual void reset();

    f32 _8;
    f32 _c;
    f32 _10;
    bool _14;
    f32 _18;
    f32 _1c;
    f32 _20;
    f32 _24;
    f32 _28;
};

// vtable 0x7102512670 (4 slots): a lock around a sead::Mutex.
class Unk_7102512670 {
public:
    virtual ~Unk_7102512670();
    virtual void lock();
    virtual void unlock();

    sead::Mutex mMutex;
};

}  // namespace ksys::eft
