#pragma once

#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::act {
class RideableBase;
}

namespace uking::action {

class AnimalMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimalMoveBase, ksys::act::ai::Action)
public:
    explicit AnimalMoveBase(const InitArg& arg);
    ~AnimalMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual sead::Vector3f* m32();
    virtual bool m33(float x);
    virtual bool m34(const sead::Vector3f& pos, float x);
    // Movement request at slot35. The three gear values are the rideable's by-value gear enum
    // (the request forwards them unchanged, which is where the argument zero-extension comes from).
    virtual bool m35(act::RideableBase* rideable, act::RideableBase::S1::UnkGear gear_type,
                     act::RideableBase::S1::UnkGear gear,
                     act::RideableBase::S1::UnkGear min_gear_at_auto_down,
                     const sead::Vector3f& direction);

    // static_param at offset 0x20
    const int* mMinUseGear_s{};
    // static_param at offset 0x28
    const int* mMaxUseGear_s{};
    // static_param at offset 0x30
    const int* mUseGearType_s{};
    // static_param at offset 0x38
    const int* mMinGearAtAutoGearDown_s{};
    // static_param at offset 0x40
    const float* mGoalDistanceTolerance_s{};
    // static_param at offset 0x48
    const bool* mCanUseHorseGearInput_s{};
    // static_param at offset 0x50
    const bool* mIsAutoGearDownEnabled_s{};
    // static_param at offset 0x58
    const bool* mHasToDecelerateNearGoal_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    int _68 = 1;
};

KSYS_CHECK_SIZE_NX150(AnimalMoveBase, 0x70);

}  // namespace uking::action
