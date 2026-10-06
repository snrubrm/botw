#include "Game/AI/Action/actionFlint.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Flint::Flint(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Flint::~Flint() = default;

bool Flint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Flint::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!*mParams.mSetDelete_s)
        return;

    auto* base = mActor->getDamageMgr();
    if (!base)
        return;

    if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(base))
        manager->addDamageCallback(4, &_38);
}

void Flint::leave_() {
    auto* base = mActor->getDamageMgr();
    if (!base)
        return;

    if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(base))
        manager->removeDamageCallback(&_38);
}

void Flint::loadParams_() {
    getStaticParam(&mParams.mRadius_s, "Radius");
    getStaticParam(&mParams.mLife_s, "Life");
    getStaticParam(&mParams.mSetDelete_s, "SetDelete");
}

void Flint::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
