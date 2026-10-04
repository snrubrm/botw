#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class Mimic : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(Mimic, ActionWithPosAngReduce)
public:
    explicit Mimic(const InitArg& arg);
    ~Mimic() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71001e669c (declared only): out of line in the original.
    void sub_71001E669C();
    void calc_() override;

    // static_param at offset 0x30
    const int* mMimicTime_s{};
    // static_param at offset 0x38
    const float* mMimicRate_s{};
    // static_param at offset 0x40
    sead::SafeString mMimicStartASName_s{};
    // static_param at offset 0x50
    sead::SafeString mMimicLoopASName_s{};
    // static_param at offset 0x60
    sead::SafeString mMimicEndASName_s{};
    // aitree_variable at offset 0x70
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x78
    bool* mIsStartResetMimicry_a{};
    s32 _80 = -1;
    f32 _84 = 0;
    ksys::Timer _88;
};

KSYS_CHECK_SIZE_NX150(Mimic, 0x98);

}  // namespace uking::action
