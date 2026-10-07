#pragma once

namespace sead {
class Heap;
}

namespace ksys::tera {

// TODO:
class ApertureMaps {
    void updateMap();
};
class ApertureMapsCollector {
    void allocateImage();
    void releaseImage();
};
class Core {
    class Grass;
    class Model;
    class Tree;
};
class ImageResourceMgr {
    void procUnloadResidualRequest();
};
class ResourceHolder;
class Scene {
    void exportFileBinary();
};
class System {
public:
    static System* instance();
    void sub_710111F518(int level, int type);
    void sub_7101112A74();
    void allocateApertureMapsCollectorImage(sead::Heap* heap);
    void loadScene();
};
class Water {
    void setUpAttributeTable();
};

bool checkTeraSystemStatus();

// 0x71011190c8 (declaration only; placeholder name and signature): called by map::PlacementMapMgr::postPlaceActorsRouteStuff with
// the tera system and every route of every map.
void sub_71011190C8(void* tera_system, void* route);

}  // namespace ksys::tera
