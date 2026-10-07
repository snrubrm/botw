#include "KingSystem/ActorSystem/actChemical.h"
#include <math/seadMathCalcCommon.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actActorChemicals.h"

namespace ksys::act {

void Chemical::notifyWatch_() {
    if (sub_7100D9CB54(_60, this)) {
        if (sUnk_7102600e50->_84 & 1) {
            sead::ThreadMgr::instance()->getCurrentThread();
            if (static_cast<const void*>(sUnk_7102600e50) != this)
                sUnk_7102600e50->_85 = 100;
        }
    }
}

void Chemical::sub_7100D907A8() {
    notifyWatch_();
    if (_1c8) {
        sub_7100D8CD24(_1c8, true);
        _1c8 = nullptr;
    }
    if (_1d0) {
        sub_7100D8CD24(_1d0, true);
        _1d0 = nullptr;
    }
    if (_18)
        _18->m34();
    _c &= ~0x100000;
}

void Chemical::sub_7100D909A4() {
    notifyWatch_();
    if (mMaterial->attribute.ref() & 0x10) {
        _c1 = 4;
        _c |= 4;
        const f32 ignition_point = mMaterial->ignition_point.ref();
        _17c = ignition_point;
        _178 = ignition_point;
        _174 = ignition_point;
        _184 = 0.0f;
    }
}

// NON_MATCHING: the original loads _174 before the first store and computes the fmin after the stores to _190 / _19c /
// _198
void Chemical::sub_7100D90A40() {
    notifyWatch_();
    if (_be & 2)
        return;
    if (mMaterial->attribute.ref() & 0x400000)
        return;
    const f32 v = sead::Mathf::clampMax(_174, 0.0f);
    _c1 = 1;
    _190 = 1.0f;
    _19c = 1.0f;
    _198 = _50;
    _17c = v;
    _178 = v;
    _174 = v;
    _194 = _50;
}

// NON_MATCHING: the original loads the material pointer first, hoists the 0.5 constant and stores _178 before _17c
void Chemical::sub_7100D90B78() {
    notifyWatch_();
    if (_c0 == 2 || _c1 == 2) {
        _c1 = 0;
        sub_7100D907A8();
        _17c = _170;
        _178 = _170;
        _188 = 0.0f;
        _174 = (mMaterial->ignition_point.ref() + _170) * 0.5f;
    }
}

void Chemical::sub_7100D91978(f32 value) {
    notifyWatch_();
    if (mMaterial->attribute.ref() & 0x8) {
        if (!(_be & 4)) {
            _1b8 = value;
            _1b4 = _58 * value;
        }
    }
}

// NON_MATCHING: the original calls the owner's slot 36 and tests bit 0 of the result (no tail call; the result is a
// merged w8 phi)
bool Chemical::sub_7100D91898() const {
    if (_c3 < 30)
        return false;
    const u32 attribute = mMaterial->attribute.ref();
    if ((attribute & 0x1) && !(_be & 0x1) && (_b8 & 0x4))
        return false;
    if (_1b8 > 0.0f)
        return false;
    if (_1e8)
        return false;
    if (_c0 != 0 && (_c0 != 2 || (attribute & 0x2)))
        return false;
    return !_18 || _18->m36();
}

// NON_MATCHING: the original selects with `pl` (not `mi`) and reads _1b4 after both selects; ours picks the
// operands the other way round with a different register allocation
f32 Chemical::sub_7100D945BC(f32 rate, f32 value, f32 delta_frame) {
    if (rate <= 0.0f || value <= 0.0f)
        return 0.0f;
    const f32 step = delta_frame / 30.0f * rate;
    const f32 current = _1b8;
    const f32 ratio = current / value;
    const f32 decrease = current < value ? step * ratio : step;
    const f32 result = current < value ? ratio : 1.0f;
    _1b4 = sead::Mathf::clampMin(_1b4 - decrease, 0.0f);
    _1b8 = _1b4 != 0.0f ? _1b4 / _58 : 0.0f;
    return result;
}

void Chemical::sub_7100D90C2C(bool on) {
    notifyWatch_();
    if (on) {
        _be |= 0x1;
        if (_c0 == 2 || _c1 == 2)
            _c1 = 0;
    } else {
        _be &= ~0x1;
    }
}

void Chemical::sub_7100D90CD8(bool on) {
    notifyWatch_();
    if (on) {
        _be |= 0x2;
        if (_c0 == 1)
            _c1 = 0;
    } else {
        _be &= ~0x2;
    }
}

void Chemical::sub_7100D90D7C(bool on) {
    notifyWatch_();
    if (on) {
        _be |= 0x4;
        if (_1b4 != 0.0f)
            _1b4 = 0.0f;
        if (_1bc != 0.0f)
            _1bc = 0.0f;
        if (_1b8 != 0.0f)
            _1b8 = 0.0f;
    } else {
        _be &= ~0x4;
    }
}

void Chemical::sub_7100D90E40(bool on) {
    notifyWatch_();
    _be = on ? (_be | 0x10) : (_be & ~0x10);
}

void Chemical::sub_7100D90ED0(bool on) {
    notifyWatch_();
    _be = on ? (_be | 0x8) : (_be & ~0x8);
}

void Chemical::sub_7100D90F60(bool on) {
    notifyWatch_();
    _be = on ? (_be | 0x20) : (_be & ~0x20);
}

void Chemical::sub_7100D90FF0(bool on) {
    notifyWatch_();
    _be = on ? (_be | 0x40) : (_be & ~0x40);
}

void Chemical::sub_7100D91098(bool on) {
    const bool changed = on != ((_c >> 6) & 1);
    if (changed)
        notifyWatch_();
    _c = on ? (_c | 0x40) : (_c & ~0x40);
    if (_18)
        _18->m32(changed);
}

// NON_MATCHING: the original tests `on ^ (_c >> 7)` directly (eor + tbz) both times; ours hoists `on & 1` and
// extracts the bit with ubfx
void Chemical::sub_7100D91158(bool on) {
    if ((_c >> 7 ^ on) & 1)
        notifyWatch_();
    if ((_c >> 7 ^ on) & 1)
        _c = on ? (_c | 0x80) : (_c & ~0x80);
}

void Chemical::sub_7100D8EAB4(int value) {
    _10 = value;
}

void Chemical::sub_7100D8F194() {
    if (_8 & 0xa)
        _8 |= 0x10;
}

bool Chemical::sub_7100D91080() const {
    return _be >> 5 & 1;
}

bool Chemical::sub_7100D9108C() const {
    return _be >> 6 & 1;
}

void Chemical::sub_7100D91390(f32 value) {
    _c |= 0x100;
    _54 = value;
    _184 = value;
}

// NON_MATCHING: the original forms the addresses (`add x8, x0, #0x182`, pre-indexed `ldrb [x8, #0x1a]!`) before the loads
u8 Chemical::sub_7100D91360() const {
    if (_1c8)
        return _1c8->_1a;
    if (_c0 == 2)
        return _182;
    return 0;
}

bool Chemical::sub_7100D913A8() const {
    return !(mMaterial->attribute.ref() & 0x2000);
}

void Chemical::sub_7100D9153C(sead::Matrix34f* out) {
    if (_18)
        _18->m4(out, this);
}

bool Chemical::sub_7100D91508() const {
    if (_c & 0x1000000)
        return false;
    if (_190 > 0.0f)
        return true;
    return _18c > 0.0f;
}

// NON_MATCHING: csel operands swapped (condition polarity)
f32 Chemical::sub_7100D91958() const {
    return (mMaterial->attribute.ref() & 0x10000) ? _170 : _174;
}

f32 Chemical::sub_7100D945AC() const {
    return _1b8 * _1b4;
}

void Chemical::sub_7100D90AF4(bool on) {
    if (on)
        _bf &= 0xfe;
    else
        _bf |= 1;
    makeChmElementMaybe(false);
}

// NON_MATCHING: the original evaluates both flag tests with a conditional compare (ccmp), no early byte test
bool Chemical::sub_7100D915A8() const {
    if (_be & 8)
        return true;
    const u32 attribute = mMaterial->attribute.ref();
    if ((attribute & 0x20008) == 8 && !(_be & 4)) {
        if ((_c & 0x200) || (attribute & 0x800))
            return false;
        return mMaterial->electrical_resistivity.ref() < 1.0f;
    }
    return false;
}

}  // namespace ksys::act
