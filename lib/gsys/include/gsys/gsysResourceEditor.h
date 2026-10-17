#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class ModelScene;

// createInstance 0x7100c5d1d8 allocates 0x24b8 bytes, constructs the singleton
// disposer at +8 and installs the Node-based ResourceEditor vtable 0x71024cf7f8.
// Only the scene reference and singleton prefix are modelled here.
class ResourceEditor : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ResourceEditor)
public:
    ResourceEditor();
    virtual ~ResourceEditor();

    // Stage unload 0x71007c5d20 supplies nullptr and true. The release method
    // 0x7100c5d3e0 only updates the scene reference; the bool's meaning is unknown.
    void sub_7100C5D3E0(ModelScene* scene, bool);

private:
    // calc 0x7100c5d444 passes this pointer to Model::bind as a ModelScene*.
    ModelScene* mScene;  // +0x28
    u8 _30[0x24b8 - 0x30];
};
static_assert(sizeof(ResourceEditor) == 0x24b8);

}  // namespace gsys
