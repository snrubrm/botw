#include "KingSystem/Terrain/teraSystem.h"
#include <container/seadSafeArray.h>

namespace ksys::tera {

// NON_MATCHING: the original reads _29 and _2780 before the two stores and _28 after them.
void Scene::sub_71011001D4(int level, int type) {
    _2940 = level;
    _2941 = type;
    const u32 max = _0[0]._29 + _2780 + _0[0]._28;
    if (_2941 > max)
        _2941 = max;
    if (_2940 > _2941)
        _2940 = _2941;
    _2998 |= 4;
}

void Scene::sub_7101100234(bool a, bool b) {
    _2998 = a ? _2998 | 8 : _2998 & ~8u;
    _2998 = b ? _2998 | 0x10 : _2998 & ~0x10u;
}

void Scene::sub_7101100260(s32 a, s32 b, s32 c, s32 d) {
    _0[0]._1c = a;
    _0[2]._1c = b;
    _0[3]._1c = c;
    _0[4]._1c = d;
    _0[5]._1c = a;
    _0[6]._1c = b;
    _0[7]._1c = c;
    _0[8]._1c = 0xfff0;
}

void Scene::sub_7101101A10(void* a, void* b, void* c, void* d, void* e) {
    _2910[0] = a;
    _2910[1] = b;
    _2910[2] = c;
    _2910[4] = d;
    _2910[3] = e;
}

void Scene::sub_7101101A7C(void* a, void* b) {
    _2920[0] = a;
    _2920[1] = b;
}

void Scene::sub_7101101AA0(void* a, void* b, void* c) {
    _2930[0] = a;
    _2930[2] = b;
    _2930[1] = c;
}

void Scene::sub_7101101914(const sead::SafeArray<s32, 19>& levels) {
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

    sub_7101101914(levels);
}

}  // namespace ksys::tera
