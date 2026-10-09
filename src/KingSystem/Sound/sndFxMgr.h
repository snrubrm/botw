#pragma once

#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
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

    u8 _8[0x50 - 8];
    Unk_7101059888* _50;
    u8 _58[0xd8 - 0x58];
};
KSYS_CHECK_SIZE_NX150(FxMgr, 0xd8);

}  // namespace ksys::snd
