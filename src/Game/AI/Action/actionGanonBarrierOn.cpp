#include "Game/AI/Action/actionGanonBarrierOn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/Actor/actLastBoss.h"

namespace uking::action {

GanonBarrierOn::GanonBarrierOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonBarrierOn::~GanonBarrierOn() = default;

bool GanonBarrierOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonBarrierOn::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    bool in_event = mActor->get1a0() != nullptr;
    if (!in_event) {
        auto* obj = mActor->getMapObject();
        in_event = obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000);
    }
    if (in_event) {
        sub_71005DB3EC(mActor);
        sub_7100739900(mActor);
    }
    mFlags.reset(Flag::Changeable);
}

void GanonBarrierOn::leave_() {
    sub_7100739918(mActor);
    if (auto* boss = sead::DynamicCast<uking::act::LastBoss>(mActor))
        boss->stunEnd();
}

void GanonBarrierOn::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void GanonBarrierOn::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GanonBarrierOn::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
