#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/Cooking/cookManager.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

// vtable 0x71023e0418 (RTTI typeInfo static 0x71025b0f00): object shared through the
// CurrentCookResultHolder AI tree variable; placeholder name.
class Unk_71023e0418 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71023e0418, Unk_71025afb58)
public:
    CookItem mCookItem;
};

class CookPotRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CookPotRoot, ksys::act::ai::Ai)
public:
    explicit CookPotRoot(const InitArg& arg);
    ~CookPotRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // map_unit_param at offset 0x38
    const bool* mInitBurnState_m{};
    // aitree_variable at offset 0x40
    void* mCurrentCookResultHolder_a{};
    bool _48 = true;
    bool mHasFinishedCookItem = true;
    u8 _4A[6];
    CookArg mCookArg;
    sead::Buffer<sead::FixedSafeString<64>> mCookIngredients;
    bool _240 = false;
    bool _241 = false;
    bool _242 = false;
    Unk_71023b0898 _248{mActor, 0x8000083};
    Unk_71023e0418 _288;
};
KSYS_CHECK_SIZE_NX150(CookPotRoot, 0x4B8);

}  // namespace uking::ai
