#pragma once

#include <prim/seadSafeString.h>

namespace ksys::evt {

// Event helpers that go through evt::Manager::instance() (TU around 0x7100dc816c-0x7100dc8ca8, with
// getActiveEventFlowPath). Placeholder names.

// 0x7100dc866c: Manager::hasActiveEvent() (false without a Manager).
bool sub_7100DC866C();
// 0x7100dc8684: Manager::isActiveEventNameEqualTo(event_name, entry_point) (false without a Manager).
bool sub_7100DC8684(const sead::SafeString& event_name, const sead::SafeString& entry_point);

}  // namespace ksys::evt
