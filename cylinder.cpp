#include "cylinder.h"

#include <Eigen/Dense>
#include <iostream>

std::tuple<double, double> Cylinder::intersectRay(Eigen::Vector3d O, Eigen::Vector3d D) {
    double a, b, c;
	double delta;
	double r = this->radius;
	double inf = std::numeric_limits<double>::infinity();

	Eigen::Vector3d w = O - this->getCenter();
    //Eigen::Matrix<double, 3, 3> M = Eigen::Matrix<double, 3, 3>::Identity() - dCil * dCil.transpose();

    a = D.transpose() * M * D;
    b = 2 * w.transpose() * M * D;
    c = (w.transpose() * M * w) - std::pow(radius, 2);

    delta = (b * b) - (4 * a * c);

    if (delta < 0) {
        return std::make_tuple(inf, inf);
    }


    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);

	double t = std::min(t1, t2);
	if (t < 0) {
		t = (t == t2) ? t = t1 : t = t2;
	}

    Eigen::Vector3d P_I;

    //Segunda verificação - Raio/Plano da base
    /*double tBase = -(O - center).dot(dCil) / (D.dot(dCil));
	P_I = O + tBase * D;
    if ((P_I - center).norm() > radius) {
        return std::make_tuple(inf, inf);
    }*/

    //Terceira verificação - Raio/Plano do topo
    /*Eigen::Vector3d Ct = center + height * dCil;
	
    double tTop = -(O-Ct).dot(dCil) / (D.dot(dCil));
	P_I = O + tTop * D;
    if ((P_I - Ct).norm() > radius) {
        return std::make_tuple(inf, inf);
    }*/

    //Primeira verificação - Raio/Superfície
    P_I = O + t * D;
    double tSurface = (P_I - center).dot(dCil);

    if (tSurface <= 0 || tSurface > height) {
        return std::make_tuple(inf, inf);
    }

    //tTop tBase tSurface

	t = std::min(t1, t2);
	if (t < 0) {
		t = (t == t2) ? t = t1 : t = t2;
	}

    return std::make_tuple(t1, t2);
}

double Cylinder::getRadius() {
    return radius;
}

Eigen::Vector3d Cylinder::getCenter() {
    return center;
}

Eigen::Vector3d Cylinder::getNormal(Eigen::Vector3d P_I) {
    Eigen::Vector3d n = M * (P_I - center);
    return n / n.norm();
}