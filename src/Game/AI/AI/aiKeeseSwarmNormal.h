#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseSwarmNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(KeeseSwarmNormal, EnemyNormal)
public:
    explicit KeeseSwarmNormal(const InitArg& arg);
    ~KeeseSwarmNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m45(const sead::Vector3f& target_pos, ksys::act::BaseProcLink& target,
             bool skip_own_pos) override;
    bool m46(const sead::Vector3f& pos, ksys::act::BaseProcLink& target) override;

protected:
};

}  // namespace uking::ai
