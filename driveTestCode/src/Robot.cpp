#include <iostream>
#include <string>
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <Joystick.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
//#include <DifferentialDrive.h>
#include <SpeedController.h>
#include "Drive/DifferentialDrive.h"
#include "DriverStation.h"



class Robot : public frc::IterativeRobot {

private:
	WPI_TalonSRX *srx1;
	WPI_TalonSRX *srx12;
	WPI_TalonSRX *srx13;

	WPI_TalonSRX *srx2;
	WPI_TalonSRX *srx21;
	WPI_TalonSRX *srx22;

	DifferentialDrive *m_robotDrive;
	DifferentialDrive *m_robotDrive2;
	DifferentialDrive *m_robotDrive3;

	frc::Joystick stick { 0 };
	double rightMotor;
	double leftMotor;
	double rightStickValue;
	double leftStickValue;

	frc::Talon test {0};
public:
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

		srx1 = new WPI_TalonSRX(1);
		srx12 = new WPI_TalonSRX(2);
		srx13 = new WPI_TalonSRX(3);

		srx2 = new WPI_TalonSRX(4);
		srx21 = new WPI_TalonSRX(5);
		srx22 = new WPI_TalonSRX(6);

		m_robotDrive = new DifferentialDrive(*srx1, *srx2);
		m_robotDrive2 = new DifferentialDrive(*srx12, *srx21);
		m_robotDrive3 = new DifferentialDrive(*srx13, *srx22);
		m_robotDrive->SetSafetyEnabled(false);
		m_robotDrive2->SetSafetyEnabled(false);
		m_robotDrive3->SetSafetyEnabled(false);



	/*	srx12->Follow(*srx1);
		srx13->Follow(*srx1);



		srx21->Follow(*srx2);
		srx22->Follow(*srx2);
*/
	}


	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {}

	void TeleopPeriodic() {

		rightStickValue = stick.GetRawAxis(1);
		leftStickValue = stick.GetRawAxis(2);
		m_robotDrive->ArcadeDrive(-rightStickValue, -leftStickValue);
		m_robotDrive2->ArcadeDrive(-rightStickValue, -leftStickValue);
		m_robotDrive3->ArcadeDrive(-rightStickValue, -leftStickValue);

		double m1 = srx1->Get();
		double m2 = srx12->Get();
		double m3 = srx13->Get();
		double m4 = srx2->Get();
		double m5 = srx21->Get();
		double m6 = srx22->Get();

		double c1 = srx1->GetOutputCurrent();
		double c2 = srx12->GetOutputCurrent();
		double c3 = srx13->GetOutputCurrent();
		double c4 = srx2->GetOutputCurrent();
		double c5 = srx21->GetOutputCurrent();
		double c6 = srx22->GetOutputCurrent();

		frc::SmartDashboard::PutNumber("m1",m1);
		frc::SmartDashboard::PutNumber("m2",m2);
		frc::SmartDashboard::PutNumber("m3",m3);
		frc::SmartDashboard::PutNumber("m4",m4);
		frc::SmartDashboard::PutNumber("m5",m5);
		frc::SmartDashboard::PutNumber("m6",m6);

		frc::SmartDashboard::PutNumber("c1",c1);
		frc::SmartDashboard::PutNumber("c2",c2);
		frc::SmartDashboard::PutNumber("c3",c3);
		frc::SmartDashboard::PutNumber("c4",c4);
		frc::SmartDashboard::PutNumber("c5",c5);
		frc::SmartDashboard::PutNumber("c6",c6);

	}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
};

START_ROBOT_CLASS(Robot)
