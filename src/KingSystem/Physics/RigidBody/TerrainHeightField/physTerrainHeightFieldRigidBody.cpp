#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"
#include <Havok/Common/Base/Types/Geometry/Sphere/hkSphere.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <math/seadMathCalcCommon.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include <Havok/Physics2012/Collide/Query/hkpRayHitCollector.h>
#include "KingSystem/ActorSystem/LOD/actLODMgr.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::phys {

// NON_MATCHING: the original loads `_34` before `_10` (argument scheduling).
Unk_71025158e8* Unk_71025158e8::sub_7101223864(const Param& param, sead::Heap* heap) {
    auto* wrapper = new (heap, 8) Unk_71025158e8;
    wrapper->sub_71012238E4(param.system, heap, param._8, param.index, param._10, param.box,
                            param.translation, param.scale, param._30, param._34);
    return wrapper;
}

void Unk_71025158e8::sub_7101223EC4() {
    if (mRigidBody) {
        delete mRigidBody;
        mRigidBody = nullptr;
    }
}

Unk_71025158e8::~Unk_71025158e8() {
    sub_7101223EC4();
}

void Unk_71025158e8::sub_7101223F80() {
    if (mRigidBody)
        mRigidBody->addToWorld();
}

void Unk_71025158e8::sub_7101223F90() {
    if (mRigidBody)
        mRigidBody->removeFromWorld();
}

void Unk_71025158e8::sub_7101223FA0() {
    if (mRigidBody)
        mRigidBody->removeFromWorldImmediately(nullptr);
}

bool Unk_71025158e8::sub_7101223FB4() const {
    return mRigidBody && mRigidBody->isAddedToWorld();
}

void Unk_71025158e8::sub_7101223FC4(SystemGroupHandler* handler) {
    if (mRigidBody)
        mRigidBody->setSystemGroupHandler(handler);
}

TerrainHeightFieldRigidBody::~TerrainHeightFieldRigidBody() {
    removeFromWorldImmediately(nullptr);
    getHkBody()->setName(nullptr);
    getHkBody()->deallocateInternalArrays();
    getHkBody()->removeReference();
}

// NON_MATCHING: local stack placement and fallback branches differ.
u32 TerrainHeightFieldRigidBody::getCollisionMasks(CollisionMasks* masks, const u32* shape_key,
                                                 const sead::Vector3f& contact_point) {
    Material material = Material::Undefined;
    s32 submaterial = 0;
    const sead::Vector2f xz{contact_point.x, contact_point.z};
    if (!tera::sub_710110C02C(&material, &submaterial, &xz, mTerrainSystem, false)) {
        if (int(material) == -1)
            submaterial = 0;
        material = Material::Undefined;
    }
    masks->material_mask =
        MaterialMask(material, submaterial, FloorCode::None, WallCode::None, true).getRawData();
    masks->collision_filter_info = 8;
    masks->ignored_layers = getIgnoredLayers().getDirect();
    return 0;
}

Unk_71025159b0::~Unk_71025159b0() = default;

// NON_MATCHING: stack slots and the fallback branches differ (as in the base class version).
u32 Unk_71025159b0::getCollisionMasks(CollisionMasks* masks, const u32* shape_key,
                                      const sead::Vector3f& contact_point) {
    Material material = Material::Undefined;
    s32 submaterial = 0;
    const sead::Vector2f xz{contact_point.x, contact_point.z};
    if (!tera::sub_710110B6A4(&material, &submaterial, &xz, mTerrainSystem)) {
        if (int(material) == -1)
            submaterial = 0;
        material = Material::Undefined;
    }
    masks->material_mask =
        MaterialMask(material, submaterial, FloorCode::None, WallCode::None, true).getRawData();
    masks->collision_filter_info = 6;
    masks->ignored_layers = getIgnoredLayers().getDirect();
    return 0;
}

// NON_MATCHING: one commuted operand of the max add (register allocation).
void Unk_7102515a58::getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const {
    hkVector4 center;
    center.load<3>(mCenter.e.data());
    center.zeroComponent<3>();
    hkVector4 half_extents;
    half_extents.load<3>(mHalfExtents.e.data());
    half_extents.zeroComponent<3>();

    hkVector4 x, y, z;
    x.setMul(half_extents.getComponent<0>(), localToWorld.getRotation().getColumn<0>());
    y.setMul(half_extents.getComponent<1>(), localToWorld.getRotation().getColumn<1>());
    z.setMul(half_extents.getComponent<2>(), localToWorld.getRotation().getColumn<2>());
    x.setAbs(x);
    y.setAbs(y);
    z.setAbs(z);

    hkVector4 extents;
    z.setAdd(z, hkSimdReal(tolerance));
    extents.setAdd(x, y);
    extents.add(z);

    hkVector4 world_center;
    world_center._setTransformedPos(localToWorld, center);
    out.m_max.setAdd(world_center, extents);
    out.m_min.setSub(world_center, extents);
}

