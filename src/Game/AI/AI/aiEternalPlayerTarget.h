#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EternalPlayerTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EternalPlayerTarget, ksys::act::ai::Ai)
public:
    explicit EternalPlayerTarget(const InitArg& arg);
    ~EternalPlayerTarget() override;
    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71003C9AAC(bool);

protected:
};

}  // namespace uking::ai
