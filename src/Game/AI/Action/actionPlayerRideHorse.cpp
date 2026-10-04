#include "Game/AI/Action/actionPlayerRideHorse.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <limits>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actMotorcycle.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/gameRumble.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/SeadController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

namespace uking::action {

// Original separate eight-byte tables, indexed by the steering flag at +0x105, bit 6.
static const f32 sUnk_7101e78f24[2] = {-0.34f, -0.15f};
static const f32 sUnk_7101e78f2c[2] = {1.2f, 0.8f};

// Independently initialized seven-entry mapping table at 0x71025ccf68.
struct Unk_71025ccf68 {
    const sead::SafeString* state;
    const char* name;
    bool check_other_bank;
};
static const Unk_71025ccf68 sUnk_71025ccf68[7] = {
    {&act::sUnk_7102603180, "Horse_Courbette", false},
    {&act::sUnk_71026031b0, "Horse_Crash", false},
    {&act::sUnk_7102603370[3], "Horse_Jump_Gear_3_S", true},
    {&act::sUnk_71026033c0[3], "Horse_Jump_Gear_3", true},
    {&act::sUnk_7102603370[4], "Horse_Jump_Gear_Top_S", true},
    {&act::sUnk_71026033c0[4], "Horse_Jump_Gear_Top", true},
    {&act::sUnk_7102603270, "Horse_Move_Slip", false},
};
// Two separate five-entry objects, independently destructed by the original initializer.
static sead::SafeArray<sead::SafeString, 5> sUnk_71025cd168 = {{
    "HorseWait", "HorseRun_Gear1", "HorseRun_Gear2", "HorseRun_Gear3", "HorseRun_Gear4"}};
static sead::SafeArray<sead::SafeString, 5> sUnk_71025cd1b8 = {{
    "Horse_Move_Gear_0_Go", "Horse_Move_Gear_1_Go", "Horse_Move_Gear_2_Go",
    "Horse_Move_Gear_3_Go", "Horse_Move_Gear_Top_Go"}};

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
    _105 = 0;
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

// NON_MATCHING: animation-name tests and the steering/landing branches compile differently.
void PlayerRideHorse::sub_710080A224() {
    auto* bike = sead::DynamicCast<act::Motorcycle>(act::getRideActor(mActor));
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor);
    auto* list = mActor->getASList();
    auto* ride_info = mActor->getPlayerRideInfo();
    // Both original virtual queries discard their results here.
    player->m383();
    player->m292();
    const bool riding_animation = act::sub_7100E813B0(list);
    if (riding_animation)
        mFlags.reset(Flag::Changeable);
    else
        mFlags.set(Flag::Changeable);
    auto* controller = player->m358();
    bool accelerating = false;
    bool turning = false;
    bool wheelie = false;
    bool drifting = false;
    bool dash_wait = false;
    bool recently_grounded = false;
    bool airborne = false;
    bool landed = false;
    bool steering_started = false;
    s32 front_landing = 0;
    s32 rear_landing = 0;
    f32 speed = 0.0f;
    if (bike) {
        accelerating = bike->sub_710007A478();
        // The original performs this query without using the returned speed.
        bike->sub_710007A4A8();
        turning = bike->x_6();
        const f32 wheelie_value = bike->x_8();
        wheelie = wheelie_value != 0.0f;
        const f32 drift_value = bike->sub_710007AB7C();
        drifting = drift_value != 0.0f;
        dash_wait = bike->_f10 == 4;
        speed = bike->_e58;
        if (!bike->_f88.isOnBit(19)) {
            ksys::Timer::update(&_dc.x, 1.0f);
            recently_grounded = _dc.x < 6.0f;
        } else {
            _dc.x = 0.0f;
            recently_grounded = true;
        }
        if (!bike->_dd0->_13d && !bike->_dd8->_13d && !bike->_f88.isOnBit(32)) {
            ksys::Timer::update(&_d4.y, 1.0f);
            airborne = _d4.y > 8.0f;
            if (recently_grounded && !(_d4.y > 8.0f)) {
                airborne = true;
                _d4.y = 8.0f;
            }
        } else {
            landed = _d4.y != 0.0f && _d4.y > 8.0f;
            _d4.y = 0.0f;
        }
        const bool steering = (_105 & (1 << 6)) != 0;
        if (speed >= sUnk_7101e78f24[steering] && speed <= sUnk_7101e78f2c[steering]) {
            speed = 0.0f;
            _105 &= ~(1 << 6);
        } else {
            steering_started = !steering && speed > 0.0f;
            _105 |= 1 << 6;
        }
        if (!(speed > 0.0f))
            _105 &= ~(1 << 7);
        else if (accelerating)
            _105 |= 1 << 7;
        sead::Vector3f front_velocity;
        bike->_dd0->_0->getLinearVelocity(&front_velocity);
        front_landing = sub_710080C324(&_dc.y, bike->_dd0->_13d, &_e8, front_velocity);
        sead::Vector3f rear_velocity;
        bike->_dd8->_0->getLinearVelocity(&rear_velocity);
        rear_landing = sub_710080C324(&_e4, bike->_dd8->_13d, &_f4, rear_velocity);
        list->x_6(1, 0, sead::Mathf::clamp(bike->speedStuff(), -1.0f, 1.0f));
        list->x_6(4, 0, sead::Mathf::clamp(bike->sub_710007A994(), -1.0f, 1.0f));
        list->x_6(2, 0, bike->sub_710007ABA4());
        const auto& velocity = bike->getVelocity();
        list->x_6(10, 0, sead::Vector2f(velocity.x, velocity.z).length());
        list->x_2(66, 42, wheelie, false);
        list->x_2(66, 43, drifting, false);
        if (!riding_animation)
            list->x_6(9, 0, bike->sub_710007A958());
    } else {
        list->x_6(1, 0, 0.0f);
        list->x_6(4, 0, 0.0f);
        list->x_6(2, 0, 0.0f);
        list->x_6(10, 0, 0.0f);
        list->x_2(66, 42, false, false);
        list->x_2(66, 43, false, false);
        if (!riding_animation)
            list->x_6(9, 0, 0.0f);
    }
    list->x_2(66, 16, true, false);
    list->x_2(66, 19, _100 < -0.4f, false);
    const auto& stick = controller->getLeftStick();
    list->x_6(6, 0, sead::Mathf::atan2(-stick.x, stick.y) * 57.295776f);
    f32 rate = 1.0f;
    if (player->isSlowTime() && player->_cf4.isOnBit(17))
        rate = *player->getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam;
    bool play_landing = false;
    if (player->m292()) {
        if (!riding_animation)
            sub_710080B208(list, rate);
    } else if (!riding_animation) {
        sead::SafeString name = sead::SafeString::cEmptyString;
        bool restart = true;
        if (turning) {
            name = "MotorcycleTurn";
        } else if (landed || front_landing != 0 || rear_landing != 0) {
            name = "MotorcycleLand";
            play_landing = true;
        } else if (airborne || recently_grounded) {
            name = "MotorcycleFall";
        } else if (wheelie) {
            name = "MotorcycleWheelie";
        } else if (drifting) {
            name = "MotorcycleDrift";
        } else if (dash_wait) {
            name = "MotorcycleDashWait";
        } else {
            restart = false;
            if (accelerating || (_105 & (1 << 7)))
                name = "MotorcycleMove";
            else if (speed == 0.0f)
                name = "MotorcycleWait";
            else
                name = "MotorcycleSlide";
        }
        const s32 slots = list->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C) ? 1 : 2;
        for (s32 slot = 0; slot < slots; ++slot) {
            const sead::SafeString current = list->x_1(slot, 0);
            if (!restart && current == "MotorcycleLand" && !list->x_4(slot, 0))
                continue;
            if (name == current)
                continue;
            list->startAnimationMaybe(-1.0f, -1.0f, name, slot, 0, true);
            list->x_3(slot, 0, &ksys::as::ASList::Unk2::sub_71011631BC, rate);
            if (list->x_7(slot, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
                list->sub_710115F2EC(slot, 0, 0.0f);
        }
    }
    if (airborne) {
        player->_cf8.setBit(8);
        player->_cf4.setBit(17);
    } else if (landed) {
        player->_cf8.resetBit(8);
        player->_cf4.resetBit(17);
    }
    _100 = mActor->getVelocity().y;
    if (ride_info)
        ride_info->_30 &= ~0xc;
    if (auto* rumble = Rumble::instance()) {
        if (play_landing && (front_landing == 2 || rear_landing == 2))
            rumble->sub_7100897FE4(1, 1);
        else if ((accelerating && steering_started) ||
                 (play_landing && (front_landing == 1 || rear_landing == 1)))
            rumble->sub_7100897FE4(0, 1);
    }
}

// NON_MATCHING: natural string comparisons, separate static arrays and slot branches differ.
void PlayerRideHorse::sub_710080B670(ksys::as::ASList* list, act::HorseRideInfo* info,
                                   ksys::act::Actor* actor, act::Rideable* rideable, s32 gear,
                                   bool* soothe, bool* shift, bool a9, bool a10, bool a11,
                                   bool a12, bool a13) {
    sead::SafeString name;
    const s32 bank = rideable->_18._9 ? rideable->_18._2e :
                                         rideable->_18.sub_7100E76CEC();
    const s8 other_bank = (rideable->_18._2c & 0xff) == 2 ?
                             3 - rideable->_18._2e : -1;
    const auto& current = actor->getASList()->x_1(0, bank);
    const auto& other = other_bank >= 0 ? actor->getASList()->x_1(0, other_bank) :
                                         sead::SafeString::cEmptyString;
    s32 copy_bank = -1;
    bool matched = false;
    for (const auto& entry : sUnk_71025ccf68) {
        if (current != *entry.state && (!entry.check_other_bank || other != *entry.state))
            continue;
        name = entry.name;
        copy_bank = current == *entry.state ? bank : other_bank;
        list->x_2(66, 19, (rideable->_18._52 >> 8) & 1, false);
        matched = true;
        break;
    }
    if (name.isEmpty()) {
        if (a9 || !a10) {
            if (!a9 || list->x_4(0, 0)) {
                if (gear == 0 && a11) {
                    name = "HorseRun_Back";
                } else {
                    name = sUnk_71025cd168[gear];
                    ksys::as::ASList::Unk4 query;
                    if (gear == 0 && actor->getASList()->x(
                            46, &query, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
                        list->goLimpFromHeadShotMaybe(47, query.name, 0);
                        list->x_6(2, 0, query._14);
                    } else {
                        list->goLimpFromHeadShotMaybe(47, "Wait", 0);
                    }
                    copy_bank = bank;
                }
            }
        } else {
            const auto& state = actor->getASList()->x_1(0, 0);
            if (state == act::sUnk_7102603160 || state == act::sUnk_7102603170)
                name = "Horse_Move_Shift_Go";
            else
                name = sUnk_71025cd1b8[gear];
            *shift = true;
        }
    }
    const bool has_bank = list->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C);
    a13 = has_bank || a13;
    const s32 slots = has_bank || (a12 && !a13) ? 1 : 2;
    for (s32 slot = 0; slot < slots; ++slot) {
        const sead::SafeString current_name = list->x_1(slot, 0);
        if (current_name == "Horse_Move_Soothe") {
            if (!a13 && !list->sub_710115F0BC(slot, 0, 0.0f))
                continue;
            if (slot != 0 && name.isEmpty()) {
                const auto& source = list->x_1(0, 0);
                const f32 frame = list->sub_710115F3F0(0, 0, false);
                list->startAnimationMaybe(-1.0f, frame, source, slot, 0, true);
                if (list->x_7(slot, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
                    list->sub_710115F2EC(slot, 0, 0.0f);
            }
        }
        if (!name.isEmpty() && name != current_name) {
            if (name == "Horse_Courbette")
                list->sub_710115EA64(rideable->_18._2f);
            list->startAnimationMaybe(-1.0f, -1.0f, name.cstr(), slot, 0, true);
            if (list->x_7(slot, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
                list->sub_710115F2EC(slot, 0, 0.0f);
        }
        if (copy_bank >= 0)
            sub_7100E7F25C(list, actor, slot, 0, copy_bank);
    }
    if (!has_bank) {
        if (!a13 && a12 && list->x_1(1, 0) != "Horse_Move_Soothe") {
            list->startAnimationMaybe(-1.0f, -1.0f, "Horse_Move_Soothe", 1, 0, true);
            *soothe = true;
        }
    } else if (a13 && list->x_1(1, 0) == "Horse_Move_Soothe") {
        const auto& source = list->x_1(0, 0);
        const f32 frame = list->sub_710115F3F0(0, 0, false);
        list->startAnimationMaybe(-1.0f, frame, source, 1, 0, true);
        if (list->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
            list->sub_710115F2EC(1, 0, 0.0f);
    }
    if (info) {
        if (matched)
            info->_30 |= 4;
        else
            info->_30 &= ~4;
        if (_104 == 1)
            info->_30 &= ~8;
        else
            info->_30 |= 8;
    }
}

// NON_MATCHING: the sector branches and natural aggregate return use different registers.
Unk_710080ae8c PlayerRideHorse::sub_710080AE8C(ksys::act::PlayerLink* player,
                                           const sead::Vector2f& input, s32 gear) {
    const f32 magnitude = input.length();
    f32 angle = sead::Mathf::atan2(input.y, input.x);
    if (angle > 3.1415927f)
        angle += -6.2831855f;
    f32 turn;
    f32 forward;
    if (angle < -2.9321527f) {
        turn = -magnitude;
        forward = 0.0f;
    } else if (angle < -1.7802364f) {
        angle = ((angle + 2.9321527f) * 1.5707964f) / 1.1519164f + -3.1415927f;
        turn = magnitude * sead::Mathf::cos(angle);
        forward = magnitude * sead::Mathf::sin(angle);
    } else if (angle < -1.3613564f) {
        turn = 0.0f;
        forward = -magnitude;
    } else if (angle < -0.20944f) {
        angle = ((angle + 1.3613564f) * 1.5707964f) / 1.1519164f + -1.5707964f;
        turn = magnitude * sead::Mathf::cos(angle);
        forward = magnitude * sead::Mathf::sin(angle);
    } else if (angle < 0.20944f) {
        turn = magnitude;
        forward = 0.0f;
    } else if (angle < 1.3613564f) {
        angle = ((angle + -0.20944f) * 1.5707964f) / 1.1519164f;
        turn = magnitude * sead::Mathf::cos(angle);
        forward = magnitude * sead::Mathf::sin(angle);
    } else if (angle < 1.7802364f) {
        turn = 0.0f;
        forward = magnitude;
    } else if (angle < 2.9321527f) {
        angle = ((angle + -1.7802364f) * 1.5707964f) / 1.1519164f + 1.5707964f;
        turn = magnitude * sead::Mathf::cos(angle);
        forward = magnitude * sead::Mathf::sin(angle);
    } else {
        turn = -magnitude;
        forward = 0.0f;
    }
    const bool first_input = player->m239();
    bool attention_input = false;
    if (gear == 0 && forward > *mAccelerateInputThreshold_s && _b4 < 0.0f &&
        !ksys::act::Attention::instance()->sub_7100D74114()) {
        attention_input = !ksys::act::Attention::instance()->sub_7100D753B0();
    }
    const bool second_input = player->m240();
    const f32 forward_abs = forward > 0.0f ? forward : -forward;
    const f32 turn_abs = turn > 0.0f ? turn : -turn;
    if (forward_abs < 0.5f && turn_abs < 0.5f) {
        _104 = 0;
        _105 |= 2;
    } else {
        if (!(_105 & 2))
            _104 = 1;
        else if (_104 == 0)
            _104 = forward_abs > turn_abs ? 2 : 1;
        if (_104 == 2)
            _104 = forward_abs > turn_abs ? 2 : 1;
        if (_104 == 2) {
            turn = 0.0f;
        } else if (_104 == 1) {
            forward = 0.0f;
            attention_input = false;
        }
    }
    if (gear == 0 && (turn > 0.0f ? turn : -turn) < *mTurnStickXInputThreshold_s)
        turn = 0.0f;
    return {turn, forward, first_input, attention_input, second_input};
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