Unk_7102515a58::Unk_7102515a58(const hkpSampledHeightFieldBaseCinfo& ci, tera::System* system,
                               const sead::Vector3f& offset, const sead::Vector3f& half_extents,
                               const sead::Vector3f& center, const sead::Vector2f& circle_center,
                               f32 radius, f32 scale, s32 a, s32 b)
    : hkpSampledHeightFieldShape(ci, HEIGHTFIELD_USER), mSystem(system), mOffset(offset),
      mHalfExtents(half_extents), mCenter(center), mCircleCenter(circle_center),
      mRadiusSq(radius > 0.0f ? radius * radius : 0.0f), mScale(scale), _d4(a), _d8(b) {
    m_extents.set(half_extents.x + half_extents.x, half_extents.y + half_extents.y,
                  half_extents.z + half_extents.z);
    m_heightCenter = 0;
}

// NON_MATCHING: the original stores `heap` to its stack slot before operator new (scheduling).
void Unk_7102515a58::sub_7101224944(sead::Heap* heap) {
    _98 = new (heap, 8) act::Unk_71011086dc;
    _98->sub_7101108774(heap);
}

hkBool Unk_7102515a58::getTriangleFlipImpl() const {
    return false;
}

// NON_MATCHING: the inlined sub_71015C3994 writes a 12-byte normal in the original (see there).
void Unk_7102515a58::collideSpheres(const CollideSpheresInput& input,
                                    SphereCollisionOutput* outputArray) const {
    const hkSphere* sphere = input.m_spheres;
    const hkSphere dummy({0, 1, 0}, hkSimdReal::getConstant<HK_QUADREAL_MAX>());
    for (int i = input.m_numSpheres - 1; i >= 0; --i) {
        *outputArray = dummy.getPositionAndRadius();
        const hkVector4& pos = sphere->getPositionAndRadius();
        hkReal normal[3];
        const hkReal height = Unk_7102515a58::sub_71015C3994(pos(0), pos(2), normal);
        outputArray->set(normal[0], normal[1], normal[2],
                         (pos(1) - height) * m_intToFloatScale(1) - sphere->getRadius());
        ++sphere;
        ++outputArray;
    }
}

// NON_MATCHING: the original reuses the query position slot for the output (stack coloring) and
// stores the normal earlier.
void Unk_7102515a58::castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                                hkpRayHitCollector& collector) const {
    const hkVector4 from = input.m_from;
    const hkVector4 to = input.m_to;
    const sead::Vector3f offset = mOffset;
    const f32 to_x = to(0) + offset.x;
    const f32 to_z = to(2) + offset.z;
    if (isInHole(to_x, to_z))
        return;

    f32 height = 0;
    sead::Vector3f normal = sead::Vector3f::ey;
    const sead::Vector2f pos(to_x, to_z);
    if (!tera::sub_71011096D0(&height, &normal, &pos, mSystem, -1, 0))
        return;

    const f32 to_y = to(1) + offset.y;
    const f32 radius = input.m_radius;
    if (!(height > to_y - radius))
        return;

    const f32 dx = to_x - (from(0) + offset.x);
    const f32 from_y = from(1) + offset.y;
    const f32 dy = to_y - from_y;
    const f32 dz = to_z - (from(2) + offset.z);

    hkpShapeRayCastOutput output;
    output.m_normal.load<3>(normal.e.data());
    output.m_normal.zeroComponent<3>();
    output.m_hitFraction = 0;

    const f32 length = sead::Mathf::sqrt(dx * dx + dy * dy + dz * dz);
    if (length > 0.0f) {
        const f32 cos = sead::Mathf::abs(dy) / length;
        if (cos > sead::Mathf::epsilon()) {
            const f32 radius_offset = radius / cos;
            const f32 hy = height - from_y;
            const f32 dist = sead::Mathf::sqrt(dx * dx + hy * hy + dz * dz);
            output.m_hitFraction = (dist - radius_offset) / length;
            output.m_hitFraction = sead::Mathf::clamp(output.m_hitFraction, 0.0f, 1.0f);
        }
    }
    output.m_extraInfo = 0;
    collector.addRayHit(cdBody, output);
}

hkReal Unk_7102515a58::getHeightAtImpl(int x, int z) const {
    f32 height = 0;
    const f32 px = x * mScale + mOffset.x;
    const f32 pz = z * mScale + mOffset.z;
    if (isInHole(px, pz))
        return 0.0f;
    const sead::Vector2f pos(px, pz);
    if (tera::sub_71011094A0(&height, &pos, mSystem, -1, 0) == 0)
        return 0.0f;
    return height;
}

hkReal Unk_7102515a58::sub_71015C398C(hkReal x, hkReal z) const {
    f32 height = 0;
    const f32 px = mOffset.x + x;
    const f32 pz = mOffset.z + z;
    if (isInHole(px, pz))
        return 0.0f;
    const sead::Vector2f pos(px, pz);
    if (tera::sub_71011094A0(&height, &pos, mSystem, -1, 0) == 0)
        return 0.0f;
    return height;
}

