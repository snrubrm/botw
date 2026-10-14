#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantRecognizeTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ForestGiantRecognizeTarget, ksys::act::ai::Ai)
public:
    explicit ForestGiantRecognizeTarget(const InitArg& arg);
    ~ForestGiantRecognizeTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x71003d95c8 (placeholder name): clears the target state and starts "発見" towards the target.
    void changeToFound();

protected:
};

}  // namespace uking::ai
