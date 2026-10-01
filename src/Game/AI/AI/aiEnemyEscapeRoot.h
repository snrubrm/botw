#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyEscapeRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyEscapeRoot, ksys::act::ai::Ai)
public:
    explicit EnemyEscapeRoot(const InitArg& arg);
    ~EnemyEscapeRoot() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void* _38{};
};

}  // namespace uking::ai
