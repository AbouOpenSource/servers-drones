//
// Created by Maanrifa Bacar Ali on 23/01/2020.
//

#ifndef DRONEPROJECT_TEXTUREVIEW_HPP
#define DRONEPROJECT_TEXTUREVIEW_HPP


#include "View.hpp"

class TextureView: public View
{

public:

    void init(DrawHelper *draw_helper, ServiceContainer *service_container) override;

    void draw(DrawHelper* draw_helper) override;

    void start() override;

    void quit() override;

protected:

    explicit TextureView(const std::string& file_name);

    int texture_id_;
    int texture_width_;
    int texture_height_;

private:

    std::string file_name_;
};


#endif //DRONEPROJECT_TEXTUREVIEW_HPP
