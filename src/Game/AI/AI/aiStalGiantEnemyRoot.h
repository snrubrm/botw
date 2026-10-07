#pragma once

#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "Game/AI/aiUnk_7102451120.h"

// Actual opaque attachment object (vtable 0x71024511a8, ctor 0x7100724814,
// destructor 0x7100724874). The original calls its destructor for three members.
class Unk_71024511a8 {
public:
    Unk_71024511a8();
    ~Unk_71024511a8();
private:
    u64 _0[0xb0 / sizeof(u64)];
};
KSYS_CHECK_SIZE_NX150(Unk_71024511a8, 0xb0);

// Embedded object constructed by 0x71005a4e14. Three 0x180-byte entries each
// contain an attachment at +0xd0; the remaining entry fields are unrecovered.
class Unk_71005A4E14 {
public:
    Unk_71005A4E14();
private:
    struct Entry {
        u64 _0[0xd0 / sizeof(u64)];
        Unk_71024511a8 mAttachment;
    };
    Entry mEntries[3];
};
KSYS_CHECK_SIZE_NX150(Unk_71005A4E14, 0x480);

namespace uking::ai {

class StalGiantEnemyRoot : public StalEnemyRoot {
    SEAD_RTTI_OVERRIDE(StalGiantEnemyRoot, StalEnemyRoot)
public:
    explicit StalGiantEnemyRoot(const InitArg& arg);
    ~StalGiantEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    bool m34() override;
    void m35(ksys::act::ai::InlineParamPack* params) override;

protected:
    void sub_71005A3530();
    sead::SafeString _300;
    sead::SafeString _310;
    sead::SafeString _320;
    sead::SafeString _330;
    Unk_71005A4E14 _340;
    // static_param at offset 0x7c0
    sead::SafeString mActorNameChin_s{};
    // static_param at offset 0x7d0
    sead::SafeString mActorNameRib1_s{};
    // static_param at offset 0x7e0
    sead::SafeString mActorNameRib2_s{};
    // static_param at offset 0x7f0
    sead::SafeString mActorNameRib3_s{};
    // static_param at offset 0x800
    sead::SafeString mActorNameRib4_s{};
    // static_param at offset 0x810
    const bool* mIsDamageToEnemy_s{};
    Unk_7102451120 _818;
    Unk_7102451148 _828;
};

KSYS_CHECK_SIZE_NX150(StalGiantEnemyRoot, 0x838);

}  // namespace uking::ai
