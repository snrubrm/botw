#include "Game/Actor/actDragon.h"

#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <math/seadMatrixCalcCommon.h>
#include <math/seadVector.h>

namespace uking::act {

namespace {
// Inline-only in the original: the same twelve isNan tests appear in sub_71006FB3FC and sub_71006FC348.
bool matrixHasNan(const sead::Matrix34f& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (sead::Mathf::isNan(m.m[i][j]))
                return true;
        }
    }
    return false;
}
}  // namespace

void Dragon::Unk_710000b710::sub_71006FC340(f32 value) {
    _890 = value;
}

void Dragon::Unk_710000b710::sub_71006FB3FC(const sead::Matrix34f& matrix) {
    _20 = matrix;
    if (matrixHasNan(_20))
        _20.makeIdentity();
}

// Stores the transform and rebuilds _84 as it times the front bone's local matrix, with the
// translation dropped while the blend is running.
void Dragon::Unk_710000b710::sub_71006FC348(const sead::Matrix34f& matrix) {
    _20 = matrix;
    if (matrixHasNan(_20))
        _20.makeIdentity();

    sead::Matrix34f base = _b8.handle._9c;
    if (_8b8 >= 1.0f || (_930 & 0x40))
        base.setTranslation(sead::Vector3f::zero);
    _84.setMul(_20, base);
}

void Dragon::Unk_710000b710::sub_71006FB7F8() {
    if (!(_930 & 4))
        return;
    if (_930 & 8)
        sub_71006FB8A8();
    _850.freeBuffer();
    _8.freeBuffer();
    _930 &= ~4;
}

void Dragon::Unk_710000b710::sub_71006FB8A8() {
    if ((_930 & 0xc) != 0xc)
        return;
    mActor->sub_71011DA868(&_5d0.handle);
    mActor->sub_71011DA868(&_338.handle);
    mActor->sub_71011DA868(&_b8.handle);
    for (s32 i = 0, n = _850.size(); i < n; ++i) {
        auto& part = _850[i];
        if (part._170.isValid() && !part._170.getName().isEmpty())
            mActor->sub_71011DA868(&part.handle);
    }
    _930 &= ~8;
}

// NON_MATCHING: the bit 3 test uses the flags before bit 0 was cleared (register choice only).
void Dragon::Unk_710000b710::sub_71006FBAD4() {
    _930 &= ~1;
    _860.setTranslation(sead::Vector3f::zero);
    if (!(_930 & 0x800)) {
        if (_930 & 8)
            sub_71006FB8A8();
        sub_71006FABC8();
    }
    if (!(_930 & 0x20))
        sub_71006FB51C();
    if (!(_930 & 0x10))
        _8.clear();
    if (!(_930 & 0x80))
        sub_71006FBB64();
}

void Dragon::Unk_710000b710::sub_71006FD830(f32 start_frame, f32 end_frame) {
    if (start_frame < 0.0f) {
        if (_930 & 0x100) {
            _8a4 = -1.0f;
            _8a8 = -1.0f;
            _8ac = 0.0f;
            _930 &= ~0x100;
        }
        return;
    }
    _8ac = 1.0f;
    _5c0 = _338.handle._9c.m[2][3];
    _5bc = _338.handle._9c.m[1][3];
    _5cc = _84.m[2][3];
    _5c4 = _84.m[0][3];
    _5b8 = _338.handle._9c.m[0][3];
    _5c8 = _84.m[1][3];
    _8a4 = start_frame;
    _8a8 = end_frame;
    _930 |= 0x100;
}

// NON_MATCHING: address generation while comparing the matrix elements.
void sub_71006FAA34(sead::RingBuffer<sead::Matrix34f>& history, const sead::Matrix34f& matrix) {
    if (history.size() > 0 && history.back() == matrix)
        return;
    if (history.size() >= history.capacity())
        history.popFront();
    history.pushBack(matrix);
}

// NON_MATCHING: matrix snapshots and vector stores use different copy scheduling.
void Dragon::Unk_710000b710::sub_71006FB998() {
    for (s32 i = 0; i < _850.size(); ++i) {
        auto& part = _850[i];
        part._1a8 = part._208;
        part._1d8 = part._208;
    }
    sub_71006FC6C8(_b8._1a8);
    for (s32 i = 0; i < _850.size(); ++i) {
        auto& part = _850[i];
        part._268 = part._238;
        part._250 = part._238;
        part._25c = sead::Vector3f::zero;
        part._274 = part._244;
    }
}

