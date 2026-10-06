#pragma once

#include "Game/AI/Action/actionTurnIgnite.h"
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WizzrobeSummon : public TurnIgnite {
    SEAD_RTTI_OVERRIDE(WizzrobeSummon, TurnIgnite)
public:
    explicit WizzrobeSummon(const InitArg& arg);
    ~WizzrobeSummon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m32(ksys::act::BaseProcHandle* handle) override;
    const sead::Matrix34f& m33() override;

protected:
    void calc_() override;

    // 0x71002beddc (declared only; 832 B): updates _f8 (the actor matrix moved to the summon position).
    void sub_71002BEDDC();

    // static_param at offset 0xd0
    const int* mSummonBufferSize_s{};
    // static_param at offset 0xd8
    const int* mWeaponIndex_s{};
    // static_param at offset 0xe0
    sead::SafeString mSummonBufferKey_s{};
    // aitree_variable at offset 0xf0
    int* mSummonCount_a{};
    sead::Matrix34f _f8 = sead::Matrix34f::ident;
};

}  // namespace uking::action
