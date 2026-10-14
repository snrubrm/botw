#include "Game/Actor/aiUnk_71025ba778.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

void Unk_71025ba778::sub_710070F350(ksys::act::Actor* actor) {
    if (!actor)
        return;
    if (!_100._8)
        actor->boneHandleStuff(&_18, false);
    _8 |= 1;
}

void Unk_71025ba778::sub_710070F79C(ksys::act::Actor* actor) {
    if (!actor)
        return;
    if (!_100._8) {
        _100.setName("Man_Spine_1");
        actor->boneHandleStuff(&_100, true);
    }
    _8 |= 2;
}

void Unk_71025ba778::sub_710070F820(ksys::act::Actor* actor) {
    _8 &= ~2;
}

void Unk_71025ba778::sub_710070F398(ksys::act::Actor* actor) {
    if (!actor || !(_8 & 1))
        return;
    actor->sub_71011DA868(&_18);
    _8 &= ~1;
    if (_100._8) {
        _8 &= ~2;
        actor->sub_71011DA868(&_100);
    }
}

// NON_MATCHING: the original keeps most of the rotate = M^T * (axis * angle) sum in each branch; ours merges it
// into the common tail. The control flow, calls and constants match.
void Unk_71025ba778::sub_710070F400(ksys::act::Actor* actor) {
    if (!(_8 & 1))
        return;

    f32 value = _18._68;
    if (value != _c) {
        ksys::VFR::lerp(&value, _c, _10, 1.0f, 0.01f);
        _18._68 = value;
    }

    const auto& mtx = actor->getMtx();
    sead::Vector3f rotate;
    if (!(_8 & 2)) {
        if (_18._d8 != sead::Vector3f::ey) {
            sub_710002F6D8(&_18._d8, sead::Vector3f::ey, 0.1f, 3.14159265f, 0.031415927f);
            sead::Vector3f axis;
            f32 angle;
            ksys::util::sub_71011EEB08(&axis, &angle, _18._d8, sead::Vector3f::ey, sead::Vector3f::ey);
            const sead::Vector3f v = axis * angle;
            rotate.x = v.x * mtx(0, 0) + v.y * mtx(1, 0) + v.z * mtx(2, 0);
            rotate.y = v.x * mtx(0, 1) + v.y * mtx(1, 1) + v.z * mtx(2, 1);
            rotate.z = v.x * mtx(0, 2) + v.y * mtx(1, 2) + v.z * mtx(2, 2);
        } else {
            if (_100._8)
                actor->sub_71011DA868(&_100);
            return;
        }
    } else {
        sead::Vector3f up{mtx(0, 1), mtx(1, 1), mtx(2, 1)};
        up.normalize();
        sub_710002F6D8(&_18._d8, up, 0.1f, 3.14159265f, 0.031415927f);
        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, _18._d8, sead::Vector3f::ey, sead::Vector3f::ey);
        if (angle > _1a8)
            angle = _1a8;
        const sead::Vector3f v = axis * angle;
        rotate.x = v.x * mtx(0, 0) + v.y * mtx(1, 0) + v.z * mtx(2, 0);
        rotate.y = v.x * mtx(0, 1) + v.y * mtx(1, 1) + v.z * mtx(2, 1);
        rotate.z = v.x * mtx(0, 2) + v.y * mtx(1, 2) + v.z * mtx(2, 2);
    }
    _100._68.makeR(rotate);
    _100._68.setTranslation(sead::Vector3f::zero);
}

Unk_7100710078::~Unk_7100710078() {
    delete _70;
}
