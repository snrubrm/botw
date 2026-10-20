#include "Game/gameNpcShopData.h"

namespace uking {

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
