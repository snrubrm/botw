#include "Game/AI/Action/actionGiantHandClapToTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

GiantHandClapToTarget::GiantHandClapToTarget(const InitArg& arg) : PunchAttack(arg) {}

GiantHandClapToTarget::~GiantHandClapToTarget() = default;

bool GiantHandClapToTarget::init_(sead::Heap* heap) {
    return PunchAttack::init_(heap);
}

void GiantHandClapToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    for (u32 i = 0; i < 3; ++i) {
        if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(),
                                                       mAtkBodyName_s[i].cstr()))
            body->setScale(1.5f);
    }
    PunchAttack::enter_(params);
}

void GiantHandClapToTarget::leave_() {
    sub_71005DB3EC(mActor);
    PunchAttack::leave_();
    for (u32 i = 0; i < 3; ++i) {
        if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(),
                                                       mAtkBodyName_s[i].cstr()))
            body->setScale(1.0f);
    }
}

void GiantHandClapToTarget::loadParams_() {
    PunchAttack::loadParams_();
    getStaticParam(&mAtkBodyScale_s, "AtkBodyScale");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GiantHandClapToTarget::calc_() {
    PunchAttack::calc_();
    sub_71005DB1D8(mActor, *mTargetPos_d);
}

}  // namespace uking::action
