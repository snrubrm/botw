#include "Game/AI/AI/aiSimpleKokkoRoot.h"
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::ai {

SimpleKokkoRoot::SimpleKokkoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleKokkoRoot::~SimpleKokkoRoot() = default;

bool SimpleKokkoRoot::init_(sead::Heap* heap) {
    *mAttackTargetActorLink_a = &_48;
    return true;
}

void SimpleKokkoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* awareness = mActor->get548();
    if (!awareness)
        return;
    awareness->m8()->m10(5, true);

    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDBC(mActor->getMtx().getBase(2));
        controller->sub_7100F605F0();
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
    }

    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        auto* body = set->getRigidBodies()[0];
        if (body) {
            getActorAttackSensor(mActor)->activateAttackSensor(
                0x2000, 9, mActor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(), 0,
                0.0f, 0, 1, -1, false, 1, -1);
            body->setTransform(mActor->getMtx());
            sub_71007A2EB0(body, mActor, nullptr);
            sub_71007A2B64(body, nullptr);
        }
    }

    _60 = ksys::Timer(*mAliveTime_s, *mAliveTime_s);
    _6c = 0;
    if (sead::IsDerivedFrom<Unk_7102370e70>(*mAttackTargetActorLink_a)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(_48.mLink, "TargetActor", -1);
        changeChild("子アクション", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(ksys::act::sUnk_71026505e0, "TargetActor", -1);
        changeChild("子アクション", &pack);
    }
}

void SimpleKokkoRoot::calc_() {
    if (!_48.mLink.hasProc())
        _60.rate = -2.0f;
    _60.update();

    if (auto* controller = mActor->getCharacterController()) {
        if (controller->sub_7100F5F264() || (controller->_116 & 4))
            ksys::Timer::update(&_6c, 1.0f);
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() ||
        _60.value <= std::numeric_limits<f32>::epsilon() || _6c > 7.0f) {
        mActor->deleteEx(ksys::act::Actor::DeleteType::_1,
                         ksys::act::BaseProc::DeleteReason::_0);
        if (auto* awareness = mActor->get548())
            awareness->m8()->m10(5, false);
    }
}

void SimpleKokkoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleKokkoRoot::loadParams_() {
    getStaticParam(&mAliveTime_s, "AliveTime");
    getAITreeVariable(&mAttackTargetActorLink_a, "AttackTargetActorLink");
}

}  // namespace uking::ai
