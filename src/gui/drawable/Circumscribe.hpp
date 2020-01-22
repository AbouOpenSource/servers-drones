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

    explicit Circumscribe(std::vector<Server>& servers);

    void init(InputManager* input_manager, EventManager* event_manager, TextureLoader texture_loader) override;

    void start() override;

    void draw() const override;

private:

    std::array<Vector2D, 5> vertices_;
    std::array<Triangle*, 3> tris_{};

    Mesh* mesh_{};

    std::vector<Server> servers_;

};


#endif //DRONEPROJECT_CIRCUMSCRIBE_HPP
