#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

bool ElementParams::sub_7101302930(void* a1) {
    return true;
}

bool ElementParams::sub_7101302938(void* a1) {
    return true;
}

bool ElementParams::sub_7101302940(void* a1) {
    return true;
}

bool ElementParams::sub_7101302948(void* a1) {
    return true;
}

void ElementParams::sub_7101302950(f32 value) {
    if (_1c >= 0)
        _1c = _14 * value;
}

f32 ElementParams::sub_710130296C(bool a) const {
    f32 end;
    if (a && _1c >= 0)
        end = _1c;
    else
        end = _14;
    return end - _10;
}

f32 ElementParams::sub_710130298C(bool a) const {
    f32 end;
    if (a && _1c >= 0)
        end = _1c;
    else
        end = _14;
    const f32 length = end - _10;
    if (length > 0) {
        const f32* current;
        if (a && _1c >= 0)
            current = &_18;
        else
            current = &_4;
        return (*current - _10) / length;
    }
    return 0;
}

bool ElementParams::sub_7101302834() const {
    if (!(_0 & 2)) {
        if (_4 >= _14)
            return true;
    }
    const f32 end = _1c;
    if (end >= 0)
        return _18 >= end;
    return false;
}

bool ElementParams::sub_7101302878(f32 value) const {
    const f32 a = _4;
    const f32 b = _8;
    if (a != b) {
        if (b < a) {
            if (a >= value && b < value)
                return true;
        } else {
            if (a >= value || b < value)
                return true;
        }
    }
    return false;
}

f32 ElementParams::sub_71013029E4(bool a, f32 t) const {
    if (a && _1c >= 0)
        return (1 - t) * _10 + _1c * t;
    return _10 + (_14 - _10) * t;
}

void ElementParams::sub_7101302A1C(f32 position) {
    const f32 length = _14;
    _18 = position;
    _4 = position;
    if (length <= position) {
        f32 result = length;
        if (_0 & 2) {
            if (length > 0) {
                f32 wrapped = length;
                if (!(length + length > position))
                    wrapped = length * f32(s32(position / length));
                result = position - wrapped;
            } else {
                result = 0;
            }
        }
        _4 = result;
    }
}

// NON_MATCHING: store scheduling (the original keeps an intermediate store of the flags and writes
// _14 / _c / _1c after the flag computation; same operations)
bool ElementParams::sub_71013028BC(bool loop, bool a2, f32 position, f32 rate, f32 start,
                                   f32 length, f32 count) {
    _4 = position;
    _18 = position;
    _8 = position - rate;
    _10 = start;
    if (loop)
        _0 |= 2;
    else
        _0 &= ~2u;
    if (a2)
        _0 |= 4;
    else
        _0 &= ~4u;
    _14 = length;
    _c = rate;
    _1c = count > 0 && loop ? length * count : -1.0f;
    _0 = (_0 & ~0x18u) | 0x10;
    return true;
}

}  // namespace ksys::as
