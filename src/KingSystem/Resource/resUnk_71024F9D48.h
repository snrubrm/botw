#pragma once

#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <container/seadTreeMap.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Thread/Event.h"

namespace nn::gfx {
class ResTexture;
}

namespace ksys::res {

class Unk_71024f9a08;
class CompactedHeap;

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
    bool sub_7100FE0F38() const;
    void sub_7100FE0850();
    bool sub_7100FE0CF8() const;
    bool sub_7100FE0D1C() const;
    u16 sub_7100FE0DE8() const;
    void sub_7100FE0EC8();
    sead::SafeString sub_7100FE0DF0() const;
    sead::SafeString sub_7100FE10A8() const;
    void sub_7100FE10D8();
    void sub_7100FE10EC(CompactedHeap* heap);

    u8 _8[0x18 - 0x8];
    sead::BitFlag8 mFlags;
    u8 mStatus;
    // FE0D38 increments this independently of the current handle-list count.
    u16 _1a;
    u8 _1c[4];
    util::Event mEvent;
    u8 _60[0xb8 - 0x60];
    sead::CriticalSection mCS;
    Unk_71024f9a28 mNode{this};
    // FE0144 constructs this, and FE028C/FE02F0 destroy it.
    util::ManagedTaskHandle mTaskHandle;
    u8 _158[0x168 - 0x158];
    // FE0144 points this at its initialized character buffer at 178.
    char* _168;
    u8 _170[0x29a - 0x170];
    // FE0348 assigns the path using a BufferedSafeString with capacity 126.
    char _29a[0x7e];
    u8 _318[0x618 - 0x318];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9a08, 0x618);
class Unk_71024F9D48;
class Unk_71024f9d68;
// Native FE0D98 removes this handle's list node while holding the resource lock.
void sub_7100FE0D98(Unk_71024f9a08* resource, Unk_71024F9D48* handle);
// Complete native bodies read the same receiver's status/flags and return bool.
bool sub_7100FE0F14(Unk_71024f9a08* resource);
bool sub_7100FE0F44(Unk_71024f9a08* resource);
nn::gfx::ResTexture* sub_7100FE0F8C(Unk_71024f9a08* resource);
void sub_7100FE852C(nn::gfx::ResTexture* texture);

// Texture-handle helper; vtable 0x71024f9d48, constructor 0x7100fe7e94.
class Unk_71024F9D48 {
public:
    Unk_71024F9D48();
    virtual ~Unk_71024F9D48();
    bool sub_7100FE7FB0() const;
    bool sub_7100FE7FBC(void* arg);
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
    util::ManagedTaskHandle _38;
};
KSYS_CHECK_SIZE_NX150(Unk_71024F9D48, 0x60);

}  // namespace ksys::res
