#include "KingSystem/Event/evtS7.h"
#include <evfl/Param.h>
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "Game/gameRoot38.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUI.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::evt {

const char* sub_71008B84F0(s32 state);

// 0x71008afc2c
S7EventFlow::~S7EventFlow() {
    if (_50) {
        if (_50->_22_0 & 2) {
            if (_50->mAdded)
                _50->sub_7101088B24(tera::System::instance(), false);
            _50->sub_71010887CC();
        }
        _50->sub_710108872C();
        delete _50;
        _50 = nullptr;
    }
}

// 0x71008afb38
void S7EventFlow::m4() {
    mState = 1;
    _24 = 0;
    _28 = 0;
    mStatus.copy(sub_71008B84F0(1));
    _28 = 0;
    _2c = -1;
    _30 = 0;
    _1c = 0;
    _38 = 0;
    _3c = -1;
    _64 = -1;
    _68 = 0;
    _40 = false;
    _48 = 0;
    sub_71008AF278();
}

// 0x71008b84e0 (CSV evt::S7EventFlow::isPlaying)
bool S7EventFlow::isPlaying() {
    return mState == 3;
}

// NON_MATCHING: stack layout only (the original reuses the type spill slot for `entry`; frame 0x10 smaller)
// 0x71008b53f0: emits the xlink entries of the event resource on the event's actors
void S7EventFlow::x(bool a1) {
    if (int(mFlow->getType()) == EventFlowType::MovieWithNoPath)
        return;
    const auto* info = mFlow->_108->_1b8;
    if (!info)
        return;
    for (s32 i = 0; i < info->_28.size(); ++i) {
        auto* set = mFlow->_110;
        if (!set)
            continue;
        const sead::SafeString entry = info->sub_7100DCA244(i).cstr();
        if (entry.isEmpty())
            continue;
        const sead::SafeString name = info->sub_7100DCA228(i).cstr();
        auto* actor = set->sub_7100DA2A28(name, entry);
        if (!actor)
            continue;
        auto* proc = sead::DynamicCast<act::Actor>(actor->mLink.getProc(nullptr));
        if (!proc)
            continue;
        if (auto* xlink = proc->getXLink())
            xlink->sub_71012345B4(info->sub_7100DCA264(i).cstr(), a1);
    }
}

// 0x71008b6748
// NON_MATCHING: only the int-conversion spill slot differs (original reuses [sp, #0x8], later reused
// by the accessor; ours uses a separate top-of-frame slot). Tried switch-on-member, switch-on-getType
// (matches in m9), if with !=, by-value local, and orderings - the spill address is the only diff.
void S7EventFlow::setup_1() {
    mFlow->getBaseProcLink();
    if (int(mFlow->getType()) != EventFlowType::MovieWithNoPath) {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        Manager::instance()->sub_7100DB0FB0(*accessor.getMessageTransceiverId(),
                                            MessageType(0x80000b2), nullptr);
        uking::ui::UI* ui = uking::ui::UI::instance();
        if (ui)
            ui->x_0(false);
        EventSystem::instance()->_144 &= ~1;
    }
}
// 0x71008afcdc
bool S7EventFlow::calc() {
    const u32 result = calc_();
    if (_14 & 2)
        uking::sub_7100F41834();
    if (_3c >= 0) {
        if (_3c == 0) {
            phys::System::instance()->sub_71012167EC(false);
            _3c = -1;
        } else {
            _3c += 1;
        }
    }
    return result & 1;
}

// 0x71008b2eb4
void S7EventFlow::m9() {
    setupDemoOverrides(true);
    switch (mFlow->getType()) {
    case EventFlowType::MovieWithNoPath:
        break;
    default:
        mFlow->x_6();
        _1c |= 0x80;
        if (mFlow->_340_bytes[3] & 2) {
            if (uking::ui::UiSubsys1::instance()->sub_71008B43CC()) {
                _1c |= 0x10000;
                uking::ui::UiSubsys1::instance()->set4cc(true);
            }
        }
        break;
    }
    setup_1_1();
    x(0);
}

// 0x71008b8118
void S7EventFlow::sub_71008B8118(evfl::MetaDataPack* pack, const sead::Matrix34f& mtx) {
    sead::Vector3f axis_y;
    mtx.getBase(axis_y, 1);
    sead::Vector3f axis_z;
    mtx.getBase(axis_z, 2);
    sead::Vector3f pos;
    mtx.getTranslation(pos);
    pack->AddFloat("arg_TargetPosX", pos.x);
    pack->AddFloat("arg_TargetPosY", pos.y);
    pack->AddFloat("arg_TargetPosZ", pos.z);
    pack->AddFloat("arg_TargetMatrixY_x", axis_y.x);
    pack->AddFloat("arg_TargetMatrixY_y", axis_y.y);
    pack->AddFloat("arg_TargetMatrixY_z", axis_y.z);
    pack->AddFloat("arg_TargetMatrixZ_x", axis_z.x);
    pack->AddFloat("arg_TargetMatrixZ_y", axis_z.y);
    pack->AddFloat("arg_TargetMatrixZ_z", axis_z.z);
}

// 0x71008b8218
// NON_MATCHING: the original keeps the destination y in a general register (x and z in float registers)
void S7EventFlow::addPhysicsParams(evfl::MetaDataPack* pack, const sead::Matrix34f& mtx, s32 group_index) {
    pack->AddInt("Arg_FieldBodyGroupIndex", group_index);
    sead::Vector3f pos = mtx.getTranslation();
    {
        phys::RayCastBodyQuery query(nullptr, phys::GroundHit::HitAll);
        sead::Vector3f start(pos.x, pos.y + 5.0f, pos.z);
        const sead::Vector3f end(pos.x, pos.y - 5.0f, pos.z);
        query.setStartAndEnd(start, end);
        query.enableLayer(phys::ContactLayer::EntityGround);
        query.enableLayer(phys::ContactLayer::EntityGroundRough);
        query.enableLayer(phys::ContactLayer::EntityGroundObject);
        if (query.worldRayCast(phys::ContactLayerType::Entity)) {
            query.getHitPosition(&start);
            pos.y = start.y;
        }
    }
    pack->AddFloat("Arg_DestinationX", pos.x);
    pack->AddFloat("Arg_DestinationY", pos.y);
    pack->AddFloat("Arg_DestinationZ", pos.z);
    pack->AddFloat("Arg_DestinationDirY", sead::Mathf::rad2deg(sead::Mathf::atan2(mtx(0, 2), mtx(2, 2))));
}

// 0x71008b6f20 (CSV evt::S7EventFlow::getStatusStr)
const char* S7EventFlow::m7() {
    return mStatus.cstr();
}

// 0x71008b59c8
void S7EventFlow::setTimeAndWeather() {
    const DemoInfo& demo = mFlow->_108->mDemoInfo;
    if (!demo.isValid())
        return;
    auto* world = world::Manager::instance();
    if (!world || !world->getTimeMgr())
        return;
    if (demo.getTime() >= 0.0f)
        world->getTimeMgr()->setTimeWithoutDayChecks(demo.getTime() * 15.0f);
    if (!demo.getWeather().isEmpty()) {
        const sead::SafeString weather = demo.getWeather();
        world->setWeatherType(weather, false, false, true);
    }
}

}  // namespace ksys::evt

