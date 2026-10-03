#include "Game/AI/Action/actionUnk_7102451320.h"

Unk_7102451320::Unk_7102451320() = default;

Unk_7102451320::~Unk_7102451320() = default;

bool Unk_7102451320::m3(gsys::Model* model, bool sorted) {
    _60.search(model, _50);
    if (_60.isValid()) {
        _20 = false;
        return true;
    }
    return false;
}

void Unk_7102451320::setName(const sead::SafeString& name) {
    if (_8)
        return;
    _50 = name;
    _60.getKey().reset();
}

void Unk_7102451320::sub_7100743414(s32 a1, bool a2, s32 a3) {}
