#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class HideLifeGage : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HideLifeGage, ksys::act::ai::Behavior)
public:
    explicit HideLifeGage(const InitArg& arg);
    ~HideLifeGage() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ u32 _28 = 0;
};
KSYS_CHECK_SIZE_NX150(HideLifeGage, 0x30);

}  // namespace uking::behavior
