#include "Game/AI/Action/actionSiteBossLswordWhirlSlash.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"
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

f32 SiteBossLswordWhirlSlash::m38() {
    if (_1f8)
        return *mCircleEmitOffset_s;
    return SiteBossLswordAtkWithChemical::m38();
}

int SiteBossLswordWhirlSlash::m39() {
    return 0;
}

bool SiteBossLswordWhirlSlash::sub_7100260B10(sead::Vector3f* out) {
    auto* object = mActor->getMapObject();
    if (!object || !object->getRails_0())
        return false;
    auto* rail = *object->getRails_0();
    if (!rail)
        return false;
    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    const f32 dist = *mEmitChangeDist_s;
    for (s32 i = 0; i < rail->getNumPoints(); ++i) {
        const sead::Vector3f point = rail->getPointTranslate(i);
        const f32 dx = point.x - x;
        const f32 dz = point.z - z;
        if (dx * dx + dz * dz < dist * dist) {
            *out = point;
            return true;
        }
    }
    return false;
}

void SiteBossLswordWhirlSlash::m37(sead::Vector3f* pos) {
    _1f8 = sub_7100260B10(pos);
    if (!_1f8)
        mActor->getMtx().getTranslation(*pos);
}

}  // namespace uking::action
