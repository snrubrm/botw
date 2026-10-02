#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

// Keeps the actors in the area in two buffers (current / previous frame, _64 selects the current one)
// and calls m32 for actors that entered and m33 for actors that left.
class ActorAreaInOutSendMessage : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(ActorAreaInOutSendMessage, AreaTagAction)
public:
    explicit ActorAreaInOutSendMessage(const InitArg& arg);
    ~ActorAreaInOutSendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // Actor entered / left the area.
    virtual void m32(const ksys::act::ActorConstDataAccess& accessor) {}
    virtual void m33(const ksys::act::ActorConstDataAccess& accessor) {}
    // Whether the actor is ignored.
    virtual bool m34(const ksys::act::ActorConstDataAccess& accessor) { return false; }
    void m5() override;
    bool m15(const ksys::act::ActorConstDataAccess& accessor) override;
    void m2() override;

    // static_param at offset 0x38
    const int* mBufferNum_s{};
    sead::SafeArray<sead::Buffer<ksys::act::BaseProcLink>, 2> _40;
    // Bit i: link i of the previous buffer is still in the area.
    u8 _60 = 0;
    s32 _64 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorAreaInOutSendMessage, 0x68);

}  // namespace uking::action
