#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyVacuumBombSelectBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyVacuumBombSelectBase, ksys::act::ai::Ai)
public:
    explicit EnemyVacuumBombSelectBase(const InitArg& arg);
    ~EnemyVacuumBombSelectBase() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34(ksys::act::BaseProcLink* link);

    bool sub_71003C3198();

protected:
    // static_param at offset 0x38 ("PartsKey0".."PartsKey4")
    sead::SafeString mPartsKey_s[5];
};

}  // namespace uking::ai
