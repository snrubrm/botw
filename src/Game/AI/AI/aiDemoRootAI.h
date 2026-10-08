#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace ksys::evt {
class ActionContext;
}

namespace uking::ai {

// Placeholder (no name known): the request object passed to the DemoRootAI helpers at 0x7100d61fac-0x7100d62d18: the child
// name at +8, the child index at +0x48, the parameter pack at +0x50 and flags at +0xaf4. Only the members that are used
// are described.
struct DemoAiRequest {
    u8 _0[8];
    sead::SafeString mChildName;
    u8 _18[0x48 - 0x18];
    s32 mChildIdx;
    u8 _4c[4];
    ksys::act::ai::InlineParamPack mParams;
};

class DemoRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DemoRootAI, ksys::act::ai::Ai)
public:
    explicit DemoRootAI(const InitArg& arg);
    ~DemoRootAI() override;
    bool initChildren(const ksys::AIDefSet& set, sead::Heap* heap) override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;
    void loadParams_() override;
    void getCurrentName(sead::BufferedSafeString* name, ksys::act::ai::ActionBase* last) const override;

    void sub_7100D62598();
    // 0x7100d62394 (placeholder name): changes to the child "Demo_Idling" (if there is one) with DisablePhysics = false.
    bool sub_7100D62394(DemoAiRequest* request);
    // 0x7100d62d18 (placeholder name): the child `name` exists and has the TriggerAction flag.
    bool sub_7100D62D18(const sead::SafeString& name);

    // The 0x7100d61fc0-0x7100d62750 node-advance helpers are free functions in this TU that read
    // _38 directly, so they are friends (they cannot go through a public accessor: the original
    // calls Buffer::operator[] on _38 itself, with the checked-index fallback).
    friend void sub_7100D61FC0(DemoRootAI*, ksys::evt::ActionContext*, u32*, bool);
    friend void sub_7100D6225C(DemoRootAI*, const sead::SafeString&, s32, bool);
    friend void sub_7100D62750(DemoRootAI*, u32, s32, ksys::act::ai::InlineParamPack*);
protected:
    sead::Buffer<ksys::act::ai::ActionBase*> _38;
    u16 _48{};
    u16 _4a{};
};

}  // namespace uking::ai
