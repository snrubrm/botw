#include "Game/AI/Action/actionBowChildDeviceAppear.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BowChildDeviceAppear::BowChildDeviceAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildDeviceAppear::~BowChildDeviceAppear() = default;

bool BowChildDeviceAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildDeviceAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = false;
    playAS("InitClose", true, 0, 0, -1.0f);
    if (auto* body = mActor->getMainBody())
        body->setContactNone();
    if (auto* body = mActor->getTgtBody())
        body->setContactNone();
}

void BowChildDeviceAppear::leave_() {
    if (auto* body = mActor->getMainBody())
        body->setContactNone();
    if (auto* body = mActor->getTgtBody())
        body->setContactNone();
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D90F60(false);
}

void BowChildDeviceAppear::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mEndTime_s, "EndTime");
}

void BowChildDeviceAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
