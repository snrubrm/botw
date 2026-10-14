#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SystemHide : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SystemHide, ksys::act::ai::Action)
public:
    explicit SystemHide(const InitArg& arg);
    ~SystemHide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual bool m32();

    // 0x71002906cc / 0x71002907bc (placeholder names): take the actor's physics out of / back into the world.
    // 0x7100290438 (lane5 s5): hides the actor (counterpart of sub_71002907BC / leave_).
    void sub_7100290438();
    void sub_71002906CC();
    void sub_71002907BC();

    // static_param at offset 0x20
    const bool* mIsOnAttention_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
    int _38 = -1;
    bool _3c = false;
    bool _3d = false;
};

}  // namespace uking::action
