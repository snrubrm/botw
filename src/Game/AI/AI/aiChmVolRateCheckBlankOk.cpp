#include "Game/AI/AI/aiChmVolRateCheckBlankOk.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

ChmVolRateCheckBlankOk::ChmVolRateCheckBlankOk(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChmVolRateCheckBlankOk::~ChmVolRateCheckBlankOk() = default;

bool ChmVolRateCheckBlankOk::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads the link buffer pointer before constructing the accessor (scheduling)
void ChmVolRateCheckBlankOk::enter_(ksys::act::ai::InlineParamPack* params) {
    _84[0] = sead::Vector3f::zero;
    _84[1] = sead::Vector3f::zero;
    _84[2] = sead::Vector3f::zero;
    _84[3] = sead::Vector3f::zero;
    _84[4] = sead::Vector3f::zero;
    _84[5] = sead::Vector3f::zero;
    _84[6] = sead::Vector3f::zero;
    _84[7] = sead::Vector3f::zero;
    _104 = *mFreezeTarget_m == 2;

    auto* actor = mActor;
    const sead::BoundBox3f aabb = actor->getAabb();
    _e4 = aabb.getMin();
    _f0 = aabb.getMax();
    _100 = aabb.getSizeX() * aabb.getSizeY() * aabb.getSizeZ();

    if (auto* object = actor->getMapObject()) {
        auto* link_data = object->getLinkData();
        if (link_data && link_data->mObjects.size() >= 1) {
            ksys::act::ActorConstDataAccess accessor;
            if (auto* linked = link_data->mObjects[0]) {
                linked->getActorWithAccessor(accessor);
                sead::Vector3f min;
                sead::Vector3f max;
                if (accessor.hasProc() && accessor.getAabb(&min, &max)) {
                    _104 = true;
                    sead::Vector3f pos;
                    accessor.getActorMtx().getTranslation(pos);

                    _fc = (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
                    _68.set(min, max);
                    _84[0].set(min.x, min.y, min.z);
                    _84[1].set(max.x, min.y, min.z);
                    _84[2].set(max.x, min.y, max.z);
                    _84[3].set(min.x, min.y, max.z);
                    _84[4].set(min.x, max.y, min.z);
                    _84[5].set(max.x, max.y, min.z);
                    _84[6].set(max.x, max.y, max.z);
                    _84[7].set(min.x, max.y, max.z);

                    const sead::Matrix34f mtx = accessor.getActorMtx();
                    sead::Matrix34f inv;
                    inv.setInverse(actor->getMtx());
                    for (int i = 0; i < 8; ++i) {
                        _84[i].setMul(mtx, _84[i]);
                        _84[i].setMul(inv, _84[i]);
                    }

                    _80 = 1;
                    _68.set(pos + min, pos + max);
                }
            }
        }
    }

    changeChild("オフ");
    mFlags.set(Flag::Changeable);
}

void ChmVolRateCheckBlankOk::calc_() {
    if (!_104)
        return;

    auto* actor = mActor;
    if (*mIsInvalidBreakJudge_s) {
        if (*mFreezeTarget_m == 2) {
            const f32 scale = *mDebugScale_s;
            actor->setScale({scale, scale, scale});
        }
        return;
    }

    const f32 scale = actor->getScale().x;
    const sead::BoundBox3f box({scale * _e4.x, _e4.y, scale * _e4.z},
                               {scale * _f0.x, scale * _f0.y, scale * _f0.z});
    if (isCurrentChild("オン"))
        return;

    switch (*mFreezeTarget_m) {
    case 0:
        for (const auto& corner : _84) {
            if (!box.isInside(corner)) {
                _80 = 300;
                changeChild("オン");
                return;
            }
        }
        break;
    case 1:
        if (actor->getChemicalStuff()) {
            const f32 volume = _100 * std::pow(actor->getScale().x, 3.0f);
            if (_fc > 0 && volume / _fc <= *mVolTh_s) {
                _80 = 300;
                changeChild("オン");
            }
        }
        break;
    case 2:
        if (scale <= *mIceBreakScale_m) {
            _80 = 300;
            changeChild("オン");
        }
        break;
    default:
        break;
    }
}

void ChmVolRateCheckBlankOk::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChmVolRateCheckBlankOk::loadParams_() {
    getStaticParam(&mVolTh_s, "VolTh");
    getStaticParam(&mDebugScale_s, "DebugScale");
    getStaticParam(&mDebugDraw_s, "DebugDraw");
    getStaticParam(&mIsInvalidBreakJudge_s, "IsInvalidBreakJudge");
    getMapUnitParam(&mFreezeTarget_m, "FreezeTarget");
    getMapUnitParam(&mIceBreakScale_m, "IceBreakScale");
}

}  // namespace uking::ai
