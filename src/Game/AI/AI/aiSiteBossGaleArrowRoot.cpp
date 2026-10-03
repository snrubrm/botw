#include "Game/AI/AI/aiSiteBossGaleArrowRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

SiteBossGaleArrowRoot::SiteBossGaleArrowRoot(const InitArg& arg) : WithoutWeaponArrow(arg) {}

SiteBossGaleArrowRoot::~SiteBossGaleArrowRoot() = default;

bool SiteBossGaleArrowRoot::init_(sead::Heap* heap) {
    return WithoutWeaponArrow::init_(heap);
}

void SiteBossGaleArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WithoutWeaponArrow::enter_(params);
}

void SiteBossGaleArrowRoot::calc_() {
    WithoutWeaponArrow::calc_();
}

void SiteBossGaleArrowRoot::leave_() {
    WithoutWeaponArrow::leave_();
}

void SiteBossGaleArrowRoot::loadParams_() {
    WithoutWeaponArrow::loadParams_();
}

bool SiteBossGaleArrowRoot::m37(bool* broke_ice_block, bool* hit_player) {
    if (!hasAttackInfo(mActor))
        return false;

    bool result = true;
    const s32 num = getNumAttackInfoMaybe(mActor);
    for (s32 i = 0; i < num; ++i) {
        auto* info = getAttackInfo(mActor, i);
        if (!info)
            continue;

        auto* link = &info->_50;
        if (!link->hasProc())
            continue;

        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.getName() == "Enemy_SiteBoss_Bow_ChildDevice") {
            result = false;
            *broke_ice_block = true;
        }
    }
    return result;
}

}  // namespace uking::ai
