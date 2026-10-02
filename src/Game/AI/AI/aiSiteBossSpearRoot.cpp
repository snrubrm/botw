#include "Game/AI/AI/aiSiteBossSpearRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::ai {

SiteBossSpearRoot::SiteBossSpearRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossSpearRoot::~SiteBossSpearRoot() = default;

bool SiteBossSpearRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossSpearRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
}

void SiteBossSpearRoot::leave_() {
    SiteBossRoot::leave_();
}

void SiteBossSpearRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mThrowSpearAttackPower_s, "ThrowSpearAttackPower");
    getStaticParam(&mThrowSpearMinDmage_s, "ThrowSpearMinDmage");
    getStaticParam(&mIceSplinterAttackPower_s, "IceSplinterAttackPower");
    getStaticParam(&mIceSplinterMinDamage_s, "IceSplinterMinDamage");
}

bool SiteBossSpearRoot::m35(act::SiteBoss* boss) {
    if (SiteBossRoot::m35(boss))
        return true;
    if (!boss->_14c8._30.isOnBit(9)) {
        if (auto* damage_mgr = sub_710072BA90(mActor)) {
            if (damage_mgr->checkDamageFlags(1) || damage_mgr->checkDamageFlags(0)) {
                if (damage_mgr->getField50() == 3)
                    return true;
            }
        }
    }
    return false;
}

}  // namespace uking::ai
