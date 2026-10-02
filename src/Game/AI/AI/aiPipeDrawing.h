#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PipeDrawing : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PipeDrawing, ksys::act::ai::Ai)
public:
    explicit PipeDrawing(const InitArg& arg);
    ~PipeDrawing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void sub_71004F6298();

protected:
};

}  // namespace uking::ai
