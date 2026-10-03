#include "Game/AI/AI/aiAirOctaRoot.h"
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

AirOctaRoot::AirOctaRoot(const InitArg& arg) : Fork2AI(arg) {}

AirOctaRoot::~AirOctaRoot() {
    delete _40;
    _40 = nullptr;
}

bool AirOctaRoot::init_(sead::Heap* heap) {
    mActor->mDrawDistanceFlags.set(2);
    if (!Fork2AI::init_(heap))
        return false;
    _40 = new (heap, 8) AirOctaDataMgr;
    *static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a) = _40;
    return _40 != nullptr;
}

void AirOctaRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* mgr = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a)))
        mgr->sub_71002FAF84(mActor);
    Fork2AI::enter_(params);
}

bool AirOctaRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x80000c8) {
        auto* data = static_cast<AirOctaDataMgr::MessageData*>(message.getUserData());
        if (data && data->unk_00 == 1) {
            if (auto* mgr = sead::DynamicCast<AirOctaDataMgr>(*static_cast<Unk_71025afb58**>(mAirOctaDataMgr_a)))
                mgr->sub_71002FB1A8(data->unk_08);
        }
    }
    return Fork2AI::handleMessage_(message);
}

void AirOctaRoot::calc_() {}

void AirOctaRoot::leave_() {
    Fork2AI::leave_();
}

void AirOctaRoot::loadParams_() {
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
