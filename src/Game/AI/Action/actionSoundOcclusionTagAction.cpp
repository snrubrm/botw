#include "Game/AI/Action/actionSoundOcclusionTagAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"

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

void SoundOcclusionTagAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
