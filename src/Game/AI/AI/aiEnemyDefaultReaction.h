#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::dmg {
class DamageManagerBase;
}

namespace uking::ai {

class EnemyDefaultReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyDefaultReaction, ksys::act::ai::Ai)
public:
    explicit EnemyDefaultReaction(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool isChangeable() const override;

    virtual bool m34(dmg::DamageManagerBase* damage_mgr, int damage_type);
    virtual void m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
                     ksys::act::ai::InlineParamPack* params);
    virtual bool m36() { return false; }
    virtual bool m37();
    virtual bool m38(dmg::DamageManagerBase* damage_mgr);
    virtual void m39(ksys::act::ai::InlineParamPack* params);
    virtual void m40(ksys::act::ai::InlineParamPack* params);
    virtual void m41(ksys::act::ai::InlineParamPack* params);
    virtual void m42(ksys::act::ai::InlineParamPack* params);
    virtual void m43(ksys::act::ai::InlineParamPack* params);
    virtual void m44();
    virtual bool m45();

protected:
    // static_param at offset 0x38
    const int* mJustGuardTimesMin_s{};
    // static_param at offset 0x40
    const int* mJustGuardTimesMax_s{};
    // static_param at offset 0x48
    const int* mSmallDamageCancelTimes_s{};
    // static_param at offset 0x50
    const bool* mInComboSmallDamageNoCancel_s{};
    int _58{};
    int _5c{};
    bool _60{};
    bool _61{};
    bool _62 = true;
};

}  // namespace uking::ai
