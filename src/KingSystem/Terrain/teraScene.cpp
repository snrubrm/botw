#include "KingSystem/Terrain/teraSystem.h"
#include <container/seadSafeArray.h>

namespace ksys::tera {

// NON_MATCHING: the original reads _29 and _2780 before the two stores and _28 after them.
void Scene::sub_71011001D4(int level, int type) {
    _2940 = level;
    _2941 = type;
    const u32 max = _29 + _2780 + _28;
    if (_2941 > max)
        _2941 = max;
    if (_2940 > _2941)
        _2940 = _2941;
    _2998 |= 4;
}

// NON_MATCHING: we unroll both loops and keep the levels in registers; the original keeps the 19-entry
// stack array and two loops.
void Scene::sub_7101101964() {
    const Terrain* terrain = Terrain::instance();
    sead::SafeArray<s32, 19> levels;
    for (s32 i = 0; i < levels.size(); ++i) {
        s32 level = i < terrain->_3dc ? 1 : 0;
        if (i < terrain->_3dd)
            level = 2;
        if (i < terrain->_3de)
            level = 3;
        levels[i] = level;
    }

    bool changed = false;
    for (s32 i = 0; i < levels.size(); ++i) {
        if (levels[i] != -1 && levels[i] != _278c[i]) {
            changed = true;
            _278c[i] = levels[i];
        }
    }
    if (changed)
        _2998 |= 4;
}

}  // namespace ksys::tera
