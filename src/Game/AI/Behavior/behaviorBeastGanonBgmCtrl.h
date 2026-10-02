#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BeastGanonBgmCtrl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BeastGanonBgmCtrl, ksys::act::ai::Behavior)
public:
    explicit BeastGanonBgmCtrl(const InitArg& arg);
    ~BeastGanonBgmCtrl() override;
    bool hasUpdateForPreDeleteCb() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool updateForPreDelete() override;

    /* 0x28 */ const int* mLevel_s{};
    /* 0x30 */ bool _30 = false;
};
KSYS_CHECK_SIZE_NX150(BeastGanonBgmCtrl, 0x38);

}  // namespace uking::behavior
