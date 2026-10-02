#include "Game/AI/AI/aiIncredibleAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

void Unk_71023fd380::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (!_38) {
        *a1 = 0;
        return;
    }

    auto* manager = sead::DynamicCast<uking::dmg::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;

    auto* attacker = manager->getAttacker();
    ksys::act::ActorConstDataAccess acc;
    if (attacker->hasProc())
        ksys::act::acquireActor(attacker, &acc);
}

namespace uking::ai {

IncredibleAction::IncredibleAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IncredibleAction::~IncredibleAction() = default;

bool IncredibleAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IncredibleAction::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100448C0C(true);
    _58._38 = false;
    changeChild("インクレディブル", params);
}

void IncredibleAction::leave_() {
    sub_7100448C0C(false);
}

void IncredibleAction::loadParams_() {
    getStaticParam(&mIsInvincible_s, "IsInvincible");
    getStaticParam(&mIsUnmoving_s, "IsUnmoving");
    getStaticParam(&mIsNoCollide_s, "IsNoCollide");
    getStaticParam(&mIsUseIncredibleActionDCCallback_s, "IsUseIncredibleActionDCCallback");
}

void IncredibleAction::calc_() {
    if (isFinished() || isFailed())
        return;

    if (*mIsUseIncredibleActionDCCallback_s) {
        bool value = false;
        if (auto* as_list = mActor->getASList()) {
            value = !as_list->x(0x16, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                true);
        } else {
            setFailed();
        }
        _58._38 = value;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
}

}  // namespace uking::ai
