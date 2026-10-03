#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonStateChangeRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonStateChangeRoot, ksys::act::ai::Ai)
public:
    explicit GanonStateChangeRoot(const InitArg& arg);
    ~GanonStateChangeRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x71003eee18 (declared only; placeholder name)
    void sub_71003EEE18();

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    f32 _40{};
};

}  // namespace uking::ai
