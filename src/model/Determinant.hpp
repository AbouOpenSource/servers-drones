#ifndef DRONEPROJECT_DETERMINANT_HPP
#define DRONEPROJECT_DETERMINANT_HPP

class Matrix33;
class Matrix44;

class Matrix22
{

public:
    float m[2][2];

    /**
     * @brief filled the m variable from a 3*3 matrix.
     * @param mat33 the 3*3 matrix
     * @param shadowLin
     * @param shadowCol
     */
    void get2x2From3x3(const Matrix33 &mat33, int shadowLin, int shadowCol);

    /**
     * @brief compute the determinant of the matrix.
     * @return the determinant of the matrix
     */
    float determinant();
};

class Matrix33
{

public:
    float m[3][3];

    /**
    * @brief filled the m variable from a 4*4 matrix.
    * @param mat44 the 4*4 matrix.
    * @param shadowLin
    * @param shadowCol
    */
    void get3x3From4x4(const Matrix44 &mat44, int shadowLin, int shadowCol);

    /**
     * @brief compute the determinant of the matrix.
     * @return the determinant of the matrix
     */
    float determinant();
};

class Matrix44
{

public:
    float m[4][4];

    /**
     * @brief compute the determinant of the matrix.
     * @return the determinant of the matrix
     */
    float determinant();
};

#endif //DRONEPROJECT_DETERMINANT_HPP
