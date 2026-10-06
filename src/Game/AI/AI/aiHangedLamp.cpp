#include "Game/AI/AI/aiHangedLamp.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

// 0x710042dbe0
void Unk_71023fa168::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a1 <= 0)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(manager->m37(), &accessor) && accessor.hasTag(0x19f6c13a)) {
        *a1 = 0;
        *a5 = -1;
        auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(
            reinterpret_cast<dmg::DamageCallbackInfo*>(a6));
        if (info)
            info->mFlags = 0;
    }
}

HangedLamp::HangedLamp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HangedLamp::~HangedLamp() = default;

bool HangedLamp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HangedLamp::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mDisableImpulseByArrow_s)
        setDamageCallbackTiming(mActor, 2, &_38);
    changeChild("待機");
}

void HangedLamp::calc_() {
    const s32* life = mActor->getLife();
    if (life && *life <= 0 && isCurrentChild("待機"))
        changeChild("発火");
}

void HangedLamp::leave_() {
    if (*mDisableImpulseByArrow_s)
        sub_71005DA114(mActor, &_38);
}

void HangedLamp::loadParams_() {
    getStaticParam(&mDisableImpulseByArrow_s, "DisableImpulseByArrow");
}

}  // namespace uking::ai
