#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::act {

Unk_710244dd20::Unk_710244dd20(ksys::act::Actor* actor) : Unk_71025ae680(actor) {}

f32 Unk_710244dd20::sub_71006D1D48() {
    f32 ratio = 1.0f;
    if (_8.isOn(8)) {
        if (auto* param = sub_71006DF5A4())
            ratio = *param->mIceBreakDamageRatio;
    }
    return ratio;
}

bool Unk_710244dd20::sub_71006D1D7C() {
    if (auto* param = sub_71006DF5A4())
        return *param->mIceBreakableByAtk;
    return false;
}

bool Unk_710244dd20::sub_71006D1DA0() {
    if (auto* param = sub_71006DF5A4())
        return *param->mElecCancelableByAtk;
    return false;
}

bool Unk_710244dd20::m17(s32 bit) const {
    return _139.isOnBit(bit);
}

bool Unk_71008502cc::sub_7100850CE4() const {
    return _8.isOn(0x3);
}

bool Unk_71008502cc::sub_7100850CF4() const {
    return _8.isOn(0x587);
}

void Unk_710244dd20::m5() {
    _8 = 0;
    _c0 = 0;
    if (auto* chemical = _10->getChemicalStuff()) {
        chemical->sub_7100D90CD8(false);
        chemical->sub_7100D90C2C(false);
        chemical->sub_7100D90D7C(false);
    }
    _138 = 0;
    _c4 = 1.0f;
    _c8 = 1.0f;
    _cc = 1.0f;
    _d0 = 1.0f;
    _d4 = 1.0f;
    _d8 = 1.0f;
    _dc = 1.0f;
    _e0 = 1.0f;
    _e4 = 1.0f;
    _e8 = 1.0f;
    _ec = 1.0f;
    _f0 = 1.0f;
    _30 = 0;
}

void Unk_710244dd20::m10() {
    m20();
    sub_71006CF338();
    sub_71006CF770();
    sub_71006CF9B4();
}

void Unk_710244dd20::m11(bool enable) {
    auto* chemical = _10->getChemicalStuff();
    if (!chemical)
        return;
    if (enable)
        chemical->sub_7100D8EEE0();
    chemical->sub_7100D90C2C(enable);
    chemical->sub_7100D90CD8(enable);
    chemical->sub_7100D90D7C(enable);
    chemical->sub_7100D90F60(enable);
}

bool Unk_710244dd20::m8(const ksys::Message& message) {
    if (_50.m2(message))
        return true;
    if (message.getType() != 0x800009b)
        return false;
    _88._30 = true;
    _88._18 = message.getSource();
    return true;
}

bool Unk_710244dd20::m16(s32 kind) {
    auto* chemical = _10->getChemicalStuff();
    if (!chemical)
        return true;
    if (kind == 3)
        return !(chemical->_b9[0] & 2);
    if (kind == 4)
        return !(chemical->_1b8 > 0.0f);
    return true;
}

void Unk_710244dd20::m20() {
    sub_71006D0C38();
    sub_71006D15EC();
    sub_71006D19AC();
    if (_88._30)
        sub_71006D0AB8();
    _88.x();
}

// 0x71006d2130: only forwards to the base implementation.
void Unk_710244dd20::m7() {
    Unk_71025ae680::m7();
}

}  // namespace uking::act

// NON_MATCHING: placeholder destructor; the original (0x7100850314) also destroys members or bases
// this class does not declare yet.
Unk_710246a960::~Unk_710246a960() = default;
