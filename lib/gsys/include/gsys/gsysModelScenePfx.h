#pragma once

#include "gsys/gsysModelSceneComponent.h"

namespace sead::hostio {
class Node;
}

namespace gsys {

// Partial: only the hostio hook is modelled. The rest of the component (D1 0x7100c35518,
// initialize 0x7100c3565c, calc 0x7100c35904, ...) is still undecompiled. The destructor is
// declared only so this file does not emit the class vtable.
class ModelScenePfx : public ModelSceneComponent {
public:
    ~ModelScenePfx() override;
    // 0x7100c36538: the component attaches no hostio node of its own.
    void attachHostIO(sead::hostio::Node* node) override;
};

}  // namespace gsys
