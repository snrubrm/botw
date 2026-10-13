#include "aal/aalDebugFileIOMgr.h"

namespace aal {

// Native default SafeString at 24C5A60 contains the pointer to
// "aal_debug_file_io" at +8; DialogArg copies that string object.
static const sead::SafeString sUnk_71024C5A60 = "aal_debug_file_io";

DebugFileIOMgr::DialogArg::DialogArg()
    : _0(sead::SafeString::cEmptyString), _10(sead::SafeString::cEmptyString),
      _20(sUnk_71024C5A60), _30(sead::SafeString::cEmptyString),
      _40(sead::SafeString::cEmptyString), _50(0x20) {}

}  // namespace aal
