#include "Game/Actor/Action/actionGuardianMiniLineBeam.h"
#include "Game/Actor/actBeamBase.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"
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
    sub_7100197468();
    sub_7100197660();
}

void GuardianMiniLineBeam::m32() {
    if (auto* actor = mActor) {
        auto* sensor = getActorAttackSensor(actor);
        const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
        sensor->activateAttackSensor(0x1000, 0x302, attack->mPower.ref(), attack->mImpulse.ref(),
                                     0.0f, 0, 1, -1, false, 1, -1);
    }
}

void GuardianMiniLineBeam::sub_7100197468() {
    auto* beam = sead::DynamicCast<act::BeamBase>(mActor);
    if (!beam || !beam->_b90._40.hasProc() || !hasAttackInfo(beam))
        return;
    auto* info = getAttackInfo(beam, 0);
    if (!info || !ksys::act::isPlayerProfile(&info->_50))
        return;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(info->_50.getProc(nullptr, nullptr));
    if (!actor)
        return;
    auto* player = sead::DynamicCast<act::PlayerBase>(actor);
    if (!player || !player->_cf0.isOnBit(0))
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&beam->_b90._40, &accessor);
    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000043), beam);
}

void GuardianMiniLineBeam::sub_7100197660() {
    auto* beam = sead::DynamicCast<act::LineBeam>(mActor);
    if (!beam || !beam->_d30 || !beam->_d48.hasProc())
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&beam->_d48, &accessor);
    if (accessor.hasTag(ksys::act::tags::IsIceMakerBlock)) {
        if (_58.hasProc() && accessor.hasProc(_58)) {
            _68.update();
            if (_68.value <= sead::Mathf::epsilon()) {
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004),
                            nullptr);
                _58.reset();
            }
            return;
        }
        accessor.linkAcquire(&_58);
    } else {
        _58.reset();
    }
    _68.reset(*mIceBlockBreakTime_s);
}

}  // namespace uking::action
