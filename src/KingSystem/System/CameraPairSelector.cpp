#include "KingSystem/System/CameraS1.h"

namespace ksys {

Unk_710131dfb8::Unk_710131dfb8(s32 id) : _8(id) {}

Unk_710131dfb8::~Unk_710131dfb8() {
    _10[0]->sub_7100D8B3E8(_8);
    _10[1]->sub_7100D8B3E8(_8);
}

s32 Unk_710131dfb8::sub_710131E060() const {
    return _c;
}

void Unk_710131dfb8::sub_710131E068(s32 index, Unk_71024dd110* camera) {
    if (_10[index])
        _10[index]->sub_7100D8B3E8(_8);
    _10[index] = camera;
    if (camera)
        camera->sub_7100D8B380(_8, index);
}

void Unk_710131dfb8::sub_710131E0D8(s32 index) {
    if (_10[index])
        _10[index]->sub_7100D8B3E8(_8);
    _10[index] = nullptr;
}

void Unk_710131dfb8::sub_710131E118(s32 index) {
    if (_c != -1 && _10[_c])
        _10[_c]->sub_7100D8B364(false);
    _c = index;
    if (_c != -1 && _10[_c])
        _10[_c]->sub_7100D8B364(true);
}

Unk_71024dd110* Unk_710131dfb8::getLookAtCamera() const {
    if (_c == -1)
        return nullptr;
    return _10[_c];
}

}  // namespace ksys
