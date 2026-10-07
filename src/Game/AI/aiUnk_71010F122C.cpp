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

// 0x71010f1314
bool Unk_710250d530::sub_71010F1314() {
    if (!mBody)
        return true;
    return !mBody->isAddedToWorld();
}
