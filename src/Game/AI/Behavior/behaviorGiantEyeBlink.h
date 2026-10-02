#pragma once

#include "Game/AI/Behavior/behaviorEyeBlink.h"

namespace uking::behavior {

class GiantEyeBlink : public EyeBlink {
    SEAD_RTTI_OVERRIDE(GiantEyeBlink, EyeBlink)
public:
    explicit GiantEyeBlink(const InitArg& arg);
    ~GiantEyeBlink() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(GiantEyeBlink, 0x70);

}  // namespace uking::behavior
