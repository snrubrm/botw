#include "Game/AI/AI/aiSiteBossBowChildDeviceRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

SiteBossBowChildDeviceRoot::SiteBossBowChildDeviceRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossBowChildDeviceRoot::~SiteBossBowChildDeviceRoot() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FB835C();
}

bool SiteBossBowChildDeviceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: regalloc / scheduling of the last stores
void SiteBossBowChildDeviceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        body->setContactAll();
        body->setGravityFactor(0.0f);
    }
    if (auto* body = mActor->getTgtBody())
        body->setContactAll();
    changeAS("Wait_Battle", true, 1, 0);
    changeChild("生成待機");
    _64 = 7;
    _68 = 7;
    _56 = false;
    xlinkEventOn(mActor, 25, 0, false);
    if (auto* chemical = mActor->getChemicalStuff()) {
        chemical->sub_7100D8EEE0();
        chemical->sub_7100D90F60(true);
    }
    _50 = *mCount_m;
    _90 = ksys::Timer(300, 300);
    _9c = *mXRotateSpeed_s;
    _70 = mActor->getCreateArgBaseProcLink();
}

void SiteBossBowChildDeviceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossBowChildDeviceRoot::loadParams_() {
    getStaticParam(&mXRotateSpeed_s, "XRotateSpeed");
    getStaticParam(&mSlowRate_s, "SlowRate");
    getMapUnitParam(&mCount_m, "Count");
}

}  // namespace uking::ai
