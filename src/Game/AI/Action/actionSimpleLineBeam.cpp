#include "Game/AI/Action/actionSimpleLineBeam.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

SimpleLineBeam::SimpleLineBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SimpleLineBeam::~SimpleLineBeam() = default;

bool SimpleLineBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleLineBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _40 = ksys::Timer(-1.0f, -1.0f, -1.0f);
    if (auto* beam = sead::DynamicCast<uking::act::LineBeam>(mActor)) {
        if (*mIsSetAtIgnoreObstacle_s)
            sub_71007A44E4(mActor, true);
        beam->sub_71000029CC();
        sub_71007A2C30(beam, "Beam", &beam->getMtx());
        m32();
    } else {
        setFailed();
    }
}

void SimpleLineBeam::leave_() {
    if (auto* beam = sead::DynamicCast<uking::act::LineBeam>(mActor))
        beam->sub_7100002BF8();
    sub_71007A2D7C(mActor, "Beam");
}

// NON_MATCHING: the original keeps `this + 0x20` and the SafeString vtable in callee-saved registers up front.
void SimpleLineBeam::loadParams_() {
    getStaticParam(&mIsGuarantee_s, "IsGuarantee");
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mIsGuardPierces_s, "IsGuardPierces");
    getStaticParam(&mIsSetAtIgnoreObstacle_s, "IsSetAtIgnoreObstacle");
}

void SimpleLineBeam::calc_() {
    if (isFinished() || isFailed())
        return;
    if (!(_40.value <= sead::Mathf::epsilon())) {
        _40.update();
        if (_40.value <= sead::Mathf::epsilon())
            sub_71007A338C(mActor, "Beam");
    }
    if (hasAttackInfo(mActor)) {
        const s32 count = getNumAttackInfoMaybe(mActor);
        for (s32 index = 0; index < count; ++index) {
            auto* info = getAttackInfo(mActor, index);
            if (info && ksys::act::isPlayerProfile(&info->_50)) {
                _40 = ksys::Timer(10.0f, 10.0f, -1.0f);
                break;
            }
        }
    }
}

void SimpleLineBeam::m32() {
    if (auto* actor = mActor) {
        const bool is_type_1 = *mType_s == 1;
        u32 attack_flags = is_type_1 ? 0x10000 : 0x1000;
        u32 attack_flags2 = is_type_1 ? 0x8200 : 0x200;
        if (*mIsGuarantee_s)
            attack_flags2 |= 0x10000008;
        if (*mIsGuardPierces_s)
            attack_flags2 |= 8;
        auto* sensor = getActorAttackSensor(actor);
        const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
        sensor->activateAttackSensor(attack_flags, attack_flags2, attack->mPower.ref(),
                                     attack->mImpulse.ref(), 0.0f, 0, 1, -1, false, 1,
                                     attack->mPowerForPlayer.ref());
    }
}

}  // namespace uking::action
