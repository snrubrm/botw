#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CliffCheckSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CliffCheckSelect, ksys::act::ai::Ai)
public:
    explicit CliffCheckSelect(const InitArg& arg);
    ~CliffCheckSelect() override;
    bool isChangeable() const override;
    bool isFinished() const override;
    bool isFailed() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

    virtual void m34(sead::Vector3f* out);

    bool sub_710035116C();

protected:
    // static_param at offset 0x38
    const float* mCheckDist_s{};
    // static_param at offset 0x40
    const float* mCheckAngle_s{};
    // static_param at offset 0x48
    const bool* mIsSelectFirstTime_s{};
};

}  // namespace uking::ai
