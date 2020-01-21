//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_CIRCUMSCRIBE_HPP
#define DRONEPROJECT_CIRCUMSCRIBE_HPP


#include <array>
#include "Drawable.hpp"
#include "../../model/Triangle.hpp"
#include "../../model/Mesh.hpp"

class Circumscribe: public Drawable
{

public:

    void start(InputManager* input_manager) override;

    void draw() const override;

    Circumscribe();

private:

    std::array<Vector2D, 5> vertices_;
    std::array<Triangle*, 3> tris_{};
    Mesh* mesh_{};

};


#endif //DRONEPROJECT_CIRCUMSCRIBE_HPP