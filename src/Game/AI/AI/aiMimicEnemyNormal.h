#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(MimicEnemyNormal, EnemyNormal)
public:
    explicit MimicEnemyNormal(const InitArg& arg);
    ~MimicEnemyNormal() override;
    bool isFinished() const override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool sub_71004A7894();
    bool sub_71004A7BB4();
    bool sub_71004A7D18();
    void sub_71004A7DDC();

    // static_param at offset 0x3d0
    const float* mPlayerForceFindDist_s{};
    // static_param at offset 0x3d8
    const float* mRideHorseMaskPlayerFindDist_s{};
    // aitree_variable at offset 0x3e0
    bool* mIsStartResetMimicry_a{};
};

}  // namespace uking::ai
