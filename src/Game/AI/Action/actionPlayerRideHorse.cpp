#include "Game/AI/Action/actionPlayerRideHorse.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <limits>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

PlayerRideHorse::PlayerRideHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerRideHorse::~PlayerRideHorse() = default;

bool PlayerRideHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerRideHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: the original stores _d4/_dc as unaligned 64-bit pairs and _d0/_e4 separately; ours merges
    // _d0 with _d4 (and _d8 with _dc) into 32-bit pairs
    mFlags.reset(Flag::Changeable);
    _b0 = 0.0f;
    _b4 = -std::numeric_limits<f32>::infinity();
    _d4.set(15.0f, 0.0f);
    _dc.set(std::numeric_limits<f32>::infinity(), 0.0f);
    _b8 = 0.0f;
    _c4 = 0.0f;
    _104 = 0;
    _d0 = 0;
    _e4 = 0.0f;
    _e8 = mActor->getVelocity();
    _f4 = mActor->getVelocity();
    _100 = mActor->getVelocity().y;
}

void PlayerRideHorse::leave_() {
    if (auto* info = mActor->getPlayerRideInfo()) {
        info->_30 &= ~0xc;
        if (auto* player_info = sead::DynamicCast<ksys::act::Player::RideInfo>(info))
            player_info->_2ec = 0;
    }
}

void PlayerRideHorse::loadParams_() {
    getStaticParam(&mAccelerateInputDelayGear0_s, "AccelerateInputDelayGear0");
    getStaticParam(&mAccelerateInputDelayGear1_s, "AccelerateInputDelayGear1");
    getStaticParam(&mAccelerateInputDelayGear2_s, "AccelerateInputDelayGear2");
    getStaticParam(&mAccelerateInputDelayGear3_s, "AccelerateInputDelayGear3");
    getStaticParam(&mAccelerateInputDelayGearTop_s, "AccelerateInputDelayGearTop");
    getStaticParam(&mAccInputIgnoreFramesGear0_s, "AccInputIgnoreFramesGear0");
    getStaticParam(&mAccInputIgnoreFramesGear1_s, "AccInputIgnoreFramesGear1");
    getStaticParam(&mAccInputIgnoreFramesGear2_s, "AccInputIgnoreFramesGear2");
    getStaticParam(&mAccInputIgnoreFramesGear3_s, "AccInputIgnoreFramesGear3");
    getStaticParam(&mAccInputIgnoreFramesGearTop_s, "AccInputIgnoreFramesGearTop");
    getStaticParam(&mDecelerateInputThreshold_s, "DecelerateInputThreshold");
    getStaticParam(&mStopInputFrames_s, "StopInputFrames");
    getStaticParam(&mAccelerateInputThreshold_s, "AccelerateInputThreshold");
    getStaticParam(&mMoveBackInputThreshold_s, "MoveBackInputThreshold");
    getStaticParam(&mStickXClampAtGear0_s, "StickXClampAtGear0");
    getStaticParam(&mTurnStickXInputThreshold_s, "TurnStickXInputThreshold");
    getStaticParam(&mConstraintBreakThreshold_s, "ConstraintBreakThreshold");
    getDynamicParam(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
}

// NON_MATCHING: the natural slot buffer size getter is inlined; slot-loop scheduling differs.
void PlayerRideHorse::sub_7100808F88() {
    auto* ride_actor = act::getRideActor(mActor);
    const sead::SafeString name = act::sub_7100E81260(mActor, ride_actor);
    auto* list = mActor->getASList();
    f32 speed = 0.0f;
    if (ride_actor) {
        const auto& velocity = ride_actor->getVelocity();
        speed = sead::Vector2f(velocity.x, velocity.z).length();
    }
    list->x_6(10, 0, speed);
    list = mActor->getASList();
    f32 angle = 0.0f;
    if (ride_actor)
        angle = act::sub_7100E8134C(mActor, ride_actor);
    list->x_6(9, 0, angle);
    const s32 slot_count = mActor->getASList()->mSlots.size();
    for (s64 slot = 0; slot < sead::Mathi::min(2, slot_count); ++slot) {
        list = mActor->getASList();
        if (slot >= list->mSlots.size())
            continue;
        const s32 bank_count = list->mSlots[slot]._20.size();
        for (s32 bank = 0; bank < bank_count; ++bank) {
            if (slot < 2 && (!*mHasToPlayRidingOnAS_d || bank == 0))
                mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, name, slot, 0, true);
            else
                mActor->getASList()->sub_710115B01C(slot, bank, true);
        }
    }
    if (*mHasToPlayRidingOnAS_d)
        ksys::act::ActorSystem::instance()->getPlayerLink()->m308();
    if (auto* info = sead::DynamicCast<ksys::act::Player::RideInfo>(mActor->getPlayerRideInfo()))
        info->_2ec = *mConstraintBreakThreshold_s;
}

