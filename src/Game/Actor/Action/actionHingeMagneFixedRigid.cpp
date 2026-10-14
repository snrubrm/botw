#include "Game/Actor/Action/actionHingeMagneFixedRigid.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/Constraint/physHingeCs.h"

namespace uking::action {

HingeMagneFixedRigid::HingeMagneFixedRigid(const InitArg& arg) : FixedMagneSliderBlock(arg) {}

HingeMagneFixedRigid::~HingeMagneFixedRigid() = default;

bool HingeMagneFixedRigid::init_(sead::Heap* heap) {
    return FixedMagneSliderBlock::init_(heap);
}

void HingeMagneFixedRigid::enter_(ksys::act::ai::InlineParamPack* params) {
    FixedMagneSliderBlock::enter_(params);
}

void HingeMagneFixedRigid::leave_() {
    FixedMagneSliderBlock::leave_();
}

void HingeMagneFixedRigid::loadParams_() {
    FixedMagneSliderBlock::loadParams_();
}

void HingeMagneFixedRigid::calc_() {
    FixedMagneSliderBlock::calc_();
}

void HingeMagneFixedRigid::m32(sead::Heap* heap) {
    if (!mActor)
        return;
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    ksys::phys::HingeCs::Param param;
    param.body_a = body;
    _38 = ksys::phys::HingeCs::make(param, heap);
}

// NON_MATCHING: load scheduling of the local z computation (as in FixedMagneSliderBlock::m34).
// Hinges the actor to the magnetised object: the pivot is `distance` in front of the actor along its z axis
// (towards the object), the object pivot is its home position and its hinge axis the home z axis.
void HingeMagneFixedRigid::m34(ksys::act::ActorLinkConstDataAccess& accessor, f32 distance) {
    auto* constraint = sead::DynamicCast<ksys::phys::HingeCs>(_38);
    if (!constraint)
        return;
    auto* actor = mActor;
    if (!actor)
        return;
    sead::Matrix34f home_mtx;
    accessor.getHomeMtx(&home_mtx);
    sead::Matrix34f target_transform;
    accessor.sub_7100D11860(&target_transform);
    const sead::Vector3f target_position = accessor.getActorMtx().getTranslation();
    const sead::Matrix34f actor_transform = actor->getMtx();
    sead::Matrix34f inverse;
    inverse.setInverse(actor_transform);
    const f32 local_z = inverse.m[2][3] + (target_position.x * inverse.m[2][0] +
                                           target_position.y * inverse.m[2][1] +
                                           target_position.z * inverse.m[2][2]);
    sead::Vector3f axis = sead::Vector3f::ez;
    if (local_z > 0.0f)
        axis = -axis;
    constraint->sub_7100F6DEAC(axis * -distance, home_mtx.getTranslation(), axis, home_mtx.getBase(2));
}

}  // namespace uking::action
