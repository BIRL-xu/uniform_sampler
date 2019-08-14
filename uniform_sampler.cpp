//
// Created by baulxu on 19-8-9.
//

#include "uniform_sampler.h"



UniformSampler::UniformSampler(
        const unsigned int n,
        const double inner_radius,
        const double outer_radius,
        const double theta_uncertainty,
        const Pose& base_pose):
        N_(n),
        inner_radius_(inner_radius),
        outer_radius_(outer_radius),
        theta_uncertainty_(theta_uncertainty*DEGREE2RADIAN),
        base_pose_(base_pose){

    // seed
    srand( (unsigned)time(NULL) );
}

UniformSampler::~UniformSampler() {

}



const double UniformSampler::randomRadius() const {
    if(outer_radius_ < inner_radius_){
        cout << "outer radius must bigger than inner radius." << endl;
        return -1.0;
    }

    const double r = outer_radius_ - inner_radius_;
    double rnd = (double) rand()/RAND_MAX * (r - 0.001) + 0.001;
    if(rnd < 0.0 || rnd > r){
        cout << "Sample" << rnd << " is beyond the range: ["
        << 0.001 << ", " << rnd << "]." << endl;
    }

    return (rnd + inner_radius_);
}

const double UniformSampler::randomTheta() const {
    double rnd = (double)rand()/RAND_MAX * 2 * theta_uncertainty_ - theta_uncertainty_;
    if(rnd < -theta_uncertainty_ || rnd > theta_uncertainty_){
        cout << "Theta sample " << rnd << "is beyond range ["
        << -theta_uncertainty_ << "," << theta_uncertainty_ << "]." << endl;
    }

    return rnd;

}

/*
 * Create point uniformly relatives to (0,0)
 */

Pose UniformSampler::getRandomPose() const {
    const double radius = randomRadius();
    const double theta = randomTheta();
#ifdef DEBUG_MODE
    cout << "sample radius = " << radius << endl;
    cout << "sample theta = " << theta << endl;
#endif
    Pose sample_pose;
    sample_pose.x = base_pose_.x + radius * cos(theta);
    sample_pose.y = base_pose_.y + radius * sin(theta);
    sample_pose.theta = base_pose_.theta + theta;

    return sample_pose;
}

