/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file Crime.cpp
 *  
 * Last modified on February 12, 20245, 15:13 PM
 */

#include "Crime.h"

using namespace std;

/*
 * Initialization of the static string that contains the value assigned to any 
 * string field (string) which is found empty in the data of a Crime
 */
const std::string Crime::UNKNOWN_VALUE = "UNKNOWN";

/*
 * Initialization of the static string that contain the default value for the
 * DateTime field in a Crime 
 */
const string Crime::DATETIME_DEFAULT = "2017-01-20 02:00:00";

/* 
 * Initialization of the static string with the default values for every field in 
 * a Crime
 */
const string Crime::CRIME_DEFAULT("0," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," +
        UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE +
        "," + ((std::string)"1") + "," + Crime::DATETIME_DEFAULT + "," +
        UNKNOWN_VALUE + ",181,181");

Crime::Crime() {
    _counter = 0;
    _id = UNKNOWN_VALUE;
    _code = UNKNOWN_VALUE;
    _group = UNKNOWN_VALUE;
    _description = UNKNOWN_VALUE;
    _district = UNKNOWN_VALUE;
    _areaReport = UNKNOWN_VALUE;
    _shooting = false;
    _dateTime = DATETIME_DEFAULT;
    _street = UNKNOWN_VALUE;
    _location = {181, 181};
}

Crime::Crime(const string &line) {
    set(line);
}

int Crime::getCounter() const {
    return _counter;
}

std::string Crime::getId() const {
    return _id;
}

std::string Crime::getCode() const {
    return _code;
}

std::string Crime::getGroup() const {
    return _group;
}

std::string Crime::getDescription() const {
    return _description;
}

std::string Crime::getDistrict() const {
    return _district;
}

std::string Crime::getStreet() const {
    return _street;
}

std::string Crime::getAreaReport() const {
    return _areaReport;
}

bool Crime::isShooting() const {
    return _shooting;
}

DateTime Crime::getDateTime() const {
    return _dateTime;
}

Coordinates Crime::getLocation() const {
    return _location;
}

bool Crime::isIDUnknown() const {
    bool unknown=false;
    if (_id==UNKNOWN_VALUE) unknown=true;
    return unknown;
}


std::string Crime::toString() const {
    string s;
    s = _counter +"," + _id + "," + _code +"," + _group + "," + _description + "," + _district + "," + _areaReport + ","
        + (_shooting ? "1" : "0") + "," + _dateTime.toString() + ","
        + _street + "," + _location.toString();
    return s;
}

void Crime::setCounter(int c) {
    _counter=c;
}

void Crime::setId(const std::string &id) {
    _id=id;
}

void Crime::setCode(const std::string &code) {
    _code=code;
}

void Crime::setGroup(const std::string &group) {
    _group=group;
}

void Crime::setDescription(const std::string &description) {
    _description=description;
}

void Crime::setDistrict(const std::string &district) {
    _district=district;
}

void Crime::setAreaReport(const std::string &areaReport) {
    _areaReport=areaReport;
}

void Crime::setStreet(const std::string &street) {
    _street=street;
}

void Crime::setShooting(bool shooting) {
    _shooting=shooting;
}

void Crime::setDateTime(const string & time) {
    _dateTime.set(time);
}

void Crime::setLocation(const Coordinates & coordinates) {
    _location.setLatitude(coordinates.getLatitude());
    _location.setLongitude(coordinates.getLongitude());
}

void Crime::set(const std::string &line) {
    if (line.empty()) {
        throw std::runtime_error("Error: Línea vacía.");
    }

    int pos = 0, field = 0;
    std::string data[12];

    // Recorrer manualmente la línea para extraer los campos separados por comas
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',' || field == 11) { // Último campo no tiene coma al final
            if (pos > i) { 
                throw std::runtime_error("Error: Campo vacío en la línea.");
            }
            data[field] = line.substr(pos, i - pos);
            pos = i + 1;
            field++;
        }
    }

    // Extraer el último campo manualmente
    //data[11] = line.substr(pos);

    // Validaciones previas a la conversión
    if (data[0].empty() || data[1].empty()) {
        throw std::runtime_error("Error: Campos obligatorios vacíos.");
    }

    try {
        setCounter(std::stoi(data[0]));
        setId(data[1]);
        setCode(data[2]);
        setGroup(data[3]);
        setDescription(data[4]);
        setDistrict(data[5]);
        setAreaReport(data[6]);
        setShooting(data[7] == "1");
        setDateTime(data[8]);
        setStreet(data[9]);
        setLocation(Coordinates(std::stof(data[10]), std::stof(data[11])));
    } catch (const std::exception &e) {
        throw std::runtime_error("Error en la conversión de datos: " + std::string(e.what()));
    }
}




void Trim(string & myString) {
    int start = 0;
    while (start < myString.length() && (myString[start] == ' ' || myString[start] == '\t')) {
        start++;
    }
    int end = myString.length() - 1;
    while (end >= 0 && (myString[end] == ' ' || myString[end] == '\t')) {
        end--;
    }
    myString = myString.substr(start, end - start + 1);
}

void Capitalize(string & myString) {
    for (int i = 0; i < myString.length(); i++) {
        if (myString[i] >= 'a' && myString[i] <= 'z') {
            myString[i] -= 32;
        }
    }
}

void Normalize(Crime & crime) {
    string id = crime.getId();
    string code = crime.getCode();
    string group = crime.getGroup();
    string description = crime.getDescription();
    string district = crime.getDistrict();
    string areaReport = crime.getAreaReport();
    string street = crime.getStreet();
    
    Trim(id);
    Trim(code);
    Trim(group);
    Trim(description);
    Trim(district);
    Trim(areaReport);
    Trim(street);
    
    Capitalize(group);
    Capitalize(description);
    Capitalize(district);
    Capitalize(street);
    
    crime.setId(id);
    crime.setCode(code);
    crime.setGroup(group);
    crime.setDescription(description);
    crime.setDistrict(district);
    crime.setAreaReport(areaReport);
    crime.setStreet(street);
}
