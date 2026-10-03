#include "Game/AI/Action/actionShutterOpenWait.h"

namespace uking::action {

ShutterOpenWait::ShutterOpenWait(const InitArg& arg) : ActionEx(arg) {}

ShutterOpenWait::~ShutterOpenWait() = default;

bool ShutterOpenWait::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterOpenWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    switch (*mMoveAxis_m) {
    case 0:
        _40.set(sead::Vector3f::ex);
        break;
    case 1:
        _40.set(sead::Vector3f::ey);
        break;
    case 2:
        _40.set(sead::Vector3f::ez);
        break;
    }
    mFlags.set(Flag::Changeable);
}

void ShutterOpenWait::leave_() {
    ActionEx::leave_();
}

void ShutterOpenWait::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mMoveAxis_m, "MoveAxis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
}

void ShutterOpenWait::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
