#include "Game/AI/Action/actionZoraHeroWaterFallJump.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ZoraHeroWaterFallJump::ZoraHeroWaterFallJump(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraHeroWaterFallJump::~ZoraHeroWaterFallJump() = default;

bool ZoraHeroWaterFallJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraHeroWaterFallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    auto* model = mActor->getModel();
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    if (as_list && model)
        as_list->sub_710115BAF8("Root");
}

void ZoraHeroWaterFallJump::leave_() {
    ksys::act::ai::Action::leave_();
}

void ZoraHeroWaterFallJump::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void ZoraHeroWaterFallJump::calc_() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* controller = actor->getCharacterController();
    sead::Vector3f move = sead::Vector3f::zero;
    sead::Vector3f rot = sead::Vector3f::zero;
    const f32 x = actor->getMtx()(0, 3);
    const f32 z = actor->getMtx()(2, 3);
    if (as_list) {
        move.set(as_list->sub_710115D2D4());
        rot.set(as_list->sub_710115D3B8());
    }
    move.rotate(actor->getMtx());
    rot.rotate(actor->getMtx());

    const sead::Vector3f player_pos = getPlayerPosition();
    sead::Vector3f diff = {player_pos.x - x, 0.0f, player_pos.z - z};
    f32 speed = diff.length();
    if (ksys::VFR::instance()->getDeltaFrame() > 0.0f) {
        speed /= ksys::VFR::instance()->getDeltaFrame();
        if (diff.squaredLength() > speed * speed) {
            const f32 length = diff.length();
            if (length > 0.0f)
                diff *= speed / length;
        }
    }
    move.x = diff.x;
    move.z = diff.z;

    if (controller) {
        sub_7100737710(controller, move);
        sub_7100737714(controller, rot);
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
