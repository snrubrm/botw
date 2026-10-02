#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ForceFixed : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ForceFixed, ksys::act::ai::Behavior)
public:
    explicit ForceFixed(const InitArg& arg);
    ~ForceFixed() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ u32 _28 = 0;
};
KSYS_CHECK_SIZE_NX150(ForceFixed, 0x30);

}  // namespace uking::behavior
