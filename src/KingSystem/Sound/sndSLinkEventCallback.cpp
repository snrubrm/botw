// The TU at 0x71012ceb94 .. 0x71012cedd8: the SLink event callback of SoundMgr::_70 (Unk_710251b730), with the
// static initialiser 0x71012ceda4.
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndSoundAttenuationMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::snd {

void Unk_710251b730::sub_71012CEBC0(sead::Heap* heap) {}

void Unk_710251b730::eventActivated(const EventArg& arg) {
    auto* xlink = eft::sub_710105E100(arg.pUserInstance);
    if (!xlink || !xlink->mActor)
        return;
    if (!xlink->mActor->m129() && !xlink->_cc.isOnBit(6))
        return;
    if (!arg.pEvent)
        return;

    xlink2::HandleSLink handle;
    handle.setResource(arg.pEvent);
    handle.setCreateId(arg.pEvent->getCreateId());
    ExpressionSoundCtrl::instance()->sub_710104FA78(handle);
}

u32 Unk_710251b730::soundPrePlay(const EventArg& arg) {
    auto* xlink = eft::sub_710105E100(arg.pUserInstance);
    if (xlink && xlink->sub_71012342F8()) {
        const sead::SafeString group =
            arg.pUserInstance->getResourceAccessor().getGroupName(*arg.pAssetCallTable);
        if (group.findIndex("Voice") != -1)
            return 1;
    }
    return 0;
}

void Unk_710251b730::soundPlayed(const EventArg& arg) {
    const auto& accessor = arg.pUserInstance->getResourceAccessor();
    if (!accessor.isLoopAsset(*arg.pAssetCallTable))
        return;
    if (sead::SafeString(accessor.getCustomParamValueString(3, *arg.pAssetCallTable)).isEmpty())
        return;

    auto* xlink = eft::sub_710105E100(arg.pUserInstance);
    if (!xlink || !xlink->_cc.isOnBit(7))
        return;
    if (arg.pAssetExecutor)
        arg.pAssetExecutor->requestReEmit(true);
}

namespace {
util::InitConstants sInitConstants;
util::InitTimeInfo sInitTimeInfo;
}  // namespace

}  // namespace ksys::snd
