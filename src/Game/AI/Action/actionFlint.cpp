#include "Game/AI/Action/actionFlint.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/physMaterialMask.h"

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

// NON_MATCHING: the original stores the masked material (`ldr w8, [x0, #8]; and w8, w8, #0x3f`) to a stack slot and
// reloads it before the compare (the comparison goes through a volatile enum temporary); our compare keeps it in w8.
void Unk_71023820a8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 == -1)
        return;

    auto* mgr = sub_710072BA90(mOwner->mActor);
    if (!mgr || mgr->getField54() == 30)
        return;

    auto* mask = mgr->m33();
    if (!mask)
        return;
    const auto material = mask->getData().getMaterial();
    if (material != ksys::phys::Material::Metal)
        *a1 = 0;
}