// NON_MATCHING: history loop and vector temporaries produce different spills and block layout.
void Dragon::Unk_710000b710::sub_71006FC6C8(const sead::Matrix34f& matrix) {
    const s32 count = _850.size();
    if (count <= 0)
        return;
    const f32 distance_squared = _890 * _890;
    s32 history_index = 1;
    sead::Vector3f previous = matrix.getTranslation();
    for (s32 i = 0; i < count; ++i) {
        bool found = false;
        const s32 history_size = _8.size();
        // Retain the last examined history sample for the next segment.
        for (s32 candidate_index = history_index; candidate_index < history_size; ++candidate_index) {
            history_index = candidate_index;
            const sead::Matrix34f candidate = *_8.unsafeGet(history_size - 1 - candidate_index);
            const auto position = candidate.getTranslation();
            const f32 length_squared = (previous - position).squaredLength();
            if (distance_squared < length_squared) {
                const f32 distance = sead::Mathf::sqrt(length_squared);
                const f32 ratio = (1.0f - distance / _890) + 1.0f;
                auto direction = (previous + (position - previous) * ratio) - previous;
                direction.normalize();
                _850[i]._238 = previous + direction * _890;
                _850[i]._244 = candidate.getBase(1);
                found = true;
                break;
            }
        }
        if (!found) {
            if (i == 0) {
                _850[i]._238 = matrix.getTranslation() + matrix.getBase(0) * _890;
                _850[i]._244 = matrix.getBase(1);
            } else {
                const auto before = i > 1 ? _850[i - 2]._238 : matrix.getTranslation();
                auto direction = _850[i - 1]._238 - before;
                direction.normalize();
                _850[i]._238 = _850[i - 1]._238 + direction * _890;
                _850[i]._244 = _850[i - 1]._244;
            }
            _930 &= ~2;
        }
        previous = _850[i]._238;
    }
}

// NON_MATCHING: zero-translation comparison and bone-name checks use different temporaries.
void Dragon::Unk_710000b710::sub_71006FABC8() {
    if ((_930 & 8) || !mActor->getModel())
        return;
    for (s32 i = _850.size() - 1; i >= 0; --i) {
        auto& part = _850[i];
        if (part._170.isValid() && !part._170.getName().isEmpty())
            mActor->boneHandleStuff(&part.handle, false);
        else
            part._1a8.makeIdentity();
    }
    if (_5d0._170.isValid())
        mActor->boneHandleStuff(&_5d0.handle, false);
    if (_338._170.isValid())
        mActor->boneHandleStuff(&_338.handle, false);
    if (_b8._170.isValid())
        mActor->boneHandleStuff(&_b8.handle, false);
    if (_20.getTranslation() == sead::Vector3f::zero)
        _20 = mActor->getMtx();
    _930 |= 8;
}

void Dragon::Unk_710000b710::sub_71006FB51C() {
    auto* model = mActor->getModel();
    const s32 count = _850.size();
    auto base = _b8.handle._9c;
    if (_8b8 >= 1.0f || (_930 & 0x40))
        base.setTranslation(sead::Vector3f::zero);
    _b8._1a8.setMul(_20, base);
    _50 = _b8._1a8;
    _338._1a8.setMul(_50, _338.handle._9c);
    for (s32 i = 0; i < count; ++i) {
        auto& part = _850[i];
        part._1a8.makeIdentity();
        part._208.makeIdentity();
        part._1d8.makeIdentity();
        if (model && part._170.isValid())
            model->getBoneWorldMatrix(part._170.getKey(), &part._208);
    }
    sub_71006FB998();
}

// NON_MATCHING: bone matrices are written directly to the part fields instead of copied from temporaries.
void Dragon::Unk_710000b710::sub_71006FBB64() {
    auto* model = mActor->getModel();
    if (!model)
        return;
    const s32 count = _850.size();
    for (s32 i = 0; i < count; ++i) {
        auto& part = _850[i];
        if (part._170.isValid() && !part._170.getName().isEmpty()) {
            const auto& key = part._170.getKey();
            model->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
                &part.handle._9c, &part.handle._cc, key.bone_index);
        }
    }
    if (_5d0._170.isValid()) {
        const auto& key = _5d0._170.getKey();
        model->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &_5d0.handle._9c, &_5d0.handle._cc, key.bone_index);
    }
    if (_338._170.isValid()) {
        const auto& key = _338._170.getKey();
        model->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &_338.handle._9c, &_338.handle._cc, key.bone_index);
    }
    if (_b8._170.isValid()) {
        const auto& key = _b8._170.getKey();
        model->getUnits()(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
            &_b8.handle._9c, &_b8.handle._cc, key.bone_index);
    }
    if (_20.getTranslation() == sead::Vector3f::zero)
        _20 = mActor->getMtx();
    auto base = _b8.handle._9c;
    if (_8b8 >= 1.0f || (_930 & 0x40))
        base.setTranslation(sead::Vector3f::zero);
    _84.setMul(_20, base);
    _b8._1a8 = _84;
    _338._1a8.setMul(_84, _338.handle._9c);
    _5d0._1a8.setMul(_84, _5d0.handle._9c);
    _894 = 1.0f;
    _898 = 0.0f;
    auto previous = _5d0._1a8;
    for (s32 i = 0; i < count; ++i) {
        auto& part = _850[i];
        part._208.setMul(previous, part.handle._9c);
        previous = part._208;
    }
    sub_71006FB998();
    for (s32 i = 0; i < count; ++i)
        _850[i]._1a8 = _850[i]._208;
    _b8.handle._20 = _b8._1a8;
    _338.handle._20 = _338._1a8;
    _5d0.handle._20 = _5d0._1a8;
    for (s32 i = 0; i < _850.size(); ++i)
        _850[i].handle._20 = _850[i]._1a8;
}

}  // namespace uking::act
