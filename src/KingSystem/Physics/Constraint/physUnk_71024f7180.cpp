#include "KingSystem/Physics/Constraint/physUnk_7102519e58.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

Unk_71024f7180::Unk_71024f7180() = default;

Unk_71024f7180::~Unk_71024f7180() = default;

void Unk_71024f7180::m5() {
    sead::Matrix34f transform;
    mBodyA->getTransform(&transform);
    sead::Matrix34f result;
    result.setMul(transform, mTransform);
    mBodyB->setTransform(result, ksys::phys::PropagateToLinkedMotions{true});
}

bool Unk_71024f7180::m6() {
    return _9c;
}
