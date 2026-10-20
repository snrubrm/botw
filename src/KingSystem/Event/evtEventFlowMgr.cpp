#include "KingSystem/ActorSystem/actSchedule.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include <limits>
#include "KingSystem/Event/evtEventFlowMgr.h"
#include <prim/seadScopedLock.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

// 0x7100dbe600
EventFlowMgr::~EventFlowMgr() {
    mSlots.freeBuffer();
    _28.freeBuffer();
    _48.freeBuffer();
    _58.freeBuffer();
    _38.freeBuffer();
    _68.freeBuffer();
}

// 0x7100dbf588
bool EventFlowMgr::areAllEventFlowsReady() const {
    for (s32 i = 0, n = mSlots.size(); i < n; ++i) {
        s32 state = mSlots[i].mState;
        if (state != 3 && state != 0)
            return false;
    }
    return true;
}

// 0x7100dc0024
bool EventFlowMgr::loadEventResourceForAllEventFlows(bool a1) {
    bool ok = true;
    for (s32 i = 0; i < mSlots.size(); ++i) {
        EventFlow& slot = mSlots[i];
        if (slot.mState != 0)
            ok &= slot.loadEventResource(a1);
    }
    return ok;
}

// 0x7100dbeb4c
EventFlow* EventFlowMgr::loadSimple(const sead::SafeString& event_name,
                                    const sead::SafeString& entry_point) {
    return load(event_name, entry_point, false, false, nullptr);
}

// 0x7100dbf048
void EventFlowMgr::unload(EventFlow* flow) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    flow->unload(true);
}

// 0x7100dbe73c
void EventFlowMgr::calc(bool a1) {
    _b8 = true;
    x_0();
    const s32 n = mSlots.size();
    if (n > 0) {
        if (a1) {
            for (s32 i = 0; i < n; ++i)
                mSlots[i].init(true);
        } else {
            for (s32 i = 0; i < n; ++i) {
                if (i % 5 == mCalcCount % 5)
                    mSlots[i].init(false);
            }
        }
    }
    ++mCalcCount;
    _b8 = false;
}

// 0x7100dbf50c
bool EventFlowMgr::sub_7100DBF50C() {
    for (s32 i = 0; i < mSlots.size(); ++i) {
        EventFlow& slot = mSlots[i];
        if (!slot._120 && !slot.sub_7100DC0EEC())
            return false;
    }
    return true;
}

// 0x7100dbf080
EventFlow* EventFlowMgr::acquireEventFlow(const sead::SafeString& event_name,
                                          const sead::SafeString& entry_point) {
    _b8 = true;
    for (s32 i = 0; i < mSlots.size(); ++i) {
        auto& slot = mSlots[i];
        if (u32(slot.mState - 3) <= 1 && slot.mEventName == event_name &&
            slot.mEntryPointName == entry_point) {
            _b8 = false;
            if (slot.mState == 3) {
                slot.setState4();
                return &slot;
            }
            return nullptr;
        }
    }
    _b8 = false;
    return nullptr;
}

// 0x7100dbf72c: releases the slot's flow record and clears the slot
void EventFlowMgr::x(EventMgrStruct3A* entry) {
    if (auto* record = entry->mFlowRecord) {
        if (!record->_0.isEmpty())
            record->sub_7100DC22E0(entry->mActor);
    }
    entry->sub_7101279FFC();
}

// 0x7100dbf778
// NON_MATCHING: the loop index comparison is extended to 64 bits instead of 32 bits.
void EventFlowMgr::x_3(u64* visited, const sead::Vector3f& position,
                      const sead::SafeString& name, EventMgrStruct3A** farthest,
                      f32* farthest_distance, EventMgrStruct3A* source) {
    EventMgrStruct3A* nearest = nullptr;
    f32 nearest_distance = std::numeric_limits<f32>::infinity();
    for (s32 i = 0; i < _28.size(); ++i) {
        auto& entry = _28[i];
        const u64 bit = u64(1) << i;
        if ((*visited & bit) || !entry.mAssigned)
            continue;
        sead::FixedSafeString<64> actor_name;
        entry.formatActorName(&actor_name);
        if (actor_name != name)
            continue;
        *visited |= bit;
        const auto actor_position = entry.mActor->getMtx().getTranslation();
        const f32 distance = sead::Vector2f(actor_position.x - position.x,
                                          actor_position.z - position.z).length();
        if (distance < nearest_distance) {
            nearest = &entry;
            nearest_distance = distance;
        }
        if (!entry.mFlowRecord) {
            entry.setFlowRecord(source->mFlowRecord);
            source->mFlowRecord->loadBaischeduleStuff(&entry);
        }
    }
    if (nearest && nearest_distance > *farthest_distance) {
        *farthest_distance = nearest_distance;
        *farthest = nearest;
    }
}

