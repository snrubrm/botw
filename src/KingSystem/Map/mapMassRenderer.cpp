#include "KingSystem/Map/mapPlacementMgr.h"

namespace ksys::map {

bool MassRenderer::sub_71011E41F4(const void* p) const {
    for (const auto& slot : _90) {
        if (slot._38 == p)
            return true;
    }
    return false;
}

}  // namespace ksys::map
