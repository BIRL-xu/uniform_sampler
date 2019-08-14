//
// Created by baulxu on 19-8-9.
//

#ifndef UNIFORMSAMPLER_UNIFORM_SAMPLER_H
#define UNIFORMSAMPLER_UNIFORM_SAMPLER_H

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<iomanip>
#include <cmath>

#define DEBUG_MODE
#define DEGREE2RADIAN 3.141592653/180.0

using namespace std;

struct Pose{
    double x = 0.0;
    double y = 0.0;
    double theta = 0.0; // [-pi, pi]
};

/*
 * @brief This class samples uniformly N pose in a circular range.
 *
 */

class UniformSampler{
public:
    UniformSampler(
            const unsigned int n,
            const double inner_radius,
            const double outer_radius,
            const double theta_uncertainty,
            const Pose& base_pose);
    ~UniformSampler();
    Pose getRandomPose() const;

private:
    const double randomRadius() const;
    const double randomTheta() const;



    struct Pose base_pose_;
    unsigned int N_ = 0;
    double inner_radius_ = 0.0;
    double outer_radius_ = 0.0;
    double theta_uncertainty_;  // radian


};


#endif //UNIFORMSAMPLER_UNIFORM_SAMPLER_H
