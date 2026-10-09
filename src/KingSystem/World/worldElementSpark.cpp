#include "KingSystem/World/worldElementSpark.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

ElementSpark* sub_71010C30E8(const ElementSparkCreateArg* arg) {
    auto* holder = Manager::instance()->getChemicalMgr()->_ae8;
    if (holder)
        return holder->sub_71010C74A0(arg);
    return nullptr;
}

}  // namespace ksys::world
