#include "Game/AI/Action/actionFlint.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/World/worldElementSpark.h"
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

// NON_MATCHING: the zero-vector copy uses different load grouping and register allocation.
void Flint::calc_() {
    auto* actor = mActor;
    if (!sub_71007A2604(actor))
        return;
    const s32 count = sub_71007A26AC(actor);
    for (s32 i = 0; i < count; ++i) {
        auto* info = sub_71007A255C(actor, i);
        if (!info || info->_20.getMaterial() != ksys::phys::Material::Metal)
            continue;
        ElementSparkCreateArg arg;
        arg.actor = nullptr;
        arg.position = sead::Vector3f::zero;
        arg.radius = 1.0f;
        arg.life = 15.0f;
        arg.position = info->_0;
        arg.radius = *mParams.mRadius_s;
        arg.life = *mParams.mLife_s;
        ksys::world::sub_71010C30E8(&arg);
    }
}

}  // namespace uking::action

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
    if (int(mask->getData().getMaterial()) != ksys::phys::Material::Metal)
        *a1 = 0;
}
