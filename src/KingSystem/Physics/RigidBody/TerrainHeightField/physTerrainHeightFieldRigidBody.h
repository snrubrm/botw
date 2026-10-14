#pragma once

#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

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

private:
    tera::System* mTerrainSystem{};
    bool _d8 = false;
};
KSYS_CHECK_SIZE_NX150(TerrainHeightFieldRigidBody, 0xe0);

}  // namespace ksys::phys
