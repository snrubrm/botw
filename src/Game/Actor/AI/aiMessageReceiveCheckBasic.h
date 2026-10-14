#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MessageReceiveCheckBasic : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MessageReceiveCheckBasic, ksys::act::ai::Ai)
public:
    explicit MessageReceiveCheckBasic(const InitArg& arg);
    ~MessageReceiveCheckBasic() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual bool m34();
    virtual bool m35();
    virtual void m36();

    // 0x71004a4d84 (defined in this TU, so Basic::enter_ inlines it): m36() and the "オフ" child.
    void changeToOff();

protected:
    bool _38 = false;
};

}  // namespace uking::ai
