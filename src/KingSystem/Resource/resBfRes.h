#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadPtrArray.h>
#include <container/seadOffsetList.h>
#include <container/seadTList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resUnk_710251A700.h"

namespace nn::gfx {
class ResTexture;
}
namespace nn::g3d {
class ResFile;
}

namespace ksys::res {

void setUseTex2(bool use);

class BfRes;
class Unk_71024F9D48;
class Unk_71024f9958;
// Native FE1310 constructs the path, load parameters and handle; FE1630 fills the
// ResFile and FileDevice pointers. BfRes1200038 consumes this whole loader object.
class Unk_71024f9a70 {
public:
    Unk_71024f9a70();
    virtual ~Unk_71024f9a70();

    struct InitArg {
        bool _0 = true;
        sead::SafeString mPath;
        sead::FileDevice* mFileDevice = nullptr;
    };
    bool init(const InitArg& arg);
    bool load();
    bool sub_7100FE15D8() const;
    bool sub_7100FE1AF0() const;
    s32 getTextureCount() const;
    sead::SafeString getTextureName(s32 index) const;
    bool hasTexture(const sead::SafeString& name) const;

private:
    sead::BitFlag8 mFlags;
    nn::g3d::ResFile* mResFile = nullptr;
    sead::FileDevice* mFileDevice = nullptr;
    sead::Resource* mResource = nullptr;
    sead::FixedSafeString<128> mPath;
    struct LoadParams {
        bool _0 = true;
        sead::SafeString mPath;
        sead::FileDevice* mFileDevice = nullptr;
    } mLoadParams;
    struct LoadStatus {
        bool success = false;
        bool _1 = false;
    };
    // FE15E4 supplies two output bytes and the native parameters at +C0.
    void sub_7100FE1630(LoadStatus* status, const LoadParams& params);
    Handle mHandle;
    // FE1AFC reads eight-byte hash/flag records from this buffer.
    struct TextureFlag {
        u32 hash;
        u8 flag;
    };
    sead::Buffer<TextureFlag> mTextureFlags;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9a70, 0x140);
struct Unk_BfResNode;  // element type of the lists at 0x138 / 0x150 (unknown)

// Vtable 0x71024f9d68 (GOT 0x259ed88): abstract callback interface (D1 0x7100fe85a4 is a shared `ret`, D0 0x7100fe85a8,
// then three pure virtuals); the constructor 0x7100fe8584 sets {vptr, -1, -1} out of line. Placeholder name.
class Unk_71024f9d68 {
public:
    Unk_71024f9d68();
    virtual ~Unk_71024f9d68();
    virtual void m2(const void* arg) = 0;
    virtual void m3(const void* arg) = 0;
    virtual void m4(const void* arg) = 0;

    // FE848C/FE84D4 produce the signed manager generation and current handle;
    // BfRes callbacks 12007B8/12007E4/120086C consume the handle at +8.
    struct CallbackArg {
        s32 mGeneration;
        Unk_71024F9D48* mHandle = nullptr;
    };
    void sub_7100FE85AC(const CallbackArg* arg);
    void sub_7100FE85B8(const CallbackArg* arg);
    void sub_7100FE85DC();

    // FE8584 initializes both words; FE85DC resets only the first one.
    s32 _8;
    s32 _c;
    s32 _10;
};

// Vtable 0x71025149d0 (GOT 0x25a25d0), the callback object at BfRes + 0x168. Its m2 / m3 / m4 are 0x71012007b8,
// 0x71012007e4 and 0x710120086c (declared only); D0 0x7100001200908. The destructor is out of line (a shared `ret`).
class Unk_71025149d0 : public Unk_71024f9d68 {
public:
    explicit Unk_71025149d0(BfRes* owner) : mOwner(owner) {}
    ~Unk_71025149d0() override;
    void m2(const void* arg) override;
    void m3(const void* arg) override;
    void m4(const void* arg) override;

    BfRes* mOwner;
};

// The third base of BfRes (at +0x38, no destructor): its m2 / m3 forward to the object at `_58`. The member names
// are the BfRes offsets. Placeholder name.
class Unk_BfResBase3 {
public:
    virtual void m0() {}
    virtual void m1() {}
    virtual void m2() = 0;
    virtual void m3(const void* arg) = 0;

    u8 _40 = 1;
    u8 _41 = 0;
    void* _48 = nullptr;
    void* _50 = nullptr;
    void* _58 = nullptr;
};

// Placeholder name (vtable 0x71025148f8, typeinfo 0x71025b71c8; ctor 0x71011fe300, size 0x1a8): the bfres
// resource of the texture handle manager. Only the type is modelled (for DynamicCast).
// TODO: incomplete.
class BfRes : public Resource, public Unk_BfResBase3 {
    SEAD_RTTI_OVERRIDE(BfRes, Resource)
public:
    BfRes();
    ~BfRes() override;
    s32 getLoadDataAlignment() const override;
    bool needsParse() const override;
    bool m2_() override;
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    void onDestroy_() override;

    // Overriders of Unk_BfResBase3::m2 / m3 (CSV BfRes::h 0x71012005f8 and BfRes::i 0x7101200628, declared only; the
    // Thn56 thunks 0x7101200610 / 0x7101200680 hold inlined copies): `_58->vslot2()` and, after a call of
    // slot 7 of Unk_710260af28::sInstance, `_58->vslot3(arg)`.
    void m2() override;
    void m3(const void* arg) override;

    // 12007B8 forwards the texture from its callback argument; 11FFD28 updates
    // resource state and invalidates this texture in linked model bindings.
    void sub_71011FFD28(nn::gfx::ResTexture* texture);

    // 0x71011ffecc: invalidates queued textures in all linked model bindings.
    void sub_71011FFECC();

    // Native FDD4A8 produces owner-bearing nodes; 11FFDF4 / 11FFE74 link/unlink them.
    void sub_71011FFDF4(sead::TListNode<Unk_71024f9958*>* node);
    void sub_71011FFE74(sead::TListNode<Unk_71024f9958*>* node);
    // Native 12003D0 decrements a texture entry selected by its CRC32 key; callers do not consume a result.
    void sub_71012003D0(u32 hash);
    // FDD100 forwards a SafeString and the native loader object; independent material-animation
    // callers pass the returned texture to MaterialAnimObj::SetResTexture.
    nn::gfx::ResTexture* sub_7101200038(u32 hash, const sead::SafeString& name,
                                      Unk_71024f9a70* loader);
    nn::gfx::ResTexture* sub_710120033C(u32 hash);

    sead::TList<Unk_71024f9958*> _60;
    sead::CriticalSection _78{nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified};
    sead::CriticalSection _b8{nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified};
    sead::CriticalSection _f8{nullptr, sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified};
    sead::OffsetList<Unk_BfResNode> _138;
    sead::OffsetList<Unk_710251A700::Entry> _150;
    Unk_71025149d0 _168{this};
    // The node of ResourceMgrTask::mBfResList.
    sead::ListNode mListNode;
    // Native ctor zeroes the array; 12007E4 appends texture resources, 11FFECC clears it.
    sead::PtrArray<nn::gfx::ResTexture> _198;
};

KSYS_CHECK_SIZE_NX150(BfRes, 0x1a8);

}  // namespace ksys::res
