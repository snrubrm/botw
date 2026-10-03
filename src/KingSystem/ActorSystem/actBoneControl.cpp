#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::act {

BoneControl::BoneControl() = default;

void BoneControl::sub_7100D82F50() {
    if (_0) {
        _0->sub_7100D8561C();
        delete _0;
        _0 = nullptr;
    }
}

void BoneControl::sub_7100D82F94() {
    if (_0)
        _0->sub_7100D85644();
}

void BoneControl::sub_7100D82FA4() {
    if (_0)
        _0->sub_7100D8566C();
}

void BoneControl::sub_7100D82FB4() {
    if (_0)
        _0->sub_7100D85794();
}

void BoneControl::sub_7100D82FC4() {
    if (_0)
        _0->sub_7100D857B0();
}

void BoneControl::sub_7100D82FE8(f32 value) {
    if (auto* unk = _0) {
        unk->_e8._28 = value;
        unk->_10._d0 = value;
    }
}

Unk_7100d860d8* sub_7100D82FFC(BoneControl* bone_control) {
    if (!bone_control)
        return nullptr;
    auto* unk = bone_control->_0;
    if (!unk)
        return nullptr;
    return &unk->_10;
}

bool sub_7100D83014(sead::Vector3f* out, const BoneControl* bone_control) {
    if (!bone_control)
        return false;
    auto* unk = bone_control->_0;
    if (!unk)
        return false;
    unk->_10.sub_7100D892C4(out);
    return true;
}


}  // namespace ksys::act
