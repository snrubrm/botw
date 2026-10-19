#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <container/seadSafeArray.h>

namespace ksys::tera {

// NON_MATCHING: the original reads _29 and _2780 before the two stores and _28 after them.
bool ApertureMapsCollector::allocateImage(sead::Heap* heap) {
    if (_2998 & 2) {
        if (auto* debug = Terrain::instance()->_a50) {
            auto entry =
                debug->_70.log("[ksys::tera::ApertureMapsCollector::allocateImage] ２重確保");
            if (entry.buffer)
                entry.buffer->setDisplayTime(10.0f);
        }
        return false;
    }

    heap->getFreeSize();
    for (Unk_71010FEDBC& record : _0) {
        record._20.sub_71010F919C(heap);
        heap->getFreeSize();
    }
    _2998 |= 0xff02;
    return true;
}

bool ApertureMapsCollector::releaseImage(bool free_memory) {
    if (!(_2998 & 2)) {
        if (auto* debug = Terrain::instance()->_a50) {
            auto entry = debug->_70.log("[ksys::tera::ApertureMapsCollector::releaseImage] ２重解放");
            if (entry.buffer)
                entry.buffer->setDisplayTime(10.0f);
        }
        return false;
    }

    _2998 &= ~2;
    for (Unk_71010FEDBC& record : _0)
        record._20.sub_71010F94F4(free_memory);
    return true;
}

void ApertureMapsCollector::sub_71011001D4(int level, int type) {
    _2940 = level;
    _2941 = type;
    const u32 max = _0[0]._20._9 + _2780 + _0[0]._20._8;
    if (_2941 > max)
        _2941 = max;
    if (_2940 > _2941)
        _2940 = _2941;
    _2998 |= 4;
}

void ApertureMapsCollector::sub_7101100234(bool a, bool b) {
    _2998 = a ? _2998 | 8 : _2998 & ~8u;
    _2998 = b ? _2998 | 0x10 : _2998 & ~0x10u;
}

void ApertureMapsCollector::sub_71010FFE70(s32 a, s32 b) {
    if (_2780 == a && _2784 == b)
        return;
    _2780 = a;
    _2784 = b;
    _2948->sub_710112727C(&_0[0], &_0[1], &_0[2], &_0[3], a, b);
    _2998 |= 0xff00;
}

void ApertureMapsCollector::sub_7101100260(s32 a, s32 b, s32 c, s32 d) {
    _0[0]._1c = a;
    _0[2]._1c = b;
    _0[3]._1c = c;
    _0[4]._1c = d;
    _0[5]._1c = a;
    _0[6]._1c = b;
    _0[7]._1c = c;
    _0[8]._1c = 0xfff0;
}

void ApertureMapsCollector::sub_71011016F4() {
    _2948->sub_7101128BA0(_2942);
}

void ApertureMapsCollector::sub_7101101A10(void* a, void* b, void* c, void* d, void* e) {
    _2910[0] = a;
    _2910[1] = b;
    _2910[2] = c;
    _2910[4] = d;
    _2910[3] = e;
}

void ApertureMapsCollector::sub_7101101A7C(void* a, void* b) {
    _2920[0] = a;
    _2920[1] = b;
}

void ApertureMapsCollector::sub_7101101AA0(void* a, void* b, void* c) {
    _2930[0] = a;
    _2930[2] = b;
    _2930[1] = c;
}

void ApertureMapsCollector::sub_7101101578(System* system, u32 flags) {
    const Unk_7101101DFC entries[] = {
        {sUnk_7101EC54AC, 0x10000, 0x100000},
        {sUnk_7101EC54B4, 0x20000, 0x200000},
        {sUnk_7101EC54B8, 0x40000, 0x400000},
        {sUnk_7101EC54BC, 0x80000, 0x800000},
    };
    sead::ScopedLock<sead::CriticalSection> lock(&_2950);
    for (s32 i = 0; i < 4; ++i) {
        const u32 flag_a = 0x10000 << i;
        const u32 flag_b = 0x100000 << i;
        if (flags & (flag_a | flag_b))
            sub_7101101DFC(system, entries[i], 0, flags & flag_a, flags & flag_b);
    }
}

// NON_MATCHING: the original tail-calls sub_7101100330 (ours calls it after the inlined request table).
void ApertureMapsCollector::sub_71011021E4(System* system, const sead::Vector3f* arg, bool request_all) {
    if (request_all)
        sub_7101101578(system, 0xff0000);
    sub_7101100330(system, arg, true, true);
}

void ApertureMapsCollector::sub_710110234C(System* system) {
    sub_71011021E4(system, &_276c, true);
}

void ApertureMapsCollector::sub_7101101914(const sead::SafeArray<s32, 19>& levels) {
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
void ApertureMapsCollector::sub_7101101964() {
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

// NON_MATCHING: register allocation in the inlined area loops.
bool ApertureMapsCollector::sub_71011020C0(u32 level) const {
    for (s32 i = 5; i < 9; ++i) {
        if (!_0[i].areAreasReadyMaybe(level))
            return false;
    }
    return true;
}

agl::TextureSampler* Unk_7101102B58::sub_7101102B58(u32 frame, u32 layer) {
    if (!(_0 & 8)) {
        if (_430 != 0 || _432 != 0) {
            _2c0.applyTextureData(_18[0]);
            _430 = 0;
            _432 = 0;
        }
        return &_2c0;
    }

    agl::TextureData& texture = _18[layer];
    const u32 offset = _38[layer];
    const u32 frame_size = (_38[layer + 1] - offset) / _8;
    texture.setImagePtr(agl::GPUMemAddrBase(_20, offset + frame_size * frame), 0);
    if (_430 != frame || _432 != layer) {
        _2c0.applyTextureData(_18[layer]);
        _430 = u8(frame);
        _432 = u8(layer);
    }
    return &_2c0;
}

}  // namespace ksys::tera
