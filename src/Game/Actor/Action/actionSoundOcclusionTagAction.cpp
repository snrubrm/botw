#include "Game/Actor/Action/actionSoundOcclusionTagAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndOcclusionMgr.h"
#include "KingSystem/System/StageInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SoundOcclusionTagAction::SoundOcclusionTagAction(const InitArg& arg) : AreaActionBase(arg) {}

SoundOcclusionTagAction::~SoundOcclusionTagAction() {
    _38.freeBuffer();
}

// NON_MATCHING: common return and final layer stores use a different block layout.
bool SoundOcclusionTagAction::init_(sead::Heap* heap) {
    const auto& map_type = ksys::StageInfo::getCurrentMapType();
    if (map_type == "MainField" || map_type == "AocField" || map_type == "GameTestField") {
        _38.tryAllocBuffer(1, heap);
        if (!_38.getBufferPtr())
            return false;
        _38[0]._0 = ksys::phys::ContactLayer::SensorPlayer;
        _50 = 0;
    } else if (map_type == "CDungeon") {
        _38.tryAllocBuffer(5, heap);
        if (!_38.getBufferPtr())
            return false;
        _38[0]._0 = ksys::phys::ContactLayer::SensorObject;
        _38[1]._0 = ksys::phys::ContactLayer::SensorSmallObject;
        _38[2]._0 = ksys::phys::ContactLayer::SensorPlayer;
        _38[3]._0 = ksys::phys::ContactLayer::SensorEnemy;
        _38[4]._0 = ksys::phys::ContactLayer::SensorNPC;
        _50 = 1;
    }
    return true;
}

void SoundOcclusionTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void SoundOcclusionTagAction::leave_() {
    AreaActionBase::leave_();
}

void SoundOcclusionTagAction::loadParams_() {
    getStaticParam(&mOcclusionLevel_s, "OcclusionLevel");
}

// NON_MATCHING: the manager and occlusion pointers use different registers.
bool SoundOcclusionTagAction::m15(const ksys::act::ActorLinkConstDataAccess& accessor) {
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
    AreaActionBase::calc_();
}

}  // namespace uking::action
