#include "Game/AI/Action/actionMamonoShopStand.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

MamonoShopStand::MamonoShopStand(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MamonoShopStand::~MamonoShopStand() = default;

bool MamonoShopStand::init_(sead::Heap* heap) {
    mActor->getModel()->getBounding(&_1c);
    return true;
}

void MamonoShopStand::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getState() == ksys::act::BaseProc::State::Calc)
        return;

    if (auto* schedule = mActor->getSchedule()) {
        if (schedule->_68 == "Action1") {
            const f32 threshold = mActor->getState() == ksys::act::BaseProc::State::Calc ? 30.0f : 5.0f;
            const sead::Vector3f& pos = mActor->getMtx().getTranslation();
            const sead::Vector3f& player_pos = getPlayerPosition();
            const sead::Vector2f diff{pos.x - player_pos.x, pos.z - player_pos.z};
            if (!(diff.length() < threshold))
                return;
        }
    }

    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    if (auto* set = mActor->getRigidBodyByName("Body")) {
        for (s32 i = 0; i < set->getRigidBodies().size(); ++i) {
            if (auto* body = set->getRigidBodies()[i])
                body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
        }
    }
}

void MamonoShopStand::leave_() {
    ksys::act::ai::Action::leave_();
}

void MamonoShopStand::loadParams_() {}

void MamonoShopStand::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
