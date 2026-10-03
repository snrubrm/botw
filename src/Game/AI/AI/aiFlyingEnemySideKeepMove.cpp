#include "Game/AI/AI/aiFlyingEnemySideKeepMove.h"

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

}  // namespace uking::ai
