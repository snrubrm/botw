#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace uking {

// Placeholder declaration (name from the CSV: SaveSystem::createInstance 0x710090ee60, ctor
// 0x710090eee8, calc 0x7100910e5c, init, invokedAutoSave, isFinishedSavingMaybe, ...; instance
// pointer at 0x71025d2028; namespace is a guess). The game-level save controller that drives
// ksys::SaveMgr. A polymorphic sead singleton; only what the AI actions use is declared.
// TODO: incomplete.
class SaveSystem {
    SEAD_SINGLETON_DISPOSER(SaveSystem)
    SaveSystem();
    virtual ~SaveSystem();

public:
    // 0x7100915764 (CSV SaveSystem::isFinishedSavingMaybe): ksys::SaveMgr is idle (+0x38 == 0) and
    // this->_3c == 0.
    bool isFinishedSavingMaybe() const;

    u8 _28[0x1a50 - 0x28];
    // bit 2 (4): auto saving paused (cleared by DisableAutoSavePausing); bit 11 (0x800) is tested by calc
    u16 _1a50;
};

}  // namespace uking
