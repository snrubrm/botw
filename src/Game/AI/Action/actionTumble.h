#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Tumble : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Tumble, ksys::act::ai::Action)
public:
    explicit Tumble(const InitArg& arg);
    ~Tumble() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // Layout from the W constructor (0x710029cc38): VFRValue at 0x1c, VFRVec3f at 0x28, floats up to 0x68.
    u8 _20[0x68 - 0x20];
    Unk_7102451970 _68;
    u8 _88[0x118 - 0x88];
};

}  // namespace uking::action
