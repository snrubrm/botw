#include "Game/AI/Action/actionGrabAttack.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"

namespace uking::action {

GrabAttack::GrabAttack(const InitArg& arg) : Grab(arg) {}

GrabAttack::~GrabAttack() = default;

void GrabAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtRigidBodyName_s.cstr())) {
        sub_71007A2B64(body, nullptr);
        sub_71007A3258(body, nullptr);
    }
    _70 = false;
    Grab::enter_(params);
}

void GrabAttack::leave_() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtRigidBodyName_s.cstr()))
        sub_71007A2D34(body);
    if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        mActor->resetConnectedCalcChild(false);
    Grab::leave_();
}

void GrabAttack::loadParams_() {
    Grab::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAtRigidBodyName_s, "AtRigidBodyName");
}

void GrabAttack::calc_() {
    Grab::calc_();
}

void GrabAttack::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

// Whether the grabbed actor (the connected calc child) hit this one.
bool GrabAttack::m33() {
    if (auto* actor = mActor) {
        auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild());
        if (child && hasAttackInfo(actor)) {
            const s32 count = getNumAttackInfoMaybe(actor);
            for (s32 i = 0; i < count; ++i) {
                auto* info = getAttackInfo(actor, i);
                if (info && info->_50.hasProcById(child))
                    return true;
            }
        }
    }
    return false;
}

}  // namespace uking::action
