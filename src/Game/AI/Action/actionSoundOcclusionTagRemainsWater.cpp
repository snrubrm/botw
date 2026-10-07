#include "Game/AI/Action/actionSoundOcclusionTagRemainsWater.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

// The original calculation reads these five consecutive configuration floats.
struct Unk_71023bfe70 {
    f32 mDistance;
    f32 mDistanceRange;
    f32 mHeight;
    f32 mHeightRange;
    f32 mScale;
};
extern const Unk_71023bfe70 sUnk_71023bfe70;

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

// NON_MATCHING: Configuration binding and floating-point register allocation differ.
void SoundOcclusionTagRemainsWater::calc_() {
    sead::Vector3f player_position = sead::Vector3f::zero;
    if (!ksys::act::ActorSystem::instance()->getPlayerPosition(&player_position))
        return;
    auto* mgr = ksys::snd::SoundMgr::instance()->_38;
    if (!mgr)
        return;
    auto* occlusion = mgr->sub_710102C104();
    if (!occlusion)
        return;
    const f32 delta = player_position.x - mActor->getMtx().m[0][3];
    const f32 distance = delta > 0.0f ? delta : -delta;
    const f32 maximum_distance = sUnk_71023bfe70.mDistance + sUnk_71023bfe70.mDistanceRange;
    f32 distance_factor;
    if (distance > maximum_distance)
        distance_factor = 1.0f;
    else if (distance > sUnk_71023bfe70.mDistance)
        distance_factor = (distance - sUnk_71023bfe70.mDistance) /
                          (maximum_distance - sUnk_71023bfe70.mDistance);
    else
        distance_factor = 0.0f;
    f32 height_factor = 1.0f;
    if (!(player_position.y <= sUnk_71023bfe70.mHeight - sUnk_71023bfe70.mHeightRange)) {
        height_factor = 0.0f;
        if (player_position.y <= sUnk_71023bfe70.mHeight && sUnk_71023bfe70.mHeightRange > 0.0f)
            height_factor = (sUnk_71023bfe70.mHeight - player_position.y) /
                            sUnk_71023bfe70.mHeightRange;
    }
    occlusion->_398 = sUnk_71023bfe70.mScale * sead::Mathf::min(distance_factor, height_factor);
}

}  // namespace uking::action