void PlayerRideHorse::calc_() {
    if (++_d0 < 2)
        return;
    if (_d0 == 2)
        sub_7100808F88();
    auto* ride_actor = act::getRideActor(mActor);
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor);
    // The original queries the ride info here even though the result is unused.
    mActor->getPlayerRideInfo();
    if (!ride_actor) {
        setFailed();
        return;
    }
    if (!player)
        return;
    auto* ride_info = ride_actor->getMotorcyclePriorityStuffMaybe();
    if (!ride_info) {
        setFailed();
        return;
    }
    if (ride_info->m17() && ride_actor->getName().findIndex("Bike") == -1)
        sub_71008093A0();
    else
        sub_710080A224();
}

// NON_MATCHING: the original preserves more SafeString virtual calls and separates its name tests.
void PlayerRideHorse::sub_710080B208(ksys::as::ASList* list, f32 rate) {
    const f32 blend = rate > 1.0f ? 5.0f / rate : -1.0f;
    sead::SafeString name = "JumpWaitHorseRide";
    sead::SafeString current = list->x_1(0, 0);
    if (rate > 0.0f) {
        if (name != current) {
            list->startAnimationMaybe(blend, -1.0f, name.cstr(), 0, 0, true);
            current = name;
        }
        list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, rate);
        current = list->x_1(1, 0);
        if (name != current) {
            list->startAnimationMaybe(blend, -1.0f, name.cstr(), 1, 0, true);
            current = name;
        }
        list->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, rate);
    } else {
        if (name != current) {
            list->startAnimationMaybe(blend, -1.0f, name.cstr(), 0, 0, true);
            current = name;
        }
        current = list->x_1(1, 0);
        if (name != current) {
            list->startAnimationMaybe(blend, -1.0f, name.cstr(), 1, 0, true);
            current = name;
        }
    }
}

// NON_MATCHING: the natural timer/result branches merge stores and arrange the return blocks differently.
s32 sub_710080C324(f32* timer, bool grounded, sead::Vector3f* previous_velocity,
                 const sead::Vector3f& velocity) {
    s32 result = 0;
    if (grounded) {
        const f32 inverse_delta = 1.0f / ksys::VFR::instance()->getDeltaFrame();
        const sead::Vector3f difference =
            (velocity - *previous_velocity) * inverse_delta;
        if (*timer != 0.0f && difference.squaredLength() > 2.25f) {
            const f32 elapsed = sead::Mathf::abs(*timer);
            if (elapsed > 20.0f)
                result = 2;
            else if (elapsed > 10.0f)
                result = 1;
            *timer = 0.0f;
        } else if (*timer > 10.0f) {
            *timer = -*timer;
        } else {
            *timer = 0.0f;
        }
    } else {
        if (*timer < 0.0f)
            *timer = 0.0f;
        ksys::Timer::update(timer, 1.0f);
    }
    previous_velocity->set(velocity);
    return result;
}

}  // namespace uking::action
