#include "KingSystem/Terrain/teraSystem.h"
#include <math/seadMathCalcCommon.h>

namespace ksys::tera {

void System::sub_7101112A74() {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i)
        mScenes[i].scene->sub_7101101964();
    _1338 &= ~8u;
}

void System::sub_7101112AF0(s32 a, s32 b) {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i)
        mScenes[i].scene->sub_71010FFE70(a, b);
}

void System::sub_7101112B80(s32 a, s32 b, s32 c, s32 d) {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i)
        mScenes[i].scene->sub_7101100260(a, b, c, d);
}

void System::sub_7101112C30(const sead::Vector3f& vec) {
    const u32 count = mScenes.size();
    for (u32 i = 0; i < count; ++i) {
        Scene* scene = mScenes[i].scene;
        scene->_2760 = vec;
        scene->_2998 |= 4;
    }
}

s32 System::sub_71011188E4() const {
    const Scene* scene = mScenes(0).scene;
    return sead::Mathi::max(scene->_2946 - 1 - scene->_2780, 0);
}

void* System::sub_710111F4F0() {
    return &mScenes(0).scene->_0[5];
}

Unk_710111F504* System::sub_710111F504() {
    return &mScenes(0).scene->_0[8];
}

void System::sub_710111F518(int level, int type) {
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].scene->sub_71011001D4(level, type);
}

bool System::sub_710111F618(s32 index) {
    return mScenes[index].scene->_2998 >> 3 & 1;
}

void System::sub_710111F644(void* value) {
    for (s32 i = 0; i < mScenes.size(); ++i)
        mScenes[i].scene->_2948->_afc0 = value;
}

// NON_MATCHING: the original keeps the comparison result in a register before the binary search step
// and checks the found index after the search.
System::Entry* System::sub_7101115080(u32 id) const {
    if (_1018.size() == 0) {
        for (s32 i = 0; i < _fa8.size(); ++i) {
            if (_fa8.getBufferPtr()[i]->mId == id)
                return _fa8.getBufferPtr()[i];
        }
        return nullptr;
    }

    const s32 idx = _1018.binarySearchC([id](const Entry* entry) {
        if (entry->mId < id)
            return -1;
        return entry->mId > id ? 1 : 0;
    });
    if (idx >= 0 && _1018.isIndexValid(idx))
        return _1018.getBufferPtr()[idx];
    return nullptr;
}

}  // namespace ksys::tera
