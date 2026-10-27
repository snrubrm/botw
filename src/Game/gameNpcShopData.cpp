#include "Game/gameNpcShopData.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/Actor/resResourceShop.h"

namespace uking {

// 0x710091ce98: copies the item names of the shop's `table_name` table into the owned items.
// NON_MATCHING: the loop's trip-count guard (`cmp w23, #1; b.lt`) and the count's register are
// missing here, which adds a sign extension and a stack spill (the frame is 0x10 larger).
bool NpcShopData::sub_710091CE98(const ksys::res::Shop* shop, const sead::SafeString& table_name) {
    if (!shop)
        return false;
    if (!ksys::act::InfoData::instance())
        return false;
    const s32 index = shop->findTableIndex(table_name);
    if (index == -1)
        return false;
    const auto& table = shop->getTables()[index];
    const s32 count = table.items.size();
    if (count == 0)
        return false;
    const auto* items = table.items.getBufferPtr();
    for (s64 i = 0; i != count; ++i)
        mItems[i].name.copy(items[i].name.ref());
    mNumItems = count;
    return true;
}

void NpcShopData::sub_710091BA3C() {
    mNumItems = 0;
    mItems.freeBuffer();
}

bool NpcShopData::sub_710091D4C8() {
    for (u32 i = 0; i < u32(mNumItems); ++i) {
        if (mItems[i].count >= 1)
            return false;
    }
    return true;
}

}  // namespace uking
