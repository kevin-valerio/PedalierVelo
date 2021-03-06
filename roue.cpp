#include "roue.h"
#include <stdio.h>
#include <iostream>

#include <GL/glu.h>

#include <math.h>       /* cos */
#include <QVector3D>
#include <QMatrix4x4>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#define PI 3.14159265

Roue::Roue(double ep_cyl, double r_cyl, double nb_dents, float coul_r, float coul_v, float coul_b){
    this->ep_cyl = ep_cyl;
    this->r_cyl = r_cyl;
    this->nb_dents = nb_dents;

    this->coul_v = coul_v;
    this->coul_b = coul_b;
    this->coul_r = coul_r;

    initPoints();
}

void Roue::initPoints(){
    GLfloat alpha = 360/nb_dents;
    nbPtsFace = 16;
    nbPtsFacette = 16;
    this->vertices = new GLfloat[nbPtsFace*3 + nbPtsFacette*3];
    this->colors = new GLfloat[nbPtsFace*3 + nbPtsFacette*3];

    QVector3D A = getVertex(0, 0, ep_cyl/2);//QVector3D(0,0,ep_cyl/2);
    QVector3D B = getVertex(0,r_cyl - h_dent/2, ep_cyl/2);//QVector3D(0,r_cyl - h_dent/2,-ep_cyl/2);

    QVector3D C = getVertex(alpha/4,r_cyl - h_dent/2, ep_cyl/2);//QVector3D(alpha/4,r_cyl - h_dent/2,ep_cyl/2);
    QVector3D D = getVertex((2*alpha)/4,r_cyl + h_dent/2, ep_cyl/2);//QVector3D((2*alpha)/4,r_roue + h_dent/2,-ep_cyl/2);

    QVector3D E = getVertex((3*alpha)/4, r_cyl + h_dent/2, ep_cyl/2);//QVector3D((2*alpha)/4,r_roue + h_dent/2,-ep_cyl/2);
    QVector3D F = getVertex(alpha, r_cyl - h_dent/2, ep_cyl/2);//QVector3D((2*alpha)/4,r_roue + h_dent/2,-ep_cyl/2);

    QVector3D G = getVertex(alpha, 0, ep_cyl/2);//QVector3D((2*alpha)/4,r_roue + h_dent/2,-ep_cyl/2);
    QVector3D H = getVertex((2*alpha)/4, 0, ep_cyl/2);//QVector3D((2*alpha)/4,r_roue + h_dent/2,-ep_cyl/2);


    QVector3D Ap = A;
    QVector3D Bp = B;
    QVector3D Cp = C;
    QVector3D Dp = D;
    QVector3D Ep = E;
    QVector3D Fp = F;
    QVector3D Gp = G;
    QVector3D Hp = H;

    Ap.setZ(-ep_cyl/2);
    Bp.setZ(-ep_cyl/2);
    Cp.setZ(-ep_cyl/2);
    Dp.setZ(-ep_cyl/2);
    Ep.setZ(-ep_cyl/2);
    Fp.setZ(-ep_cyl/2);
    Gp.setZ(-ep_cyl/2);
    Hp.setZ(-ep_cyl/2);

    QVector3D color = QVector3D(coul_r, coul_v, coul_b);

    setColors(color);

    addVertice(A);
    addVertice(B);
    addVertice(C);
    addVertice(D);
    addVertice(E);
    addVertice(F);
    addVertice(G);
    addVertice(H);

    addVertice(Ap);
    addVertice(Bp);
    addVertice(Cp);
    addVertice(Dp);
    addVertice(Ep);
    addVertice(Fp);
    addVertice(Gp);
    addVertice(Hp);


    addVertice(B);
    addVertice(C);
    addVertice(Cp);
    addVertice(Bp);

    addVertice(C);
    addVertice(D);
    addVertice(Dp);
    addVertice(Cp);

    addVertice(D);
    addVertice(E);
    addVertice(Ep);
    addVertice(Dp);

    addVertice(E);
    addVertice(F);
    addVertice(Fp);
    addVertice(Ep);
}

void Roue::draw(QOpenGLShaderProgram *m_program, QMatrix4x4 matrix, int m_matrixUniform){
    double angle = 360/nb_dents;
    for (int i = 0; i<nb_dents; i++){
        matrix.rotate(angle, 0, 0, 1);
        m_program->setUniformValue(m_matrixUniform, matrix);
        drawBlock();
    }
}

void Roue::drawBlock(){
    glDrawArrays(GL_POLYGON, 0, nbPtsFace/2);
    glDrawArrays(GL_POLYGON, nbPtsFace/2, nbPtsFace/2);
    glDrawArrays(GL_QUADS, nbPtsFacette, nbPtsFacette);
}

QVector3D Roue::getVertex(float o, float h, float z){
    GLfloat y = sin(o*PI/180)*h;
    GLfloat x = cos(o*PI/180)*h;
    return QVector3D(x, y, z);
}


