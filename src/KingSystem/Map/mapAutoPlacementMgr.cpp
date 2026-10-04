#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_7100736460.h"

namespace ksys::map {

SEAD_SINGLETON_DISPOSER_IMPL(AutoPlacementMgr)

void AutoPlacementMgr::sub_7100659F94(act::Actor* actor) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : _5b118) {
        if (entry.actor == actor) {
            entry.actor = nullptr;
            _171e46 = true;
            break;
        }
    }
}

bool AutoPlacementMgr::auto0(const sead::Vector3f& pos, u32 placement_type) {
    return _171ef0.x(pos, true, 1 << placement_type, placement_type == 0 ? &_189df8 : nullptr);
}

bool AutoPlacementMgr::isNonAutoPlacement(const sead::Vector3f& pos, bool a2) {
    if (a2) {
        dlc::isPlayingOneHitObliteratorQuest();
        if (_171e68[6] > 0)
            return true;
    }
    return _171ef0.x(pos, true, 0x40, nullptr);
}

bool AutoPlacementMgr::auto9() {
    return _171e48 > 0;
}

// NON_MATCHING: the original reads the counter once more (a discarded volatile load) after the decrement
void AutoPlacementMgr::sub_7100659DE0(int type, bool enable) {
    if (enable) {
        ++_171e4c[type];
        _171e68[type] = 5;
    } else {
        --_171e4c[type];
    }
}

}  // namespace ksys::map
