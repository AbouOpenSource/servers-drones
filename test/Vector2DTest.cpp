//
// Created by abou on 19/12/2019.
//

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <catch2/catch.hpp>
#include "../src/model/Vector2D.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

TEST_CASE("The  creation test","[creation]"){
    Vector2D first = new Vector2D(10,20);
    Vector2D second = new Vector2D(1,3);
    Vector2D somme = first+second;
    float_t produit = first*second;
    bool sommeTest;
    somme.getAxisX() == Vector2D(11,23).getAxisX() && somme.getAxisY()==Vector2D(11,23).getAxisY()?sommeTest= true:sommeTest= false;

    bool produitTest;



    REQUIRE(sommeTest);
    REQUIRE(produit == 70);



}