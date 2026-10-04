#include "KingSystem/ActorSystem/actChemical.h"

namespace ksys::act {

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

bool Chemical::sub_7100D913A8() const {
    return !(mMaterial->attribute.ref() & 0x2000);
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
