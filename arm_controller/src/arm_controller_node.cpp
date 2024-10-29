// #include "rclcpp/rclcpp.hpp"
// #include "sensor_msgs/msg/joint_state.hpp"  // Include corretto per sensor_msgs/JointState
// #include "std_msgs/msg/float64_multi_array.hpp"


// class ArmControllerNode : public rclcpp::Node {
// public:
//     ArmControllerNode() : Node("arm_controller_node") {
//         // Subscriber al topic joint_states
//         joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
//             "joint_states", 10,
//             std::bind(&ArmControllerNode::jointStateCallback, this, std::placeholders::_1)
//         );

//         // Publisher per inviare comandi al controller
//         position_controller_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
//             "/position_controller/command", 10
//         );

//         // Timer per pubblicare comandi periodici
//         timer_ = this->create_wall_timer(
//             std::chrono::milliseconds(3000),
//             std::bind(&ArmControllerNode::publishCommands, this)
//         );
//     }

// private:
//     // Callback per il subscriber joint_states
//     void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) {
//         RCLCPP_INFO(this->get_logger(), "Joint positions:");
//         for (size_t i = 0; i < msg->position.size(); ++i) {
//             RCLCPP_INFO(this->get_logger(), "  - Joint %ld: %f", i, msg->position[i]);
//         }
//     }

//     // Funzione per pubblicare comandi sul controller
//     void publishCommands() {
//         std_msgs::msg::Float64MultiArray command_msg;
//         command_msg.data = {1.0, 1.0, 1.0, 1.0}; // Imposta i comandi per i giunti

//         RCLCPP_INFO(this->get_logger(), "Publishing commands to /position_controller/command:");
//         for (size_t i = 0; i < command_msg.data.size(); ++i) {
//             RCLCPP_INFO(this->get_logger(), "  - Command %ld: %f", i, command_msg.data[i]);
//         }

//         position_controller_publisher_->publish(command_msg);
//     }

//     // Subscriber e Publisher
//     rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
//     rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr position_controller_publisher_;

//     // Timer per la pubblicazione dei comandi
//     rclcpp::TimerBase::SharedPtr timer_;
// };

// int main(int argc, char *argv[]) {
//     rclcpp::init(argc, argv);
//     rclcpp::spin(std::make_shared<ArmControllerNode>());
//     rclcpp::shutdown();
//     return 0;
// }

// #include "rclcpp/rclcpp.hpp"
// #include "sensor_msgs/msg/joint_state.hpp"  
// #include "std_msgs/msg/float64_multi_array.hpp"

// class ArmControllerNode : public rclcpp::Node {
// public:
//     ArmControllerNode() : Node("arm_controller_node"), joint_positions_(4, 0.0) {
//         // Subscriber al topic joint_states
//         joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
//             "joint_states", 10,
//             std::bind(&ArmControllerNode::jointStateCallback, this, std::placeholders::_1)
//         );

//         // Publisher per inviare comandi al controller
//         position_controller_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
//             "/position_controller/command", 10
//         );

//         // Timer per pubblicare comandi periodici
//         timer_ = this->create_wall_timer(
//             std::chrono::milliseconds(3000),
//             std::bind(&ArmControllerNode::publishCommands, this)
//         );
//     }

// private:
//     // Callback per il subscriber joint_states
//     void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) {
//         if (msg->position.size() >= joint_positions_.size()) {
//             for (size_t i = 0; i < joint_positions_.size(); ++i) {
//                 joint_positions_[i] = msg->position[i];
//             }
//             RCLCPP_INFO(this->get_logger(), "Aggiornate le posizioni dei giunti:");
//             for (size_t i = 0; i < joint_positions_.size(); ++i) {
//                 RCLCPP_INFO(this->get_logger(), "  - Joint %ld: %f", i, joint_positions_[i]);
//             }
//         }
//     }

//     // Funzione per pubblicare comandi basati sulle posizioni attuali dei giunti
//     void publishCommands() {
//         std_msgs::msg::Float64MultiArray command_msg;
//         command_msg.data = joint_positions_; // Usa le posizioni ricevute per i comandi

//         RCLCPP_INFO(this->get_logger(), "Invio comandi a /position_controller/command:");
//         for (size_t i = 0; i < command_msg.data.size(); ++i) {
//             RCLCPP_INFO(this->get_logger(), "  - Command %ld: %f", i, command_msg.data[i]);
//         }

//         position_controller_publisher_->publish(command_msg);
//     }

