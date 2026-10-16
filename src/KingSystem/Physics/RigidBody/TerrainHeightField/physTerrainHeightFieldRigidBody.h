#pragma once

#include <Havok/Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {
class Unk_71011086dc;
}

namespace ksys::tera {
class System;
}

namespace ksys::phys {

// Complete factory 1223864 allocates 18 bytes. Its two-slot table is 25158E8;
// independent divided-mesh and map-patcher lifetimes own and delete these wrappers.
class Unk_71025158e8 {
public:
    // Argument of the factory 0x7101223864; the divided-mesh constructor 0x7100fc5e48 builds one on the stack and
    // makes the four boundary wrappers with `index` 0..3. The factory forwards every field to 0x71012238e4.
    struct Param {
        tera::System* system;
        s32 _8;
        s32 index;
        s32 _10;
        sead::BoundBox2f box;
        sead::Vector2f translation;
        f32 scale;
        f32 _30;
        bool _34;
    };
    KSYS_CHECK_SIZE_NX150(Param, 0x38);

    // 0x7101223864
    static Unk_71025158e8* sub_7101223864(const Param& param, sead::Heap* heap);
    // 0x71012238e4 (CSV makeTerrainHeightFieldRigidBody; declared only)
    void sub_71012238E4(tera::System* system, sead::Heap* heap, s32 a, s32 index, s32 b,
                        const sead::BoundBox2f& box, const sead::Vector2f& translation, f32 scale, f32 c,
                        bool d);

    virtual ~Unk_71025158e8();
    void sub_7101223EC4();
    void sub_7101223F80();
    void sub_7101223F90();
    void sub_7101223FA0();
    bool sub_7101223FB4() const;
    void sub_7101223FC4(SystemGroupHandler* handler);

private:
    /* 0x08 */ RigidBody* mRigidBody = nullptr;
    // The full producer stores a Havok shape here; its concrete interface stays opaque.
    u8 _10[8]{};
};
KSYS_CHECK_SIZE_NX150(Unk_71025158e8, 0x18);

class TerrainHeightFieldRigidBody : public RigidBody {
    SEAD_RTTI_OVERRIDE(TerrainHeightFieldRigidBody, RigidBody)
public:
    ~TerrainHeightFieldRigidBody() override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* shape_key,
                          const sead::Vector3f& contact_point) override;
    bool getD8() const { return _d8; }

protected:
    tera::System* mTerrainSystem{};
    bool _d8 = false;
};
KSYS_CHECK_SIZE_NX150(TerrainHeightFieldRigidBody, 0xe0);

// vtable 0x71025159b0 (placeholder name): the terrain rigid body Unk_71025158e8::sub_71012238E4 builds for
// height field type 6 (shape Unk_7102515b40). It shares TerrainHeightFieldRigidBody's RTTI and D1 and only
// changes the collision masks (material from tera::sub_710110B6A4, filter 6).
class Unk_71025159b0 : public TerrainHeightFieldRigidBody {
public:
    ~Unk_71025159b0() override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* shape_key,
                          const sead::Vector3f& contact_point) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71025159b0, 0xe0);

// vtable 0x7102515a58 (placeholder name): a terrain height field shape (heights from
// tera::sub_71011094A0, with an optional circular hole). Built by Unk_71025158e8::sub_71012238E4 with a
// user-type sampled height field cinfo; 0xe0 bytes.
class alignas(16) Unk_7102515a58 : public hkpSampledHeightFieldShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(Unk_7102515a58)

    // 0x7101224848
    Unk_7102515a58(const hkpSampledHeightFieldBaseCinfo& ci, tera::System* system,
                   const sead::Vector3f& offset, const sead::Vector3f& half_extents,
                   const sead::Vector3f& center, const sead::Vector2f& circle_center, f32 radius,
                   f32 scale, s32 a, s32 b);

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;
    void collideSpheres(const CollideSpheresInput& input,
                        SphereCollisionOutput* outputArray) const override;
    void castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                    hkpRayHitCollector& collector) const override;
    hkReal getHeightAtImpl(int x, int z) const override;
    hkBool getTriangleFlipImpl() const override;
    hkReal sub_71015C398C(hkReal x, hkReal z) const override;
    hkReal sub_71015C3994(hkReal x, hkReal z, hkVector4& normalOut) const override;
    hkUint32 m28(const hkVector4& position) const override;

    // 0x7101224944 (placeholder name): creates the object at 0x98 on `heap` (called by sub_71012238E4).
    void sub_7101224944(sead::Heap* heap);

protected:
    bool isInHole(f32 x, f32 z) const {
        return mRadiusSq > 0.0f && (sead::Vector2f(x, z) - mCircleCenter).squaredLength() < mRadiusSq;
    }

    tera::System* mSystem;
    act::Unk_71011086dc* _98 = nullptr;
    sead::Vector3f mOffset;
    sead::Vector3f mHalfExtents;
    sead::Vector3f mCenter;
    // Heights inside the circle around mCircleCenter (squared radius mRadiusSq) read as 0.
    sead::Vector2f mCircleCenter;
    f32 mRadiusSq;
    f32 mScale;
    s32 _d4;
    s32 _d8;
};
KSYS_CHECK_SIZE_NX150(Unk_7102515a58, 0xe0);

// vtable 0x7102515b40 (placeholder name): heights from tera::sub_710110B4A4. Its ctor 0x7101224e08 inlines
// the Unk_7102515a58 ctor (vtable store) with no hole.
class Unk_7102515b40 : public Unk_7102515a58 {
public:
    HK_DECLARE_CLASS_ALLOCATOR(Unk_7102515b40)

    // 0x7101224e08 (the radius is unused)
    Unk_7102515b40(const hkpSampledHeightFieldBaseCinfo& ci, tera::System* system,
                   const sead::Vector3f& offset, const sead::Vector3f& half_extents,
                   const sead::Vector3f& center, const sead::Vector2f& circle_center, f32 radius,
                   f32 scale, s32 a, s32 b);

    void collideSpheres(const CollideSpheresInput& input,
                        SphereCollisionOutput* outputArray) const override;
    void castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                    hkpRayHitCollector& collector) const override;
    hkReal getHeightAtImpl(int x, int z) const override;
    hkReal sub_71015C398C(hkReal x, hkReal z) const override;
    hkReal sub_71015C3994(hkReal x, hkReal z, hkVector4& normalOut) const override;
    hkUint32 m28(const hkVector4& position) const override;

    // 0x7101224f80 (declaration only, 5204 bytes): the sphere cast.
    void sub_7101224F80(const hkpSphereCastInput& input, const hkpCdBody& cdBody, bool flag,
                        hkpRayHitCollector& collector, hkReal max_extra_penetration,
                        hkReal radius) const;
};

}  // namespace ksys::phys
