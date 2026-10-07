#pragma once

#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include <prim/seadBitFlag.h>

namespace ksys::res {

// Texture-handle helper; vtable 0x71024f9d48, constructor 0x7100fe7e94.
class Unk_71024F9D48 {
public:
    Unk_71024F9D48();
    virtual ~Unk_71024F9D48();
    bool sub_7100FE7FB0() const;
    bool sub_7100FE7FBC(void* arg);
    void sub_7100FE8328(u32 value);
    u32 sub_7100FE8330();
    void sub_7100FE8414(void* resource);
    void sub_7100FE8474(void* resource, u32 status);

private:
    void* _8 = nullptr;
    void* _10 = nullptr;
    sead::BitFlag8 _18;
    u8 _19[3];
    u32 _1c = 0;
    u32 _20 = 1;
    void* _28 = nullptr;
    void* _30 = nullptr;
    util::ManagedTaskHandle _38;
};
KSYS_CHECK_SIZE_NX150(Unk_71024F9D48, 0x60);

}  // namespace ksys::res
