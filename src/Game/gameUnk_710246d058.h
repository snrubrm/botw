#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/System/SeadController.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

// Placeholder name (vtable 0x710246d448; ctor 0x71008bf5dc, D1 0x71008bf61c, D0 0x71008bf620).
// Not decompiled: the ctor passes a zero 4-byte value to SeadController and stores its argument in
// _1f8.
class Unk_710246d448 : public ksys::SeadController {
protected:
    void* _1f0;
    s32 _1f8;
};
KSYS_CHECK_SIZE_NX150(Unk_710246d448, 0x200);

// Unknown primary base of Unk_710246d058: 8 bytes, only a virtual destructor (Unk_710246d058's
// vtable starts with D1/D0, followed by its own entries).
class Unk_710246d058Base {
public:
    virtual ~Unk_710246d058Base();
};

// Placeholder name (vtable 0x710246d058, RTTI static 0x71025b7c00; TU 0x71008bcf44-0x71008bd9f4).
// The player's controller: Player::initControllerMaybe stores
// DynamicCast<this type>(MaskController::getController(1)) in PlayerBase::_17d0 — the
// sead::Controller part is the secondary base at +8. Not decompiled yet: only the members that
// AI/action code calls are declared (members at 0x208 and 0x220 are destroyed by 0x71008be9dc).
class Unk_710246d058 : public Unk_710246d058Base, public Unk_710246d448 {
public:
    // 0x71008bd3bc (CSV name): whether the button mapped to `key` is held. The key -> button mask
    // table is at 0x710246cfa0 (sead::Buffer<u32>, 41 entries); B and X are swapped when the
    // JumpButtonChange flag is set.
    bool playerCheckController(int key) const;
    // 0x71008bd430 (CSV name): same with the trigger mask.
    bool controllerCheckPressedMaybe(int key) const;
};

}  // namespace uking
