#include "KingSystem/ActorSystem/AS/asDungeonClearSelector.h"
#include "KingSystem/GameData/gdtManager.h"

namespace ksys::as {

// NON_MATCHING: boolean result combination uses a direct conjunction.
int DungeonClearSelector::m39(Context* ctx, u32, const res::ASResource* resource) {
    if (mChildren.size() != 2)
        return 0;
    if (_18 == gdt::InvalidHandle)
        sub_710131A940(ctx, resource);
    bool value = false;
    return gdt::Manager::instance()->getBool(_18, &value) && value;
}

}  // namespace ksys::as
