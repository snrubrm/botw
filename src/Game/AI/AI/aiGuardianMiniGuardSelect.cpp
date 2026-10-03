#include "Game/AI/AI/aiGuardianMiniGuardSelect.h"
#include "Game/AI/aiGuardianMiniWeaponUtil.h"
#include "Game/AI/aiUnk_71007091AC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniGuardSelect::GuardianMiniGuardSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniGuardSelect::~GuardianMiniGuardSelect() = default;

bool GuardianMiniGuardSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GuardianMiniGuardSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GuardianMiniGuardSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: the final `return 1` is a `cset eq` in ours (select) but separate return blocks in the
// original; everything else matches.
// 0x710041cce0 (placeholder name): 2 if the weapon in the first slot selected by sub_71007091AC is a type 4
// weapon, 1 if the second one is, otherwise 0 (also without a model / enemy).
s32 GuardianMiniGuardSelect::sub_710041CCE0() {
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return 0;
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(actor, &a, &b, &c);
    if (a == -1 || b == -1)
        return 0;
    auto* enemy = static_cast<uking::act::Enemy*>(actor);
    if (hasType4Weapon(enemy, a))
        return 2;
    if (hasType4Weapon(enemy, b))
        return 1;
    return 0;
}

// 0x710041ced0 (placeholder name): resets the three guard AS slots.
void GuardianMiniGuardSelect::sub_710041CED0() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (!actor->getModel())
        return;
    if (!actor->getASList())
        return;
    actor->getASList()->sub_710115B01C(*mASSlotRight_s, 0, true);
    actor->getASList()->sub_710115B01C(*mASSlotLeft_s, 0, true);
    actor->getASList()->sub_710115B01C(*mASSlotBack_s, 0, true);
    actor->getASList()->sub_710115C11C();
    actor->getASList()->sub_710115BED4(true);
}

// NON_MATCHING: block layout: the original places the default arm (sub_710041CED0 + "ノーガード") right after the
// two compares; ours puts it last (compare order and everything else match).
void GuardianMiniGuardSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 guard = sub_710041CCE0();
    if (guard == 1) {
        changeChild("左腕ガード", params);
    } else if (guard == 2) {
        changeChild("右腕ガード", params);
    } else {
        sub_710041CED0();
        changeChild("ノーガード", params);
    }
}

void GuardianMiniGuardSelect::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void GuardianMiniGuardSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniGuardSelect::loadParams_() {
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
}

}  // namespace uking::ai
