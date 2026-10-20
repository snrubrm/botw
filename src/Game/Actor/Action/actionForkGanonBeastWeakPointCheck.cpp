#include "Game/Actor/Action/actionForkGanonBeastWeakPointCheck.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_710070284C.h"
#include "Game/Actor/aiUnk_71025b2d88.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/System/Timer.h"

// Full native helper uses the signed AS slot as an animation-slot offset; namespace unknown.
void sub_7100703904(ksys::act::Actor* actor, s32 slot);
// Complete native helper selects the weak-point index from the rigid body's name.
s32 sub_71007028F8(ksys::act::Actor* actor, ksys::phys::RigidBody* body);

namespace uking::action {

// NON_MATCHING: the original recomputes the entry address from the index for each access (smaddl / madd) and
// keeps the string constants out of the hoisted registers
void Unk_GanonBeastWeakPointXLinkHandles::sub_71001552E4() {
    for (s32 i = 0; i < 4; ++i) {
        if (mEntries[i].mIndex < 0)
            continue;
        mEntries[i].mIndex = -1;
        mEntries[i].mEffect.kill();
        mEntries[i].mSound.fade();
    }
}

// NON_MATCHING: same codegen difference as sub_71001552E4
Unk_GanonBeastWeakPointXLinkHandles::~Unk_GanonBeastWeakPointXLinkHandles() {
    for (s32 i = 0; i < 4; ++i) {
        if (mEntries[i].mIndex < 0)
            continue;
        mEntries[i].mIndex = -1;
        mEntries[i].mEffect.kill();
        mEntries[i].mSound.fade();
    }
}

// NON_MATCHING: point-mask calculation is scheduled after the RTTI query.
void Unk_710238b078::call(s32* damage, s32*, u32*, u32*, s32* reaction,
                         act::DamageCallbackInfo*) {
    mBody = nullptr;
    if (*damage <= 0)
        return;
    auto* manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
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
                         act::DamageCallbackInfo*) {
    if (*damage <= 0)
        return;
    auto* manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
    if (manager && !ksys::act::hasTag(manager->getAttacker(), ksys::act::tags::AffectBeastGanon))
        *damage = 0;
}

void Unk_710238b0b0::call(s32* damage, s32*, u32*, u32*, s32* reaction,
                         act::DamageCallbackInfo*) {
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
    if (sead::DynamicCast<act::DamageManager>(mDamageManager)) {
        if (sub_7100702894(mOwner->getActor())) {
            *damage = 0;
            *reaction = 2;
        } else {
            *damage = 1;
        }
    }
}

// NON_MATCHING: the original schedules the zero stores of 0x70 and 0xc8..0x120 differently
ForkGanonBeastWeakPointCheck::ForkGanonBeastWeakPointCheck(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

// NON_MATCHING: the original has no calls to the destructors of Unk_71025b2d88 and Unk_71025b27b8 (inline there;
// they are out of line here because they emit those vtables)
ForkGanonBeastWeakPointCheck::~ForkGanonBeastWeakPointCheck() = default;

bool ForkGanonBeastWeakPointCheck::init_(sead::Heap* heap) {
    mWeakPointAliveFlag.mFlags = 0x23fff;
    mWeakPointActiveFlag.mFlags = 0;
    *static_cast<Unk_71025afb58**>(mWeakPointActiveFlag_a) = &mWeakPointActiveFlag;
    *static_cast<Unk_71025afb58**>(mWeakPointAliveFlag_a) = &mWeakPointAliveFlag;
    *static_cast<Unk_71025afb58**>(mGanonBeastWeakPointXLinkHandle_a) = &mXLinkHandles;
    mXLinkHandles.mHandles.sub_71001552E4();
    *static_cast<Unk_71025afb58**>(mWeakPointCounter_a) = &mWeakPointCounter;
    mWeakPointCounter._8 = 0;
    return true;
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

// NON_MATCHING: the original branches for the 0x138 flag update; ours uses a csel
void ForkGanonBeastWeakPointCheck::calc_() {
    if (mWeakPointCounter._8 > 0.0f) {
        if (*mIsWeakPointAppearMode_a) {
            ksys::Timer::update(&mWeakPointCounter._8, -1.0f);
            if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_80000000) &&
                mWeakPointCounter._8 <= 0.0f) {
                mWeakPointCounter._8 = 1.0f;
            }
        } else {
            mWeakPointCounter._8 = 0.0f;
        }
    }

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unit = sead::DynamicCast<uking::act::Unk_710244dd20>(actor->m159())) {
            if (*mIsWeakPointAppearMode_a)
                unit->_138 &= ~8;
            else
                unit->_138 |= 8;
        }
    }

    const bool appear_mode = *mIsWeakPointAppearMode_a;
    const bool playing = _1d8.sub_7101241B6C();
    if (appear_mode) {
        if (playing)
            _1d8.fadeXLink();
    } else if (!playing) {
        xlinkSearchAndEmit(mActor, "Boost", 2, &_1d8);
    }
    sub_71001556D4();
}

}  // namespace uking::action