//     // Variabili membro
//     rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
//     rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr position_controller_publisher_;
//     rclcpp::TimerBase::SharedPtr timer_;
//     std::vector<double> joint_positions_; // Vettore per memorizzare le posizioni dei giunti
// };

// int main(int argc, char *argv[]) {
//     rclcpp::init(argc, argv);
//     rclcpp::spin(std::make_shared<ArmControllerNode>());
//     rclcpp::shutdown();
//     return 0;
// }

// #include <rclcpp/rclcpp.hpp>
// #include <sensor_msgs/msg/joint_state.hpp>
// #include <std_msgs/msg/float64_multi_array.hpp>

// class ArmControllerNode : public rclcpp::Node {
// public:
//     ArmControllerNode() : Node("arm_controller_node") {
//         // Inizializza il subscriber per il topic "joint_states"
//         joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
//             "joint_states", 10, std::bind(&ArmControllerNode::jointStateCallback, this, std::placeholders::_1));
        
//         // Inizializza il subscriber per i comandi manuali
//         command_subscriber_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
//             "/position_controller/command", 10, std::bind(&ArmControllerNode::manualCommandCallback, this, std::placeholders::_1));

//         // Inizializza il publisher per il topic "/position_controller/command"
//         command_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/position_controller/command", 10);
//     }

// private:
//     void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) {
//         // Stampa le posizioni delle giunture
//         RCLCPP_INFO(this->get_logger(), "Current joint positions:");
//         for (auto position : msg->position) {
//             RCLCPP_INFO(this->get_logger(), "Position: %f", position);
//         }

//         // Pubblica solo se non ci sono comandi manuali
//         if (!manual_command_received_) {
//             auto command_msg = std_msgs::msg::Float64MultiArray();
//             command_msg.data = msg->position;  // Usa le posizioni attuali come esempio
//             command_publisher_->publish(command_msg);
//         } else {
//             RCLCPP_INFO(this->get_logger(), "Manual command received. Skipping automatic publishing.");
//         }
//     }

//     void manualCommandCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
//         // Aggiorna la posizione con il comando manuale e imposta il flag
//         manual_command_received_ = true;

//         RCLCPP_INFO(this->get_logger(), "Manual command received. Updating position:");
//         for (auto position : msg->data) {
//             RCLCPP_INFO(this->get_logger(), "Position: %f", position);
//         }

//         // Pubblica il comando ricevuto manualmente
//         command_publisher_->publish(*msg);
//     }

//     rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
//     rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr command_subscriber_;
//     rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr command_publisher_;
//     bool manual_command_received_ = false;
// };

// int main(int argc, char * argv[]) {
//     rclcpp::init(argc, argv);
//     rclcpp::spin(std::make_shared<ArmControllerNode>());
//     rclcpp::shutdown();
//     return 0;
// }

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class ArmControllerNode : public rclcpp::Node
{
public:
  ArmControllerNode()
  : Node("arm_controller_node")
  {
    // Publisher per il topic /position_controller/commands
    command_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/position_controller/commands", 10);

    // Subscriber per il topic joint_states
    joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>(
      "joint_states", 10, std::bind(&ArmControllerNode::jointStateCallback, this, _1));

    // Timer per inviare il comando una sola volta dopo l'inizio
    timer_ = this->create_wall_timer(
      5000ms, std::bind(&ArmControllerNode::publishCommand, this));

    RCLCPP_INFO(this->get_logger(), "Arm Controller Node initialized. Waiting for joint states...");
  }

private:
  // Funzione callback per il subscriber del topic joint_states
  void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Current joint positions:");
    for (size_t i = 0; i < msg->position.size(); ++i) {
      RCLCPP_INFO(this->get_logger(), "  Joint %zu position: %f", i, msg->position[i]);
    }
  }

  // Funzione per pubblicare il comando sul topic /position_controller/commands
  void publishCommand()
  {
    auto command_msg = std_msgs::msg::Float64MultiArray();
    command_msg.data = {1.0, 1.0, 1.0, 1.0}; // Imposta il comando a (1, 1, 1, 1)
    RCLCPP_INFO(this->get_logger(), "Publishing command to position (1, 1, 1, 1)");

    command_publisher_->publish(command_msg);

    // Ferma il timer dopo aver inviato il comando una volta
    timer_->cancel();
  }

  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr command_publisher_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmControllerNode>());
  rclcpp::shutdown();
  return 0;
}


