#include "Game/Damage/dmgClothStiffnessMgr.h"
#include <prim/seadScopedLock.h>

namespace uking::dmg {

void ClothStiffnessMgr::sub_7100665B20() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mEntries[0]._a8 = nullptr;
    mEntries[0].mRefCount = 0;
    mEntries[1]._a8 = nullptr;
    mEntries[1].mRefCount = 0;
    mEntries[2]._a8 = nullptr;
    mEntries[2].mRefCount = 0;
}

}  // namespace uking::dmg
