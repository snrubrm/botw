#include "KingSystem/Physics/StaticCompound/physStaticCompoundUtil.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Havok/Physics2012/Internal/Collide/BvCompressedMesh/hkpBvCompressedMeshShape.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

// NON_MATCHING: shape tests are reordered, the compound instance array is loaded after the filter call,
// and the existing bool return type adds a conversion after recursive calls.
bool getMaterialMaskFromCollidable(RigidBodyCollisionMasks* p_masks, u32* p_collision_filter_info,
                                   const hkpShape& shape, const u32* shape_key) {
    switch (shape.getType()) {
    case hkcdShapeType::LIST: {
        if (*shape_key == HK_INVALID_SHAPE_KEY) {
            p_masks->material_mask = 0;
            *p_collision_filter_info = 0;
            return true;
        }
        hkpShapeBuffer buffer;
        const auto& list = static_cast<const hkpListShape&>(shape);
        const hkpShape* child = list.getChildShape(*shape_key, buffer);
        return getMaterialMaskFromCollidable(p_masks, p_collision_filter_info, *child, shape_key);
    }
    case hkcdShapeType::STATIC_COMPOUND: {
        if (*shape_key == HK_INVALID_SHAPE_KEY) {
            p_masks->material_mask = 0;
            *p_collision_filter_info = 0;
            return true;
        }
        const auto& compound = static_cast<const hkpStaticCompoundShape&>(shape);
        int instance_id;
        hkpShapeKey child_key;
        compound.decomposeShapeKey(*shape_key, instance_id, child_key);
        *p_collision_filter_info = compound.getCollisionFilterInfo(*shape_key);
        return getMaterialMaskFromCollidable(p_masks, p_collision_filter_info,
                                             *compound.getInstances()[instance_id].getShape(),
                                             &child_key);
    }
    case hkcdShapeType::BV_COMPRESSED_MESH: {
        if (*shape_key == HK_INVALID_SHAPE_KEY) {
            p_masks->material_mask = 0;
            *p_collision_filter_info = 0;
            return true;
        }
        const auto& mesh = static_cast<const hkpBvCompressedMeshShape&>(shape);
        if (mesh.getCollisionFilterInfoMode() ==
            hkpBvCompressedMeshShape::PER_PRIMITIVE_DATA_PALETTE)
            *p_collision_filter_info = mesh.getCollisionFilterInfo(*shape_key);
        if (mesh.getUserDataMode() != hkpBvCompressedMeshShape::PER_PRIMITIVE_DATA_NONE)
            p_masks->material_mask = mesh.getPrimitiveUserData(*shape_key);
        else
            p_masks->material_mask = shape.getUserData();
        return false;
    }
    default:
        p_masks->material_mask = shape.getUserData();
        return false;
    }
}

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
