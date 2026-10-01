#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

class WolfLinkReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkReaction, ksys::act::ai::Ai)
public:
    explicit WolfLinkReaction(const InitArg& arg);
    ~WolfLinkReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

    virtual void m34();
    virtual bool m35();

protected:
    bool _38 = true;
    act::WolfLink* _40 = nullptr;
};
KSYS_CHECK_SIZE_NX150(WolfLinkReaction, 0x48);

}  // namespace uking::ai
