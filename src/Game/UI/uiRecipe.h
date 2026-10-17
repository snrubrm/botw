#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actInfoData.h"

namespace uking::ui {

using RecipeItems = sead::SafeArray<ksys::act::InfoData::RecipeInfo::Item, 3>;

void sub_7100A91784(RecipeItems* items, const sead::SafeString& actor);
bool sub_7100A90A34(const RecipeItems& items);

}  // namespace uking::ui
