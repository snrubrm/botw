#include "Game/Actor/Action/actionMoveHomePosBase.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MoveHomePosBase::MoveHomePosBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveHomePosBase::~MoveHomePosBase() = default;

bool MoveHomePosBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveHomePosBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsReturn_s) {
        _44.set(sead::Vector3f::zero);
        _38.set(_44 + sead::Vector3f::ey * *mDynMoveDis_d);
    } else {
        _38.set(sead::Vector3f::zero);
        _44.set(_38 + sead::Vector3f::ey * *mDynMoveDis_d);
    }
}

void MoveHomePosBase::leave_() {
    if (auto* body = m32()) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
}

void MoveHomePosBase::loadParams_() {
    getStaticParam(&mIsReturn_s, "IsReturn");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getDynamicParam(&mDynMoveSpeed_d, "DynMoveSpeed");
}

// NON_MATCHING: vector chase and matrix multiplication registers differ.
void MoveHomePosBase::calc_() {
    const f32 step = *mDynMoveSpeed_d * ksys::VFR::instance()->getDeltaFrame();
    auto difference = _44 - _38;
    const f32 distance = difference.length();
    if (distance <= step) {
        _38 = _44;
        setFinished();
    } else {
        difference *= 1.0f / distance;
        _38 += difference * step;
    }
    sead::Matrix34f matrix;
    mActor->getHomeMtx(&matrix);
    sead::Matrix34f translation;
    translation.makeT(_38);
    matrix.setMul(matrix, translation);
    if (auto* body = m32())
        body->changePositionAndRotation(matrix, sead::Mathf::epsilon());
}

ksys::phys::RigidBody* MoveHomePosBase::m32() {
    return mActor->getMainBody();
}

}  // namespace uking::action
