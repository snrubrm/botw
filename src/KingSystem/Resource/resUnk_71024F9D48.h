#pragma once

#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include "KingSystem/Resource/resCompactedHeap.h"
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include <prim/seadStringBuilder.h>
#include <container/seadTreeMap.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Thread/Event.h"
#include <nn/gfx/gfx_ResTexture.h>

namespace sead {
class FileDevice;
}

namespace ksys::res {

class Unk_71024f9a08;
class CompactedHeap;
class Unk_710260e960;
class TextureHandleMgr;
class Unk_71024F9D48;

// FE0144 constructs this key at 118; FE0348 writes its hash at 120.
class Unk_71024f9a50 {
public:
    virtual ~Unk_71024f9a50();

    s32 compare(const Unk_71024f9a50& rhs) const {
        if (mHash < rhs.mHash)
            return -1;
        if (rhs.mHash < mHash)
            return 1;
        return 0;
    }

    u32 mHash;
    Unk_71024f9a08* mOwner = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9a50, 0x18);

// The complete FE67D4 tree consumer uses the key's hash and standard node links.
class Unk_71024f9a28 : public sead::TreeMapNode<Unk_71024f9a50> {
public:
    explicit Unk_71024f9a28(Unk_71024f9a08* owner) { mKey.mOwner = owner; }
    ~Unk_71024f9a28() override;
    void erase_() override;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9a28, 0x38);

// FE2890 allocates 0x618 bytes and calls FE0144, which installs vtable 24F9A08.
// FE0348 sets the status byte and flags independently of the query consumers.
class Unk_71024f9a08 {
public:
    virtual ~Unk_71024f9a08();
    // Whole FE3004 and FE6134 produce this 38-byte request; FE0584 only reads it.
    struct LoadArg {
        bool _0;
        bool _1;
        u8 _2;
        sead::SafeString path;
        sead::FileDevice* device;
        CompactedHeap* heap;
        CompactedHeap* mipHeap;
        nn::gfx::ResTexture* texture;
    };
    KSYS_CHECK_SIZE_NX150(LoadArg, 0x38);
    // Complete FE0584 and FE0860 independently produce the record consumed by FE09EC.
    struct TransferArg {
        bool _0 = false;
        bool _1 = false;
        nn::gfx::ResTexture* texture = nullptr;
        CompactedHeap* heap = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(TransferArg, 0x18);
    // Complete FE5754 produces this pair for release FE0C40.
    struct UnloadArg {
        CompactedHeap* heap;
        CompactedHeap* mipHeap;
    };
    KSYS_CHECK_SIZE_NX150(UnloadArg, 0x10);
    void sub_7100FE0C40(const UnloadArg& arg);
    bool sub_7100FE0348(const sead::SafeString& path, bool reset,
                          CompactedHeap* mipHeap, CompactedHeap* heap);
    // Complete FE04D0 waits for the event and allocation records.
    void sub_7100FE04D0();
    void sub_7100FE09EC(bool* success, const TransferArg& arg);
    bool sub_7100FE0C38(const LoadArg& arg);
    bool sub_7100FE0584(const LoadArg& arg);
    bool sub_7100FE0860(const LoadArg& arg);
    bool sub_7100FE0F38() const;
    bool sub_7100FE0ED0() const;
    void sub_7100FE0E10();
    void sub_7100FE0E64();
    void sub_7100FE0850();
    bool sub_7100FE0CF8() const;
    bool sub_7100FE0D1C() const;
    bool sub_7100FE0D0C() const;
    s64 sub_7100FE10C0() const;
    u32 sub_7100FE0DE8() const;
    void sub_7100FE0EC8();
    sead::SafeString sub_7100FE0DF0() const;
    sead::SafeString sub_7100FE10A8() const;
    void sub_7100FE10D8();
    void sub_7100FE10EC(CompactedHeap* heap);
    sead::FileDevice* sub_7100FE0E08() const;

