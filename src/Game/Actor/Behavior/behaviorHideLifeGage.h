#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class HideLifeGage : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HideLifeGage, ksys::act::ai::Behavior)
public:
    explicit HideLifeGage(const InitArg& arg);
    ~HideLifeGage() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ u32 _28 = 0;
};
KSYS_CHECK_SIZE_NX150(HideLifeGage, 0x30);

}  // namespace uking::behavior
