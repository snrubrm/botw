#include "Game/AI/AI/aiSiteBossSmallDamageRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::ai {

SiteBossSmallDamageRoot::SiteBossSmallDamageRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSmallDamageRoot::~SiteBossSmallDamageRoot() = default;

bool SiteBossSmallDamageRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSmallDamageRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* damage_mgr = sub_710072BA90(mActor)) {
        // The result is unused, but the call is in the original.
        damage_mgr->getField54();
        if (damage_mgr->checkDamageFlags(1))
            changeChild("大ダメージ");
        else
            changeChild("小ダメージ");
    }
    mFlags.set(Flag::Changeable);
}

void SiteBossSmallDamageRoot::calc_() {}

bool SiteBossSmallDamageRoot::isFinished() const {
    if (getCurrentChild() && getCurrentChild()->isFinished())
        return true;
    return mFlags.isOn(Flag::Finished);
}

void SiteBossSmallDamageRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSmallDamageRoot::loadParams_() {}

}  // namespace uking::ai
