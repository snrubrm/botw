#pragma once

#include <gfx/seadColor.h>
#include <prim/seadSafeString.h>

namespace gsys {

// Partial model of the game's process meter. The class has its own two vtables and at least
// 0x98 bytes of state; only the system-wide measurement hooks are declared here.
class ProcessMeter {
public:
    // 0x7100c58ddc / 0x7100c58de0: empty in this build.
    void measureProcessBeginSystem(const sead::SafeString& name, const sead::Color4f& color);
    void measureProcessEndSystem();
};

}  // namespace gsys
