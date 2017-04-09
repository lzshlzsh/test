/**
 * @file point.h
 * @brief
 * @version 1.0
 * @date 01/16/2016 12:10:56 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#ifndef  __POINT_H__
#define  __POINT_H__

#include <sys/time.h>

#include <string>
#include <iostream>

/**
 * @brief 
 * @class Point1d
 */
class Point1d
{
public:
    double x_;
    /**
     * @brief
     */
    Point1d (const double x): x_(x) {}
protected:
private:
};

/**
 * @brief 
 * @class Point2d
 */
class Point2d: virtual public Point1d
{
public:
    double y_;
    /**
     * @brief
     */
    Point2d (const double x, const double y): Point1d(x), y_(y) {}
protected:
private:
};


/**
 * @brief 
 * @class Point3d
 */
class Point3d: virtual public Point2d
{
public:
    double z_;
    /**
     * @brief
     */
    Point3d (const double x, const double y, const double z): 
        Point1d(x), Point2d(x, y), z_(z) {}
protected:
private:
};

/**
 * @brief 
 * @class TimeProfile
 */
class TimeProfile
{
public:
    /**
     * @brief
     */
    TimeProfile (const std::string &info = ""): info_(info) {
        gettimeofday(&start_, NULL);
    }
    ~TimeProfile() {
        struct timeval now;
        gettimeofday(&now, NULL);
        std::cout << info_ << '\t'
            << (now.tv_sec - start_.tv_sec) * 1000000 + (now.tv_usec - start_.tv_usec)
            << std::endl;
    }
protected:
private:
    struct timeval start_;
    std::string info_;
};

enum {
    X, Y, Z,
    ITERATIONS = 10000000,
};

void foo(Point3d &pa, Point3d &pb);
#endif

