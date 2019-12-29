#include <iostream>
#include <cstdlib>
#include "glutWindow.h"

using namespace std;

class Example: public GlutWindow {
public:
    static const int n=20;
    int tab[n];
    int orderedTab[n];

    Example(const string &title,int argc,char **argv):GlutWindow(argc,argv,title,820,150,FIXED) {};
    void initArrays();
    void sort();

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
    void onMouseDown(int button,double cx,double cy) override;
};

void Example::initArrays() {
    // fill the tab array with 20 different random values between 0 and 99
    for(int i=0; i<n; i++) {
        int v,j;
        do {
            v = std::rand()%100;
            j =0;
            while (j<i && tab[j]!=v) {
                j++;
            }
        } while (j<i);
        tab[i]=v;
    }

}

void Example::sort() {
    orderedTab[0]=tab[0];
    int otsize=1;
    for (int i=1; i<n; i++) {
        int j=0;
        while (j<otsize && orderedTab[j]<tab[i]) {
            j++;
        }
        for (int k = otsize; k > j; k--) {
            orderedTab[k] = orderedTab[k - 1];
        }
        orderedTab[j]=tab[i];
        otsize++;
    }
}

void Example::onStart() {
    cout << "Start..."  << endl;
    glClearColor(0.25,0.25,0.25,1.0);
    initArrays();
    sort();
}

void Example::onQuit() {
    cout << "The end."  << endl;
}

void Example::onDraw() {
    glPushMatrix();

    for (int i=0; i<20; i++) {
        glColor3f(0.0f,0.0f,0.0f);
        box(10, 10, 40, 80);
        glColor3f(1.0f,1.0f,1.0f);
        box(10, 90, 40, 40);
        rect(10, 10, 40, 40);
        rect(10, 50, 40, 40);

        drawText(30,60,to_string(tab[i]),ALIGN_CENTER);

        drawText(30,20,to_string(orderedTab[i]),ALIGN_CENTER);

        glColor3f(0.0f,0.0f,0.0f);
        rect(10, 90, 40, 40);
        drawText(30,100,to_string(i),ALIGN_CENTER);

        glTranslated(40,0.0,0.0);
    }
    glPopMatrix();
}

void Example::onMouseMove(double cx,double cy) {
    cout << cx << "," << cy << endl;
}

void Example::onMouseDown(int button, double cx, double cy) {
    initArrays();
    sort();
}

int main(int argc,char **argv) {
    Example ex("GLUT 2D tutorial", argc,argv);
    ex.start();
    return 0;
}
