#pragma once

#include "Game/AI/AI/aiAssassinBossRootBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Damage callbacks without RTTI of their own (functions in the AssassinBossRoot TU,
// 0x710031a6fc..0x710031b050); `call` is declared only. Placeholder names = vtables.
class Unk_71023d7bd0 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = false;
    bool _25 = false;
    bool _26 = false;
    bool _27 = false;
};

class Unk_71023d7c08 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = false;
};

class Unk_71023d7c40 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    bool _24 = false;
    bool _25 = false;
};

class Unk_71023d7c78 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;
};

class AssassinBossRoot : public AssassinBossRootBase {
    SEAD_RTTI_OVERRIDE(AssassinBossRoot, AssassinBossRootBase)
public:
    explicit AssassinBossRoot(const InitArg& arg);
    ~AssassinBossRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m35() override;
    void m37() override;
    void m42() override;
    bool m45() override;
    void m46() override;
    void m47() override;

    void sub_7100319AB4();

protected:
    struct Params {
        // static_param at offset 0x2b0
        const int* mIronBallNum_s{};
        // static_param at offset 0x2b8
        const int* mBattleAvoidNum_s{};
    };
    Params mParams;
    Unk_71023d7bd0 _2c0;
    Unk_71023d7c08 _2e8;
    Unk_71023d7c40 _310;
    Unk_71023d7c78 _338;
    Unk_7102372510 _360{mActor, 0x8000008};
    Unk_7102368740 _390{mActor, 0x8000037};
    bool _400 = false;
};
KSYS_CHECK_SIZE_NX150(AssassinBossRoot, 0x408);

}  // namespace uking::ai