// 0x7100dbfbac
// NON_MATCHING: native record traversal and actor-name comparison scheduling differ.
void EventFlowMgr::sub_7100DBFBAC(f32 nearest_distance, f32 farthest_distance,
                                 EventMgrStruct3A* nearest, EventMgrStruct3A* farthest) {
    EventMgrStruct3B* record = nullptr;
    for (s32 i = 0; i < _48.size(); ++i) {
        if (_48[i]._0.isEmpty()) {
            record = &_48[i];
            break;
        }
    }
    if (nearest_distance < farthest_distance - 3.0f && farthest && !record) {
        record = farthest->mFlowRecord;
        for (s32 i = 0; i < _28.size(); ++i) {
            auto& entry = _28[i];
            if (entry.mAssigned && entry.mFlowRecord == record) {
                entry.setFlowRecord(nullptr);
                if (!record->_0.isEmpty())
                    record->sub_7100DC22E0(nullptr);
            }
        }
    }
    if (!record)
        return;
    sead::FixedSafeString<64> name;
    nearest->formatActorName(&name);
    record->sub_7100DC1340(0, mCalcCount, name);
    for (s32 i = 0; i < _28.size(); ++i) {
        auto& entry = _28[i];
        if (!entry.mAssigned)
            continue;
        sead::FixedSafeString<64> actor_name;
        entry.formatActorName(&actor_name);
        if (actor_name == name) {
            entry.setFlowRecord(record);
            record->loadBaischeduleStuff(&entry);
        }
    }
}

// 0x7100dbe85c
// NON_MATCHING: native actor traversal and planar-distance scheduling differ.
void EventFlowMgr::x_0() {
    auto* player = act::ActorSystem::instance()->getPlayer();
    if (!player)
        return;
    EventMgrStruct3A* farthest = nullptr;
    f32 farthest_distance = 0;
    u64 visited = 0;
    EventMgrStruct3A* nearest = nullptr;
    f32 nearest_distance = std::numeric_limits<f32>::infinity();
    for (s32 i = 0; i < _28.size(); ++i) {
        auto& entry = _28[i];
        if (!entry.mAssigned)
            continue;
        sead::FixedSafeString<64> name;
        entry.formatActorName(&name);
        const auto position = entry.mActor->getMtx().getTranslation();
        const auto player_position = player->getMtx().getTranslation();
        const f32 distance = sead::Vector2f(position.x - player_position.x,
                                          position.z - player_position.z).length();
        if (!entry.mFlowRecord) {
            if (distance < nearest_distance) {
                nearest = &entry;
                nearest_distance = distance;
            }
        } else {
            if (visited & (u64(1) << i))
                continue;
            x_3(&visited, player->getMtx().getTranslation(), name, &farthest,
                &farthest_distance, &entry);
        }
        x_4(&entry);
    }
    if (nearest)
        sub_7100DBFBAC(nearest_distance, farthest_distance, nearest, farthest);
    x_5(player->getMtx().getTranslation());
    for (s32 i = 0; i < _58.size(); ++i) {
        if (!_58[i]._0.isEmpty() && _58[i]._168 != mCalcCount)
            _58[i].sub_7100DC22E0(nullptr);
    }
    for (s32 i = 0; i < _68.size(); ++i) {
        if (!_68[i]._0.isEmpty() && _68[i]._168 != mCalcCount)
            _68[i].sub_7100DC22E0(nullptr);
    }
}

// 0x7100dbfa00
// NON_MATCHING: empty-slot conditional-select operands are swapped.
void EventFlowMgr::x_4(EventMgrStruct3A* entry) {
    auto* schedule = entry->mActor->getSchedule();
    if (!schedule || schedule->_10.isEmpty())
        return;
    EventMgrStruct3B* empty = nullptr;
    for (s32 i = 0; i < _58.size(); ++i) {
        auto& record = _58[i];
        if (!record._0.isEmpty() && record._0 == schedule->_10) {
            record._168 = mCalcCount;
            return;
        }
        if (record._0.isEmpty())
            empty = &record;
    }
    if (empty) {
        empty->sub_7100DC1340(1, mCalcCount, schedule->_10);
        empty->sub_7100DC1E64();
    }
}

// 0x7100dbfe98
// NON_MATCHING: empty-slot conditional-select operands are swapped.
void EventFlowMgr::x_5(const sead::Vector3f& position) {
    for (s32 i = 0; i < _38.size(); ++i) {
        auto& entry = _38[i];
        if (!entry.mAssigned)
            continue;
        EventMgrStruct3B* empty = nullptr;
        bool found = false;
        for (s32 j = 0; j < _68.size(); ++j) {
            auto& record = _68[j];
            if (!record._0.isEmpty() && record._170 == entry.mActor) {
                record._168 = mCalcCount;
                record._178 = (position - entry.mActor->getMtx().getTranslation()).length();
                found = true;
                break;
            }
            if (record._0.isEmpty())
                empty = &record;
        }
        if (!found && empty) {
            empty->sub_7100DC1340(2, mCalcCount, "EventTag");
            empty->sub_7100DC2090(entry.mActor);
        }
    }
}

}  // namespace ksys::evt
