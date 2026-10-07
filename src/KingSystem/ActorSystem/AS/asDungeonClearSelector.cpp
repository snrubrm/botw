#include "KingSystem/ActorSystem/AS/asDungeonClearSelector.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/System/StageInfo.h"

namespace ksys::as {

DungeonClearSelector::DungeonClearSelector(const CreateArg&, s32, const res::ASResource*)
    : _18(gdt::InvalidHandle) {}

DungeonClearSelector::~DungeonClearSelector() = default;


// NON_MATCHING: boolean result combination uses a direct conjunction.
int DungeonClearSelector::m39(Context* ctx, u32, const res::ASResource* resource) {
    if (mChildren.size() != 2)
        return 0;
    if (_18 == gdt::InvalidHandle)
        sub_710131A940(ctx, resource);
    bool value = false;
    return gdt::Manager::instance()->getBool(_18, &value) && value;
}

// NON_MATCHING: the destination string address is computed earlier.
void DungeonClearSelector::sub_710131A940(Context* ctx, const res::ASResource* resource) {
    if (ctx) {
        ASList* list = ctx->mList;
        sead::SafeString name(list->sub_710115ECF4(sub_7101165408(resource), 0));
        const sead::SafeString& map_name = name.isEmpty() ? StageInfo::getCurrentMapName() : name;
        _20.format("Clear_%s", map_name.cstr());
    }
    _18 = gdt::Manager::instance()->getBoolHandle(_20);
}

}  // namespace ksys::as
