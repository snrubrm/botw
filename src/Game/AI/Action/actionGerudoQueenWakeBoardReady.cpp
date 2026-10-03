#include "Game/AI/Action/actionGerudoQueenWakeBoardReady.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

GerudoQueenWakeBoardReady::GerudoQueenWakeBoardReady(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GerudoQueenWakeBoardReady::~GerudoQueenWakeBoardReady() = default;

bool GerudoQueenWakeBoardReady::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GerudoQueenWakeBoardReady::enter_(ksys::act::ai::InlineParamPack* params) {
    _20 = ksys::eft::searchAndEmitELink(mActor, "SafetyZone");
    playAS("WakeBoarding", false, 0, 0, -1.0f);
}

void GerudoQueenWakeBoardReady::leave_() {
    xlink::fade(_20, -1);
}

void GerudoQueenWakeBoardReady::loadParams_() {}

void GerudoQueenWakeBoardReady::calc_() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();

    f32 scale = 0;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam())
        scale = 2 * global->getGlobalParam()->mGerudoQueenSafetyAreaRadius.ref();

    _20.setPosition(pos, scale);
    setFinished();
}

}  // namespace uking::action
