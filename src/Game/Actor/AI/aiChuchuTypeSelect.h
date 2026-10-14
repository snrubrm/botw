#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChuchuTypeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChuchuTypeSelect, ksys::act::ai::Ai)
public:
    explicit ChuchuTypeSelect(const InitArg& arg);
    ~ChuchuTypeSelect() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
