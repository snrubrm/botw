#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwimEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(SwimEnemyNormal, EnemyNormal)
public:
    explicit SwimEnemyNormal(const InitArg& arg);
    ~SwimEnemyNormal() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_71005B488C();

protected:
    bool _3d0 = false;
};
KSYS_CHECK_SIZE_NX150(SwimEnemyNormal, 0x3d8);

}  // namespace uking::ai