// NON_MATCHING: the 12-byte normal is written as three floats; the original's store order differs.
hkReal Unk_7102515a58::sub_71015C3994(hkReal x, hkReal z, hkReal (&normalOut)[3]) const {
    f32 height = 0;
    sead::Vector3f normal = sead::Vector3f::ey;
    const f32 px = mOffset.x + x;
    const f32 pz = mOffset.z + z;
    if (isInHole(px, pz)) {
        normalOut[0] = 0;
        normalOut[1] = 1;
        normalOut[2] = 0;
        return 0.0f;
    }
    const sead::Vector2f pos(px, pz);
    if (tera::sub_71011096D0(&height, &normal, &pos, mSystem, -1, 0) == 0)
        return 0.0f;
    normalOut[0] = normal.x;
    normalOut[1] = normal.y;
    normalOut[2] = normal.z;
    return height;
}

// NON_MATCHING: stack slots and the fallback branches differ (as in getCollisionMasks).
hkUint32 Unk_7102515a58::m28(const hkVector4& position) const {
    s32 submaterial = 0;
    Material material = Material::Undefined;
    const sead::Vector2f pos(position(0), position(2));
    if (!tera::sub_710110C02C(&material, &submaterial, &pos, mSystem, false)) {
        if (int(material) == -1)
            submaterial = 0;
        material = Material::Undefined;
    }
    return MaterialMask(material, submaterial, FloorCode::None, WallCode::None, true).getRawData();
}

Unk_7102515b40::Unk_7102515b40(const hkpSampledHeightFieldBaseCinfo& ci, tera::System* system,
                               const sead::Vector3f& offset, const sead::Vector3f& half_extents,
                               const sead::Vector3f& center, const sead::Vector2f& circle_center,
                               f32, f32 scale, s32 a, s32 b)
    : Unk_7102515a58(ci, system, offset, half_extents, center, circle_center, 0.0f, scale, a, b) {}

// NON_MATCHING: the inlined sub_71015C3994 writes a 12-byte normal in the original (see there).
void Unk_7102515b40::collideSpheres(const CollideSpheresInput& input,
                                    SphereCollisionOutput* outputArray) const {
    const hkSphere* sphere = input.m_spheres;
    const hkSphere dummy({0, 1, 0}, hkSimdReal::getConstant<HK_QUADREAL_MAX>());
    for (int i = input.m_numSpheres - 1; i >= 0; --i) {
        *outputArray = dummy.getPositionAndRadius();
        const hkVector4& pos = sphere->getPositionAndRadius();
        hkReal normal[3];
        const hkReal height = Unk_7102515b40::sub_71015C3994(pos(0), pos(2), normal);
        outputArray->set(normal[0], normal[1], normal[2],
                         (pos(1) - height) * m_intToFloatScale(1) - sphere->getRadius());
        ++sphere;
        ++outputArray;
    }
}

void Unk_7102515b40::castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                                hkpRayHitCollector& collector) const {
    sub_7101224F80(input, cdBody, true, collector, input.m_maxExtraPenetration, input.m_radius);
}

hkReal Unk_7102515b40::getHeightAtImpl(int x, int z) const {
    f32 height = 0;
    const sead::Vector2f pos(x * mScale + mOffset.x, z * mScale + mOffset.z);
    const u32 status = tera::sub_710110B4A4(&height, &pos, mSystem);
    if (status == 0 || status == 0xffffffff)
        return 0.0f;
    return height;
}

hkReal Unk_7102515b40::sub_71015C398C(hkReal x, hkReal z) const {
    f32 height = 0;
    const sead::Vector2f pos(mOffset.x + x, mOffset.z + z);
    const u32 status = tera::sub_710110B4A4(&height, &pos, mSystem);
    if (status == 0 || status == 0xffffffff)
        return 0.0f;
    return height;
}

// NON_MATCHING: see Unk_7102515a58::sub_71015C3994 (12-byte normal).
hkReal Unk_7102515b40::sub_71015C3994(hkReal x, hkReal z, hkReal (&normalOut)[3]) const {
    f32 height = 0;
    sead::Vector3f normal = sead::Vector3f::ey;
    const sead::Vector2f pos(mOffset.x + x, mOffset.z + z);
    const u32 status = tera::sub_710110B52C(&height, &normal, &pos, mSystem);
    if (status == 0 || status == 0xffffffff)
        return 0.0f;
    normalOut[0] = normal.x;
    normalOut[1] = normal.y;
    normalOut[2] = normal.z;
    return height;
}

// NON_MATCHING: stack slots and the fallback branches differ (as in getCollisionMasks).
hkUint32 Unk_7102515b40::m28(const hkVector4& position) const {
    s32 submaterial = 0;
    Material material = Material::Undefined;
    const sead::Vector2f pos(position(0), position(2));
    if (!tera::sub_710110B6A4(&material, &submaterial, &pos, mSystem)) {
        if (int(material) == -1)
            submaterial = 0;
        material = Material::Undefined;
    }
    return MaterialMask(material, submaterial, FloorCode::None, WallCode::None, true).getRawData();
}

}  // namespace ksys::phys
