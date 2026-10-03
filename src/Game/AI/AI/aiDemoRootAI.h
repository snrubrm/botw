#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

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
protected:
    sead::Buffer<ksys::act::ai::ActionBase*> _38;
    u16 _48{};
    u16 _4a{};
};

}  // namespace uking::ai
