#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonGrudgeNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(GanonGrudgeNormal, EnemyNormal)
public:
    explicit GanonGrudgeNormal(const InitArg& arg);
    ~GanonGrudgeNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m48(sead::Vector3f* pos) override;

    void m34() override;
    void m36() override;
    void calc_() override;

protected:
    sead::Vector3f _3d0{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(GanonGrudgeNormal, 0x3e0);

}  // namespace uking::ai
