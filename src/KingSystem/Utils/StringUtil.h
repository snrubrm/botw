#pragma once

#include <prim/seadSafeString.h>

namespace ksys::util {

// 0x71010c2ee4 (own TU after ManagedTaskHandle): returns whether `name` is one of the
// `separator`-separated entries of `list` (empty entries are skipped).
bool sub_71010C2EE4(const sead::SafeString& name, const sead::SafeString& list, char separator);

}  // namespace ksys::util
