#include "Game/AI/Action/actionAtOnWait.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

AtOnWait::AtOnWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool AtOnWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AtOnWait::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* set = actor->getRigidBodyByName(sub_71007A24BC()->cstr())) {
        const s32 count = set->getRigidBodies().size();
        for (s32 i = 0; i < count; ++i) {
            auto* body = set->getRigidBody(i);
            if (!body)
                continue;
            if (!body->isAddedToWorld())
                body->setTransform(actor->getMtx());
            static const u32 sAttackAttr[4] = {9, 10, 12, 0x20000008};
            const s32 type = *mAtkAttrType_s;
            const u32 attack_flags = u32(type) <= 3 ? sAttackAttr[type] : 9;
            auto* sensor = getActorAttackSensor(actor);
            const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
            sensor->activateAttackSensor(1, attack_flags, attack->mPower.ref(),
                                         attack->mImpulseLarge.ref(), 0.0f,
                                         attack->mGuardBreakPower.ref(), 0, -1, false, 1, -1);
            sub_71007A2B64(body, nullptr);
        }
    }
    mFlags.set(Flag::Changeable);
}

void AtOnWait::leave_() {
    auto* set = mActor->getRigidBodyByName(sub_71007A24BC()->cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i])
            sub_71007A2D34(body);
    }
}

void AtOnWait::loadParams_() {
    getStaticParam(&mAtkAttrType_s, "AtkAttrType");
}

void AtOnWait::calc_() {
    auto* actor = mActor;
    auto* set = actor->getRigidBodyByName(sub_71007A24BC()->cstr());
    if (!set)
        return;
    for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
        if (auto* body = set->getRigidBodies()[i])
            body->changePositionAndRotation(actor->getMtx(), sead::Mathf::epsilon());
    }
}

}  // namespace uking::action
