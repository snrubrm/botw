#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ForkAnimalASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAnimalASPlay, ksys::act::ai::Action)
public:
    explicit ForkAnimalASPlay(const InitArg& arg);
    ~ForkAnimalASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    // 0x710013d91c: selects the next gear of the rideable (SelectNextGear / SelectNextGearType) and
    // clears AS slots 1 and 2; called by AnimalTurn too (calc_ inlines it).
    void sub_710013D91C();

    // static_param at offset 0x20
    const int* mAllowChangeableFrame_s{};
    // static_param at offset 0x28
    const int* mSelectNextGearType_s{};
    // static_param at offset 0x30
    const int* mSelectNextGear_s{};
    // static_param at offset 0x38
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x40
    sead::SafeString mASKeyName_s{};
    ksys::Timer _50;
};

KSYS_CHECK_SIZE_NX150(ForkAnimalASPlay, 0x60);

}  // namespace uking::action
