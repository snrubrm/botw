#include "Game/AI/AI/aiSiteBossPierceBulletAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::ai {

SiteBossPierceBulletAttack::SiteBossPierceBulletAttack(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossPierceBulletAttack::~SiteBossPierceBulletAttack() = default;

bool SiteBossPierceBulletAttack::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossPierceBulletAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);
    _338 = false;
}

void SiteBossPierceBulletAttack::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
    if (auto* child = mActor->getConnectedCalcChild()) {
        child->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        mActor->resetConnectedCalcChild(false);
    }
    if (!_338)
        m41();
}

void SiteBossPierceBulletAttack::calc_() {
    SiteBossShootNormalArrowRoot::calc_();
    if (isCurrentChild("弾発射"))
        sub_71005D74E8(mActor);
}

bool SiteBossPierceBulletAttack::m34() {
    return sub_7100588164(false);
}

void SiteBossPierceBulletAttack::m40() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066C590(nullptr, 20);
}

void SiteBossPierceBulletAttack::m41() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_1560.sub_710066C5B8(nullptr, 20);
        _338 = true;
    }
}

s32 SiteBossPierceBulletAttack::m44() {
    return 12;
}

void SiteBossPierceBulletAttack::m50(ksys::act::BaseProc* proc, s32 idx) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066DB98(proc, idx);
}

}  // namespace uking::ai
