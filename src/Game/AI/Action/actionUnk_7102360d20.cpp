#include "Game/AI/Action/actionUnk_7102360d20.h"

Unk_7102360d20::Unk_7102360d20(ksys::act::ai::ActionBase* owner) : Unk_71023c8678(owner) {}

Unk_7102360d20::~Unk_7102360d20() {
    if (_38)
        _38 = sead::AnyDelegateR<sead::Vector3f>::UnbindDummy();
}

void Unk_7102360d20::m13(sead::Vector3f* pos) {
    if (_38)
        *pos = _38();
    else
        Unk_71023c8678::m13(pos);
}
