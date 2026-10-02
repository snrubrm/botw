#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyWaitViewItem : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyWaitViewItem, ksys::act::ai::Ai)
public:
    explicit EnemyWaitViewItem(const InitArg& arg);
    ~EnemyWaitViewItem() override;
    void calc_() override;

    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35();
    virtual void m36();

    void sub_71003C3A2C(bool);

protected:
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
