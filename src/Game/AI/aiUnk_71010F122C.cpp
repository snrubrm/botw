#include "Game/AI/aiUnk_71010F122C.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

Unk_710250d530::Unk_710250d530() = default;

Unk_710250d530::~Unk_710250d530() {
    if (mBody) {
        if (mBody->isAddedToWorld())
            mBody->removeFromWorldImmediately(nullptr);
        delete mBody;
        mBody = nullptr;
    }
}
