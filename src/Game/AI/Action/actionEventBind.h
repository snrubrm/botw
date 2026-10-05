#pragma once

#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace ksys::act {
class ActorBind;
}

// Name from the CSV (ActorLinkForEventBindMaybe::rtti1): the object the "EventBindUnit" AI tree variable points to
// (EventBind embeds it at +0x130; its vtable is also stored by NPCHorseRide's constructor). `_8` is the ModelBindInfo
// that was bound last (EventBind::leave_ unbinds it).
class ActorLinkForEventBindMaybe : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(ActorLinkForEventBindMaybe, Unk_71025afb58)
public:
    ~ActorLinkForEventBindMaybe() override = default;

    ksys::act::ModelBindInfo* _8 = nullptr;
};

namespace uking::action {

class EventBind : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventBind, ksys::act::ai::Action)
public:
    explicit EventBind(const InitArg& arg);
    ~EventBind() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual ksys::act::BaseProcLink* m32();

    // aitree_variable at offset 0x20
    void* mEventBindUnit_a{};
    // dynamic_param at offset 0x28
    float* mRotOffsetX_d{};
    // dynamic_param at offset 0x30
    float* mRotOffsetY_d{};
    // dynamic_param at offset 0x38
    float* mRotOffsetZ_d{};
    // dynamic_param at offset 0x40
    float* mTransOffsetX_d{};
    // dynamic_param at offset 0x48
    float* mTransOffsetY_d{};
    // dynamic_param at offset 0x50
    float* mTransOffsetZ_d{};
    // dynamic_param at offset 0x58
    bool* mIsContinueBind_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x80
    sead::SafeString mNodeName_d{};
    ksys::act::ModelBindInfo _90;
    ActorLinkForEventBindMaybe _130;
};
KSYS_CHECK_SIZE_NX150(EventBind, 0x140);

}  // namespace uking::action
