#include "State.h"

State::State(){
    stage = "Pre Launch";
    recordDataStage = "PreFlight";
    timeAbsolute = millis();
    timePreviousStage = 0;
    position.x() = 0; position.y() = 0; position.z() = 0;
    velocity.x() = 0; velocity.y() = 0; velocity.z() = 0;
    acceleration.x() = 0; acceleration.y() = 0; acceleration.z() = 0;
    apogee = position.z();

    barometerFlag = false; gpsFlag = false; imuFlag = false; lightSensorFlag = false;
}

void State::addBarometer(const Barometer& Barometer){
    stateBarometer = Barometer;
    barometerFlag = true;
}

void State::addGPS(const GPS& gps){
    stateGPS = gps;
    gpsFlag = true;
}

void State::addIMU(const IMU& imu){
    stateIMU = imu;
    imuFlag = true;
}

void State::addLightSensor(const LightSensor& LightSensor){
    stateLightSensor = LightSensor;
    lightSensorFlag = true;
}

void State::settimeAbsolute(){
    timeAbsolute = millis();
}

void State::determineaccelerationMagnitude(imu::Vector<3> accel){
    accelerationMagnitude = sqrt((accel.x()*accel.x()) + (accel.y()*accel.y()) + (accel.z()*accel.z()));
}

void State::determineapogee(double zPosition){
    if(apogee < zPosition){
        apogee = zPosition;
    }
}

void State::determinetimeSincePreviousStage(){
    timeSincePreviousStage = timeAbsolute - timePreviousStage;
}

void State::determinetimeSinceLaunch(){
    timeSinceLaunch = timeAbsolute - timeLaunch;
}

void State::setcsvHeader(){
    csvHeader = "";
    csvHeader += "Time"; csvHeader += ",";
    csvHeader += "Stage"; csvHeader += ",";
    csvHeader += "PosX"; csvHeader += ","; csvHeader += "PosY"; csvHeader += ","; csvHeader += "PosZ"; csvHeader += ",";
    csvHeader += "VeloX"; csvHeader += ","; csvHeader += "VeloY"; csvHeader += ","; csvHeader += "VeloZ"; csvHeader += ",";
    csvHeader += "AccelX"; csvHeader += ","; csvHeader += "AccelY"; csvHeader += ","; csvHeader += "AccelZ"; csvHeader += ",";
    if(barometerFlag){
        stateBarometer.setcsvHeader();
        csvHeader += stateBarometer.getcsvHeader();
    }
    if(gpsFlag){
        stateGPS.setcsvHeader();
        csvHeader += stateGPS.getcsvHeader();
    }
    if(imuFlag){
        stateIMU.setcsvHeader();
        csvHeader += stateIMU.getcsvHeader();
    }
    if(lightSensorFlag){
        stateLightSensor.setcsvHeader();
        csvHeader += stateLightSensor.getcsvHeader();
    }
}

void State::setdataString(){
    dataString = "";
    dataString += String(timeAbsolute); dataString += ",";
    dataString += stage; dataString += ",";
    dataString += String(position.x()); dataString += ",";
    dataString += String(position.y()); dataString += ",";
    dataString += String(position.z()); dataString += ",";
    dataString += String(velocity.x()); dataString += ",";
    dataString += String(velocity.x()); dataString += ",";
    dataString += String(velocity.x()); dataString += ",";
    dataString += String(acceleration.x()); dataString += ",";
    dataString += String(acceleration.y()); dataString += ",";
    dataString += String(acceleration.z()); dataString += ",";
    if(barometerFlag){
        stateBarometer.setdataString();
        dataString += stateBarometer.getdataString();
    }
    if(gpsFlag){
        stateGPS.setdataString();
        dataString += stateGPS.getdataString();
    }
    if(imuFlag){
        stateIMU.setdataString();
        dataString += stateIMU.getdataString();
    }
    if(lightSensorFlag){
        stateLightSensor.setdataString();
        dataString += stateLightSensor.getdataString();
    }
}

String State::getdataString(){
    return dataString;
}

String State::getrecordDataStage(){
    return recordDataStage;
}