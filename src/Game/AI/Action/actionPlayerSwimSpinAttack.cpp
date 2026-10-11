#include "Game/AI/Action/actionPlayerSwimSpinAttack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

PlayerSwimSpinAttack::PlayerSwimSpinAttack(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimSpinAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x400);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x800);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimAttack", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->decreaseStaminaForActionMaybe(*mEnergyDash_s * player->x_67());
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;
}

void PlayerSwimSpinAttack::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        if (auto* body = set->findBodyByHavokName("AtkPlayerBody"))
            body->removeFromWorld();
    }
}

void PlayerSwimSpinAttack::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
}

void PlayerSwimSpinAttack::calc_() {
    static_cast<ksys::act::Player*>(mActor)->sub_710085C55C();
    static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (mActor->getASList()->x_4(0, 0)) {
        setFinished();
        return;
    }
    ksys::as::ASList::Unk4 query;
    if (mActor->getASList()->x(3, &query, 0, 0,
                              &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
            if (auto* body = set->findBodyByHavokName("AtkPlayerBody"))
                body->addToWorld();
        }
    } else if (mActor->getASList()->x(3, nullptr, 0, 0,
                                     &ksys::as::ASList::Unk2::sub_710116388C, true)) {
        if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
            if (auto* body = set->findBodyByHavokName("AtkPlayerBody"))
                body->removeFromWorld();
        }
    }
    if (mActor->getASList()->x(0, nullptr, 0, 0,
                              &ksys::as::ASList::Unk2::sub_71011638DC, true) &&
        static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(2) &&
        !static_cast<ksys::act::Player*>(mActor)->x_44()) {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
    }
    if (mActor->getASList()->x(0, nullptr, 0, 0,
                              &ksys::as::ASList::Unk2::sub_71011638DC, true) &&
        static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(0x24) &&
        !static_cast<ksys::act::Player*>(mActor)->x_44()) {
        static_cast<ksys::act::Player*>(mActor)->_17f1 = true;
    }
    if (mActor->getASList()->x(2, nullptr, 0, 0,
                              &ksys::as::ASList::Unk2::sub_710116383C, true))
        _1c = true;
}

bool PlayerSwimSpinAttack::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
