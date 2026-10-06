#include "Game/AI/Action/actionSoundOcclusionTagRemainsWater.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SoundOcclusionTagRemainsWater::SoundOcclusionTagRemainsWater(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SoundOcclusionTagRemainsWater::~SoundOcclusionTagRemainsWater() = default;

bool SoundOcclusionTagRemainsWater::init_(sead::Heap* heap) {
    if (auto* mgr = ksys::snd::SoundMgr::instance()->_38) {
        auto* actor = mActor;
        const sead::Vector3f translation = actor->getMtx().getTranslation();
        if (auto* occlusion = mgr->sub_710102C104()) {
            sead::Vector3f position = translation;
            position.y = translation.y + actor->getScale().y;
            const sead::Vector3f size = actor->getScale() * 2;
            occlusion->sub_7101037ED8(&position, &size);
            occlusion->sub_7101037F5C(0x10);
            occlusion->sub_7101037F64(true);
        }
    }
    return true;
}

void SoundOcclusionTagRemainsWater::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* mgr = ksys::snd::SoundMgr::instance()->_38) {
        if (auto* occlusion = mgr->sub_710102C104())
            occlusion->sub_7101037F64(true);
    }
}

void SoundOcclusionTagRemainsWater::leave_() {
    if (auto* mgr = ksys::snd::SoundMgr::instance()->_38) {
        if (auto* occlusion = mgr->sub_710102C104())
            occlusion->sub_7101037F64(false);
    }
}

void SoundOcclusionTagRemainsWater::loadParams_() {}

void SoundOcclusionTagRemainsWater::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
