#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeActiveEnemy : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeActiveEnemy, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeActiveEnemy(const InitArg& arg);
    ~EnemyNoticeActiveEnemy() override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    void changeToNotice();
    // 0x71003a4e30: changeChild("行動") with TargetPos and TargetActor.
    void changeToAct();

protected:
    struct Params {
        // dynamic_param at offset 0x38
        sead::Vector3f* mTargetPos_d{};
        // dynamic_param at offset 0x40
        ksys::act::BaseProcLink* mTargetActor_d{};
    };
    Params mParams;
    f32 _48{};
    int _4c{};
    int _50{};
    f32 _54{};
};

}  // namespace uking::ai
