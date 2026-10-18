#include "Game/Actor/Action/actionAnimalMoveBase.h"
#include "KingSystem/System/VFR.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

#include "KingSystem/ActorSystem/AS/ASList.h"

#include "KingSystem/ActorSystem/actActorSensorUtil.h"

#include "KingSystem/Physics/CharacterController/physCharacterController.h"

#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AnimalMoveBase::AnimalMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalMoveBase::~AnimalMoveBase() = default;

bool AnimalMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    const s32 max = *mMaxUseGear_s;
    s32 gear = *mMinUseGear_s;
    if (max >= gear) {
        auto* random = sead::GlobalRandom::instance();
        gear += random->getU32((max + 1) - gear);
    }
    _68 = gear;
    if (*mCanUseHorseGearInput_s) {
        const act::Rideable::Gear input_gear(rideable->_134);
        if (int(input_gear) > 0)
            gear = rideable->_134;
    }
    rideable->sub_7100E63224(u32(*mUseGearType_s), u32(gear));
    rideable->_18.sub_7100E770C4(false);
}

void AnimalMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalMoveBase::loadParams_() {
    getStaticParam(&mMinUseGear_s, "MinUseGear");
    getStaticParam(&mMaxUseGear_s, "MaxUseGear");
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mMinGearAtAutoGearDown_s, "MinGearAtAutoGearDown");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mCanUseHorseGearInput_s, "CanUseHorseGearInput");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
    getStaticParam(&mHasToDecelerateNearGoal_s, "HasToDecelerateNearGoal");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: gear source enums and repeated table lookup / clamp scheduling differ.
void AnimalMoveBase::calc_() {
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    act::sub_7100E7F698(rideable, as_list, controller);

    const auto* target = m32();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f direction(target->x - position.x, 0.0f, target->z - position.z);
    const f32 distance = direction.normalize();
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    const f32 velocity_length = velocity.normalize();

    if (isLandedMaybe(mActor, false)) {
        const s32 count = sub_71007A47C4(mActor);
        for (s32 i = 0; i < count; ++i) {
            if (auto* contact = sub_71007A471C(mActor, i)) {
                sead::Vector3f axis;
                f32 angle = 0.0f;
                ksys::util::sub_71011EEB08(&axis, &angle, direction, contact->_c,
                                          sead::Vector3f::ey);
                if (angle >= 1.7453293f) {
                    setFailed();
                    return;
                }
            }
        }
    }
    if (!m34(velocity, velocity_length / 30.0f)) {
        setFailed();
        return;
    }

    const s32 gear_type = *mUseGearType_s;
    s32 requested_gear = _68;
    if (*mCanUseHorseGearInput_s) {
        const s32 input_gear = s32(rideable->_134);
        if (input_gear > 0)
            requested_gear = input_gear;
    }
    requested_gear = sead::Mathi::min(requested_gear, rideable->_168);
    if (*mHasToDecelerateNearGoal_s) {
        s32 row = gear_type;
        const auto* speed_entry = &act::sUnk_7102603058;
        if (requested_gear != 0 && rideable->_170) {
            if (row >= rideable->_178)
                row = 0;
            speed_entry = &rideable->_170->mGears[row][requested_gear - 1];
        }
        const f32 scale = rideable->_164;
        const f32 stopping_ratio = (speed_entry->mSpeed * scale) / (speed_entry->_4 * scale);
        f32 tolerance = *mGoalDistanceTolerance_s;
        if (!(tolerance >= 0.0f)) {
            f32 rate = speed_entry->_4 * scale;
            if (rate <= 0.0f)
                rate = 1.5707964f;
            tolerance = (scale * speed_entry->mSpeed) / rate;
        }
        const f32 stopping_distance = (stopping_ratio + stopping_ratio) - tolerance;
        if (stopping_distance > 0.0f && distance <= stopping_distance)
            requested_gear = 1;
    }

    s32 final_gear = requested_gear;
    if (*mIsAutoGearDownEnabled_s && requested_gear > *mMinGearAtAutoGearDown_s) {
        const s32 adjusted = sead::Mathi::max(s32(rideable->_a0._7c), requested_gear) -
                             s32(rideable->_a0._7e);
        final_gear = sead::Mathi::max(*mMinGearAtAutoGearDown_s,
                                    sead::Mathi::min(adjusted, requested_gear));
    }
    if (final_gear != 0) {
        if (m35(rideable, gear_type, requested_gear, *mMinGearAtAutoGearDown_s, direction) &&
            *mIsAutoGearDownEnabled_s && requested_gear > *mMinGearAtAutoGearDown_s) {
            const s32 adjusted = sead::Mathi::max(s32(rideable->_a0._7c), requested_gear) -
                                 s32(rideable->_a0._7e);
            final_gear = sead::Mathi::max(*mMinGearAtAutoGearDown_s,
                                        sead::Mathi::min(adjusted, requested_gear));
        }
        rideable->sub_7100E63224(u32(gear_type), u32(final_gear));
    } else {
        as_list->x_6(1, 0, 0.0f);
        as_list->x_6(2, 0, 0.0f);
        as_list->x_6(9, 0, 0.0f);
        rideable->sub_7100E62B84();
        rideable->sub_7100E63224(0, 0);
    }
    if (m33(distance))
        setFinished();
}

sead::Vector3f* AnimalMoveBase::m32() {
    return mTargetPos_d;
}

bool AnimalMoveBase::m33(float x) {
    return false;
}

bool AnimalMoveBase::m34(const sead::Vector3f& pos, float x) {
    const f32 dist = ksys::VFR::instance()->getDeltaFrame() * x * 2.0f;
    if (dist > 0.0f && sub_710072FEC4(mActor, pos, dist, nullptr, true, nullptr))
        return false;
    return true;
}

// NON_MATCHING: original enum identities of the three integer movement arguments are unknown.
bool AnimalMoveBase::m35(act::RideableBase* rideable, s32 gear_type, s32 gear,
                         s32 min_gear_at_auto_down, const sead::Vector3f& direction) {
    return rideable->sub_7100E63560(gear_type, gear, min_gear_at_auto_down, direction, 0);
}

}  // namespace uking::action
