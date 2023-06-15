#include "myactuator_rmd/driver.hpp"

#include <cstdint>
#include <string>

#include "myactuator_rmd/actuator_state/feedback.hpp"
#include "myactuator_rmd/actuator_state/gains.hpp"
#include "myactuator_rmd/actuator_state/motor_status_1.hpp"
#include "myactuator_rmd/actuator_state/motor_status_2.hpp"
#include "myactuator_rmd/actuator_state/motor_status_3.hpp"
#include "myactuator_rmd/protocol/node.hpp"
#include "myactuator_rmd/protocol/requests.hpp"
#include "myactuator_rmd/protocol/responses.hpp"
#include "myactuator_rmd/exceptions.hpp"


namespace myactuator_rmd {

  Driver::Driver(std::string const& ifname, std::uint32_t const actuator_id)
  : Node{ifname, actuator_id} {
    return;
  }

  std::uint32_t Driver::getVersionDate() {
    GetVersionDateRequest const request {};
    auto const response {sendRecv<GetVersionDateResponse>(request)};
    return response.getVersion();
  }

  std::string Driver::getMotorModel() {
    GetMotorModelRequest const request {};
    auto const response {sendRecv<GetMotorModelResponse>(request)};
    return response.getModel();
  }

  MotorStatus1 Driver::getMotorStatus1() {
    GetMotorStatus1Request const request {};
    auto const response {sendRecv<GetMotorStatus1Response>(request)};
    return response.getStatus();
  }

  MotorStatus2 Driver::getMotorStatus2() {
    GetMotorStatus2Request const request {};
    auto const response {sendRecv<GetMotorStatus2Response>(request)};
    return response.getStatus();
  }

  MotorStatus3 Driver::getMotorStatus3() {
    GetMotorStatus3Request const request {};
    auto const response {sendRecv<GetMotorStatus3Response>(request)};
    return response.getStatus();
  }

  Gains Driver::getControllerGains() {
    GetControllerGainsRequest const request {};
    auto const response {sendRecv<GetControllerGainsResponse>(request)};
    return response.getGains();
  }

  Gains Driver::setControllerGains(Gains const& gains, bool const is_persistent) {
    if (is_persistent) {
      SetControllerGainsPersistentlyRequest const request {gains};
      auto const response {sendRecv<SetControllerGainsPersistentlyResponse>(request)};
      return response.getGains();
    } else {
      SetControllerGainsRequest const request {gains};
      auto const response {sendRecv<SetControllerGainsResponse>(request)};
      return response.getGains();
    }
  }

  Feedback Driver::sendTorqueSetpoint(float const current) {
    SetTorqueRequest const request {current};
    auto const response {sendRecv<SetTorqueResponse>(request)};
    return response.getStatus();
  }

  Feedback Driver::sendVelocitySetpoint(float const speed) {
    SetVelocityRequest const request {speed};
    auto const response {sendRecv<SetVelocityResponse>(request)};
    return response.getStatus();
  }

  Feedback Driver::sendPositionAbsoluteSetpoint(float const position, float const max_speed) {
    SetPositionAbsoluteRequest const request {position, max_speed};
    auto const response {sendRecv<SetPositionAbsoluteResponse>(request)};
    return response.getStatus();
  }

  void Driver::stopMotor() {
    StopMotorRequest const request {};
    [[maybe_unused]] auto const response {sendRecv<StopMotorResponse>(request)};
    return;
  }

  void Driver::shutdownMotor() {
    ShutdownMotorRequest const request {};
    [[maybe_unused]] auto const response {sendRecv<ShutdownMotorResponse>(request)};
    return;
  }

}
