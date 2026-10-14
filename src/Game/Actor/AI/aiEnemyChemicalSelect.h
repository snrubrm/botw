#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class Chemical;
}

namespace uking::ai {

class EnemyChemicalSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyChemicalSelect, ksys::act::ai::Ai)
public:
    explicit EnemyChemicalSelect(const InitArg& arg);
    ~EnemyChemicalSelect() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsCheckActive_s{};
    // static_param at offset 0x40
    sead::SafeString mChmObjName_s{};
    ksys::act::Chemical* _50{};
};

}  // namespace uking::ai
