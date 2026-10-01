#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DieSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DieSelect, ksys::act::ai::Ai)
public:
    explicit DieSelect(const InitArg& arg);
    ~DieSelect() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    virtual void m34(s32 a2, s32 a3, bool a4, bool a5);
    virtual void m35() {}

protected:
};

}  // namespace uking::ai
