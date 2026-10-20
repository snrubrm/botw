#pragma once

#include <basis/seadTypes.h>
#include "gsys/gsysModelSceneComponent.h"

namespace gsys {
class RenderBufferContext;

// ModelScene constructs this component at +0x3778, before the next component
// at +0x4ea0. C17558 initializes its owned context pointer; C176EC creates it.
class ModelSceneBuffer : public ModelSceneComponent {
public:
    ModelSceneBuffer();
    ~ModelSceneBuffer() override;

    // Inline-only accessor name: Graphics F34F1C reads this pointer through the scene.
    RenderBufferContext* getRenderBufferContext() const { return mRenderBufferContext; }

private:
    RenderBufferContext* mRenderBufferContext;
    u8 _258[0x1728 - 0x258];
};
static_assert(sizeof(ModelSceneBuffer) == 0x1728);

}  // namespace gsys
