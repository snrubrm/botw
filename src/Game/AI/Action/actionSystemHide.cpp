#include "Game/AI/Action/actionSystemHide.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

// 0x7100ee54e8 (declared only; lane5 s5): placeholder name.
void sub_7100EE54E8(ksys::act::Actor* actor);

namespace uking::action {

SystemHide::SystemHide(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemHide::~SystemHide() = default;

bool SystemHide::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemHide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemHide::leave_() {
    sub_71002907BC();
    sub_71007A3540(mActor);
    if (auto* chemical = mActor->getChemicalStuff()) {
        chemical->sub_7100D90F60(false);
        chemical->sub_7100D91098(_3d);
        sub_71006F5A80(chemical);
    }
    sub_7100EE54E8(mActor);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1);
    if (*mIsOnAttention_s) {
        ksys::act::enableAttClient(mActor, "LockOn");
        ksys::act::enableAttClient(mActor, "AutoAim");
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = _38;
    if (auto* awareness = mActor->get548())
        awareness->_18._50 = false;
}

void SystemHide::sub_71002906CC() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EC44();
    if (auto* set = mActor->getRigidBodyByName(sub_71007A24E4()->cstr()))
        set->removeFromWorld();
    if (auto* set = mActor->getRigidBodyByName(sub_71007A250C()->cstr())) {
        _3c = !set->hasNoRigidBodyWithFlag8(true);
        set->removeFromWorld();
        for (int i = 0; i < set->getRigidBodies().size(); ++i) {
            if (auto* body = set->getRigidBodies()[i])
                body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
        }
    }
}

void SystemHide::sub_71002907BC() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EC30();
    if (auto* set = mActor->getRigidBodyByName(sub_71007A24E4()->cstr()))
        set->addToWorld();
    if (auto* set = mActor->getRigidBodyByName(sub_71007A250C()->cstr())) {
        if (_3c) {
            set->addToWorld();
            if (auto* physics = mActor->getPhysics()) {
                for (int i = 0; i < set->getRigidBodies().size(); ++i) {
                    if (auto* body = set->getRigidBodies()[i])
                        physics->sub_7100FBAF18(body);
                }
            }
        }
    }
}

void SystemHide::loadParams_() {
    getStaticParam(&mIsOnAttention_s, "IsOnAttention");
    getStaticParam(&mASName_s, "ASName");
}

void SystemHide::calc_() {
    if (isFinished() || isFailed())
        return;
    if (m32()) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFailed();
    }
}

bool SystemHide::m32() {
    return mActor->sub_7100EE1E94();
}

}  // namespace uking::action
