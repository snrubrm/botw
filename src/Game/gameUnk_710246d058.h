#pragma once

#include <basis/seadTypes.h>

namespace uking {

// Placeholder name (vtable 0x710246d058, RTTI static 0x71025b7c00; TU 0x71008bcf44-0x71008bd9f4).
// The player's controller: Player::initControllerMaybe stores
// DynamicCast<this type>(MaskController::getController(1)) in PlayerBase::_17d0 — the
// sead::Controller-derived part is a secondary base at +8. Not decompiled yet: only the members that
// AI/action code calls are declared.
class Unk_710246d058 {
public:
    // 0x71008bd3bc (CSV name): whether the button mapped to `key` is held. The key -> button mask
    // table is at 0x710246cfa0 (sead::Buffer<u32>, 41 entries); B and X are swapped when the
    // JumpButtonChange flag is set.
    bool playerCheckController(int key) const;
    // 0x71008bd430 (CSV name): same with the trigger mask.
    bool controllerCheckPressedMaybe(int key) const;
};

}  // namespace uking
