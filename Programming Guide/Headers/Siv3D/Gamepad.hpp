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
# include "Fwd.hpp"
# include "String.hpp"
# include "Key.hpp"
# include "PropertyMacro.hpp"

namespace s3d
{
	/// <summary>
	/// ゲームパッドの情報
	/// </summary>
	struct GamepadInfo
	{
		/// <summary>
		/// 現在の接続のインデックス
		/// </summary>
		uint32 index = 0;

		/// <summary>
		/// 名称
		/// </summary>
		String name;

		/// <summary>
		/// ボタンの総数
		/// </summary>
		uint32 num_buttons = 0;

		/// <summary>
		/// 軸の総数
		/// </summary>
		uint32 num_axes = 0;
	};

	/// <summary>
	/// デッドゾーンの計算方式
	/// </summary>
	enum class DeadZoneType
	{
		/// <summary>
		/// デッドゾーンなし
		/// </summary>
		None,

		/// <summary>
		/// 軸独立
		/// </summary>
		Independent,

		/// <summary>
		/// 円形
		/// </summary>
		Circular
	};

	/// <summary>
	/// デッドゾーンの定義
	/// </summary>
	/// <remarks>
	/// 現在のバージョンでは XInput にしか適用できません。
	/// </remarks>
	struct DeadZone
	{
		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr DeadZone() = default;

		/// <summary>
		/// デッドゾーンを定義します。
		/// </summary>
		/// <param name="_size">
		/// デッドゾーンの大きさ
		/// </param>
		/// <param name="_maxValue">
		/// 飽和地点
		/// </param>
		/// <param name="_type">
		/// デッドゾーンの計算方式
		/// </param>
		constexpr DeadZone(double _size, double _maxValue, DeadZoneType _type)
			: size(_size)
			, maxValue(_maxValue)
			, type(_type) {}

		/// <summary>
		/// デッドゾーン無し
		/// </summary>
		/// <remarks>
		/// { 0.0, 1.0, DeadZoneType::None }
		/// </remarks>
		const static DeadZone None;

		/// <summary>
		/// デッドゾーンの大きさ
		/// </summary>
		double size = 0.0;

		/// <summary>
		/// 飽和地点
		/// </summary>
		double maxValue = 1.0;

		/// <summary>
		/// デッドゾーンの計算方式
		/// </summary>
		DeadZoneType type = DeadZoneType::None;
	};

	/// <summary>
	/// ゲームパッド
	/// </summary>
	class Gamepad
	{
	private:

		uint32 m_userIndex;

	public:

		/// <summary>
		/// 指定したインデックスのゲームパッドにアクセスします。
		/// </summary>
		/// <param name="userIndex">
		/// インデックス
		/// </param>
		Gamepad(uint32 userIndex);

		/// <summary>
		/// 接続されているかを示します。
		/// </summary>
		bool isConnected() const;

		/// <summary>
		/// Z 軸を持つかを示します。
		/// </summary>
		Property_Get(bool, hasZ) const;

		/// <summary>
		/// R 軸を持つかを示します。
		/// </summary>
		Property_Get(bool, hasR) const;

		/// <summary>
		/// U 軸を持つかを示します。
		/// </summary>
		Property_Get(bool, hasU) const;

		/// <summary>
		/// V 軸を持つかを示します。
		/// </summary>
		Property_Get(bool, hasV) const;

		/// <summary>
		/// POV を持つかを示します。
		/// </summary>
		Property_Get(bool, hasPOV) const;

		/// <summary>
		/// X 軸の値 [0.0-1.0] を示します。
		/// </summary>
		Property_Get(double, x) const;

		/// <summary>
		/// Y 軸の値 [0.0-1.0] を示します。
		/// </summary>
		Property_Get(double, y) const;

		/// <summary>
		/// Z 軸の値 [0.0-1.0] を示します。
		/// </summary>
		Property_Get(double, z) const;

		/// <summary>
		/// R 軸の値 [0.0-1.0] を示します。
		/// </summary>
		Property_Get(double, r) const;

		/// <summary>
		/// U 軸の値 [0.0-1.0] を示します。
		/// </summary>
		Property_Get(double, u) const;

		/// <summary>
		/// V 軸の値 [0.0-1.0] を示します。
		/// </summary>
		Property_Get(double, v) const;
	
		Property_Get(Key, povForward) const;
		
		Property_Get(Key, povRight) const;
	
		Property_Get(Key, povBackward) const;

		Property_Get(Key, povLeft) const;

		/// <summary>
		/// ボタンの総数を示します。
		/// </summary>
		Property_Get(uint32, num_buttons) const;

		/// <summary>
		/// 軸の総数を示します。
		/// </summary>
		Property_Get(uint32, num_axes) const;

		/// <summary>
		/// 指定した番号のボタンの情報を返します。
		/// </summary>
		/// <param name="number">
		/// ボタン番号
		/// </param>
		/// <returns>
		/// ボタンの情報
		/// </returns>
		Key button(uint32 number) const;

		/// <summary>
		/// インデックス
		/// </summary>
		Property_Get(uint32, index) const;
	};
}
