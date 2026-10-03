#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeSound, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeSound(const InitArg& arg);
    ~EnemyNoticeSound() override;

    bool isFinished() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35();

    void changeToNotice();
    // 0x71003a6568: like changeToNotice with the child "行動".
    void changeToAct();

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    f32 _40{};
};

}  // namespace uking::ai
