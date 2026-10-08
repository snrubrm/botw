#include "Game/UI/uiSwkbdMgr.h"
#include <prim/seadStringUtil.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(SwkbdMgr)

// D1 0x71009858fc, D0 0x7100985900
SwkbdMgr::~SwkbdMgr() = default;

// 0x7100985c4c
void SwkbdMgr::sub_7100985C4C() {}

// 0x7100985c54
bool SwkbdMgr::x() const {
    if (_28 == sead::SafeStringBase<char16>::cNullChar)
        return false;
    return _78 == 0;
}

// 0x7100985ca8
void SwkbdMgr::x_0() {
    sead::FixedSafeString<64> name;
    const char16* text = &_28;
    sead::StringUtil::convertUtf16ToUtf8(name.getBuffer(), name.getBufferSize(), text, -1);
    ksys::gdt::setFlag_Horse_NewName(name);
    ksys::gdt::setFlag_Horse_IsNewNameEntered(true);
}

// 0x7100985c84
bool SwkbdMgr::x_1() const {
    return (_78 & 0x3fffff) == 0x29f;
}

const char16* SwkbdMgr::sub_7100985C98() const {
    return &_28;
}

bool SwkbdMgr::sub_7100985CA0() const {
    return true;
}

}  // namespace uking::ui
