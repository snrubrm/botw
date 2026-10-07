#include "Game/AI/AI/aiSiteBossSwordRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::ai {

SiteBossSwordRoot::SiteBossSwordRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossSwordRoot::~SiteBossSwordRoot() = default;

// NON_MATCHING: configuration subobject address is computed before the floating-point constant load.
bool SiteBossSwordRoot::init_(sead::Heap* heap) {
    if (!SiteBossRoot::init_(heap))
        return false;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (ksys::act::hasTag(mActor, ksys::act::tags::EnemySiteBoss_R))
            boss->_1534 = 10;
        else
            boss->_1534 = *mIsRemainBoss_s ? 2 : 6;
        boss->_1560._99 = (boss->_1534 & 0xc) == 4;
        const s32 add_power = *mAddAttackPower_s;
        const s32 power = 24 + add_power * getNumberOfClearedRemains();
        boss->_2390.sub_71007224DC(2, power, s32(power * 0.8f));
    }
    return true;
}

void SiteBossSwordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
    act::SiteBoss::x_2(sead::DynamicCast<act::Enemy>(mActor), mActor);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (ksys::act::hasTag(mActor, ksys::act::tags::EnemySiteBoss_R))
            boss->_1534 = 10;
        else
            boss->_1534 = *mIsRemainBoss_s ? 2 : 6;
        boss->_14c8._30.set(0x50);
    }
}

void SiteBossSwordRoot::leave_() {
    SiteBossRoot::leave_();
}

void SiteBossSwordRoot::calc_() {
    SiteBossRoot::calc_();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_1558.isOn(0x30))
            boss->sub_71002D23F0();
        else if (boss->_1558.isOn(2))
            boss->sub_71002D2420();
        if (!boss->_14c8._30.isOn(4))
            boss->sub_71002D2390();
        else
            boss->sub_71002D22B8();
        if (!boss->_1558.isOn(0x10)) {
            boss->x_5(false);
            boss->x_6(false);
        }
    }
}

void SiteBossSwordRoot::loadParams_() {
    SiteBossRoot::loadParams_();
}

}  // namespace uking::ai
