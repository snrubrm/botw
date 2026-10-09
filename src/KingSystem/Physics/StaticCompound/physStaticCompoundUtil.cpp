#include "KingSystem/Physics/StaticCompound/physStaticCompoundUtil.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>

namespace ksys::phys {

// NON_MATCHING: the existing bool callee declaration adds return conversion and prevents the native tail call.
u32 getCollisionFilterInfoFromCollidable(RigidBodyCollisionMasks* p_masks,
                                         u32* p_collision_filter_info,
                                         const hkpCollidable& collidable, const u32* shape_key) {
    *p_collision_filter_info = collidable.getCollisionFilterInfo();
    return getMaterialMaskFromCollidable(p_masks, p_collision_filter_info,
                                         *collidable.getShape(), shape_key);
}

}  // namespace ksys::phys
