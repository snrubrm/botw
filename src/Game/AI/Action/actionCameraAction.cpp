#include "Game/AI/Action/actionCameraAction.h"
#include "Game/AI/aiXlinkHandle.h"
#include "Game/Actor/actCameraUtil.h"

namespace uking::action {

CameraAction::CameraAction(const InitArg& arg)
    : ksys::act::ai::Action(arg), Unk_7102459708(this) {}

bool CameraAction::init_(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return m32(heap);
}

void CameraAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraAction::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
    m36();
}

void CameraAction::calc_() {
    if (auto* camera = getCamera())
        camera->_860.sub_710079C158(1, *mBowFlag_s);

    if (auto* camera = getCamera())
        camera->_860._0._30 = camera->_860.sub_710079ADA0();

    auto* camera = getCamera();
    if (camera && camera->_860._804.sub_710079AE50(0x80000)) {
        act::Unk_71009214b8 states[6];
        sub_710074B590(states);
        m34();
        sub_710074B838(states);
    } else {
        m34();
    }

    m40();
    m41();
}

void CameraAction::sub_710074B590(act::Unk_71009214b8* states) {
    if (auto* camera = getCameraActor()) {
        states[0] = camera->_860._0;
        states[1] = camera->_860._38;
        states[2] = camera->_860._70;
        states[3] = camera->_860._a8;
        states[4] = camera->_860._e0;
        states[5] = camera->_860._118;
    }
}

void CameraAction::sub_710074B838(const act::Unk_71009214b8* states) {
    if (auto* camera = getCamera()) {
        camera->_860._0 = states[0];
        camera->_860._38 = states[1];
        camera->_860._70 = states[2];
        camera->_860._a8 = states[3];
        camera->_860._e0 = states[4];
        camera->_860._118 = states[5];
    }
}

void CameraAction::m33() {}

void CameraAction::m34() {}

void CameraAction::m36() {}

// The original zeroes x0 (`mov x0, xzr`): a 64-bit return type of unknown meaning.
u64 CameraAction::m37() {
    return 0;
}

void CameraAction::m40() {
    if (auto* camera = getCamera())
        camera->_860._0.sub_71009237BC();
}

void CameraAction::m41() {
    if (auto* camera = getCamera()) {
        if (camera->_860._817 != 0xff)
            ++camera->_860._817;
    }
}

void CameraAction::sub_710074BCB4() {
    if (_48 & 1) {
        _48 &= ~1;
        xlink::fade(_30, -1);
    }
}

}  // namespace uking::action
