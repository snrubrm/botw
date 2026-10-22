#pragma once

#include <basis/seadTypes.h>

namespace vlt {

// Native singleton at 0x7102652458. Its task layout and inheritance remain unmodeled.
// Complete setInstance 11F34D4 and destruction 11F34F4/11F3674/11F36C0 establish this pointer.
class LayerMgrTask {
public:
    static LayerMgrTask* sInstance;
    // 0x71011f34d4: sets sInstance to `instance` once and marks it (the field at +0x168).
    static void setInstance(LayerMgrTask* instance);

private:
    u8 _0[0x168];
    bool _168;
};

}  // namespace vlt
