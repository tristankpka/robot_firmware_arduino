#include <Arduino.h>

namespace Rbt
{
    class Robot
    {
    public:
        Robot(): leftMotor(LEFT_MOTOR_INIT), rightMotor(RIGHT_MOTOR_INIT), distanceSensor(DISTANCE_SENSOR_INIT)
        {
            initialize();
            move();
        }
        void move()
        {
             state = stateMoving;
             leftMotor.setSpeed(255);
             rightMotor.setSpeed(255);
        }
        
        void stop()
        {
             state = stateStopped;
             leftMotor.setSpeed(0);
             rightMotor.setSpeed(0);
        }
        
        bool isStopped()
        {
             return state == stateStopped;
        }
        
        bool obstacleAhead(unsigned int distance)
        {
             return (distance <= TOO_CLOSE);
        }
        
        bool doneRunning(unsigned long currentTime)
        {
             return (currentTime >= endTime);
        }
        
        void initialize()
        {
            state = stateStopped;
            startTime = millis();
            endTime = millis() + RUN_TIME * 1000;            
        }
        void run()
        {
            unsigned long currentTime = millis();
            unsigned long elapsedTime = currentTime - startTime;            
            int distance = distanceSensor.getDistance();
            log("state: %s, currentTime: %ul, distance: %u\n", getStateName(state), currentTime, distance);        
            
            if(obstacleAhead(distance))
              stop();
            else
              move();
        }
    private:
        enum state_t {stateStopped = 0, stateMoving = 1};
        state_t state;
        
        const char* getStateName(state_t state)
        {
             static const char* stateNames[] = {"stateStopped", "stateMoving"};  
             return stateNames[state];
        }    
        
        unsigned long startTime;
        unsigned long endTime;
        
        Motor leftMotor;
        Motor rightMotor;
        DistanceSensor distanceSensor;
    };
};