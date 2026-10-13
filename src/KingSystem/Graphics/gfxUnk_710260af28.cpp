#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>

void Unk_710260af28::sub_7100F1D058(gsys::Model* model, u32 flags) {
    for (s32 i = 0; i < model->getUnits().size(); ++i)
        sub_7100F1D0BC(model->getUnits()[i]->mModelUnit, flags);
}

void Unk_710260af28::sub_7100F1C77C(gsys::Model* model, const void* user_data) {
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()[i]->mModelUnit;
        const s32 count = unit->getMaterialNum();
        for (s32 material = 0; material < count; ++material)
            sub_7100F1C824(unit, material, user_data);
    }
}
