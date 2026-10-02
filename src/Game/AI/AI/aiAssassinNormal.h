#pragma once

#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(AssassinNormal, LandHumEnemyNormal)
public:
    explicit AssassinNormal(const InitArg& arg);
    ~AssassinNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    s32 m53() override;
    bool m55() override {
        if (EnemyNormal::m55())
            return true;
        return isCurrentChild("不審物排除後");
    }

protected:
    ksys::act::BaseProcLink _400;
    sead::Vector3f _410;
};

}  // namespace uking::ai
