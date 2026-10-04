#include "Game/Damage/dmgDamageManager.h"

namespace uking::dmg {

void DamageManager::preDelete1() {
    if (mStruct20_a) {
        delete mStruct20_a;
        mStruct20_a = nullptr;
    }
    if (mStruct20_b) {
        delete mStruct20_b;
        mStruct20_b = nullptr;
    }
}

s32 DamageManager::sub_71006D8534() const {
    return _220 ? _220->_10 : 0;
}

}  // namespace uking::dmg
