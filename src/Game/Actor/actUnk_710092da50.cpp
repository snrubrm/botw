#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/System/CameraS1.h"
#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSoundParam.h>
#include <aal/aalSystemAccessor.h>

void sub_7100D8AED0(sead::LookAtCamera* camera, sead::PerspectiveProjection* projection);

bool sub_710092DA58(sead::PerspectiveProjection* projection) {
    if (auto* camera = sub_7100923E74()) {
        sub_7100D8AED0(camera, projection);
        return true;
    }
    return false;
}

bool sub_710092DA88(sead::PerspectiveProjection* projection) {
    if (auto* camera = sub_7100923E74()) {
        sub_7100D8AED0(camera, projection);
        return true;
    }
    return false;
}

const sead::Viewport* sub_710092DAB8() {
    if (auto* mgr = ksys::CameraMgr::instance())
        return mgr->sub_7100D8C4C8();
    return nullptr;
}

const sead::Viewport* sub_710092DAD0() {
    if (auto* mgr = ksys::CameraMgr::instance())
        return mgr->sub_7100D8C4C8();
    return nullptr;
}

void sub_710092DAE8(ksys::act::BaseProcAccessor* accessor) {
    if (!accessor)
        return;
    if (auto* root = uking::act::Root6::instance())
        root->sub_7100927198(accessor);
}

void getRoot6SomeActor(ksys::act::BaseProcAccessor* accessor) {
    if (!accessor)
        return;
    if (auto* root = uking::act::Root6::instance())
        root->sub_71009287CC(accessor);
}

void sub_710092DB30(ksys::act::BaseProcLink* link) {
    if (!link)
        return;
    if (auto* root = uking::act::Root6::getInstance())
        link->acquire(root->sub_71009285F0(), false);
}

void sub_710092DB74(uking::act::Camera** camera) {
    if (!camera)
        return;
    if (auto* root = uking::act::Root6::getInstance())
        *camera = root->sub_71009285F0();
}

ksys::util::Unk_7101EC6BAC sub_710092DBA4() {
    if (auto* root = uking::act::Root6::instance()) {
        if (auto* camera = root->sub_71009285F0())
            return camera->_139c;
    }
    return ksys::util::sUnk_7101EC6BAC;
}



bool sub_710092DC00() {
    auto* root = uking::act::Root6::instance();
    if (!root)
        return false;
    auto* camera = root->sub_71009285F0();
    if (!camera)
        return false;
    return camera->_860.sub_710079C120(1);
}

// NON_MATCHING: placeholder destructor; the original (0x710092de00) also destroys members or bases
// this class does not declare yet.
Unk_71024742f0::~Unk_71024742f0() = default;

// 0x710092e088: the state machine at +0x40 runs its current state.
void Unk_71024742f0::m5() {
    mStateMachine.run();
}

// 0x710092e090: sets the volume of the "eBookSize_Weapon_Sword_004" sound group to 1.
void Unk_71024742f0::m6() {
    auto* group_mgr = aal::SystemAccessor::getGroupMgr();
    if (!group_mgr)
        return;
    if (auto* group = group_mgr->findGroup("eBookSize_Weapon_Sword_004"))
        group->getParam().setVolume(1.0f);
}
