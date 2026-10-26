#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actInfoData.h"

namespace uking::ui {

using RecipeItems = sead::SafeArray<ksys::act::InfoData::RecipeInfo::Item, 3>;

// The buy-check record the shop helpers fill: the purchase type (0 = rupees, 1 = recipe, 2 = mamo,
// -1 while unresolved), the recipe ingredients and the computed price.
struct ShopBuyInfo {
    /* 0x000 */ s32 type = -1;
    u8 _4[4];
    /* 0x008 */ RecipeItems items;
    /* 0x128 */ s32 price = 0;
};
KSYS_CHECK_SIZE_NX150(ShopBuyInfo, 0x130);

void sub_7100A91784(RecipeItems* items, const sead::SafeString& actor);
bool sub_7100A90A34(const RecipeItems& items);

}  // namespace uking::ui
