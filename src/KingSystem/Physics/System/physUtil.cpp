#include "KingSystem/Physics/System/physUtil.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <Havok/Physics2012/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <math/seadMatrix.h>
#include <math/seadMathCalcCommon.h>
#include <limits>
#include <Havok/Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Havok/Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <Havok/Physics2012/Internal/Collide/BvCompressedMesh/hkpBvCompressedMeshShape.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

MotionType motionTypeFromText(const sead::SafeString& text) {
    static constexpr const char* texts[] = {
        "Dynamic",
        "Fixed",
        "Keyframed",
    };
    static_assert(int(MotionType::Dynamic) == 0);
    static_assert(int(MotionType::Fixed) == 1);
    static_assert(int(MotionType::Keyframed) == 2);

    int type = 0;
    for (const char* type_text : texts) {
        if (text == type_text)
            return static_cast<MotionType>(type);
        ++type;
    }
    return MotionType::Unknown;
}

// NON_MATCHING: the original's mask temporary is 4 bytes (getMaterialMaskFromCollidable only writes
// material_mask), so it keeps one frame instead of tail-calling the height field slot.
u32 getMaterialMaskFromShape(const hkpShape& shape, const u32* shape_key,
                             const sead::Vector3f& position) {
    if (shape.getType() == hkcdShapeType::SAMPLED_HEIGHT_FIELD)
        return static_cast<const hkpSampledHeightFieldShape&>(shape).m28(position);

    RigidBodyCollisionMasks masks;
    u32 collision_filter_info;
    getMaterialMaskFromCollidable(&masks, &collision_filter_info, shape, shape_key);
    return masks.material_mask;
}

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

Unk_71024f9570* Unk_71024f9570::make(sead::Heap* heap, RigidBody* body) {
    auto* listener = new (heap, 8) Unk_71024f9570(body);
    body->getHkBody()->addContactListener(listener);
    return listener;
}

void Unk_71024f9570::destroy(Unk_71024f9570* listener) {
    listener->mBody->getHkBody()->removeContactListener(listener);
    delete listener;
}

// NON_MATCHING: the vector build (the two normalizes and the sign multiply) is scheduled differently; the
// callback is otherwise the original's: it keeps clear of character rigid bodies and only rewrites the
// normal of faces that are steeper than 0.707 and shallower than 0.98.
void Unk_71024f9570::contactPointCallback(const hkpContactPointEvent& event) {
    auto* contact_point = event.m_contactPoint;
    if (contact_point->getPosition().getInt24W() == hkpCharacterRigidBody::m_magicNumber)
        return;
    if (!_10)
        return;

    const f32 sign = getRigidBody(*event.getBody(1)) == mBody ? -1.0f : 1.0f;

    const sead::Vector3f normal = toVec3(contact_point->getSeparatingNormal());
    const f32 dot = -sign * normal.dot(sead::Vector3f::ey);
    if (dot <= 0.707f || dot >= 0.98f)
        return;

    sead::Matrix34f mtx;
    mBody->getTransform(&mtx);

    sead::Vector3f up(-mtx(0, 2), 0.0f, -mtx(2, 2));
    up.normalize();
    up.y = -1.0f;
    up.normalize();
    up *= sign;

    contact_point->setNormalOnly(toHkVec4(up));
}

Unk_71024f95b0* Unk_71024f95b0::make(sead::Heap* heap, RigidBody* body) {
    auto* listener = new (heap, 8) Unk_71024f95b0(body);
    body->getHkBody()->addContactListener(listener);
    return listener;
}

void Unk_71024f95b0::destroy(Unk_71024f95b0* listener) {
    listener->mBody->getHkBody()->removeContactListener(listener);
    delete listener;
}

// NON_MATCHING: the direction build is scheduled differently from the original.
void Unk_71024f95b0::contactPointCallback(const hkpContactPointEvent& event) {
    if (event.m_contactPointProperties->m_flags & hkContactPointMaterial::CONTACT_IS_DISABLED)
        return;

    auto* contact_point = event.m_contactPoint;
    if (contact_point->getPosition().getInt24W() == hkpCharacterRigidBody::m_magicNumber)
        return;

    const f32 sign = getRigidBody(*event.getBody(1)) == mBody ? -1.0f : 1.0f;

    const sead::Vector3f normal = toVec3(contact_point->getSeparatingNormal());
    sead::Matrix34f mtx;
    mBody->getTransform(&mtx);

    if (static_cast<f32>(sead::Mathf::round(sign * normal.dot(sead::Vector3f::ey) * 100.0f)) *
            0.01f >
        0.5f)
        return;

    const sead::Vector3f contact_pos = toVec3(contact_point->getPosition());
    const sead::Vector3f body_pos = toVec3(mBody->getHkBody()->getPosition());
    if (contact_pos.y - body_pos.y > -0.02f)
        return;

    sead::Vector3f dir = body_pos - contact_pos;
    if (dir.normalize() >= std::numeric_limits<f32>::epsilon())
        contact_point->setNormalOnly(toHkVec4(dir * sign));
}

}  // namespace ksys::phys
