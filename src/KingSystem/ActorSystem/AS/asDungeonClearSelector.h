#pragma once

#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

// Recovered prefix only. The string and event-slot tail and their lifetime are unresolved;
// do not construct this partial declaration or infer its full size.
class DungeonClearSelector : public Selector {
    SEAD_RTTI_OVERRIDE(DungeonClearSelector, Selector)
public:
    ~DungeonClearSelector() override;
    int m39(Context* ctx, u32 value, const res::ASResource* resource) override;

private:
    // Undefined and inaccessible only to prevent constructing this partial declaration.
    // The original constructor's source signature is not established.
    DungeonClearSelector();
    void sub_710131A940(Context* ctx, const res::ASResource* resource);
    gdt::FlagHandle _18;
};

}  // namespace ksys::as
