#include "KingSystem/Terrain/teraEditor.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelScene.h>
#include <gsys/gsysModelUnit.h>
#include "Game/gameGraphics.h"
#include "Game/gameStageStateMaybe.h"
#include "KingSystem/Terrain/teraSystem.h"

// 0x710107e7cc
Unk_7102504260::~Unk_7102504260() = default;

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

bool Unk_7102504260::sub_710107EC48() const {
    return false;
}

// NON_MATCHING: the mode-word copy into the SeadController loads the destination pointer before the source in
// the original (a class-type assignment there); ours is `_28->_1ec = _40` on a plain u32, so the two loads swap.
void Unk_7102504260::m6() {
    // Discarded in the original (the tick is measured but not used).
    nn::os::GetSystemTick();
    if (uking::StageStateMaybe::isActiveNaviMaybe(this)) {
        _28->_1ec = _40;
        auto* terrain = ksys::tera::Terrain::instance();
        const sead::BitFlag32 flags = terrain->_a50->_18;
        if (flags.isOnBit(8) == terrain->_30.isOnBit(3)) {
            if (!flags.isOnBit(8))
                terrain->_30.set(8);
            else
                terrain->_30.reset(8);
        }
        auto* scene = Graphics::instance()->getUnk_aa8();
        if (scene)
            terrain->_a50->_1b0 = scene->_7f8;
    }
    // The first model scene's rain intensity.
    m20(Graphics::instance()->mModelScenes[0]->_5da0);
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
