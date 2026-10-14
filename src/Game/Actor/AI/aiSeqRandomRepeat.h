#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqRandomRepeat : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqRandomRepeat, ksys::act::ai::Ai)
public:
    explicit SeqRandomRepeat(const InitArg& arg);
    ~SeqRandomRepeat() override;

    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMinActionNum_s{};
    // static_param at offset 0x40
    const int* mMaxActionNum_s{};
    // static_param at offset 0x48
    const bool* mIsEndChangeable_s{};
    int _50 = 0;
};
KSYS_CHECK_SIZE_NX150(SeqRandomRepeat, 0x58);

}  // namespace uking::ai
