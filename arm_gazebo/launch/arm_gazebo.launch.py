from launch import LaunchDescription
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
import os
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
)
from launch.actions import RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.actions import TimerAction





def generate_launch_description():
    # Includi il file di lancio da `arm_gazebo`
    arm_gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([
                FindPackageShare("arm_gazebo"),
                "launch",
                "arm_world.launch.py"
            ])
        ])
    )

    


    # Includi il file di lancio da `arm_control`
    # arm_control_launch = TimerAction(
    #     period=2.0,
    #     actions=[
    #         IncludeLaunchDescription(
    #             PythonLaunchDescriptionSource([
    #                 PathJoinSubstitution([
    #                     FindPackageShare("arm_control"),
    #                     "launch",
    #                     "arm_control.launch.py"
    #                 ])
    #             ])
    #         )
    #     ]
    # )

    arm_control_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([
                FindPackageShare("arm_control"),
                "launch",
                "arm_control.launch.py"
            ])
        ])
    )


    bridge_camera = Node(
        package='ros_ign_bridge',
        executable='parameter_bridge',
        arguments=[
            '/camera@sensor_msgs/msg/Image@gz.msgs.Image',
            '/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo',
            '--ros-args',
            '-r', '/camera:=/videocamera',
        ],
        output='screen'
    )
            
            


    

    # Aggiungi entrambi i lanci alla descrizione di lancio
    return LaunchDescription([
        arm_gazebo_launch,
        arm_control_launch,
        bridge_camera
    ])
