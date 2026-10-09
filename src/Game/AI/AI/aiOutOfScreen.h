#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class OutOfScreen : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OutOfScreen, ksys::act::ai::Ai)
public:
    explicit OutOfScreen(const InitArg& arg);
    ~OutOfScreen() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_71004F4054();
    void sub_71004F4270(sead::Vector3f* out);

protected:
    // static_param at offset 0x38
    const int* mUpdateInterval_s{};
    // static_param at offset 0x40
    const float* mTagetDistance_s{};
    // static_param at offset 0x48
    const float* mDeleteDistance_s{};
    ksys::Timer _50;
};
KSYS_CHECK_SIZE_NX150(OutOfScreen, 0x60);

}  // namespace uking::ai
