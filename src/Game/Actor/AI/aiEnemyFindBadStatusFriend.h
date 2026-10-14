#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFindBadStatusFriend : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFindBadStatusFriend, ksys::act::ai::Ai)
public:
    explicit EnemyFindBadStatusFriend(const InitArg& arg);
    ~EnemyFindBadStatusFriend() override;
    void calc_() override;

    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void changeToStasis();

protected:
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
