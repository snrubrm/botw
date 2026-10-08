#include "Game/AI/aiUnk_71010F122C.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxRigidBody.h"

Unk_710250d530::Unk_710250d530() = default;

Unk_710250d530::~Unk_710250d530() {
    if (mBody) {
        if (mBody->isAddedToWorld())
            mBody->removeFromWorldImmediately(nullptr);
        delete mBody;
        mBody = nullptr;
    }
}

// 0x71010f1314
bool Unk_710250d530::sub_71010F1314() {
    if (!mBody)
        return true;
    return !mBody->isAddedToWorld();
}

void Unk_710250d530::sub_71010F1344(f32 speed) {
    mSpeed = speed;
    if (mElement && mElement->mWind)
        mElement->mWind->mSpeed = speed;
}

void Unk_710250d530::sub_71010F1364(const sead::Vector3f* direction) {
    mDirection = *direction;
    if (mElement && mElement->mWind)
        mElement->mWind->mDirection = *direction;
}

void Unk_710250d530::sub_71010F15C8(const sead::Matrix34f* mtx) {
    auto* body = mBody;
    if (body && sead::IsDerivedFrom<ksys::phys::BoxRigidBody>(body))
        body->setTransform(*mtx);
}

void Unk_710250d530::sub_71010F1664(const sead::Vector3f* extents) {
    auto* body = mBody;
    if (body && sead::IsDerivedFrom<ksys::phys::BoxRigidBody>(body))
        static_cast<ksys::phys::BoxRigidBody*>(body)->setExtents(*extents);
}

void Unk_710250d530::sub_71010F17FC(bool remove_links) {
    if (!mEnabled)
        return;

    if (mElement) {
        mElement->m28();
        mElement = nullptr;
    }

    if (!mBody)
        return;

    if (remove_links) {
        mBody->removeFromWorldAndResetLinks();
    } else if (mBody->isAddedToWorld() || mBody->isAddingBodyToWorld()) {
        mBody->removeFromWorld();
    }
}
