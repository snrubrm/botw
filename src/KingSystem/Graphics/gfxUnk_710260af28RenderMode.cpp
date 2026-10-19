#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include <gsys/gsysModelRenderUnit.h>
#include <gsys/gsysModelUnit.h>

// The original's sub_7100F1ED28 (0x7100f1ed28) calls this out of line and keeps its "this" pointer
// in a callee-saved register, which only happens when the callee is in another translation unit.
// The render mode setter therefore has its own file here.
void Unk_710260af28::sub_7100F1ED8C(gsys::ModelUnit* unit, int mode) {
    switch (mode) {
    case 0:
        unit->setUnkIndex(22);
        unit->enableRenderViewOption(static_cast<gsys::ModelEnum::RenderViewOption>(0), false, -1);
        unit->enableRenderOption(static_cast<gsys::ModelEnum::RenderOption>(2), false);
        for (int i = 0; i < unit->getModelRenderUnitNum(); ++i) {
            u32& flags = unit->getModelRenderUnit(i)->getFlags10();
            flags = (flags & 0xc3ffffff) | 0x08000000;
        }
        break;
    case 1:
        unit->setUnkIndex(0);
        for (int i = 0; i < unit->getModelRenderUnitNum(); ++i)
            unit->getModelRenderUnit(i)->getFlags10() &= 0xc3ffffff;
        break;
    }
}
