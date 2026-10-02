#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRide : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseRide, ksys::act::ai::Action)
public:
    explicit HorseRide(const InitArg& arg);
    ~HorseRide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x71001ad8a0 (declaration only): starts the AS `name` on the upper (a2) or both body slots
    // unless it is already playing.
    void sub_71001AD8A0(const char* name, bool a2);
    // 0x71001ada78: true when the AS of slot `UpperBodyASSlot` has ended (or there is no ASList).
    bool sub_71001ADA78() const;
    // 0x71001adaa0: turns the actor towards `target`.
    void sub_71001ADAA0(const sead::Vector3f& target);
    // 0x71001adaa8: stops the look-at.
    void sub_71001ADAA8();

    // static_param at offset 0x20
    const int* mUpperBodyASSlot_s{};
    // static_param at offset 0x28
    const int* mLowerBodyASSlot_s{};
};

}  // namespace uking::action
