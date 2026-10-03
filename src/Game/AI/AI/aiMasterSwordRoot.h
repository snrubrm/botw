#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "Game/AI/aiUnk_7102407678.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MasterSwordRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(MasterSwordRoot, WeaponRootAI)
public:
    explicit MasterSwordRoot(const InitArg& arg);
    ~MasterSwordRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x71004a3410 (not decompiled): (re)creates the magic attack actor into _100.
    void sub_71004A3410();

protected:
    bool _e8 = false;
    // aitree_variable at offset 0xf0
    void* mMagicCreateUnit_a{};
    Unk_7102407678 _f8;
};
KSYS_CHECK_SIZE_NX150(MasterSwordRoot, 0x190);

}  // namespace uking::ai
