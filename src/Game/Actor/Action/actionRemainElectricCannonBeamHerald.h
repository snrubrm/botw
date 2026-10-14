#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Event/evtResidentEvent.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <container/seadTList.h>

namespace uking::action {

// Single-virtual callback at vtable 0x71023b30d8, embedded at action+0x48.
// The constructor's self node and unlink helper establish the TListNode base at +8.
class Unk_71023b30d8 : public sead::TListNode<Unk_71023b30d8*> {
public:
    Unk_71023b30d8() : TListNode(this) {}
    virtual void sub_710022C55C(ksys::act::Actor* actor);
    void sub_710022BE20(ksys::act::Actor* actor);
    void sub_710022C2D0(ksys::act::Actor* actor);

    xlink2::HandleELink _28;
    Unk_71012419b4 _38;
    Unk_71012419b4 _58;
    xlink2::HandleELink _78;
    f32 _88 = 1.0f;
    bool _8c = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71023b30d8, 0x90);

class RemainElectricCannonBeamHerald : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonBeamHerald, ksys::act::ai::Action)
public:
    explicit RemainElectricCannonBeamHerald(const InitArg& arg);
    ~RemainElectricCannonBeamHerald() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mHeraldTime_s{};
    // dynamic_param at offset 0x28
    bool* mWillBeProtected_d{};
    f32 _30 = 0.0f;
    xlink2::HandleELink _38;
    Unk_71023b30d8 _48;
    bool _d8 = false;
    ksys::evt::ResidentEvent _e0;
};
KSYS_CHECK_SIZE_NX150(RemainElectricCannonBeamHerald, 0x2b0);

}  // namespace uking::action
