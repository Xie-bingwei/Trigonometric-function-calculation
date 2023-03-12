#include "Trigonometric.h"

double Pow(double x, int n)
{
    double res = 1.0;
    for(int i = n; i != 0; i /= 2){
        if(i % 2 != 0){
            res *= x;
        }
        x *= x;
    }
    return  n < 0 ? 1 / res : res;
}

double sin_180(double direction)
{
    if(direction > 180)
        return -1;                                  

    double angle[13] = {45, 26.565, 14.036, 7.125, 3.5763,
                        1.7899, 0.8952, 0.4476, 0.22381,
                        0.1119, 0.0559, 0.028, 0.01399};		// 12 times
    double x=1;
    double y=0;
    double k=0.60723;//0.63664;
    double x_new, y_new;

    for(int i = 0; i < 12; i++)
    {
        angle[i] = (angle[i] / 45) * Pow(2, 20);
    }

    direction = (direction / 45) * Pow(2, 20);

    for(int i = 0; i < 12; i++)
    {
        if(direction > 0)
        {
            x_new = (x - y * (1 / Pow(2, i)));
            y_new = (y + x * (1 / Pow(2, i)));
            x = x_new;
            y = y_new;
            direction -= angle[i];
        }
        else{
            x_new = (x + y * (1 / Pow(2, i)));
            y_new = (y - x * (1 / Pow(2, i)));
            x = x_new;
            y = y_new;
            direction += angle[i];
        }
    }

    return y * k;
}

double sin_360(double direction)
{
    if(direction < 180)
        return -1;                                  
    return -sin_180(direction - 180);
}

double cos_180(double direction)
{
    if(direction <= 90)
        return sin_180(90 - direction);
    else if(direction > 90 && direction <= 180)
        return -sin_180(direction - 90);
    return -1;                               
}

double cos_360(double direction)
{
    if(direction > 180)
        return cos_180(360 - direction);
    else
        return -1;                                 
}

double arctan_90(float x, float y, float* r)
{
    double angle[50] = {45.0, 26.565051177077986, 14.036243467926479, 7.125016348901799,
                        3.5763343749973515, 1.7899106082460694, 0.8951737102110744,
                        0.4476141708605531, 0.22381050036853808, 0.1119056770662069,
                        0.05595289189380367, 0.02797645261700368, 0.013988227142265015,
                        0.006994113675352919, 0.003497056850704011, 0.0017485284269804495,
                        0.0008742642136937803, 0.00043713210687233457, 0.00021856605343934782,
                        0.00010928302672007149, 5.464151336008544e-05, 2.732075668004893e-05,
                        1.3660378340025243e-05, 6.830189170012718e-06, 3.4150945850063712e-06,
                        1.7075472925031871e-06, 8.537736462515938e-07, 4.2688682312579694e-07,
                        2.1344341156289847e-07, 1.0672170578144923e-07, 5.336085289072462e-08,
                        2.668042644536231e-08, 1.3340213222681154e-08, 6.670106611340577e-09,
                        3.3350533056702886e-09, 1.6675266528351443e-09, 8.337633264175721e-10,
                        4.1688166320878607e-10, 2.0844083160439303e-10, 1.0422041580219652e-10,
                        5.211020790109826e-11, 2.605510395054913e-11, 1.3027551975274565e-11,
                        6.513775987637282e-12, 3.256887993818641e-12, 1.6284439969093206e-12,
                        8.142219984546603e-13, 4.0711099922733015e-13, 2.0355549961366507e-13,
                        1.0177774980683254e-13, };		// 50 times

    double k = 0.6072529350088814;                          // 旋转矩阵比例因子
    double direction = 0;
    float convention_tan = 1;                                   //  约定的tan的值(为2^(-i))，这里的初始值为i = 0

    for(int i = 0; i < 50; i++)
    {
        int sigma = (y < 0) ? 1 : -1;
        float pre_x = x;
        x -= sigma * convention_tan * y;
        y += sigma * convention_tan * pre_x;

        direction -= sigma * angle[i];
        convention_tan = convention_tan / 2;
    }

    *r = x * k;
    return direction;
}

double arctan(float x, float y, float* r)
{
    if(x > 0)
        return arctan_90(x, y, r);
    else
        return 180 + arctan_90(-x, -y, r);
}
