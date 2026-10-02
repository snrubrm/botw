#include "Game/Actor/actUnk_7100701be4.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// NON_MATCHING: the second bone-validity test compiles to a separate `cmn; b.hs` branch in the
// original (ours is a ccmp chain like the first one).
bool Unk_7100701be4::sub_7100701BE4(const sead::SafeString& left, const sead::SafeString& right,
                                    const sead::Vector3f& offset) {
    _192 = false;
    _190 = false;
    _184 = offset;
    _158 = mActor->getModel()->searchBone(left);
    if (!_158.isValid())
        return false;
    _8.setName(left);
    _160 = sead::Vector3f::zero;
    _15c = mActor->getModel()->searchBone(right);
    if (!_15c.isValid())
        return false;
    _b0.setName(right);
    _16c = sead::Vector3f::zero;
    _191 = true;
    return true;
}

void Unk_7100701be4::sub_7100701CE8() {
    if (!_191)
        return;
    if (_192) {
        _192 = false;
    } else if (!_193) {
        mActor->boneHandleStuff(&_8, false);
        mActor->boneHandleStuff(&_b0, false);
        _193 = true;
    }
}

void Unk_7100701be4::sub_7100701D4C() {
    mActor->sub_71011DA868(&_8);
    _160 = sead::Vector3f::zero;
    mActor->sub_71011DA868(&_b0);
    _16c = sead::Vector3f::zero;
    _193 = false;
}

void Unk_7100701be4::sub_7100701DBC(s32 count) {
    _190 = true;
    _17c = 0;
    _178 = 5.0f;
    _180 = count;
}

void Unk_7100701be4::sub_7100701DD8() {
    _190 = true;
    _178 = 5.0f;
    _17c = 2;
}

void Unk_7100701be4::sub_7100701DF0() {
    _190 = true;
    _17c = 3;
    _178 = 5.0f;
    _180 = 0;
}

}  // namespace uking::act
