#include "Game/Actor/Action/actionSiteBossCreateIceSplinter.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SiteBossCreateIceSplinter::SiteBossCreateIceSplinter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossCreateIceSplinter::~SiteBossCreateIceSplinter() = default;

bool SiteBossCreateIceSplinter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossCreateIceSplinter::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    _38 = false;
    _44[1] = 0;
}

void SiteBossCreateIceSplinter::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossCreateIceSplinter::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIgnitionNum_d, "IgnitionNum");
}

bool SiteBossCreateIceSplinter::isFinished() const {
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true) ||
        ksys::act::ai::ActionBase::isFinished()) {
        return true;
    }
    return isFinishedAS(0, 0);
}

// NON_MATCHING: native fixed-index ignition checks remain a range loop.
void SiteBossCreateIceSplinter::calc_() {
    if (sub_71005DD780(mActor, 69, nullptr, 0, 0))
        _38 = true;
    if (_38) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            s32 first;
            s32 end;
            const s32 ignition_num = *mIgnitionNum_d;
            switch (ignition_num) {
            case 1:
                first = 0;
                end = 1;
                break;
            case 3:
                first = 1;
                end = 4;
                break;
            case 5:
                first = 4;
                end = 9;
                break;
            default:
                first = end = 0;
                break;
            }
            for (s32 i = first; i < end; ++i) {
                if (_44[1] & (1 << i))
                    continue;
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&boss->_1560._1e0[i], &accessor);
                if (!accessor.isStateCalc()) {
                    boss->_1560.sub_710066D708(i);
                    _44[1] |= 1 << i;
                    return;
                }
            }
            if (ignition_num == 1 && (_44[1] & 1))
                return;
        }
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
