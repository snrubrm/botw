#include "Game/Actor/aiUnk_71025ba778.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>

// The class's own TU (destructor 0x7100f72b94, factory 0x7100f72bf8 and the functions after it).

Unk_7100F72BF8::~Unk_7100F72BF8() {
    _8.freeBuffer();
}

void Unk_7100F72BF8::sub_7100F72FF4() {
    sead::Matrix34f cumulative = sead::Matrix34f::ident;
    for (s32 i = 0; i < _8.size(); ++i) {
        auto& entry = _8[i];
        sead::Matrix34f matrix;
        sead::Vector3f scale;
        const auto& key = entry._18.getKey();
        _0->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &matrix, &scale, key.bone_index);
        cumulative *= matrix;
        entry._50 = matrix;
        entry._80 = cumulative;
    }
}

// NON_MATCHING: container bounds-check scheduling differs.
void Unk_7100F72BF8::sub_7100F73114(s32 index) {
    sead::Matrix34f cumulative = index < 1 ? sead::Matrix34f::ident : _8[index - 1]._80;
    for (s32 i = index; i < _8.size(); ++i) {
        auto& entry = _8[i];
        cumulative *= entry._50;
        entry._80 = cumulative;
    }
}

// NON_MATCHING: matrix multiply temporaries and buffer reloads differ.
void Unk_7100F72BF8::sub_7100F731F8(s32 index, const sead::Matrix34f& matrix,
                                   bool update_cumulative, bool propagate) {
    _8[index]._50 = matrix;
    if (update_cumulative) {
        const auto& parent = index < 1 ? sead::Matrix34f::ident : _8[index - 1]._80;
        _8[index]._80.setMul(parent, matrix);
        if (propagate) {
            sead::Matrix34f cumulative = index < 0 ? sead::Matrix34f::ident : _8[index]._80;
            for (s32 i = index + 1; i < _8.size(); ++i) {
                auto& entry = _8[i];
                cumulative *= entry._50;
                entry._80 = cumulative;
            }
        }
    }
    const auto& entry = _8[index];
    _0->setBoneLocalMatrix(entry._18.getKey(), entry._50, sead::Vector3f::ones);
}
