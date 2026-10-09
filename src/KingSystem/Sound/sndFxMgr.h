#pragma once

#include "KingSystem/Utils/Types.h"
#include <basis/seadTypes.h>

namespace sead {
class Heap;
class DrawContext;
class Camera;
class Projection;
class Viewport;
}
namespace ksys::snd {
class Unk_7101059888;

// Whole SoundMgr::init 11fab7c allocates d8 bytes, calls 104fe98 and stores +50.
// Own constructor installs the whole two-slot table 2502520 (D1 104ff34, D0 105004c).
// Whole FxMgr::init 10504fc creates the 98-byte manager at +50; own D1 deletes it.
class FxMgr {
public:
    FxMgr();
    virtual ~FxMgr();
    void init(sead::Heap* heap);
    // Whole SoundMgr::calc 11FB8A4 calls 1050348 with its FxMgr pointer.
    void sub_7101050348();
    // Whole 105034C updates effect state using only this.
    void sub_710105034C();
    void sub_71010511D4();
    void sub_71010514F4(sead::DrawContext* context, const sead::Camera& camera,
                      const sead::Projection& projection, const sead::Viewport& viewport);

    u8 _8[0x50 - 8];
    Unk_7101059888* _50;
    u8 _58[0xa8 - 0x58];
    // Whole calculation 1050104 uses this signed index for the five-float preset table.
    s32 _a8;
    u8 _ac[0xd8 - 0xac];
};
KSYS_CHECK_SIZE_NX150(FxMgr, 0xd8);

}  // namespace ksys::snd
