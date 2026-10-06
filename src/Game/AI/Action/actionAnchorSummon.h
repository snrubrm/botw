#pragma once

#include <container/seadBuffer.h>
#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnchorSummon : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(AnchorSummon, ActionWithPosAngReduce)
public:
    explicit AnchorSummon(const InitArg& arg);
    ~AnchorSummon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void sub_710008C850(const sead::Vector3f& pos, s32 index);

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x40
    sead::SafeString mSummonActor_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mSummonActorEquip1_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mSummonActorEquip2_d{};
    sead::Buffer<Unk_710235aba0> _70;
    sead::Buffer<ksys::act::BaseProcHandle> _80;
    bool _90 = false;
};

}  // namespace uking::action
