#include "KingSystem/System/UI/ArcResource.h"
#include "KingSystem/System/UI/ArcResourceMgr.h"

namespace ksys::ui {

// 0x710109d814
ArcResource::ArcResource(ArcResourceMgr* mgr, const sead::SafeString& name, u8* data,
                         res::Handle* handle)
    : eui::ArcResourceMgr::ArcResource(mgr, name, data), mHandle(handle) {}

}  // namespace ksys::ui
