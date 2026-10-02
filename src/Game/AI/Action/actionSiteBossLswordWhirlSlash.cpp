#include "Game/AI/Action/actionSiteBossLswordWhirlSlash.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

SiteBossLswordWhirlSlash::SiteBossLswordWhirlSlash(const InitArg& arg)
    : SiteBossLswordAtkWithChemical(arg) {}

SiteBossLswordWhirlSlash::~SiteBossLswordWhirlSlash() = default;

void SiteBossLswordWhirlSlash::loadParams_() {
    SiteBossLswordAtkWithChemical::loadParams_();
    getStaticParam(&mEmitChangeDist_s, "EmitChangeDist");
    getStaticParam(&mCircleEmitOffset_s, "CircleEmitOffset");
}

void SiteBossLswordWhirlSlash::calc_() {
    SiteBossLswordAtkWithChemical::calc_();
}

int SiteBossLswordWhirlSlash::m34() {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0xe, &query, 0, 0))
        return 1;
    return SiteBossLswordAtk::m34();
}

}  // namespace uking::action
