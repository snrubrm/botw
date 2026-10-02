#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RestLifeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RestLifeSelect, ksys::act::ai::Ai)
public:
    explicit RestLifeSelect(const InitArg& arg);
    ~RestLifeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100550C44(ksys::act::ai::InlineParamPack* params);

protected:
    // static_param at offset 0x38
    const float* mLifeRatio_s{};
    // static_param at offset 0x40
    const bool* mIsTrgOnly_s{};
    // static_param at offset 0x48
    const bool* mIsEnter_s{};
    s32 _50 = 0;
    bool _54 = false;
};
KSYS_CHECK_SIZE_NX150(RestLifeSelect, 0x58);

}  // namespace uking::ai
