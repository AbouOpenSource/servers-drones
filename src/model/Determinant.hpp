#ifndef DRONEPROJECT_DETERMINANT_HPP
#define DRONEPROJECT_DETERMINANT_HPP

class Matrix33;
class Matrix44;

class Matrix22
{

public:
    float m[2][2];

    void get2x2From3x3(const Matrix33 &mat33,int shadowLin, int shadowCol);

    float determinant();
};

class Matrix33
{

public:
    float m[3][3];

    void get3x3From4x4(const Matrix44 &mat44,int shadowLin, int shadowCol);

    float determinant();
};

class Matrix44
{

public:
    float m[4][4];

    float determinant();
};

#endif //DRONEPROJECT_DETERMINANT_HPP
