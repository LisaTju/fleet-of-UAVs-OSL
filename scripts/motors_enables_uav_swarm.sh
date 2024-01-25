cd ~/quadrotor-simulation
rosservice call /robot_0/enable_motors "enable: true"
rosservice call /robot_1/enable_motors "enable: true"
rosservice call /robot_2/enable_motors "enable: true"
rosservice call /robot_3/enable_motors "enable: true"
