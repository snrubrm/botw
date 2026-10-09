#pragma once

#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include <prim/seadBitFlag.h>

namespace nn::gfx {
class ResTexture;
}

namespace ksys::res {

// FE0144 installs vtable 24F9A08. Its native texture accessor FE0F8C is declared
// with the proved receiver and return domain; the storage layout stays opaque.
class Unk_71024f9a08;
class Unk_71024F9D48;
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

private:
    void* _8 = nullptr;
    void* _10 = nullptr;
    sead::BitFlag8 _18;
    u8 _19[3];
    u32 _1c = 0;
    u32 _20 = 1;
    Unk_71024f9a08* _28 = nullptr;
    void* _30 = nullptr;
    util::ManagedTaskHandle _38;
};
KSYS_CHECK_SIZE_NX150(Unk_71024F9D48, 0x60);

}  // namespace ksys::res
