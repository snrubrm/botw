#include "KingSystem/Utils/StringUtil.h"

namespace ksys::util {

bool sub_71010C2EE4(const sead::SafeString& name, const sead::SafeString& list, char separator) {
    const char* str = list.cstr();
    const s32 length = list.calcLength();
    s32 start = 0;
    for (s32 i = 0; i <= length; ++i) {
        if (i == length || str[i] == separator) {
            const s32 n = i - start;
            if (n > 0 && list.getPart(start).comparen(name, n) == 0)
                return true;
            start = i + 1;
        }
    }
    return false;
}

}  // namespace ksys::util
