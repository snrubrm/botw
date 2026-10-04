#include "Game/AI/Action/actionSimpleLineBeam.h"
#include "KingSystem/ActorSystem/actActor.h"
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
    ksys::act::ai::Action::enter_(params);
}

void SimpleLineBeam::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleLineBeam::loadParams_() {
    getStaticParam(&mIsGuarantee_s, "IsGuarantee");
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mIsGuardPierces_s, "IsGuardPierces");
    getStaticParam(&mIsSetAtIgnoreObstacle_s, "IsSetAtIgnoreObstacle");
}

void SimpleLineBeam::calc_() {
    ksys::act::ai::Action::calc_();
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
