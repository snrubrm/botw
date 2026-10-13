#pragma once

namespace vlt {

// Native singleton at 0x7102652458. Its task layout and inheritance remain unmodeled.
// Complete setInstance 11F34D4 and destruction 11F34F4/11F3674/11F36C0 establish this pointer.
class LayerMgrTask {
public:
    static LayerMgrTask* sInstance;
};

}  // namespace vlt
