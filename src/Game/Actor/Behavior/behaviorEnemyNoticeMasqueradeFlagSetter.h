#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EnemyNoticeMasqueradeFlagSetter : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EnemyNoticeMasqueradeFlagSetter, ksys::act::ai::Behavior)
public:
    explicit EnemyNoticeMasqueradeFlagSetter(const InitArg& arg);
    ~EnemyNoticeMasqueradeFlagSetter() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mTiming_s{};
    /* 0x30 */ const bool* mIsOn_s{};
};
KSYS_CHECK_SIZE_NX150(EnemyNoticeMasqueradeFlagSetter, 0x38);

}  // namespace uking::behavior
