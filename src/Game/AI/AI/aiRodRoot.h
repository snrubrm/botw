#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "Game/AI/aiUnk_7102407678.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class RodRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(RodRoot, WeaponRootAI)
public:
    explicit RodRoot(const InitArg& arg);
    ~RodRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_71005539C0();
    void sub_71005531E8();
    void sub_7100553CF0();
    // 0x71005535f8 / 0x7100553e5c (not decompiled; placeholder names).
    void sub_71005535F8();
    void sub_7100553E5C(s32 idx);

protected:
    // aitree_variable at offset 0xe8
    Unk_7102407678** mMagicCreateUnit_a{};
    Unk_71012419b4 _f0;
    s32 _110 = -1;
    s32 _114 = 0;
    Unk_7102407678 _118;
};
KSYS_CHECK_SIZE_NX150(RodRoot, 0x1b0);

}  // namespace uking::ai
