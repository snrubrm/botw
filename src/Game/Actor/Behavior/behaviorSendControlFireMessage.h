#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

class SendControlFireMessage : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SendControlFireMessage, ksys::act::ai::Behavior)
public:
    explicit SendControlFireMessage(const InitArg& arg);
    ~SendControlFireMessage() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const bool* mIsIgnite_s{};
    /* 0x30 */ ksys::Timer _30;
};
KSYS_CHECK_SIZE_NX150(SendControlFireMessage, 0x40);

}  // namespace uking::behavior
