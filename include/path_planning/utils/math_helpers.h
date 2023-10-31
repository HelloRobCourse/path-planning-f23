#ifndef PATH_PLANNING_UTILS_MATH_HELPERS_H
#define PATH_PLANNING_UTILS_MATH_HELPERS_H

#include <cmath>
#include <random>
#include <chrono>
#include <thread>

#define PI          3.14159265
#define RAD_TO_DEG  180 / PI
#define EPS         1e-5

/**
 * Generates a random float.
 */
static inline float generateRandomNumber(float low, float high)
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<float> distribution(low, high);
    return distribution(gen);
}

/**
 * Normalizes angle to range [-PI, PI].
 * @param  angle Angle to normalize.
 * @return       Normalized angle.
 */
static inline float normalizeAngle(float angle)
{
  float result = fmod(angle + M_PI, 2.0 * M_PI);
  if (result <= 0) return result + M_PI;
  return result - M_PI;
}

/**
 * Checks whether two variables are close together, within EPS.
 */
template <class T>
static inline bool isClose(const T x1, const T x2)
{
    return abs(x1 - x2) <= EPS;
}

/**
 * Computes a parabola of the form:
 *
 *   f(x) = (x - h)^2 + k
 **/
static inline float parabola(float x, float h, float k)
{
  return pow(x - h, 2) + k;
}

/**
 * Gets the current time in microseconds.
 */
static inline int getTimeMicro()
{
    auto now = std::chrono::system_clock::now();
    return now.time_since_epoch().count();
}

/**
 * Sleeps for the provided number of seconds.
 */
static inline void sleepFor(float secs)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(secs * 1000)));
}

#endif // PATH_PLANNING_UTILS_MATH_HELPERS_H
