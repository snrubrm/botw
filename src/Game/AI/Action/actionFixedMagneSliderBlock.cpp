#include "Game/AI/Action/actionFixedMagneSliderBlock.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/Constraint/physFixedCs.h"

namespace uking::action {

FixedMagneSliderBlock::FixedMagneSliderBlock(const InitArg& arg) : FixedMagneStick(arg) {}

FixedMagneSliderBlock::~FixedMagneSliderBlock() = default;

bool FixedMagneSliderBlock::init_(sead::Heap* heap) {
    return FixedMagneStick::init_(heap);
}

void FixedMagneSliderBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    FixedMagneStick::enter_(params);
}

void FixedMagneSliderBlock::leave_() {
    FixedMagneStick::leave_();
}

void FixedMagneSliderBlock::loadParams_() {
    FixedMagneStick::loadParams_();
}

void FixedMagneSliderBlock::calc_() {
    FixedMagneStick::calc_();
}

// NON_MATCHING: matrix/scalar load scheduling and register allocation differ.
void FixedMagneSliderBlock::m34(ksys::act::ActorConstDataAccess& accessor, f32 distance) {
    auto* constraint = sead::DynamicCast<ksys::phys::FixedCs>(_38);
    auto* actor = mActor;
    if (!constraint || !actor)
        return;
    sead::Matrix34f target_transform;
    accessor.sub_7100D11860(&target_transform);
    const sead::Matrix34f actor_transform = actor->getMtx();
    sead::Vector3f y_axis = sead::Vector3f::ey;
    if (actor_transform.getBase(1).dot(target_transform.getBase(1)) < 0.0f)
        y_axis = -y_axis;
    sead::Matrix34f target_frame;
    accessor.sub_7100D105A8(&target_frame);
    const sead::Vector3f target_position = accessor.getActorMtx().getTranslation();
    sead::Matrix34f inverse;
    inverse.setInverse(actor_transform);
    const f32 local_z = inverse.m[2][3] +
                        (target_position.x * inverse.m[2][0] +
                         target_position.y * inverse.m[2][1] +
                         target_position.z * inverse.m[2][2]);
    sead::Vector3f z_axis = sead::Vector3f::ez;
    if (local_z > 0.0f)
        z_axis = -z_axis;
    sead::Matrix34f actor_frame;
    actor_frame.setBase(0, sead::Vector3f::ex);
    actor_frame.setBase(1, y_axis);
    actor_frame.setBase(2, z_axis);
    actor_frame.setTranslation(z_axis * -distance);
    constraint->sub_7100F6D6D8(actor_frame, target_frame);
}

}  // namespace uking::action
