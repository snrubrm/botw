#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HiddenOctarockSearchTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HiddenOctarockSearchTarget, ksys::act::ai::Ai)
public:
    explicit HiddenOctarockSearchTarget(const InitArg& arg);
    ~HiddenOctarockSearchTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool sub_7100432B0C(sead::Vector3f* out);
    // static_param at offset 0x38
    const float* mNoticeTerrorLevel_s{};
    // static_param at offset 0x40
    const float* mNoticeWorryRange_s{};
};

}  // namespace uking::ai
