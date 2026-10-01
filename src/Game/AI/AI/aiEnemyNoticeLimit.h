#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeLimit : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeLimit, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeLimit(const InitArg& arg);

    bool isFinished() const override;

    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mOverNum_s{};
};

}  // namespace uking::ai
