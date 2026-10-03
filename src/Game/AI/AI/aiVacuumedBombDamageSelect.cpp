#include "Game/AI/AI/aiVacuumedBombDamageSelect.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

VacuumedBombDamageSelect::VacuumedBombDamageSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

VacuumedBombDamageSelect::~VacuumedBombDamageSelect() = default;

bool VacuumedBombDamageSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void VacuumedBombDamageSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr());
    auto* bomb = sead::DynamicCast<Unk_7102370e70>(*mVacuumedExplodingBomb_a);
    if (manager && bomb && manager->getAttacker()->hasProc() &&
        *manager->getAttacker() == bomb->mLink) {
        changeChild("体内爆発", params);
    } else {
        changeChild("その他", params);
    }
}

void VacuumedBombDamageSelect::calc_() {}

void VacuumedBombDamageSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void VacuumedBombDamageSelect::loadParams_() {
    getAITreeVariable(&mVacuumedExplodingBomb_a, "VacuumedExplodingBomb");
}

}  // namespace uking::ai
