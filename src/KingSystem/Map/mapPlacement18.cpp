#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapRail.h"

namespace ksys::map {

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

}  // namespace ksys::map
