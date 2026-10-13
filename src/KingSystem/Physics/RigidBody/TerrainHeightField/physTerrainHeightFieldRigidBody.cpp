#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::phys {

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
    {
        MaterialMask mask(material, submaterial, FloorCode::None, WallCode::None, true);
        masks->material_mask = mask.getRawData();
    }
    masks->collision_filter_info = 8;
    masks->ignored_layers = getIgnoredLayers().getDirect();
    return 0;
}

}  // namespace ksys::phys
