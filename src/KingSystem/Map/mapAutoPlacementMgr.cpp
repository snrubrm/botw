#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_7100736460.h"
#include "Game/gameStatisticsMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapAutoPlacementFlowMgr.h"

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

int AutoPlacementMgr::sub_7100659158(int idx, bool near_flow) {
    auto* mgr = AutoPlacementFlowMgr::instance();
    return (near_flow ? mgr->getResource2(idx) : mgr->getResource1(idx))->placement_type;
}

// NON_MATCHING: the original loads the placement type with `ldrsb x20` (sign-extended to 64 bits, tested with
// `cbnz x20` after the call); ours loads `ldrb w20` and sign-extends later (for `s8` / `int` / `long` locals alike).
bool AutoPlacementMgr::sub_71006591BC(int idx, bool near_flow) {
    auto* mgr = AutoPlacementFlowMgr::instance();
    const s8 type = (near_flow ? mgr->getResource2(idx) : mgr->getResource1(idx))->placement_type;
    if (dlc::isPlayingOneHitObliteratorQuest() && type == 0)
        return true;
    return _171e68[type] > 0;
}

f32 AutoPlacementMgr::sub_7100659230(const sead::Vector3f& pos) {
    f32 value = 0;
    if (uking::StatisticsMgr::instance()->query(&value, 1, _189db0, &pos))
        return value * 50.0f;
    return 0.0f;
}

f32 AutoPlacementMgr::sub_71006592E8(const sead::Vector3f& pos) {
    f32 value = 0;
    if (uking::StatisticsMgr::instance()->query(&value, 1, _189dd0, &pos))
        return value * 200.0f;
    return 0.0f;
}

// NON_MATCHING: only the select polarity of the free-entry choice (`csel x25, x12, x25, eq` in the original, `csel
// x25, x25, x12, ne` here). `is_box` is a u32 (the original stores the raw argument register).
bool AutoPlacementMgr::sub_7100659E40(act::Actor* actor, const sead::SafeString& actor_name, int count,
                                      u32 is_box) {
    if (u32(count - 1) >= 0x7fff)
        return false;

    auto lock = sead::makeScopedLock(mCS);
    Unk1* free_entry = nullptr;
    for (auto& entry : _5b118) {
        if (entry.actor == actor)
            return false;
        if (!entry.actor && !entry._8b62 && !free_entry)
            free_entry = &entry;
    }
    if (!free_entry)
        return false;

    free_entry->actor = actor;
    free_entry->mtx = actor->getMtx();
    free_entry->scale = actor->getScale();
    free_entry->name = actor_name;
    free_entry->is_box = is_box;
    free_entry->count = count;
    free_entry->_8b62 = true;
    _171e46 = true;
    return true;
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
