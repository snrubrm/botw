#pragma once

namespace aal {

class Shape;

/// Keeps track of all the live shapes (they register in `Shape::create` and unregister in `Shape::destroy`).
class ShapeMgr {
public:
    void addShape(Shape* shape);
    void removeShape(Shape* shape);
};

}  // namespace aal
