#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DisableGiantArmorWeakPoint : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableGiantArmorWeakPoint, ksys::act::ai::Behavior)
public:
    explicit DisableGiantArmorWeakPoint(const InitArg& arg);
    ~DisableGiantArmorWeakPoint() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mWeakPointIdx_s{};
};
KSYS_CHECK_SIZE_NX150(DisableGiantArmorWeakPoint, 0x30);

}  // namespace uking::behavior
