#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetInAreaSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetInAreaSelect, ksys::act::ai::Ai)
public:
    explicit TargetInAreaSelect(const InitArg& arg);
    ~TargetInAreaSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // Pure in the original vtable (slot 34 is null); AssassinMagicTgtSelect / EnemyTargetInAreaSelect
    // / TargetInFanAreaSelect override it. m35 / m36 are empty (emitted in AssassinMagicTgtSelect's
    // TU); TargetInFanAreaSelect overrides them with the InlineParamPack* parameter.
    virtual bool m34() = 0;
    virtual void m35(ksys::act::ai::InlineParamPack* params) {}
    virtual void m36(ksys::act::ai::InlineParamPack* params) {}

protected:
    // static_param at offset 0x38
    const int* mOption_s{};
};

}  // namespace uking::ai
