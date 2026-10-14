#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetBattleNodeBasisSelfPosBattle : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetBattleNodeBasisSelfPosBattle, ksys::act::ai::Behavior)
public:
    explicit SetBattleNodeBasisSelfPosBattle(const InitArg& arg);
    ~SetBattleNodeBasisSelfPosBattle() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mSetFlag_s{};
};
KSYS_CHECK_SIZE_NX150(SetBattleNodeBasisSelfPosBattle, 0x30);

}  // namespace uking::behavior
