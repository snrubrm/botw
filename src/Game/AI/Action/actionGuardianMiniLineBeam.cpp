#include "Game/AI/Action/actionGuardianMiniLineBeam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

GuardianMiniLineBeam::GuardianMiniLineBeam(const InitArg& arg) : SimpleLineBeam(arg) {}

GuardianMiniLineBeam::~GuardianMiniLineBeam() = default;

void GuardianMiniLineBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLineBeam::enter_(params);
    _58.reset();
    const f32 time = *mIceBlockBreakTime_s;
    _68 = ksys::Timer(time, time);
}

void GuardianMiniLineBeam::loadParams_() {
    SimpleLineBeam::loadParams_();
    getStaticParam(&mIceBlockBreakTime_s, "IceBlockBreakTime");
}

void GuardianMiniLineBeam::calc_() {
    SimpleLineBeam::calc_();
}

void GuardianMiniLineBeam::m32() {
    if (auto* actor = mActor) {
        auto* sensor = getActorAttackSensor(actor);
        const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
        sensor->activateAttackSensor(0x1000, 0x302, attack->mPower.ref(), attack->mImpulse.ref(),
                                     0.0f, 0, 1, -1, false, 1, -1);
    }
}

}  // namespace uking::action
