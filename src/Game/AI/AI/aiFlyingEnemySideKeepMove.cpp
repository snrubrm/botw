#include "Game/AI/AI/aiFlyingEnemySideKeepMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

FlyingEnemySideKeepMove::FlyingEnemySideKeepMove(const InitArg& arg) : FlyingEnemyKeepMove(arg) {}

FlyingEnemySideKeepMove::~FlyingEnemySideKeepMove() = default;

bool FlyingEnemySideKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyKeepMove::init_(heap);
}

void FlyingEnemySideKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (*mSideDirType_s) {
    case 1:
        m37(&_88);
        break;
    case 2:
        m38(&_88);
        break;
    case 4:
        m38(&_88);
        sub_71003D342C();
        break;
    case 3:
        m37(&_88);
        sub_71003D342C();
        break;
    default:
        m37(&_88);
        sub_71003D342C();
        break;
    }
    _98.mActor = mActor;
    _98.mValue = 15.0f;
    FlyingEnemyKeepMove::enter_(params);
}

void FlyingEnemySideKeepMove::calc_() {
    if (u32(*mSideDirType_s - 1) >= 2) {
        _98.sub_7100D3BC4C(-1.0f);
        if (_98.mValue <= 0.0f) {
            _98.mValue = 15.0f;
            sub_71003D342C();
        }
    }
    FlyingEnemyKeepMove::calc_();
}

void FlyingEnemySideKeepMove::leave_() {
    FlyingEnemyKeepMove::leave_();
}

void FlyingEnemySideKeepMove::loadParams_() {
    FlyingEnemyKeepMove::loadParams_();
    getStaticParam(&mSideDirType_s, "SideDirType");
}

void FlyingEnemySideKeepMove::m34(sead::Vector3f* out) {
    *out = _88;
}

void FlyingEnemySideKeepMove::m37(sead::Vector3f* out) {
    *out = sead::Vector3f::ex;
}

void FlyingEnemySideKeepMove::m38(sead::Vector3f* out) {
    *out = -sead::Vector3f::ex;
}

namespace {
void negate(sead::Vector3f& v) {
    v.x = -v.x;
    v.y = -v.y;
    v.z = -v.z;
}
}  // namespace

// 0x71003d342c
void FlyingEnemySideKeepMove::sub_71003D342C() {
    if (u32(*mSideDirType_s - 1) < 2)
        return;

    sead::Vector3f direction = _88;
    if (*mSideDirType_s == 3)
        m37(&direction);
    else if (*mSideDirType_s == 4)
        m38(&direction);

    sead::Vector3f positive;
    m35(&positive, direction);
    sead::Vector3f negative;
    m35(&negative, -direction);

    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    const sead::Vector3f* second = &negative;
    const sead::Vector3f* first = &positive;
    if (*mSideDirType_s == 0) {
        if ((position - positive).squaredLength() > (position - negative).squaredLength()) {
            negate(direction);
            first = &negative;
            second = &positive;
        }
    }
    if (sub_710072E928(position, *first, nullptr, nullptr, nullptr, 0.0f) &&
        !sub_710072E928(position, *second, nullptr, nullptr, nullptr, 0.0f)) {
        negate(direction);
    }
    _88 = direction;
}

}  // namespace uking::ai
