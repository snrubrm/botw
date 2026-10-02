#include "Game/AI/Action/actionPlayerCleaningAround.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerCleaningAround::PlayerCleaningAround(const InitArg& arg) : PlayerAction(arg) {}

PlayerCleaningAround::~PlayerCleaningAround() = default;

bool PlayerCleaningAround::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

// NON_MATCHING: register allocation (matrix / timer stores)
void PlayerCleaningAround::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(8);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(10);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(0.0f);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F63388(true, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc = 0;
    player->_20c0 = 0;
    if (auto* set = mActor->getPhysics()->findBodyByName("Player")) {
        if (auto* body = set->findBodyByHavokName("Cleaning")) {
            body->addToWorld();
            sead::Matrix34f mtx;
            mtx.makeT(mActor->getMtx().getTranslation());
            body->setTransform(mtx);
        }
    }
    const f32 time = *mCleaningTime_s;
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(time, time);
}

void PlayerCleaningAround::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(1.0f);
        controller->sub_7100F63388(false, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
    }
}

void PlayerCleaningAround::loadParams_() {
    getStaticParam(&mCleaningTime_s, "CleaningTime");
}

void PlayerCleaningAround::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1844.value <= sead::Mathf::epsilon()) {
        if (auto* set = mActor->getPhysics()->findBodyByName("Player")) {
            if (auto* body = set->findBodyByHavokName("Cleaning")) {
                if (body->isAddedToWorld())
                    body->removeFromWorld();
            }
        }
        setFinished();
    } else {
        player->_1844.update();
    }
}

}  // namespace uking::action
