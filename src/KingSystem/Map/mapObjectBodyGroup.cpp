#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMap.h"
#include "KingSystem/Map/mapPlacementMapMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace ksys::map {

// NON_MATCHING: the original loads the object's index before the PlacementMapMgr pointer (scheduling).
// 0x71011dd3d8 (CSV ActorCreator::c; placeholder name): the field body group of the map object ("FieldBodyGroup" + 1; null when
// the object has none).
phys::StaticCompoundRigidBodyGroup* sub_71011DD3D8(Object* obj) {
    if (obj && obj->getMubinIter().isValid()) {
        s32 group_idx = -1;
        obj->getMubinIter().tryGetParamIntByKey(&group_idx, "FieldBodyGroup");
        ++group_idx;
        auto* map = PlacementMgr::instance()->mPlacementMapMgr->getMap(obj->getIdx());
        if (map->_388 != 1 && group_idx < 1)
            return nullptr;
        return map->getFieldBodyGroup(group_idx);
    }
    return nullptr;
}

}  // namespace ksys::map
