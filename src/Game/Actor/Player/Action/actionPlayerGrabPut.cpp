#include "Game/Actor/Player/Action/actionPlayerGrabPut.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actCameraUtil.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerGrabPut::PlayerGrabPut(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: scheduling of the ground probe start / end vectors; the original loads the AS list before
// testing the hit normal.
void PlayerGrabPut::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80000000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->_1834 = sub_710092DBA4();

    auto* scene = GameSceneSubsys12::instance();
    _28 = ksys::act::sub_710086B194() == ksys::act::AttActionCodeValue(0x1800027);
    if (_28) {
        mActor->getASList()->x_6(0x10, 0, 1.5f);
    } else if (scene) {
        if (scene->_a78.load() & 8)
            mActor->getASList()->x_6(0x10, 0, 6.0f);
        else
            mActor->getASList()->x_6(0x10, 0, 1.0f);
        if (scene->sub_71006652C8()) {
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
            ui::PauseMenuDataMgr::instance()->removeGrabbedItems();
        }
    }

    if (!static_cast<ksys::act::Player*>(mActor)->m203()) {
        sead::Vector3f dir;
        static_cast<ksys::act::Player*>(mActor)->_1b18.getBase(dir, 2);
        dir.normalize();
        sead::Vector3f start = dir + static_cast<ksys::act::Player*>(mActor)->_1770;
        sead::Vector3f end = start;
        start.y += 2.0f;
        end.y -= 2.0f;
        sead::Vector3f hit_pos;
        sead::Vector3f hit_normal;
        if (static_cast<ksys::act::Player*>(mActor)->sub_710087F360(start, end, &hit_pos,
                                                                    &hit_normal) &&
            hit_normal.y > 0.5f) {
            mActor->getASList()->x_6(0x10, 0,
                                     hit_pos.y - static_cast<ksys::act::Player*>(mActor)->_1770.y);
        } else {
            mActor->getASList()->x_6(0x10, 0, 0.0f);
        }
    }

    if (static_cast<ksys::act::Player*>(mActor)->_17f0)
        static_cast<ksys::act::Player*>(mActor)->sub_7100855BB4("TurnAttention", false, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GrabPut", true, -1.0f);
    player = static_cast<ksys::act::Player*>(mActor);
    const f32 frame = player->_c44.isOnBit(21) ? *mPutStartFrmae_s : 1.0f;
    player->_1844 = ksys::Timer(frame, frame);
}

void PlayerGrabPut::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
}

void PlayerGrabPut::loadParams_() {
    getStaticParam(&mPutStartFrmae_s, "PutStartFrmae");
}

void PlayerGrabPut::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    if (!_28) {
        player = static_cast<ksys::act::Player*>(mActor);
        if (!(player->_1844.value <= sead::Mathf::epsilon())) {
            player->_1844.update();
            if (static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon()) {
                if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
                    sub_71005DC3CC(actor);
            }
        }
    }
    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        if (static_cast<ksys::act::Player*>(mActor)->sub_7100857014(
                -1.0f, &static_cast<ksys::act::Player*>(mActor)->_1834, -1, -1)) {
            static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (!_28) {
        if (mActor->getASList()->sub_710115FBC8(70, nullptr, &ksys::as::ASList::Unk2::sub_71011637EC,
                                                true)) {
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
                sub_71005DC394(actor);
        }
    }
    if (mActor->getASList()->x_4(0, 0)) {
        static_cast<ksys::act::Player*>(mActor)->m228(false);
        setFinished();
    }
}

bool PlayerGrabPut::isChangeable() const {
    return false;
}

}  // namespace uking::action
