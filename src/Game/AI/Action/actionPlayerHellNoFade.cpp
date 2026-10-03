#include "Game/AI/Action/actionPlayerHellNoFade.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::action {

PlayerHellNoFade::PlayerHellNoFade(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: scheduling. The original builds the Matrix34f with nine scalar stores (the 3x3 identity, translation
// untouched) and loads _1770 after them; the Timer stores follow `mActor` loaded between the CleaningTime pointer and
// its value, after the switchToAnimSequenceMaybe arguments were materialised (same as PlayerSkin::enter_).
void PlayerHellNoFade::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(31);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(7);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(8);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(9);
    ksys::eft::searchAndEmitSLink(mActor, "warp", false);
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(*mCleaningTime_s, *mCleaningTime_s);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->sub_710086D5B8();
    auto* actor = mActor;
    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(0.0f);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F63388(true, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (auto* body_set = mActor->getPhysics()->findBodyByName("Player")) {
        if (auto* body = body_set->findBodyByHavokName("Cleaning")) {
            body->addToWorld();
            sead::Matrix34f mtx{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
            mtx.setTranslation(static_cast<ksys::act::Player*>(mActor)->_1770);
            body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
        }
    }
    if (auto* placement_mgr = ksys::map::PlacementMgr::instance())
        placement_mgr->_1f8 = 0;
}

void PlayerHellNoFade::leave_() {
    auto* actor = mActor;
    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x80000);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(1.0f);
        controller->sub_7100F63388(false, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
    }
}

void PlayerHellNoFade::loadParams_() {
    getStaticParam(&mCleaningTime_s, "CleaningTime");
}

void PlayerHellNoFade::calc_() {
    static_cast<ksys::act::Player*>(mActor)->setCE0Locked(0x8);
    if (!(static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon())) {
        static_cast<ksys::act::Player*>(mActor)->_1844.update();
        return;
    }
    if (auto* body_set = mActor->getPhysics()->findBodyByName("Player")) {
        if (auto* body = body_set->findBodyByHavokName("Cleaning"))
            body->removeFromWorld();
    }
    auto* placement_mgr = ksys::map::PlacementMgr::instance();
    if (!placement_mgr || placement_mgr->_1f8 >= 11)
        setFinished();
}

bool PlayerHellNoFade::isChangeable() const {
    return false;
}

}  // namespace uking::action
