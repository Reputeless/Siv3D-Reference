//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Gamepad.hpp"

namespace s3d
{
	/// <summary>
	/// XInput 対応コントローラ
	/// </summary>
	class XInput
	{
	private:

		uint32 m_userIndex;

	public:

		enum
		{
			/// <summary>
			/// 最大接続数
			/// </summary>
			MaxUser = 4
		};

		/// <summary>
		/// 指定したユーザインデックスのコントローラにアクセスします。
		/// </summary>
		/// <param name="userIndex">
		/// ユーザインデックス
		/// </param>
		XInput(uint32 userIndex);

		/// <summary>
		/// 接続されているかを示します。
		/// </summary>
		bool isConnected() const;

		/// <summary>
		/// 十字ボタンの上ボタン
		/// </summary>
		Property_Get(Key, buttonUp) const;

		/// <summary>
		/// 十字ボタンの下ボタン
		/// </summary>
		Property_Get(Key, buttonDown) const;

		/// <summary>
		/// 十字ボタンの左ボタン
		/// </summary>
		Property_Get(Key, buttonLeft) const;

		/// <summary>
		/// 十字ボタンの右ボタン
		/// </summary>
		Property_Get(Key, buttonRight) const;

		/// <summary>
		/// START ボタン
		/// </summary>
		Property_Get(Key, buttonStart) const;

		/// <summary>
		/// BACK ボタン
		/// </summary>
		Property_Get(Key, buttonBack) const;

		/// <summary>
		/// 左スティックの押し込み
		/// </summary>
		Property_Get(Key, buttonLThumb) const;

		/// <summary>
		/// 右スティックの押し込み
		/// </summary>
		Property_Get(Key, buttonRThumb) const;

		/// <summary>
		/// LB ボタン
		/// </summary>
		Property_Get(Key, buttonLB) const;

		/// <summary>
		/// RB ボタン
		/// </summary>
		Property_Get(Key, buttonRB) const;

		/// <summary>
		/// A ボタン
		/// </summary>
		Property_Get(Key, buttonA) const;

		/// <summary>
		/// B ボタン
		/// </summary>
		Property_Get(Key, buttonB) const;

		/// <summary>
		/// X ボタン
		/// </summary>
		Property_Get(Key, buttonX) const;

		/// <summary>
		/// Y ボタン
		/// </summary>
		Property_Get(Key, buttonY) const;

		/// <summary>
		/// 左トリガーの値 [0.0, 1.0]
		/// </summary>
		Property_Get(double, leftTrigger) const;

		/// <summary>
		/// 右トリガーの値 [0.0, 1.0]
		/// </summary>
		Property_Get(double, rightTrigger) const;

		/// <summary>
		/// 左スティックの X 軸の値 [-1.0, 1.0]
		/// </summary>
		Property_Get(double, leftThumbX) const;

		/// <summary>
		/// 左スティックの Y 軸の値 [-1.0, 1.0]
		/// </summary>
		Property_Get(double, leftThumbY) const;

		Optional<int32> leftThumbAs4Directions(double threshold = 0.2) const;

		Optional<int32> leftThumbAs8Directions(double threshold = 0.2) const;

		/// <summary>
		/// 右スティックの X 軸の値 [-1.0, 1.0]
		/// </summary>
		Property_Get(double, rightThumbX) const;

		/// <summary>
		/// 右スティックの Y 軸の値 [-1.0, 1.0]
		/// </summary>
		Property_Get(double, rightThumbY) const;

		Optional<int32> rightThumbAs4Directions(double threshold = 0.2) const;

		Optional<int32> rightThumbAs8Directions(double threshold = 0.2) const;

		/// <summary>
		/// 左トリガーにデッドゾーンを設定します。
		/// </summary>
		/// <param name="deadZone">
		/// 設定するデッドゾーン
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setLeftTriggerDeadZone(const DeadZone& deadZone = { 0.12, 1.0, DeadZoneType::Independent });

		/// <summary>
		/// 右トリガーにデッドゾーンを設定します。
		/// </summary>
		/// <param name="deadZone">
		/// 設定するデッドゾーン
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setRightTriggerDeadZone(const DeadZone& deadZone = { 0.12, 1.0, DeadZoneType::Independent });

		/// <summary>
		/// 左スティックにデッドゾーンを設定します。
		/// </summary>
		/// <param name="deadZone">
		/// 設定するデッドゾーン
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setLeftThumbDeadZone(const DeadZone& deadZone = { 0.24, 1.0, DeadZoneType::Circular });

		/// <summary>
		/// 右スティックにデッドゾーンを設定します。
		/// </summary>
		/// <param name="deadZone">
		/// 設定するデッドゾーン
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setRightThumbDeadZone(const DeadZone& deadZone = { 0.26, 1.0, DeadZoneType::Circular });

		/// <summary>
		/// バイブレーションを設定します。
		/// </summary>
		/// <param name="leftMotorSpeed">
		/// 低周波の左モータのスピード、0 は停止、1.0 は最大速度
		/// </param>
		/// <param name="rightMotorSpeed">
		/// 高周波の右モータのスピード、0 は停止、1.0 は最大速度
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setVibration(double leftMotorSpeed, double rightMotorSpeed) const;
		
		/// <summary>
		/// バイブレーションを停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void stopVibration() const;

		/// <summary>
		/// ユーザインデックス
		/// </summary>
		Property_Get(uint32, userIndex) const;
	};
}
