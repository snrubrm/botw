#include "KingSystem/Terrain/teraEditor.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/Terrain/teraSystem.h"

void Unk_7102504260::sub_710107E900(gsys::Model* model, bool visible) {
    for (u32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits()(i)->mModelUnit;
        {
            const auto name = unit->getName();
            if (name == sead::SafeString("TeraTerrain")) {
                // called through a pointer in the original (not devirtualised)
                unit->setMaterialVisible(
                    (&ksys::tera::Terrain::instance()->_370->_4ae0->_10)->getMaterialIndexMaybe(3),
                    visible);
            }
        }
        {
            const auto name = unit->getName();
            if (name == sead::SafeString("TeraRoute")) {
                // called through a pointer in the original (not devirtualised)
                unit->setMaterialVisible(
                    (&ksys::tera::Terrain::instance()->_370->_4ae0->_f98)->getMaterialIndexMaybe(5),
                    visible);
                // called through a pointer in the original (not devirtualised)
                unit->setMaterialVisible(
                    (&ksys::tera::Terrain::instance()->_370->_4ae0->_f98)->getMaterialIndexMaybe(6),
                    visible);
            }
        }
    }
}

bool Unk_7102504260::m9() {
    sub_710107E900(ksys::tera::Terrain::instance()->sub_710114DEE0(), true);
    return true;
}

void Unk_7102504260::m10() {
    sub_710107E900(ksys::tera::Terrain::instance()->sub_710114DEE0(), false);
}

static_assert(offsetof(ksys::tera::Terrain, mTerrainArena) == 0x2e0);
static_assert(offsetof(ksys::tera::Terrain, mSteraArena) == 0x2e8);
static_assert(offsetof(ksys::tera::Terrain::Unk4ae0, _f98) == 0xf98);
