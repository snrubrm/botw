#include "Game/AI/Action/actionSiteBossShieldBashAttack.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossShieldBashAttack::SiteBossShieldBashAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossShieldBashAttack::~SiteBossShieldBashAttack() = default;

bool SiteBossShieldBashAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossShieldBashAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;
    sub_710073FA90(&_5c, mActor);
    playAS("ShieldBash", false, 0, 0, -1.0f);
    _80 = true;
    _81 = false;
    _50.value = *mInitSpeed_s;
    _50.prev_value = *mInitSpeed_s;
    m33();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.setBit(2);
}

void SiteBossShieldBashAttack::leave_() {
    m35();
    m32();
}

void SiteBossShieldBashAttack::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mKeepDist_s, "KeepDist");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossShieldBashAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

void SiteBossShieldBashAttack::m32() {}

bool SiteBossShieldBashAttack::isChangeable() const {
    return _80;
}

void SiteBossShieldBashAttack::m33() {
    if (!_48) {
        _48 = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkShield");
        if (!_48)
            return;
    }
    sub_71007A2B64(_48, nullptr);
    sub_71007A3258(_48, nullptr);
}

}  // namespace uking::action
