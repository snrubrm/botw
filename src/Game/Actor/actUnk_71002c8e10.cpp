#include "Game/Actor/actMotorcycleStickControl.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/VFR.h"

namespace uking::act {

Unk_71002c8e10::Unk_71002c8e10(f32 a, f32 b, bool flag) {
    const f32 first = a > 0.0f ? a : 0.008f;
    _4 = first;
    const f32 second = b > 0.0f ? b : 0.008f;
    _8 = second;
    _0 = flag ? second : -first;
}

void Unk_71002c8e10::sub_71002C8E44(bool flag) {
    if (_0 > 0.0f) {
        if (!flag) {
            _0 -= ksys::VFR::instance()->getDeltaTime();
            if (!(_0 <= 0.0f))
                return;
        }
    } else if (flag) {
        _0 = ksys::VFR::instance()->getDeltaTime() + _0;
        if (!(_0 >= 0.0f))
            return;
    }
    _0 = flag ? _8 : -_4;
}

f32 Unk_71002c8b5c::sub_71002C8B5C(f32 target) {
    const f32 cur = _8;
    _8 = sead::Mathf::clamp(target, cur - mRates.y * ksys::VFR::instance()->getDeltaFrame(),
                            _8 + mRates.x * ksys::VFR::instance()->getDeltaFrame());
    return _8;
}

void Unk_71002c8c58::sub_71002C8C58() {
    if (mFader.getValue() == mFader.getNextValue()) {
        if (mFader.getValue() > 0.5f)
            mFader.moveTo(0.0f, _30);
        else
            mFader.moveTo(1.0f, _2c);
    }
    mFader.calc();
}

void Unk_71002c8c58::sub_71002C8CAC(f32 a, f32 b, f32 c) {
    mFader.setValueImmediate(0.0f);
    _28 = a;
    _2c = b;
    _30 = c;
}

void Unk_71002c8cf8::sub_71002C8CF8() {
    if (mFader.getValue() == mFader.getNextValue()) {
        if (mFader.getValue() > 0.5f) {
            mFader.moveTo(0.0f, _44 == _40 ? _3c : _30);
        } else {
            mFader.moveTo(1.0f, _44 == _40 ? _38 : _2c);
            _44 = _44 >= _40 ? 0 : _44 + 1;
        }
    }
    mFader.calc();
}

void Unk_71002c8cf8::sub_71002C8D88(f32 a, f32 b, f32 c) {
    mFader.setValueImmediate(0.0f);
    _28 = a;
    _2c = b;
    _30 = c;
}

void Unk_71002c8cf8::sub_71002C8DD4(f32 a, f32 b, f32 c, f32 count) {
    _40 = s32(count);
    _44 = 0;
    _34 = a;
    _38 = b;
    _3c = c;
}

f32 Unk_71002c8cf8::sub_71002C8DEC() const {
    return mFader.getValue() * (_44 == _40 ? _34 : _28);
}

}  // namespace uking::act
