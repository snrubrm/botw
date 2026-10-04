#include "Game/AI/aiUnk_71006F3CC4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"

Unk_7102450038::Unk_7102450038(ksys::act::ai::ActionBase* owner) : mOwner(owner) {}

Unk_7102450038::~Unk_7102450038() {}

void Unk_7102450038::sub_71006F3DE8() {
    _18 = 0;
    _1c = -100.0f;
}

void Unk_7102450038::sub_71006F3DF4() {}

void Unk_7102450038::sub_71006F3DF8() {
    mOwner->getStaticParam(&_8, "FlyHeightMin");
}

// NON_MATCHING: the original sinks the store of `_18` of both paths into one store at the end (and compares
// `_18 > 0` with `cmp` / `b.le`; ours decrements first)
void Unk_7102450038::sub_71006F3CEC(f32 a1) {
    if (!(*_8 > 0.0f))
        return;

    auto* actor = mOwner->getActor();
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (_18 > 0) {
        _18 = _18 - 1;
    } else {
        sead::Vector3f to = pos;
        to.y = pos.y - (a1 * 4 + *_8);
        sead::Vector3f hit;
        const f32 height = sub_710072E500(pos, to, &hit, nullptr, nullptr, 0.0f) ? hit.y + *_8 : -100.0f;
        _18 = 4;
        _1c = height;
        if (mOwner->getActor()->sub_71011DB30C())
            _18 = _18 * 10;
    }
}
