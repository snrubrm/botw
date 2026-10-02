#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BalloonBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BalloonBehavior, ksys::act::ai::Behavior)
public:
    explicit BalloonBehavior(const InitArg& arg);
    ~BalloonBehavior() override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(BalloonBehavior, 0x28);

}  // namespace uking::behavior