    u8 _8[0x18 - 0x8];
    sead::BitFlag8 mFlags;
    u8 mStatus;
    // FE0D38 increments this independently of the current handle-list count.
    u16 _1a;
    u8 _1c[4];
    Event mEvent;
    // Complete FE0144 constructs both 0x20-byte allocation records.
    CompactedHeap::Allocation mAllocation;
    CompactedHeap::Allocation mMipAllocation;
    // FE0144 initializes offset 8; FE0D38/FE0D98 insert and erase texture handles.
    sead::OffsetList<Unk_71024F9D48> mHandles;
    sead::CriticalSection mCS;
    Unk_71024f9a28 mNode{this};
    // FE0144 constructs this, and FE028C/FE02F0 destroy it.
    ManagedTaskHandle mTaskHandle;
    // FE0584 copies the request byte; FE0860 uses it in the texture path suffix.
    u8 _158;
    // FE0584 and FE0860 independently set the load-result byte.
    u8 _159;
    u8 _15a[6];
    // FE0584 copies the load device here; FE3760 forwards it to getUncompressedSize.
    sead::FileDevice* mFileDevice;
    // Whole FE0144 sets buffer 178, length 0 and capacity 80; FE0584/FE0860 use
    // StringBuilder::copy/copyAt and its reverse search on the same object.
    sead::FixedStringBuilder<128> mPath;
    // FE0F8C hands &this member to the ResTexture placeholder sub_7100FDDC24.
    nn::gfx::ResTexture _1f8;
    // Complete FE0348 stores the bounded requester path length here.
    u16 mRequesterLength;
    // FE0348 assigns the path using a BufferedSafeString with capacity 126.
    char _29a[0x7e];
    u8 _318[0x618 - 0x318];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9a08, 0x618);
class Unk_71024F9D48;
class Unk_71024f9d68;
void sub_7100FE0D38(Unk_71024f9a08* resource, Unk_71024F9D48* handle);
// Native FE0D98 removes this handle's list node while holding the resource lock.
void sub_7100FE0D98(Unk_71024f9a08* resource, Unk_71024F9D48* handle);
// Complete native bodies read the same receiver's status/flags and return bool.
bool sub_7100FE0F14(Unk_71024f9a08* resource);
bool sub_7100FE0F44(Unk_71024f9a08* resource);
nn::gfx::ResTexture* sub_7100FE0F8C(Unk_71024f9a08* resource);
extern nn::gfx::ResTexture* sUnk_710260EAD0;
void sub_7100FE852C(nn::gfx::ResTexture* texture);

// Texture-loading arguments: complete FE6FC8 constructor and FE7190 consumer.
// The final virtual slot selects path, model or material-animation texture loading.
class Unk_71024f9cf0 {
    SEAD_RTTI_BASE(Unk_71024f9cf0)
public:
    Unk_71024f9cf0();
    virtual ~Unk_71024f9cf0();
    virtual s32 getType() const = 0;

    u8 _8 = 0;
    u8 _9 = 0;
    u8 _a = 1;
    sead::SafeString mPath;
    sead::Heap* mHeap = nullptr;
    sead::FileDevice* mFileDevice = nullptr;
    Unk_71024f9d68* mCallback = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9cf0, 0x38);

// Texture-handle helper; vtable 0x71024f9d48, constructor 0x7100fe7e94.
class Unk_71024F9D48 {
    friend class TextureHandleMgr;
public:
    Unk_71024F9D48();
    virtual ~Unk_71024F9D48();
    bool sub_7100FE7FB0() const;
    bool sub_7100FE7FBC(void* arg);
    bool sub_7100FE8074(const Unk_710260e960* arg);
    void sub_7100FE8328(u32 value);
    u32 sub_7100FE8330();
    bool sub_7100FE8338();
    bool sub_7100FE83CC();
    bool sub_7100FE83DC();
    // The returned texture is consumed by BfRes11FF1B8 ForceBindTexture and
    // independent material-animation SetResTexture calls.
    nn::gfx::ResTexture* sub_7100FE83EC();
    void sub_7100FE8414(Unk_71024f9a08* resource);
    void sub_7100FE8428();
    void sub_7100FE8474(Unk_71024f9a08* resource, u32 status);
    void sub_7100FE848C();
    void sub_7100FE84D4();

private:
    void* _8 = nullptr;
    void* _10 = nullptr;
    sead::BitFlag8 _18;
    u8 _19[3];
    u32 _1c = 0;
    u32 _20 = 1;
    Unk_71024f9a08* _28 = nullptr;
    Unk_71024f9d68* _30 = nullptr;
    ManagedTaskHandle _38;
};
KSYS_CHECK_SIZE_NX150(Unk_71024F9D48, 0x60);

}  // namespace ksys::res
