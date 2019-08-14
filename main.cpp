#include "uniform_sampler.h"
#include <yaml-cpp/yaml.h>

using namespace std;
//计算机的随机数都是由伪随机数，即是由小M多项式序列生成的，
//其中产生每个小序列都有一个初始值，即随机种子。
//（注意： 小M多项式序列的周期是65535，
//即每次利用一个随机种子生成的随机数的周期是65535，
//当你取得65535个随机数后它们又重复出现了。）
//
//c++/c的随机函数 rand() 与srand()
//
//rand()和srand()，所在的头文件是stdlib.h
//
//srand(unsigned int seed)用来初始化随机数发生器，
//设置rand()产生随机数时的随机数种子，rand()函数用来做随机数发生器，
//返回在[0,RAND_MAX )间的均匀分布的随机数，其中RAND_MAX是系统设置值。
//
//若seed值相同，则rand()每次产生的伪随机数序列就相同。用户未设定随机数种子时，
//系统默认的随机数种子为1。因此一般使用系统时间作为随机数种子，则每一次运行程序所得到的序列都不相同。

int main(int argc, char* argv[])
{
/*
    if(argc != (1+4)){
        cout << "Input error!" << endl;
        cout << "Usage: " << endl;
        cout << "./uniformsampler N innter_radius outer_radius theta_uncertainty(degree)" << endl;
        return -1;
    }
    cout << "N = " << atoi(argv[1]) << endl;
    cout << "inner_radius = " << atof(argv[2]) << endl;
    cout << "outer_radius = " << atof(argv[3]) << endl;
    cout << "theta_uncertianty = " << atof(argv[4]) << "(degree)"<< endl;

    UniformSampler sampler(
            atoi(argv[1]), */
/*Number wanted to sample uniformly*//*

            atof(argv[2]), */
/*innter radius (m)*//*

            atof(argv[3]), */
/*outer radius (m)*//*

            atof(argv[4]));*/
/*Uncertainty of theta in degree*//*


    for(int i = 0; i < atoi(argv[1]); ++i){
       Pose pose = sampler.getRandomPose();
//
//       cout << "r = " << r << endl;
//       cout << "theta = " << theta << endl;
       cout << "pose = {" << pose.x << ", " << pose.y << ", " << pose.theta << "}." << endl;
   }
*/

    YAML::Node config = YAML::LoadFile("../config.yaml");
    if(config["N"] &&
        config["inner_radius"] &&
        config["outer_radius"] &&
        config["theta_uncertainty"] &&
        config["pose"]["x"] &&
        config["pose"]["y"] &&
        config["pose"]["theta"]){

        cout << "N = " << config["N"].as<int>() << endl;
        const unsigned int num_samples = config["N"].as<int>();
        const double inner_radius = config["inner_radius"].as<double>();
        const double outer_radius = config["outer_radius"].as<double>();
        const double theta_uncertainty = config["theta_uncertainty"].as<double>();
        const struct Pose base_pose = {config["pose"]["x"].as<double>(),
                                          config["pose"]["y"].as<double>(),
                                          config["pose"]["theta"].as<double>()};
#ifdef DEBUG_MODE
        cout << "num_samples = " << num_samples << endl;
        cout << "inner_radius = " << inner_radius << endl;
        cout << "outer_radius = " << outer_radius << endl;
        cout << "theta_uncertainty = " << theta_uncertainty << endl;
        cout << "base_pose = {" << base_pose.x << ", " << base_pose.y << ", " << base_pose.theta << "}" << endl;
#endif

        for(int i = 0; i < num_samples; ++i){
            UniformSampler sampler(num_samples,
                    inner_radius,
                    outer_radius,
                    theta_uncertainty,
                    base_pose);
            Pose pose = sampler.getRandomPose();

            cout << "pose = {" << pose.x << ", " << pose.y << ", " << pose.theta << "}." << endl;
        }

    } else{
        cout << "[ERROR]-Read configuration file error!" << endl;
        return -1;
    }


    return 0;
}