#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace uking::act {

// Unnamed polymorphic root; placeholder name from its RTTI typeInfo static at 0x71025b1528. It has
// no virtual destructor (the vtable of the derived class below only has the two RTTI slots).
class Unk_71025b1528 {
    SEAD_RTTI_BASE(Unk_71025b1528)
};

// Placeholder name (vtable 0x7102376d50, RTTI static 0x71025b1538). Built inline on the stack by
// DropWeapon, ForkDropWeapon, ForkASTrgWeaponDrop, GuardBreak and Sleep and passed as the `void*`
// argument of playerOrEnemyDropWeapon / ActorWeapons::dropWeapon, which hands it to Weapon::x_4
// (0x71002e5ff0; it DynamicCasts it and reads `mFlags`: bit 0 copies the weapon's parent link, bit 1
// is stored at Weapon+0xf70 and bit 2 at Weapon+0xf71; callers pass 0 or `ChemReset ? 2 : 0`).
class Unk_7102376d50 : public Unk_71025b1528 {
    SEAD_RTTI_OVERRIDE(Unk_7102376d50, Unk_71025b1528)
public:
    sead::BitFlag8 mFlags;
};

}  // namespace uking::act
