#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapRail.h"

namespace ksys::map {

// Initialized by the native rail-type hash initializer at 0x7100d5ccf4.
extern u32 sRailTypeRouteHash;
extern u32 sRailTypeConnectableHash;

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

}  // namespace ksys::map
