#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace uking::act {

// Keeps the original destructor's vtable update, as in upstream
// GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
Unk_71025ae680::~Unk_71025ae680() {
    ;
}

void Unk_71025ae680::m6() {
    if (!(_a & 3))
        m10();
    _a &= ~0x24;
}

// Preserves the original own D1, as in upstream
// GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
Unk_710244ff68::~Unk_710244ff68() {
    ;
}

bool Unk_710244ff68::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _30._30 = true;
    _30._18 = message.getSource();
    return true;
}

// Keep each original own D1, following upstream GameDataFlagSelector's user-provided
// destructor form (commit 96101229).
Unk_710244ebc8::~Unk_710244ebc8() { ; }
Unk_710244eb48::~Unk_710244eb48() { ; }
Unk_710244fee8::~Unk_710244fee8() { ; }

bool Unk_710244ebc8::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _40._30 = true;
    _40._18 = message.getSource();
    return true;
}

void Unk_710244ebc8::m13(int index) {
    if (index == 4)
        _20.fadeXLink();
    _8.resetBit(index);
}

void Unk_71025ae680::sub_71006DF67C(s32 value) {
    auto* actor = _10;
    if (auto* life = actor->getLife()) {
        const s32 max_life = actor->getMaxLife();
        *life += value;
        if (*life > max_life)
            *life = max_life;
        else if (*life < 0)
            *life = 0;
    }
}

void Unk_710244eb48::m5() {
    sub_71006E252C();
}

// lane4 s64: out-of-line copy of m5's body (the original has both: m5 inlines this).
void Unk_710244eb48::sub_71006E252C() {
    if (_58.sub_7101241B6C())
        _58.fadeXLink();
}

bool Unk_710244eb48::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _20._30 = true;
    _20._18 = message.getSource();
    return true;
}

void Unk_710244eb48::m10() {
    if (!_20._30)
        return;
    sub_71006E264C();
    _20._30 = false;
    _20._8.reset();
    // called through a pointer in the original (not devirtualised)
    (&_20)->m3();
}

void Unk_710244fee8::m5() {
    sub_71006EE354();
}

// lane4 s64: out-of-line copy of m5's body (the original has both: m5 inlines this).
void Unk_710244fee8::sub_71006EE354() {
    if (_58.sub_7101241B6C())
        _58.fadeXLink();
}

bool Unk_710244fee8::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _20._30 = true;
    _20._18 = message.getSource();
    return true;
}

void Unk_710244fee8::m10() {
    if (!_20._30)
        return;
    sub_71006EE474();
    _20._30 = false;
    _20._8.reset();
    // called through a pointer in the original (not devirtualised)
    (&_20)->m3();
}

void Unk_71025ae680::sub_71006DF750() {
    m13(11);
}

void Unk_71025ae680::sub_71006DF6EC() {
    m13(7);
    m13(8);
    m13(9);
    m13(10);
}

ksys::res::DamageParam* Unk_71025ae680::sub_71006DF5A4() {
    if (!_10 || !_10->getParam())
        return nullptr;
    return _10->getParam()->getRes().mDamageParam;
}

}  // namespace uking::act
