#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

// Unnamed class of the object WizzrobeRoot shares through the "WizzrobeMagicWeatherUnit" AI tree
// variable (WizzrobeRoot::_208). Placeholder name = vtable address. Its ctor (0x71005ff064), D2 and D0
// are emitted in the WizzrobeRoot TU; its other functions live at 0x7100741c24-0x71007420b8.
class Unk_7102431fa8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102431fa8, Unk_71025afb58)
public:
    // NON_MATCHING: the original zeroes _14 before _10 (store order)
    explicit Unk_7102431fa8(ksys::act::Actor* actor) : _d0(actor) {}
    ~Unk_7102431fa8() override = default;

    // 0x71007420b8 (CSV ICF name sead::XmlElement::TmpAttribute::TmpAttribute)
    void sub_71007420B8(const sead::SafeString& start_as_name, const sead::SafeString& stop_as_name,
                        s32 target_idx);
    // 0x7100741c24
    void sub_7100741C24();
    // 0x7100741e14
    void sub_7100741E14();

    u64 _8 = 0;
    bool _10 = false;
    // zeroed with a single 8-byte store by the ctor (aggregate of two words)
    u32 _14[2]{};
    sead::FixedSafeString<64> _20{sead::SafeString::cEmptyString};
    sead::FixedSafeString<64> _78{sead::SafeString::cEmptyString};
    ksys::act::Actor* _d0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102431fa8, 0xd8);
