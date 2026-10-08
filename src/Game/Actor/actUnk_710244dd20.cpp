#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

namespace uking::act {

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

bool Unk_710244dd20::sub_71006D22B4(s32 bit) const {
    return _139.isOnBit(bit);
}

bool Unk_71008502cc::sub_7100850CE4() const {
    return _8.isOn(0x3);
}

bool Unk_71008502cc::sub_7100850CF4() const {
    return _8.isOn(0x587);
}

}  // namespace uking::act
