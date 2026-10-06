#include "Game/AI/Action/actionBowChildDeviceAppear.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
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

// NON_MATCHING: identical code (the out-param `getBase(dir, 0)` reproduces the integer component loads); only the
// numbering of the fp registers (s8-s10) differs.
void BowChildDeviceAppear::calc_() {
    if (_30) {
        _34.update();
        if (_34.value <= sead::Mathf::epsilon())
            setFinished();
        return;
    }

    _34.reset(*mEndTime_s);
    if (auto* body = mActor->getMainBody()) {
        sead::Vector3f dir;
        mActor->getMtx().getBase(dir, 0);
        dir.normalize();
        dir *= *mInitSpeed_s;
        body->setLinearVelocity(dir, sead::Mathf::epsilon());
        body->setGravityFactor(0.0f);
    }
    _30 = true;
    xlinkEventOn(mActor, 25, 1, false);
}

}  // namespace uking::action
