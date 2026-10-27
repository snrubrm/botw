#include "Game/gameNpcShopData.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/Actor/resResourceShop.h"
#include "Game/UI/uiPauseMenuDataMgr.h"

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

// 0x710091d8e4: whether any item of the shop's `table_name` table can still be made.
// NON_MATCHING: the original also constructs three unused sead::FixedSafeString<64> locals before the
// loop (three inlined ctors with their out-of-line assureTerminationImpl_ calls); writing them out is
// the only residue.
bool NpcShopData::sub_710091D8E4(const ksys::res::Shop* shop, const sead::SafeString& table_name,
                                 bool a, bool b) {
    if (!shop)
        return false;
    if (!ksys::act::InfoData::instance() || !ui::PauseMenuDataMgr::instance())
        return false;
    const s32 index = shop->findTableIndex(table_name);
    if (index == -1)
        return false;
    const auto& table = shop->getTables()[index];
    const s32 count = table.items.size();
    if (count == 0)
        return false;
    const auto* items = table.items.getBufferPtr();
    for (s64 i = 0; i < count; ++i) {
        if (sub_710091D51C(items[i].name.ref(), a, b))
            return true;
    }
    return false;
}

// 0x710091d6d8: copies the names of the shop table's items that can still be made into the owned items.
// NON_MATCHING: the loop's trip-count guard (`cmp w22, #1; b.lt` -> num = 0) is missing here, which also
// merges the zero initialisation of `num` into the loop entry.
bool NpcShopData::sub_710091D6D8(const ksys::res::Shop* shop, const sead::SafeString& table_name,
                                 bool a, bool b) {
    if (!shop)
        return false;
    if (!ksys::act::InfoData::instance() || !ui::PauseMenuDataMgr::instance())
        return false;
    const s32 index = shop->findTableIndex(table_name);
    if (index == -1)
        return false;
    const auto& table = shop->getTables()[index];
    const s32 count = table.items.size();
    if (count == 0)
        return false;
    const auto* items = table.items.getBufferPtr();
    s32 num = 0;
    for (u64 i = 0; i != count; ++i) {
        const auto& item = items[i];
        if (sub_710091D51C(item.name.ref(), a, b)) {
            mItems[num].name.copy(item.name.ref());
            ++num;
        }
    }
    mNumItems = num;
    return true;
}

bool NpcShopData::sub_710091D4C8() {
    for (u32 i = 0; i < u32(mNumItems); ++i) {
        if (mItems[i].count >= 1)
            return false;
    }
    return true;
}

}  // namespace uking
