#pragma once

#include <basis/seadTypes.h>
#include "Game/gameGraphics.h"

namespace ksys::gfx {

// Placeholder: the model render data handed to the renderers' teardown (0x7100f1f0f0). Only the block
// at +0x88 that the teardown frees is modelled.
struct ModelRenderDataMaybe {
    struct Block {
        // The map renderer's unit group this render data registered.
        Unk_7100f185a4::UnitGroup* mGroup;
        u8 _8[0x28];
        // Freed with delete[] before the block itself is deleted.
        u8* _30;
    };

    u8 _0[0x88];
    /* 0x88 */ Block* _88;
};

// Name from the CSV (0x7100f1f0f0). Only the teardown is modelled.
class UkingModelRenderOptionsMgr {
public:
    // 0x7100f1f0f0: destroys the model render data through the map renderer, the far model renderer
    // and the grudge renderer held by Graphics, then frees data's block at +0x88.
    void destroyModelRenderData(ModelRenderDataMaybe* data);
};

}  // namespace ksys::gfx
