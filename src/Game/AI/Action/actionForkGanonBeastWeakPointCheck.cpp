#include "Game/AI/Action/actionForkGanonBeastWeakPointCheck.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/AI/aiUnk_710070284C.h"
#include "Game/AI/aiUnk_71025b2d88.h"
#include "KingSystem/ActorSystem/actTag.h"

// Full native helper uses the signed AS slot as an animation-slot offset; namespace unknown.
void sub_7100703904(ksys::act::Actor* actor, s32 slot);
// Complete native helper selects the weak-point index from the rigid body's name.
s32 sub_71007028F8(ksys::act::Actor* actor, ksys::phys::RigidBody* body);

namespace uking::action {

// NON_MATCHING: point-mask calculation is scheduled after the RTTI query.
void Unk_710238b078::call(s32* damage, s32*, u32*, u32*, s32* reaction,
                         dmg::DamageCallbackInfo*) {
    mBody = nullptr;
    if (*damage <= 0)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    if (!manager)
        return;
    mBody = manager->sub_71006D69F8();
    if (!mBody)
        return;
    const s32 weak_point = sub_71007028F8(manager->mActor, mBody);
    auto* alive = sead::DynamicCast<Unk_71025b2d88>(
        *static_cast<Unk_71025afb58**>(mOwner->mWeakPointAliveFlag_a));
    if (alive->mFlags & ~(1u << weak_point)) {
        *damage = 0;
        *reaction = 2;
    }
}

void Unk_710238b040::call(s32* damage, s32*, u32*, u32*, s32*,
                         dmg::DamageCallbackInfo*) {
    if (*damage <= 0)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    if (manager && !ksys::act::hasTag(manager->getAttacker(), ksys::act::tags::AffectBeastGanon))
        *damage = 0;
}

void Unk_710238b0b0::call(s32* damage, s32*, u32*, u32*, s32* reaction,
                         dmg::DamageCallbackInfo*) {
    mWeakPoint = 18;
    if (*damage <= 0)
        return;
    const auto position = mOwner->getActor()->getMtx().getTranslation();
    const auto& player_position = getPlayerPosition();
    const sead::Vector2f offset(position.x - player_position.x,
                               position.z - player_position.z);
    if (offset.length() > 220.0f) {
        *damage = 0;
        *reaction = 2;
        return;
    }
    if (sead::DynamicCast<dmg::DamageManager>(mDamageManager)) {
        if (sub_7100702894(mOwner->getActor())) {
            *damage = 0;
            *reaction = 2;
        } else {
            *damage = 1;
        }
    }
}

ForkGanonBeastWeakPointCheck::ForkGanonBeastWeakPointCheck(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastWeakPointCheck::~ForkGanonBeastWeakPointCheck() = default;

bool ForkGanonBeastWeakPointCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastWeakPointCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    _200 = *mIsWeakPointAppearMode_a;
    if (isRootAiParamINot5())
        sub_7100703904(mActor, 0);
    if (!mDamageCallback.mDamageManager)
        setDamageCallbackTiming(mActor, 0, &mDamageCallback);
    if (!mLastWeakPointDamageCallback.mDamageManager)
        setDamageCallbackTiming(mActor, 5, &mLastWeakPointDamageCallback);
    _1f8 = 0.0f;
    _1fc = 0.0f;
    _201 = false;
}

void ForkGanonBeastWeakPointCheck::leave_() {
    if (mDamageCallback.mDamageManager)
        sub_71005DA114(mActor, &mDamageCallback);
    if (mLastWeakPointDamageCallback.mDamageManager)
        sub_71005DA114(mActor, &mLastWeakPointDamageCallback);
}

void ForkGanonBeastWeakPointCheck::loadParams_() {
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mLastWeakCounter_s, "LastWeakCounter");
    getStaticParam(&mLastWeakSlowEndSafeTime_s, "LastWeakSlowEndSafeTime");
    getAITreeVariable(&mLastDamageWeakPointIdx_a, "LastDamageWeakPointIdx");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
    getAITreeVariable(&mGanonBeastWeakPointXLinkHandle_a, "GanonBeastWeakPointXLinkHandle");
    getAITreeVariable(&mWeakPointCounter_a, "WeakPointCounter");
}

void ForkGanonBeastWeakPointCheck::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
