#include "Game/AI/AI/aiGuardianMiniGroggy.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

// Source namespace and return spelling are inferred from the named caller; declaration only.
void sub_7100428358(ksys::act::Actor* actor, bool enabled, s32 slot);

namespace uking::ai {

bool GuardianMiniGroggy::sub_710041C850(s32* slot) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    *slot = -1;
    for (s32 idx = 0; idx < 3; ++idx) {
        auto* weapon = enemy->getWeapons()->getEquippedWeapon(idx);
        if (sead::IsDerivedFrom<act::Weapon>(weapon)) {
            if (static_cast<act::Weapon*>(weapon)->_cf0 != 4)
                return false;
            *slot = idx;
        }
    }
    return *slot != -1;
}

GuardianMiniGroggy::GuardianMiniGroggy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
GuardianMiniGroggy::~GuardianMiniGroggy() {
    ;
}

void GuardianMiniGroggy::enter_(ksys::act::ai::InlineParamPack* params) {
    _75 = false;
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "GroggyLoop", 1, 0, true);
    _68 = ksys::Timer(*mChanceTime_s, *mChanceTime_s);
    changeChild("チャンス", params);
}

// NON_MATCHING: Vector snapshots use different load scheduling and register allocation.
void GuardianMiniGroggy::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("終了")) {
        setFinished();
        return;
    }
    if (isCurrentChild("チャンス")) {
        if (!(_68.value <= sead::Mathf::epsilon())) {
            sead::Vector3f position = mActor->getMtx().getTranslation();
            sead::Vector3f direction = mActor->getMtx().getBase(2);
            direction.normalize();
            position += direction * 5.0f;
            sub_71005DB068(mActor, position);
            _68.update();
            if (_68.value <= sead::Mathf::epsilon()) {
                auto* list = mActor->getASList();
                list->sub_710115B140(sead::SafeString(mRestartASName_s.cstr()), 0, 0, 1, 1);
            }
        } else if (mActor->getASList()->x_4(0, 1)) {
            auto* list = mActor->getASList();
            list->sub_710115B140(sead::SafeString(mDefaultASName_s.cstr()), 0, 0, 1, 1);
            changeChild("終了", nullptr);
        }
    }
    _74 = sub_710041C850(&_78);
    if (!_75 && _74 && _78 != -1) {
        sub_7100428358(mActor, false, _78);
        playerOrEnemyDropWeapon(mActor, &sead::Vector3f::zero, _78, false, false, nullptr, false);
        _75 = true;
    }
}

void GuardianMiniGroggy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniGroggy::loadParams_() {
    getStaticParam(&mChanceTime_s, "ChanceTime");
    getStaticParam(&mRestartASName_s, "RestartASName");
    getStaticParam(&mDefaultASName_s, "DefaultASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
