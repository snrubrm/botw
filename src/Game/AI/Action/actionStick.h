#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "Game/AI/aiUnk_710244ECF0.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

class Stick : public ActionEx {
    SEAD_RTTI_OVERRIDE(Stick, ActionEx)
public:
    explicit Stick(const InitArg& arg);
    ~Stick() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710027d3ac (placeholder name): binds the stick to the parent link of the StickActor actor if that actor is in
    // the calc state.
    bool sub_710027D3AC();

    // dynamic_param at offset 0x20
    sead::Vector3f* mStickPos_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mStickPosDiv_d{};
    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mStickActor_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mStickBodyName_d{};
    /* 0x48 */ Unk_710244ecf0 _48;
    /* 0xc0 */ ksys::act::ModelBindInfo _c0;
    /* 0x160 */ u32 _160 = 0;
    /* 0x164 */ u16 _164 = 0;
};
KSYS_CHECK_SIZE_NX150(Stick, 0x168);

}  // namespace uking::action
