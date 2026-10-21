#include "KingSystem/Sound/sndUnk_7102502138.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::snd {

// NON_MATCHING (createInstance, which inlines this constructor): the original keeps the dead `mMaxNum = 0` store of the
// FixedObjList (`str wzr, [x19, #0x98]` before the node links) and schedules the first list stores differently.
Unk_7102502138::Unk_7102502138() = default;

Unk_7102502138::Unk70Entry::Unk70Entry()
    : _0(1.0f), _4(0), _8(1.0f), _c(0), _10(0.4f), _60(false) {}

Unk_7102502138::Unk70Entry* Unk_7102502138::sub_710103B488() {
    return mList.emplaceBack();
}

const sead::SafeString* Unk_7102502138::sub_710103B4F8() {
    for (auto& entry : mList) {
        if (entry._60)
            return &entry._18;
    }
    return nullptr;
}

SEAD_SINGLETON_DISPOSER_IMPL(Unk_7102502138)

Unk_7102502138::~Unk_7102502138() {
    if (_68) {
        delete _68;
        _68 = nullptr;
    }
    mInitialized = false;
}

void Unk_7102502138::init(sead::Heap* heap) {
    if (!mInitialized) {
        _68 = new (heap, 8) Unk68;
        _68->init(heap);
        mInitialized = true;
    }
}

// NON_MATCHING: the original walks the list by node (current node, next node and the object derived from it stay live:
// one more callee-saved register than ours).
void Unk_7102502138::sub_710103B234() {
    if (_68)
        _68->sub_710104BEF0();

    act::ActorLinkConstDataAccess accessor;
    act::ActorSystem::instance()->getPlayer(&accessor);
    auto* xlink = accessor.sub_7100D0F214();
    if (!xlink)
        return;
    auto* user = xlink->_50;
    if (!user)
        return;

    auto lock = sead::makeScopedLock(mCS);
    s32 count = 0;
    for (auto it = mList.begin(), next = it; it != mList.end(); it = next) {
        ++next;
        if (it->sub_710103B5C8(user, count < 2)) {
            ++count;
            mList.erase(&*it);
        }
    }
}

void Unk_7102502138::sub_710103B33C(f32 value) {
    auto lock = sead::makeScopedLock(mCS);
    if (_68)
        _68->sub_710104DF54(value);
}

void Unk_7102502138::sub_710103B384(f32 value) {
    auto lock = sead::makeScopedLock(mCS);
    if (_68)
        _68->sub_710104E004(value);
}

void Unk_7102502138::sub_710103B3CC(const Unk_710251b170::Strength* strength) {
    auto lock = sead::makeScopedLock(mCS);
    if (_68)
        _68->sub_710104E0A0(strength);
}

void Unk_7102502138::sub_710103B41C(bool flag) {
    _68->sub_710104D398(flag);
}

void Unk_7102502138::sub_710103B430(bool flag) {
    _68->sub_710104D620(flag);
}

void Unk_7102502138::sub_710103B414(const sead::SafeString& name) {
    _68->sub_710104D068(name);
}

void Unk_7102502138::sub_710103B428(const sead::SafeString& name, xlink::XLink* xlink) {
    _68->sub_710104D3B0(name, xlink);
}

void Unk_7102502138::sub_710103B43C(const sead::SafeString& name) {
    _68->sub_710104D638(name);
}

void Unk_7102502138::sub_710103B444(bool flag) {
    _68->sub_710104D834(flag);
}

void Unk_7102502138::sub_710103B450(const sead::SafeString& name) {
    _68->sub_710104D84C(name);
}

void Unk_7102502138::sub_710103B458(const sead::SafeString& name) {
    _68->sub_710104D9E8(name);
}

void Unk_7102502138::sub_710103B460(const sead::SafeString& name) {
    _68->sub_710104DB84(name);
}

void Unk_7102502138::sub_710103B468(bool flag) {
    _68->sub_710104DD20(flag);
}

void Unk_7102502138::sub_710103B47C(bool flag) {
    _68->sub_710104DD88(flag);
}

void Unk_7102502138::sub_710103B474(s32 value) {
    _68->sub_710104DD7C(value);
}

// NON_MATCHING: the original computes both bytes before storing them
void Unk_71012C5034::sub_71012C384C(const sead::SafeString& name) {
    const bool result = m2(name);
    _c = result;
    _d = !result;
}

void Unk_71012C5034::sub_71012C3888(const Unk_710251b170::Speed* speed) {
    if (_d) {
        _c = m3();
        _d = false;
    }
    if (_c)
        m4(speed);
}

void Unk_71012C5034::sub_71012C38F8(const Unk_710251b170::Strength* strength) {
    if (_d) {
        _c = m3();
        _d = false;
    }
    if (_c)
        m5(strength);
}

void Unk_71012C5034::sub_71012C3968() {
    m6();
    _c = false;
    _d = false;
}


}  // namespace ksys::snd
