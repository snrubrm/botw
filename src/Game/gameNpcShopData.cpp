#include "Game/gameNpcShopData.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/Actor/resResourceShop.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiTUStatics.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/GameData/gdtManager.h"
#include <algorithm>

namespace uking {

// The TU's statics (static initializer 0x710091da68): the two additional shop tables are appended to
// the biggest table; they come before the uiTUStatics.h block at 0x71025d2280.
static sead::FixedSafeString<32> sUpdateAdditionalShop("Update_Additional_Shop");
static sead::FixedSafeString<32> sAoCAdditionalShop("AoC_Additional_Shop");

// 0x710091b7c8: sizes the item buffer to the largest table plus the update / DLC additional tables.
bool NpcShopData::initFromBshopMaybe(const ksys::res::Shop* shop, sead::Heap* heap) {
    if (!shop || !heap)
        return false;

    s32 num = 0;
    for (s32 i = 0; i < shop->getNumTables(); ++i) {
        const auto& table = shop->getTables()[i];
        num = std::max(num, table.column_num.ref());
    }

    const s32 index = shop->findTableIndex(sUpdateAdditionalShop);
    if (index != -1) {
        const auto& table = shop->getTables()[index];
        const s32 columns = table.column_num.ref();
        num += table.items.size() > 0 ? columns : 0;
    }

    if (auto* aoc = ksys::aoc::Manager::instance(); aoc && aoc->getVersion()) {
        const s32 aoc_index = shop->findTableIndex(sAoCAdditionalShop);
        if (aoc_index != -1) {
            const auto& table = shop->getTables()[aoc_index];
            const s32 aoc_columns = table.column_num.ref();
            num += table.items.size() > 0 ? aoc_columns : 0;
        }
    }

    if (num < 1)
        return false;

    auto* items = new (heap, 8, std::nothrow) Item[num];
    if (!items)
        return true;
    mItems = sead::Buffer<Item>(num, items);
    return true;
}

// 0x710091ce98: copies the item names of the shop's `table_name` table into the owned items.
// NON_MATCHING: the destination Buffer's bounds check takes the index as s32 here (`smaddl` and a 32-bit
// compare) where the original compares the 64-bit index (`madd`, `cmp x`) - its sead::Buffer::operator[]
// takes a wider index type.
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
    if (count >= 1) {
        for (u64 i = 0; i != u32(count); ++i) {
            const auto& src_name = items[i].name.ref();
            mItems[i].name.copy(src_name);
        }
    }
    mNumItems = count;
    return true;
}

// 0x710091d030: resets the "<actor>_<item>" stock flags of every item of the table: the actor name plus
// '_' is the prefix of every key, the value is the item's _40 - count.
// NON_MATCHING: the prefix copy and the per-item key build are scheduled differently (the original keeps
// the FixedSafeString<128> copy vptr stores and the append's length loads in another order), and the frame
// is 0x20 smaller here.
bool NpcShopData::sub_710091D030(const sead::SafeString& actor_name) {
    auto* mgr = ksys::gdt::Manager::instance();
    sead::FixedSafeString<128> prefix;
    prefix = actor_name;
    prefix.append('_');
    if (mItems.size() == 0)
        return true;
    for (u32 i = 0; i != u32(mItems.size()); ++i) {
        const Item& item = mItems[i];
        sead::FixedSafeString<128> key;
        key = prefix;
        key.append(item.name);
        if (!mgr->setS32(item._40 - item.count, key))
            return false;
    }
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
    if (count >= 1) {
        for (u64 i = 0; i != u32(count); ++i) {
            const auto& item = items[i];
            if (sub_710091D51C(item.name.ref(), a, b)) {
                mItems[num].name.copy(item.name.ref());
                ++num;
            }
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
