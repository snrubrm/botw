#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SoundTriggerTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SoundTriggerTag, ksys::act::ai::Ai)
public:
    explicit SoundTriggerTag(const InitArg& arg);
    ~SoundTriggerTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_7100E1BB90();

    // map_unit_param at offset 0x38
    const int* mSoundDelay_m{};
    // map_unit_param at offset 0x40
    sead::SafeString mSound_m{};
    // map_unit_param at offset 0x50
    sead::SafeString mSLinkInst_m{};
    // static_param (loaded in enter_)
    const bool* mAlways_s{};
    bool _68{};
};

}  // namespace uking::ai
