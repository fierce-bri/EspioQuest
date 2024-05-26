#include "feedback.h"

// Default constructor for the Feedback class template
template <typename T>
Feedback<T>::Feedback() {}

// Member function definition for calculating the score
template<typename T>
T Feedback<T>::calculateScore(T numOfPoints){
    // Calculate the score as a percentage based on the number of points
    return (numOfPoints / 10) * 100;
}

// Explicit instantiation of the class template for double data type
template class Feedback<double>;
