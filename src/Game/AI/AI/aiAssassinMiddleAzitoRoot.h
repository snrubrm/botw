#pragma once

#include "Game/AI/AI/aiAssassinNormal.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Awareness filter of AssassinMiddleAzitoRoot::m56 (vtable 0x71023d8848; m2 0x710031f8c8,
// D0 0x710031fa88): actors whose name is in the comma-separated list *_28 (LikeItem).
class Unk_71023d8848 : public ksys::act::Unk_71024dccf8 {
public:
    explicit Unk_71023d8848(const sead::SafeString* list) : _28(list) {}
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ const sead::SafeString* _28 = nullptr;
};

// Awareness filter of AssassinMiddleAzitoRoot::m66 (vtable 0x71023d8870; m2 0x710031f9a8,
// D0 0x710031faac): the enemy target filter, plus kokkos unless excluded by _30.
class Unk_71023d8870 : public Unk_71024514e8 {
public:
    using Unk_71024514e8::Unk_71024514e8;
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

class AssassinMiddleAzitoRoot : public AssassinNormal {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoRoot, AssassinNormal)
public:
    explicit AssassinMiddleAzitoRoot(const InitArg& arg);
    ~AssassinMiddleAzitoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    // 0x710031f404: not decompiled (calls the unnamed ksys::evt::Manager function 0x7100db0ca0).
    bool handleMessage_(const ksys::Message* message) override;

    void m49(Unk1* out, s32 idx) override;
    s32 m52(s32 idx) override;
    s32 m53() override { return 13; }
    bool m56(Unk2* out, Unk1* info) override;
    void m57(s32 type, Unk2* target) override;
    void m58(s32 type, Unk2* target) override;
    void m59() override;
    void m60(Unk3* out) override;
    void m61(Unk3* out) override;
    bool m66(Unk2* out, Unk1* info) override;
    bool m67(Unk2* out, Unk1* info) override;
    bool m75(const ksys::act::BaseProcLink& link) override { return sub_710031F804(link); }
    virtual bool m76();

    // 0x710031e748
    bool sub_710031E748(const char* unit_config_name);
    // 0x710031ead0
    void sub_710031EAD0(const ksys::act::BaseProcLink* link);
    // 0x710031f028 (name from the CSV)
    void assassinMiddleFindLikeItem(Unk2* target);
    // 0x710031f804
    bool sub_710031F804(const ksys::act::BaseProcLink& link) const;

protected:
    // static_param at offset 0x420
    sead::SafeString mEntryPoint_s{};
    // static_param at offset 0x430
    sead::SafeString mDemoName_s{};
    // static_param at offset 0x440
    sead::SafeString mLikeItem_s{};
    ksys::act::BaseProcLink _450;
    Unk_710235aba0 _460{mActor, 0x8000040};
    Unk_7102450678 _490;
    sead::SafeArray<ksys::act::BaseProcLink, 10> _4c8;
    bool _568 = false;
};

}  // namespace uking::ai
