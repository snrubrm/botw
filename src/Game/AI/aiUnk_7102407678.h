#pragma once

#include <container/seadSafeArray.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/Types.h"

namespace uking::ai {

// vtable 0x7102407678 (RTTI typeInfo static 0x71025b1988): object shared through the
// MagicCreateUnit AI tree variable (MasterSwordRoot::_f8, RodRoot::_118); placeholder name.
class Unk_7102407678 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102407678, Unk_71025afb58)
public:
    ksys::act::BaseProcHandle _8;
    sead::SafeArray<ksys::act::BaseProcHandle, 8> _18;
};
KSYS_CHECK_SIZE_NX150(Unk_7102407678, 0x98);

}  // namespace uking::ai
