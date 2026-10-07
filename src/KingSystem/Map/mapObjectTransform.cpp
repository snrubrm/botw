#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {
class StaticCompoundRigidBodyGroup;
}

namespace ksys::map {
// 0x71011dd3d8 (CSV ActorCreator::c; declared only; placeholder name): the static compound body group of the map object (null if
// the object has none).
phys::StaticCompoundRigidBodyGroup* sub_71011DD3D8(Object* obj);
}  // namespace ksys::map

// 0x7100ee7168: writes the transform of the map object (rotation and translation), moved by its static compound group (the
// result of the group's transformed matrix is discarded).
bool sub_7100EE7168(const ksys::map::Object* obj, sead::Matrix34f* out) {
    if (!obj)
        return false;
    out->makeRT(obj->getRotate(), obj->getTranslate());
    auto* group = ksys::map::sub_71011DD3D8(const_cast<ksys::map::Object*>(obj));
    if (group) {
        if (auto* system = ksys::phys::System::instance()) {
            if (auto* mgr = system->getStaticCompoundMgr())
                mgr->getTransformedMatrix(group, *out);
        }
    }
    return true;
}
