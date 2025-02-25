/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file Coordinate.cpp  
 * 
 * Last modified on February 12, 20245, 15:03 PM
 */

#include "Coordinates.h"
#include <cmath>


const float Coordinates::INVALID_COORDINATE=181.0;

using namespace std;


Coordinates::Coordinates(float latitude, float longitude) {
    _latitude=latitude;
    _longitude=longitude;
}

float Coordinates::getLatitude() const {
    return _latitude;
}

float Coordinates::getLongitude() const {
    return _longitude;
}

bool Coordinates::isValid() const {
    bool valid=false;
    if(_latitude>-90&&_latitude<90&&_longitude>-180&&_longitude<180){
        valid=true;
    }
    return valid;
    
}

void Coordinates::set(float latitude, float longitude){
    _latitude=latitude;
    _longitude=longitude;
}

void Coordinates::setLatitude(float latitude) {
     _latitude=latitude;
}

void Coordinates::setLongitude(float longitude) {
    _longitude=longitude;
}

std::string Coordinates::toString() const {
    string s=to_string(_latitude)+" , "+to_string(_longitude)+"\n";
    return s;
}

Coordinates Coordinates::length(const Coordinates &second) const{
    float length_lat=fabs(_latitude-second.getLatitude());
    float length_lon=fabs(_longitude-second.getLongitude());
    Coordinates length(length_lat,length_lon);
    return length;
}                        

bool Coordinates::isInsideArea(const Coordinates &bottomLeft, const Coordinates &topRight) const {
    bool inside=false;
    if(_latitude >= bottomLeft.getLatitude() && _latitude <= topRight.getLatitude() &&_longitude >= bottomLeft.getLongitude() && _longitude <= topRight.getLongitude()) inside=true;
    return inside;
    
}  
