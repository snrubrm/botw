#include "Game/Actor/AI/aiElectricCable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"
#include <aal/aalListener.h>
#include <aal/aalListenerMgr.h>
#include <aal/aalSoundSource.h>
#include <aal/aalSystemAccessor.h>
#include <geom/seadGeometry.h>
#include <limits>
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace uking::ai {

ElectricCable::ElectricCable(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    _40 = nullptr;
    _48 = nullptr;
}

ElectricCable::~ElectricCable() {
    if (_70) {
        _70->destroy();
        _70 = nullptr;
    }
}

bool ElectricCable::init_(sead::Heap* heap) {
    _70 = aal::ShapeSegment::create("ElectricCable", heap);
    _70->mFlags.resetBit(aal::Shape::KeepPosition);
    _70->mFlags.resetBit(aal::Shape::KeepRotation);
    return true;
}

void ElectricCable::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor)
        return;

    _40 = actor->sub_71011D8A44(0);
    if (_40) {
        _48 = actor->sub_71011D8A44(1);
        if (_48) {
            auto* object = actor->getMapObject();
            if (object && object->getRails_0()) {
                _50 = static_cast<ksys::map::Rail**>(object->getRails_0())[0];
                if (_50) {
                    actor->getMtx().getTranslation(_58);
                    actor->getMtx().getTranslation(_64);
                    changeChild("Wait");
                    _78 = false;
                    return;
                }
            }
        }
    }
    changeChild("Wait");
}

// NON_MATCHING: stack slot sharing (home matrix / UI info / names), and the original writes the shape vector
// directly (devirtualised ShapeSegment::setVector).
void ElectricCable::calc_() {
    auto* actor = mActor;
    if (actor && _50) {
        // discarded calls: both results are unused in the original
        if (!isCurrentChild("Wait"))
            isCurrentChild("Energized");

        const s32 num_points = _50->getNumPoints();
        sead::Vector3f prev = _50->getPointTranslate(0);
        auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr();
        sead::Matrix34f prev_mtx;
        actor->getHomeMtx(&prev_mtx);
        sead::Matrix34f mtx;
        mtx.makeT(prev);
        if (mgr) {
            mtx = mgr->getTransformedMatrix(actor->getFieldBodyGroup(), mtx);
            mtx.getTranslation(prev);
        }
        prev_mtx.setTranslation(prev);

        sead::Vector3f closest_start = sead::Vector3f::zero;
        sead::Vector3f closest_end = sead::Vector3f::zero;
        f32 min_distance = std::numeric_limits<f32>::max();
        for (s32 i = 1; i < num_points; ++i) {
            sead::Vector3f cur = _50->getPointTranslate(i);
            sead::Matrix34f cur_mtx;
            actor->getHomeMtx(&cur_mtx);
            sead::Matrix34f point_mtx;
            point_mtx.makeT(cur);
            if (mgr) {
                point_mtx = mgr->getTransformedMatrix(actor->getFieldBodyGroup(), point_mtx);
                point_mtx.getTranslation(cur);
            }
            cur_mtx.setTranslation(cur);

            if (i == 1) {
                if (auto* body = actor->findPhysicsBodyByName("Chemical", "ElectricCable_0"))
                    body->changePositionAndRotation(prev_mtx, sead::Mathf::epsilon());
                _58 = prev;
            }
            if (i == num_points - 1) {
                if (auto* body = actor->findPhysicsBodyByName("Chemical", "ElectricCable_1"))
                    body->changePositionAndRotation(cur_mtx, sead::Mathf::epsilon());
                _64 = cur;
            }

            f32 distance = std::numeric_limits<f32>::max();
            if (auto* listener_mgr = aal::SystemAccessor::getListenerMgr()) {
                if (auto* listener = listener_mgr->getListener(0)) {
                    const sead::Vector3f listener_pos = listener->getMatrix().getTranslation();
                    f32 t;
                    distance = sead::Geometry::calcSquaredDistancePointToSegment(
                        listener_pos, sead::Segment3f(prev, cur), &t);
                }
            }
            if (distance < min_distance) {
                min_distance = distance;
                closest_start = prev;
                closest_end = cur;
            }
            prev = cur;
        }

        if (_70) {
            _70->setPosition(closest_start);
            _70->setVector(closest_end - closest_start);
        }
    }

    const bool energized = (_40 && _40->_1b8 > 0.0f) || (_48 && _48->_1b8 > 0.0f);

    if (*mIsDisplayOnUI_m) {
        ElectricCableUiInfo info;
        info.start = _58;
        info.center = (_64 + _58) * 0.5f;
        info.end = _64;
        info.energized = energized;
        info.actor = actor;
        ui::sub_7100A9D2B0(&info);
    }

    auto* child = getCurrentChild();
    if (energized) {
        if ((child->isChangeable() || child->isFinished() || child->isFailed()) &&
            isCurrentChild("Wait")) {
            changeChild("Energized");
            auto handle = ksys::eft::searchAndEmitSLink(mActor, "On", false);
            if (handle.isActive()) {
                if (auto* executor =
                        static_cast<xlink2::EventSLink*>(handle.getEvent())->getAliveAssetExecutor()) {
                    if (auto* source = executor->getHandle()->getSoundSource()) {
                        if (_70)
                            source->mSpatialSetting.setShape(_70);
                    }
                }
            }
        }
    } else if ((child->isChangeable() || child->isFinished() || child->isFailed()) &&
               !isCurrentChild("Wait")) {
        changeChild("Wait");
    }
}

void ElectricCable::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ElectricCable::loadParams_() {
    getMapUnitParam(&mIsDisplayOnUI_m, "IsDisplayOnUI");
}

}  // namespace uking::ai
