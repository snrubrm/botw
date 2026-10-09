#include "KingSystem/Physics/StaticCompound/physStaticCompoundUtil.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

// NON_MATCHING: the shape and group-output pointers use exchanged registers.
void getBodyGroupAndObjectFromSCShape(StaticCompoundRigidBodyGroup** p_body_group,
                                      map::Object** p_object, const hkpShape& shape,
                                      const u32* shape_key) {
    if (shape.getType() == hkcdShapeType::STATIC_COMPOUND) {
        auto* mgr = System::instance()->getStaticCompoundMgr();
        if (mgr) {
            mgr->getBodyGroupAndMapObject(p_body_group, p_object,
                                          static_cast<const hkpStaticCompoundShape&>(shape),
                                          shape_key);
            return;
        }
    }
    *p_body_group = nullptr;
}

// NON_MATCHING: the existing bool callee declaration adds return conversion and prevents the native tail call.
u32 getCollisionFilterInfoFromCollidable(RigidBodyCollisionMasks* p_masks,
                                         u32* p_collision_filter_info,
                                         const hkpCollidable& collidable, const u32* shape_key) {
    *p_collision_filter_info = collidable.getCollisionFilterInfo();
    return getMaterialMaskFromCollidable(p_masks, p_collision_filter_info,
                                         *collidable.getShape(), shape_key);
}

}  // namespace ksys::phys
