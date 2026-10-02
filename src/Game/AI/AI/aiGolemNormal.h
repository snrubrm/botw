#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(GolemNormal, EnemyNormal)
public:
    explicit GolemNormal(const InitArg& arg);
    ~GolemNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    s32 m52(s32 idx) override;
    s32 m53() override { return 10; }

    void m34() override;
    void m37() override;
    void m38() override;

protected:
};

}  // namespace uking::ai
