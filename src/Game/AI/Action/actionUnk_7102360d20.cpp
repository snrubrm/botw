#include "Game/AI/Action/actionUnk_7102360d20.h"

// NON_MATCHING: lib/sead's AnyDelegateR<R>::UnbindDummy has an `s32 mUnk = 1` member that the
// original dummy (vtable 0x7102360dd8) doesn't have -> extra store to +0x40
Unk_7102360d20::Unk_7102360d20(ksys::act::ai::ActionBase* owner) : Unk_71023c8678(owner) {}

// NON_MATCHING: same extra UnbindDummy::mUnk store. The original unbinds through a pointer to the
// delegate (x20 = &_38 for both the isNoDummy call and the vptr store), which suggests this reset
// lives in a sead AnyDelegate member (destructor/unbind) that lib/sead doesn't have.
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
