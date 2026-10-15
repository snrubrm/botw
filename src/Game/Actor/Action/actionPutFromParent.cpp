#include "Game/Actor/Action/actionPutFromParent.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"

namespace uking::action {

PutFromParent::PutFromParent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PutFromParent::~PutFromParent() = default;

void PutFromParent::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _38.x(sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()));
    _38._28 = sub_71005DC5AC(actor).cstr();
    _38._30.getKey().reset();
    _38._68 = sub_71005DC57C(actor);
    _38._98 = 0;
    mActor->sub_71011DA824(&_38);
    sub_7100738C88(actor, sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()));
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F62CA8(false);
        _e8 = controller->sub_7100F62CA0();
        controller->sub_7100F62C14(-1.0f);
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    } else if (auto* body = actor->getMainBody()) {
        body->clearEntityMotionFlag4(false);
        _e8 = body->getMaxImpulse();
        body->setMaxImpulse(-1.0f);
        _f0 = body->getLinearDamping();
        _ec = body->getAngularDamping();
        body->setLinearDamping(0.0f);
        body->setAngularDamping(0.0f);
    }
    _f4 = sead::Mathf::deg2rad(30.0f);
    if (auto* object = actor->m100()) {
        const f32 angle = object->sub_7100E4EFC4();
        if (ksys::act::isPlayerProfile(
                sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent())) &&
            getGParamList() && getGParamList()->getLiftable()) {
            const s32 frames = getGParamList()->getLiftable()->mPutRotFrame.ref();
            if (frames > 0)
                _f4 = sead::Mathf::clampMin(angle / static_cast<f32>(frames), sead::Mathf::deg2rad(0.5f));
        }
    }
    _f8 = false;
    _e4 = false;
    _e5 = false;
    _e6 = false;
    _d8 = nullptr;
    _e0 = 1.0f;
}

bool PutFromParent::sub_71002255F4(sead::Vector3f start, sead::Vector3f end,
                                   sead::Vector3f* hit_pos) {
    auto* actor = mActor;
    if (!_e4 && actor->getConnectedCalcParent())
        actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    ksys::phys::RayCastBodyQuery query(sub_710072E804(actor, 0), ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityNPC);
    query.enableLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
    query.enableLayer(ksys::phys::ContactLayer::EntityPlayer);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    if (hit_pos)
        query.getHitPosition(hit_pos);
    return true;
}

void PutFromParent::leave_() {
    auto* actor = mActor;
    actor->resetConnectedCalcParent(false);
    actor->sub_71011DA834(&_38);
    sub_7100738DC8(actor);
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F62CA8(true);
        controller->sub_7100F62C14(_e8);
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        if (controller->get64().x == 0.0f && controller->get64().z == 0.0f) {
            sead::Vector3f up;
            actor->getMtx().getBase(up, 2);
            sub_710072C1B4(controller, up);
        }
    } else if (auto* body = actor->getMainBody()) {
        body->clearEntityMotionFlag4(true);
        body->setMaxImpulse(_e8);
        body->setLinearDamping(_f0);
        body->setAngularDamping(_ec);
    }
    if (auto* obj = actor->m100()) {
        obj->_b0 = 0;
        obj->_b8 = 0;
    }
}

void PutFromParent::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mHoldOffXLinkKey_s, "HoldOffXLinkKey");
}

void PutFromParent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
