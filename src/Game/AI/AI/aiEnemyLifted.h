#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyLifted : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyLifted, ksys::act::ai::Ai)
public:
    explicit EnemyLifted(const InitArg& arg);
    ~EnemyLifted() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

    virtual void m34();

protected:
    sead::Vector3f _38{0, 0, 0};
    Unk_7102451bd8 _48;
};

}  // namespace uking::ai
