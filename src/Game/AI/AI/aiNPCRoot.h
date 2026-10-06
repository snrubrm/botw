#pragma once

#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act {
class NPC;
}

namespace uking::ai {

class NPCRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCRoot, ksys::act::ai::Ai)
public:
    explicit NPCRoot(const InitArg& arg);
    ~NPCRoot() override;
    bool hasPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    // 0x71004dc9b8
    bool handleMessage_(const ksys::Message* message) override;
    // 0x71004dcba8: forwards mActor to the unnamed 0x71007132e4.
    void onPreDelete() override;

    virtual void m34();

    // Bound to the delegate _218.
    void sub_71004D8C5C();

protected:
    // 0x71004dc204: whether the player wears the Black / Stalfos / PhantomGanon armor series
    bool sub_71004DC204();
    struct Unk1 {
        bool _0 = false;
        ksys::act::BaseProcLink _8;
        void* _18 = nullptr;
        u32 _20 = 0;
        sead::FixedSafeString<32> _28;
    };

    // static_param at offset 0x38
    const int* mReleaseInterest2Time_s{};
    // static_param at offset 0x40
    const float* mPlayerHitVelocity_s{};
    // static_param at offset 0x48
    sead::SafeString mStaggerUpperASName_s{};
    // static_param at offset 0x58
    sead::SafeString mStaggerUpperRunASName_s{};
    act::NPC* _68 = nullptr;
    ksys::act::BaseProcLink _70;
    ksys::act::BaseProcLink _80;
    Unk1 _90[3];
    ksys::act::BaseProcLink _1b0;
    sead::Vector3f _1c0 = {0, 0, 0};
    f32 _1cc = 0;
    f32 _1d0 = 0;
    f32 _1d4 = 0;
    sead::Vector3f _1d8 = {-1, -1, -1};
    sead::Vector3f _1e4 = sead::Vector3f::zero;
    sead::Vector3f _1f0;
    u32 _1fc = 0;
    bool _200 = false;
    bool _201 = false;
    bool _202 = false;
    bool _203 = false;
    bool _204 = true;
    sead::Vector3f _208;
    u32 _214 = 0;
    sead::Delegate<NPCRoot> _218{this, &NPCRoot::sub_71004D8C5C};
};
KSYS_CHECK_SIZE_NX150(NPCRoot, 0x238);

}  // namespace uking::ai
