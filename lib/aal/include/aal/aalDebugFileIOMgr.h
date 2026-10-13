#pragma once

#include <prim/seadSafeString.h>

namespace aal {

class DebugFileIOMgr {
public:
    class DialogArg {
    public:
        DialogArg();

    private:
        // Full CustomCurveXmlReader BA8CF8 constructs this 0x58-byte record
        // and assigns SafeStrings at +0/+10/+20/+30/+40.
        sead::SafeString _0;
        sead::SafeString _10;
        sead::SafeString _20;
        sead::SafeString _30;
        sead::SafeString _40;
        u32 _50;
    };
    static_assert(sizeof(DialogArg) == 0x58);
};

}  // namespace aal
