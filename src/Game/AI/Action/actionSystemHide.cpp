#include "Game/AI/Action/actionSystemHide.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

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
    ksys::act::ai::Action::leave_();
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
