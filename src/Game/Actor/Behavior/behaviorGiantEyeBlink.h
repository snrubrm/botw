#pragma once

#include "Game/Actor/Behavior/behaviorEyeBlink.h"

namespace uking::behavior {

class GiantEyeBlink : public EyeBlink {
    SEAD_RTTI_OVERRIDE(GiantEyeBlink, EyeBlink)
public:
    explicit GiantEyeBlink(const InitArg& arg);
    ~GiantEyeBlink() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(GiantEyeBlink, 0x70);

}  // namespace uking::behavior
