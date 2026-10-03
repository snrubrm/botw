#pragma once

#include "Game/AI/AI/aiPriestBossMeta.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossMetaAIRoot : public PriestBossMeta {
    SEAD_RTTI_OVERRIDE(PriestBossMetaAIRoot, PriestBossMeta)
public:
    explicit PriestBossMetaAIRoot(const InitArg& arg);
    ~PriestBossMetaAIRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void calc_() override;

    void sub_710052618C();
    bool sub_710052656C(Unk_7102450fa8::Unk3* out);
    void sub_71005266A0();
    void sub_7100526918();

protected:
    // static_param at offset 0x50
    const int* mLife_s{};
    // static_param at offset 0x58
    const float* mPlayerRecoverFromFallFrames_s{};
    // static_param at offset 0x60
    sead::SafeString mBowActorName_s{};
    // static_param at offset 0x70
    sead::SafeString mArrowActorName_s{};
    // static_param at offset 0x80
    sead::SafeString mWeaponActorName_s{};
    // static_param at offset 0x90
    sead::SafeString mThunderActorName_s{};
    // map_unit_param at offset 0xa0
    const int* mPriestBossStartPhase_m{};
    // map_unit_param at offset 0xa8
    sead::SafeString mUniqueNameMessageLabel_m{};
    Unk_71023dbd40 _b8{mActor, 0x80000d7};
    Unk_7102409958 _e8{mActor, 0x80000da};
    void* _128 = nullptr;
    f32 _130 = -1.0f;
    Unk_7102450fa8* _138 = nullptr;
    Unk_7102450fa8::Phase _140;
    s32 _144 = -1;
};
KSYS_CHECK_SIZE_NX150(PriestBossMetaAIRoot, 0x148);

// Child names of PriestBossMetaAIRoot per phase (段階_通常, 段階_分身, 段階_巨大化, 段階_祭り, 段階_終了);
// defined in the PriestBossMetaAIRoot TU (static initialiser 0x7100525eb8).
extern sead::SafeArray<sead::SafeString, 5> sUnk_71025bb7e0;
// "Main" x5 and "0", "1", "", "", "" (used by PriestBossPhase::calc_).
extern sead::SafeArray<sead::SafeString, 5> sUnk_71025bb830;
extern sead::SafeArray<sead::SafeString, 5> sUnk_71025bb880;

}  // namespace uking::ai
