#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EnemyKeepAnimeDriven : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EnemyKeepAnimeDriven, ksys::act::ai::Behavior)
public:
    explicit EnemyKeepAnimeDriven(const InitArg& arg);
    ~EnemyKeepAnimeDriven() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mTransBoneName_s{};
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyKeepAnimeDriven, 0x40);

}  // namespace uking::behavior
