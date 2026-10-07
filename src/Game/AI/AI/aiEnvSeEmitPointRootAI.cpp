#include "Game/AI/AI/aiEnvSeEmitPointRootAI.h"
#include <limits>
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Sound/sndMgr.h"

namespace uking::ai {

EnvSeEmitPointRootAI::EnvSeEmitPointRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnvSeEmitPointRootAI::~EnvSeEmitPointRootAI() = default;

bool EnvSeEmitPointRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads the player's coordinates before the actor's in the xz distance (ours loads the
// actor's first).
void EnvSeEmitPointRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    f32 distance = std::numeric_limits<f32>::max();
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::ActorSystem::instance()->getPlayer(&accessor);
        if (accessor.hasProc()) {
            const auto& mtx = accessor.getActorMtx();
            if (auto* actor = mActor) {
                const sead::Vector3f diff{actor->getMtx().m[0][3] - mtx.m[0][3], 0.0f,
                                          actor->getMtx().m[2][3] - mtx.m[2][3]};
                distance = diff.length();
            }
        }
    }

    if (!(*mInvalidatePlayDistance_s <= distance && distance <= *mPlayDistance_s)) {
        changeChild("待機", nullptr);
        if (auto* point = sead::DynamicCast<act::EnvSeEmitPoint>(mActor))
            ksys::snd::SoundMgr::instance()->_38->_20->sub_7101029C98(point);
    } else {
        changeChild("再生", nullptr);
        if (auto* point = sead::DynamicCast<act::EnvSeEmitPoint>(mActor))
            ksys::snd::SoundMgr::instance()->_38->_20->sub_7101029BB0(point);
    }
}

void EnvSeEmitPointRootAI::leave_() {
    if (auto* point = sead::DynamicCast<act::EnvSeEmitPoint>(mActor))
        ksys::snd::SoundMgr::instance()->_38->_20->sub_7101029C98(point);
}

void EnvSeEmitPointRootAI::loadParams_() {
    getStaticParam(&mInvalidatePlayDistance_s, "InvalidatePlayDistance");
    getStaticParam(&mPlayDistance_s, "PlayDistance");
}

}  // namespace uking::ai
