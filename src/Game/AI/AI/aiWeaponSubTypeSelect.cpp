#include "Game/AI/AI/aiWeaponSubTypeSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h"

namespace uking::ai {

WeaponSubTypeSelect::WeaponSubTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponSubTypeSelect::~WeaponSubTypeSelect() = default;

void WeaponSubTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005F18C0(params);
}

void WeaponSubTypeSelect::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void WeaponSubTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponSubTypeSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

// 0x71005f18c0
void WeaponSubTypeSelect::sub_71005F18C0(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getWeapons() || static_cast<u32>(*mWeaponIdx_s) >= 6) {
        changeChild("通常武器", params);
        return;
    }
    if (auto* weapon = sub_71005D83E8(mActor, *mWeaponIdx_s)) {
        if (!weapon->m231()) {
            if (!weapon->m232()) {
                weapon->m233();
            } else if (auto* gparams = weapon->getParam()->getRes().mGParamList) {
                if (auto* sword = gparams->getLargeSword()) {
                    if (sword->mWeaponSubType.ref() == "Fan") {
                        changeChild("うちわ", params);
                        return;
                    }
                }
            }
        }
    }
    changeChild("通常武器", params);
}

}  // namespace uking::ai
