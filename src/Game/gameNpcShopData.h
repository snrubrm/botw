#pragma once

#include <basis/seadTypes.h>

namespace uking {

// Placeholder declaration (name from the CSV: NpcShopData::initFromBshopMaybe 0x710091b7c8,
// NpcShopData::giveItem 0x710091ba74; namespace is a guess). A 0x20-byte polymorphic object (vtable
// at GOT 0x7102579248 -> 0x7102358858, only a trivial virtual destructor) embedded in the NPC actor
// (ctor 0x71001c810) and in the NPCMakeArtifact / NPCPurchase / NPCSale actions at +0x20. Only the
// members that the constructors initialise are declared.
class NpcShopData {
public:
    virtual ~NpcShopData() = default;

    // 0x710091ba3c (declared only): frees the array at +0x10 (allocated with new[], 8-byte cookie)
    // and clears +8 / +0x10 / +0x18. The three actions call it from their destructors.
    void sub_710091BA3C();

    s32 _28 = 0;
    void* _30 = nullptr;
    s32 _38 = 0;
};
static_assert(sizeof(NpcShopData) == 0x20);

}  // namespace uking
