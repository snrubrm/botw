#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>

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

}  // namespace ksys::phys
