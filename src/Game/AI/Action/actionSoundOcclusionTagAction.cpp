#include "Game/AI/Action/actionSoundOcclusionTagAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Sound/sndOcclusionMgr.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SoundOcclusionTagAction::SoundOcclusionTagAction(const InitArg& arg) : AreaTagAction(arg) {}

SoundOcclusionTagAction::~SoundOcclusionTagAction() {
    _38.freeBuffer();
}

bool SoundOcclusionTagAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SoundOcclusionTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SoundOcclusionTagAction::leave_() {
    AreaTagAction::leave_();
}

void SoundOcclusionTagAction::loadParams_() {
    getStaticParam(&mOcclusionLevel_s, "OcclusionLevel");
}

// NON_MATCHING: the manager and occlusion pointers use different registers.
bool SoundOcclusionTagAction::m15(const ksys::act::ActorConstDataAccess& accessor) {
    switch (_50) {
    case 0:
        if (ksys::act::isPlayerProfile(accessor) && mOcclusionLevel_s) {
            auto* sound = ksys::snd::SoundMgr::instance();
            const float level = *mOcclusionLevel_s;
            sound->mOcclusionMgr->_70 = level + level;
            sound->mOcclusionMgr->sub_7101056868();
            if (level == 1.0f) {
                if (auto* bgm = ksys::snd::sub_7100FFDC80())
                    bgm->_3c = true;
            }
        }
        break;
    case 1:
        ksys::act::isPlayerProfile(accessor);
        return false;
    }
    return true;
}

void SoundOcclusionTagAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
