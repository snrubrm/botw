#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapRail.h"
#include <random/seadGlobalRandom.h>

namespace ksys::map {

// Initialized by the native rail-type hash initializer at 0x7100d5ccf4.
extern u32 sRailTypeRouteHash;
extern u32 sRailTypeConnectableHash;

Placement18::Placement18(sead::Heap* heap) : _0(nullptr), _8(nullptr), _10(nullptr) {
    if (!Placement18a::instance())
        Placement18a::createInstance(heap);

    _0 = new (heap, 8) RailTypeMap;
    _0->allocBuffer(8, heap);
    _8 = new (heap, 8) sead::PtrArray<sead::PtrArray<Rail>>;
    _10 = new (heap, 8) sead::PtrArray<sead::PtrArray<Rail>>;
    _8->allocBuffer(80, heap);
    _10->allocBuffer(80, heap);
    for (s32 i = 0; i < 80; ++i) {
        auto* routes = new (heap, 8) sead::PtrArray<Rail>;
        routes->allocBuffer(80, heap);
        _8->pushBack(routes);
        auto* connectable = new (heap, 8) sead::PtrArray<Rail>;
        connectable->allocBuffer(16, heap);
        _10->pushBack(connectable);
    }
}

bool sub_7100D4953C(const RailRoute* route, const sead::SafeString& route_ids) {
    if (route_ids.isEmpty())
        return true;
    const char* route_id = route->getRouteId();
    if (!route_id)
        return false;
    return route_ids.findIndex(sead::SafeString(route_id)) != -1;
}

Rail* Placement18::sub_7100D48744(const sead::SafeString& unique_name) {
    return sub_7100D48254(unique_name);
}

Rail* Placement18::sub_7100D48748(s32 cell_idx, u32 rail_type_hash, const u32& hash_id) {
    Rail* rail = sub_7100D487BC(cell_idx, rail_type_hash, hash_id);
    if (!rail) {
        static const s32 offsets[] = {1, -1, 8, -8, 9, -7, 7, -9};
        for (s32 i = 0; !rail && i < 8; ++i)
            rail = sub_7100D487BC(cell_idx + offsets[i], rail_type_hash, hash_id);
    }
    return rail;
}

Rail* Placement18::sub_7100D487BC(s32 cell_idx, u32 rail_type_hash, const u32& hash_id) {
    if (u32(cell_idx) >= 80)
        return nullptr;
    if (rail_type_hash == sRailTypeConnectableHash) {
        for (auto it = _10->unsafeAt(cell_idx)->begin(), end = _10->unsafeAt(cell_idx)->end(); it != end; ++it) {
            const u32& rail_hash = it->getHashId();
            if (hash_id == rail_hash)
                return &*it;
        }
    } else if (rail_type_hash == sRailTypeRouteHash) {
        for (auto it = _8->unsafeAt(cell_idx)->begin(), end = _8->unsafeAt(cell_idx)->end(); it != end; ++it) {
            const u32& rail_hash = it->getHashId();
            if (hash_id == rail_hash)
                return &*it;
        }
    }
    return nullptr;
}

// NON_MATCHING: the second route scan schedules the selection arithmetic and loop registers differently.
const RailConnectablePoint* Placement18::sub_7100D49324(const sead::SafeString& route_ids) {
    s32 total = 0;
    for (s32 i = 0; i < 80; ++i) {
        const s32 count = _8->unsafeAt(i)->size();
        for (s32 j = 0; j < count; ++j) {
            const auto* route = static_cast<const RailRoute*>(_8->at(i)->at(j));
            if (route && sub_7100D4953C(route, route_ids)) {
                const s32 num_points = route->getNumPoints();
                if (num_points > 1)
                    total += num_points;
            }
        }
    }
    s32 index = sead::GlobalRandom::instance()->getU32(total);
    for (s32 i = 0; i < 80; ++i) {
        const s32 count = _8->unsafeAt(i)->size();
        for (s32 j = 0; j < count; ++j) {
            const auto* route = static_cast<const RailRoute*>(_8->unsafeAt(i)->at(j));
            if (route && sub_7100D4953C(route, route_ids)) {
                const s32 num_points = route->getNumPoints();
                if (num_points >= 2) {
                    const s32 remaining = index - num_points;
                    if (remaining <= 0)
                        return static_cast<const RailConnectablePoint*>(route->getPoint(sead::GlobalRandom::instance()->getU32(index)));
                    index = remaining;
                }
            }
        }
    }
    return nullptr;
}

const RailConnectablePoint* Placement18::sub_7100D495B0(const sead::SafeString& point_name) {
    for (s32 i = 0; i < 80; ++i) {
        const s32 count = _8->unsafeAt(i)->size();
        for (s32 j = 0; j < count; ++j) {
            const auto* route = static_cast<const RailRoute*>(_8->at(i)->at(j));
            if (!route)
                continue;
            const s32 num_points = route->getNumPoints();
            for (s32 k = 0; k < num_points; ++k) {
                const char* name = route->getCheckPointName(k);
                if (name && point_name.isEqual(sead::SafeString(name)))
                    return static_cast<const RailConnectablePoint*>(route->getPoint(k));
            }
        }
    }
    return nullptr;
}

void Placement18::sub_7100D49784(f32* min_dist, const RailPoint** closest, const RailRoute* route,
                                   const sead::Vector3f* pos, const sead::SafeString& route_ids) {
    if (!sub_7100D4953C(route, route_ids))
        return;
    const s32 count = route->getNumPoints();
    for (s32 i = 0; i < count; ++i) {
        const auto* point = route->getPoint(i);
        if (point) {
            const auto& translate = point->getTranslate();
            const f32 dx = translate.x - pos->x;
            const f32 dz = translate.z - pos->z;
            const f32 dist = dx * dx + dz * dz;
            if (dist < *min_dist) {
                *min_dist = dist;
                *closest = point;
            }
        }
    }
}

}  // namespace ksys::map
