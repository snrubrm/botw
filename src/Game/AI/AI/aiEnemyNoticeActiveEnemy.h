#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeActiveEnemy : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeActiveEnemy, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeActiveEnemy(const InitArg& arg);
    ~EnemyNoticeActiveEnemy() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void sub_71003A4B3C();

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
    f32 _48{};
    int _4c{};
    int _50{};
    int _54{};
};

}  // namespace uking::ai
