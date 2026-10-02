#include "Game/AI/AI/aiSiteBossSwordRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::ai {

SiteBossSwordRoot::SiteBossSwordRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossSwordRoot::~SiteBossSwordRoot() = default;

bool SiteBossSwordRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
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

void SiteBossSwordRoot::loadParams_() {
    SiteBossRoot::loadParams_();
}

}  // namespace uking::ai
