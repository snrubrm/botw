#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x7102407678 (RTTI typeInfo static 0x71025b1988): object shared through the
// MagicCreateUnit AI tree variable (MasterSwordRoot::_f8); placeholder name.
class Unk_7102407678 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102407678, Unk_71025afb58)
public:
    ksys::act::BaseProcHandle _8;
    ksys::act::BaseProcHandle _18[8];
};
KSYS_CHECK_SIZE_NX150(Unk_7102407678, 0x98);

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
