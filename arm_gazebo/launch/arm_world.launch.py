from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
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


 

def generate_launch_description():
    declared_arguments = []

    # declared_arguments.append(
    #     DeclareLaunchArgument(
    #         "rviz_config_file", 
    #         default_value=PathJoinSubstitution(
    #             [FindPackageShare("arm_description"), "config", "rviz", "arm.rviz"]
    #         ),
    #         description="RViz config file (absolute path) to use when launching rviz.",
    #     )
    #  )

    # # Percorso al file URDF
    # urdf_file = os.path.join(
    #     get_package_share_directory('arm_gazebo'), 
    #     'urdf', 
    #     'arm.urdf'
    #     #'modified_arm2.urdf'
    # )
    

    # # Trova il percorso del pacchetto che contiene gli URDF e le meshes
    # arm_description_path = FindPackageShare('arm_description').find('arm_description')

    # # Percorso completo del file URDF che vuoi usare
    # urdf_file = PathJoinSubstitution([arm_description_path, 'urdf', 'arm.urdf'])


    # come ha fatto il prof su ros2_simulation
    urdf_path = get_package_share_directory('arm_description')

    urdf_file = os.path.join(urdf_path, "urdf", "arm.urdf.xacro")

    with open(urdf_file, 'r') as infp:
        link_desc = infp.read()

    #robot_description_links = {"robot_description": link_desc}
    

  


   # robot_description = {'robot_description': PathJoinSubstitution([get_package_share_directory('arm_description'), 'urdf', 'arm.urdf'])}

    robot_description_xacro = {"robot_description": Command(['xacro ', urdf_file])}
    #robot_description_iiwa_xacro = {"robot_description": Command(['xacro ', xacro_iiwa, ' joint_a3_pos:=2.0', ' joint_a4_pos:=0.2'])}

    # joint_state_publisher_node = Node(
    #     package="joint_state_publisher_gui",
    #     executable="joint_state_publisher_gui",
    #     name="joint_state_publisher_gui",
    #     output="both"
    # )
   
    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[robot_description_xacro,
                    {"use_sim_time": True},
            ],
        remappings=[('/robot_description', '/robot_description')]
    )


    # rviz_node = Node(
    #     package="rviz2",
    #     executable="rviz2",
    #     name="rviz2",
    #     output="log",
    #     arguments=["-d", LaunchConfiguration("rviz_config_file")],
    # )

    declared_arguments.append(DeclareLaunchArgument('gz_args', default_value='-r -v 1 empty.sdf',
                              description='Arguments for gz_sim'),)
    
    gazebo_ignition = IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [PathJoinSubstitution([FindPackageShare('ros_gz_sim'),
                                    'launch',
                                    'gz_sim.launch.py'])]),
            launch_arguments={'gz_args': LaunchConfiguration('gz_args')}.items()
    )

    position = [0.0, 0.0, 0.0]

    gz_spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=['-topic', 'robot_description',
                   '-name', 'arm',
                   '-allow_renaming', 'true',
                    "-x", str(position[0]),
                    "-y", str(position[1]),
                    "-z", str(position[2]),],
    )
 
    ign = [gazebo_ignition, gz_spawn_entity]

     

    # joint_state_broadcaster = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
    # )  

    # position_controller = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=["position_controller", "--controller-manager", "/controller_manager"],  
    # ) 

    # #Launch the ros2 controllers after the model spawns in Gazebo 
    # delay_joint_traj_controller = RegisterEventHandler(
    #     event_handler=OnProcessExit(
    #         target_action=gz_spawn_entity,
    #         on_exit=[position_controller],
    #     )
    # )

    # delay_joint_state_broadcaster = (
    #     RegisterEventHandler(
    #         event_handler=OnProcessExit(
    #             target_action=gz_spawn_entity,
    #             on_exit=[joint_state_broadcaster],
    #         )
    #     )
    # )
     
    nodes_to_start = [
        robot_state_publisher_node,  
        #joint_state_publisher_node,
        *ign,
        #delay_joint_traj_controller, 
        #delay_joint_state_broadcaster,
        #rviz_node
    ]

    return LaunchDescription(declared_arguments + nodes_to_start) 