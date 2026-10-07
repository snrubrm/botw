#pragma once

#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/GameData/gdtManager.h"

namespace ksys::as {

// Selector with the map-clear flag name and an original empty game-data reinit event slot.
class DungeonClearSelector : public Selector {
    SEAD_RTTI_OVERRIDE(DungeonClearSelector, Selector)
public:
    DungeonClearSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    ~DungeonClearSelector() override;
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);
    int m39(Context* ctx, u32 value, const res::ASResource* resource) override;

private:
    void sub_710131A940(Context* ctx, const res::ASResource* resource);
    gdt::FlagHandle _18;
    sead::FixedSafeString<128> _20;
    gdt::Manager::ReinitSignal::Slot _b8;
};

KSYS_CHECK_SIZE_NX150(DungeonClearSelector, 0x128);

}  // namespace ksys::as
