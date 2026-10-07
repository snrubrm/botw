#include <prim/seadEnum.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::act {

namespace {
SEAD_ENUM(NavState, None, A, B, C)

NavState readA(ksys::phys::NavMeshCharacter* nav) {
    auto lock = sead::makeScopedLock(nav->_1e0);
    return NavState(nav->_296);
}

NavState readB(ksys::phys::NavMeshCharacter* nav) {
    auto lock = sead::makeScopedLock(nav->_1e0);
    return NavState(nav->_294);
}
}

// NON_MATCHING: the original tests the state against 3, 2, 1 in that order (ours: 1, 2, 3) and builds the flag
// mask with a mov/movk pair instead of a single mov.
// Advances the state `_8` (0 -> 1 -> 2 -> 3) from the character's path state; both state reads are SEAD_ENUM-like
// values taken under the character's critical section (the first one is not used).
void Enemy::Unk_12d0::sub_7100710F28() {
    if (!_0)
        return;
    (void)int(readA(_0));
    const int state = int(readB(_0));
    if (state == 3) {
        if ((_0->_220 & 0x10040000) == 0 && u32(_8 + 1) <= 1)
            _8 = 2;
    } else if (state == 2) {
        if ((_0->_220 & 0x10040000) == 0)
            _8 = 3;
    } else if (state == 1) {
        if ((_0->_220 & 0x10040000) == 0 && _8 == 0)
            _8 = 1;
    }
}

}  // namespace uking::act
