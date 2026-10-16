#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EnemyKeepAnimeDriven : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EnemyKeepAnimeDriven, ksys::act::ai::Behavior)
public:
    explicit EnemyKeepAnimeDriven(const InitArg& arg);
    ~EnemyKeepAnimeDriven() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mTransBoneName_s{};
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyKeepAnimeDriven, 0x40);

}  // namespace uking::behavior
