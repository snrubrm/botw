#include "Game/AI/AI/aiSiteBossPierceBulletAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

SiteBossPierceBulletAttack::SiteBossPierceBulletAttack(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossPierceBulletAttack::~SiteBossPierceBulletAttack() = default;

bool SiteBossPierceBulletAttack::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossPierceBulletAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);
}

void SiteBossPierceBulletAttack::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
}

void SiteBossPierceBulletAttack::calc_() {
    SiteBossShootNormalArrowRoot::calc_();
    if (isCurrentChild("弾発射"))
        sub_71005D74E8(mActor);
}

bool SiteBossPierceBulletAttack::m34() {
    return sub_7100588164(false);
}

s32 SiteBossPierceBulletAttack::m44() {
    return 12;
}

}  // namespace uking::ai
