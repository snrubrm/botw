#include "Game/AI/Action/actionSiteBossCreateChildDevice.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

SiteBossCreateChildDevice::SiteBossCreateChildDevice(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossCreateChildDevice::~SiteBossCreateChildDevice() = default;

bool SiteBossCreateChildDevice::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossCreateChildDevice::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _40 = 0;
    _41 = false;
    _42 = false;
    if (!actor->get1a0() &&
        (!actor->getMapObject() ||
         !actor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000)))
        sub_71002583A4();
    _44 = m32();
    _48 = ksys::Timer(30.0f, 30.0f);
}

void SiteBossCreateChildDevice::leave_() {
    mActor->getASList()->sub_710115B01C(3, 0, true);
    mActor->getASList()->sub_710115B01C(4, 0, true);
    mActor->getASList()->sub_710115B01C(5, 0, true);
    mActor->getASList()->sub_710115B01C(6, 0, true);
    mActor->getASList()->sub_710115C11C();
    if (_41)
        return;

    auto* target = sub_71005D9050(mActor);
    if (!target || !target->hasProcInCalcState())
        return;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066C518(target, 20);
}

void SiteBossCreateChildDevice::loadParams_() {
    getDynamicParam(&mIsCreateA_d, "IsCreateA");
    getDynamicParam(&mIsCreateB_d, "IsCreateB");
    getDynamicParam(&mIsCreateC_d, "IsCreateC");
    getDynamicParam(&mIsCreateD_d, "IsCreateD");
}

// NON_MATCHING: the original does not jump-thread the `!created && _44 == 0` test after the early-out assignment
// (created = false, _44 = 0) and keeps `&boss->_1560` in a register across the first loop; ours threads it
void SiteBossCreateChildDevice::calc_() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return;

    if (_40 == 0) {
        bool created = false;
        for (int i = 0; i < 20; i++) {
            const u32 bit = 1u << i;
            if (!(_44 & bit))
                continue;
            u32 flags = boss->_1560._9c;
            if (!(flags & bit)) {
                if (!boss->_1560._1e0[i].hasProcInCalcState())
                    continue;
                flags = boss->_1560._9c;
            }
            boss->_1560._9c = flags & ~bit;
            created = true;
            _44 &= ~bit;
        }

        _48.update();
        if (_48.value <= sead::Mathf::epsilon() || mActor->get1a0() ||
            (mActor->getMapObject() &&
             mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
            created = false;
            _44 = 0;
        }

        if (!created && _44 == 0) {
            _40 = 1;
            auto* target = sub_71005D9050(mActor);
            if (target && target->hasProcInCalcState()) {
                const u32 mask = m32();
                for (u32 i = 0; i < 20; i++) {
                    if (mask & (1u << i)) {
                        boss->_1560.sub_710066D9B8(i);
                        boss->_1560.sub_710066C13C(target, i);
                    }
                }
            }
            playAS("Reflector_Appear", false, 0, 0, -1.0f);
            if (auto* boss2 = sead::DynamicCast<act::SiteBoss>(mActor))
                boss2->_1558.reset(0x20000);
        }
    } else {
        if (sub_71005DD780(mActor, 0x47, nullptr, 0, 0)) {
            _41 = true;
            auto* target = sub_71005D9050(mActor);
            if (target && target->hasProcInCalcState())
                boss->_1560.sub_710066C518(target, 20);
        }
        if (!isFinishedAS(0, 0)) {
            if (!_42)
                return;
        } else if (!_42) {
            playAS("Wait", false, 0, 0, -1.0f);
            _42 = true;
            _48 = ksys::Timer(30.0f, 30.0f);
        }
        _48.update();
        if (_48.value <= sead::Mathf::epsilon())
            setFinished();
    }
}

int SiteBossCreateChildDevice::m32() {
    return (*mIsCreateA_d ? 1 : 0) | (*mIsCreateB_d ? 2 : 0) | (*mIsCreateC_d ? 4 : 0) | (*mIsCreateD_d ? 8 : 0);
}

}  // namespace uking::action
