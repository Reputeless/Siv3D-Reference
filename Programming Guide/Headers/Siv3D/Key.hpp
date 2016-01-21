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
# include "PropertyMacro.hpp"
# include "Array.hpp"
# include "Utility.hpp"

namespace s3d
{
	enum class KeyDeviceType : uint8
	{
		Keyboard,

		Gamepad,

		XInput,
	};

	/// <summary>
	/// キー
	/// </summary>
	/// <remarks>
	/// 入力デバイスのキーやボタンを示します。
	/// </remarks>
	class Key
	{
	private:

		KeyDeviceType m_deviceType = KeyDeviceType::Keyboard;

		uint8 m_userIndex = 0;

		uint8 m_code = 0;

		uint8 m_reserved = 0;

	public:

		struct VirtualKeyCode{};

		struct GamepadKeyCode{};

		struct XInputKeyCode{};

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Key() = default;

		/// <summary>
		/// アルファベットか数字でキーを指定します。
		/// </summary>
		/// <param name="alnum">
		/// アルファベットか数字
		/// </param>
		explicit Key(wchar alnum);

		/// <summary>
		/// 仮想キーコードでキーを指定します。
		/// </summary>
		/// <param name="code">
		/// 仮想キーコード
		/// </param>
		constexpr Key(uint8 code, const VirtualKeyCode&)
			: m_deviceType(KeyDeviceType::Keyboard)
			, m_code(code) {}

		constexpr Key(uint32 userIndex, uint8 code, const GamepadKeyCode&)
			: m_deviceType(KeyDeviceType::Gamepad)
			, m_userIndex(static_cast<uint8>(userIndex))
			, m_code(code) {}

		constexpr Key(uint32 userIndex, uint8 code, const XInputKeyCode&)
			: m_deviceType(KeyDeviceType::XInput)
			, m_userIndex(static_cast<uint8>(userIndex))
			, m_code(code) {}

		/// <summary>
		/// キーがクリックされたことを示します。
		/// </summary>
		Property_Get(bool, clicked) const;

		/// <summary>
		/// キーが押されていることを示します。
		/// </summary>
		Property_Get(bool, pressed) const;

		/// <summary>
		/// キーが離されたことを示します。
		/// </summary>
		Property_Get(bool, released) const;

		/// <summary>
		/// キーが押されている場合、押し始めからの経過時間を示します。
		/// </summary>
		Property_Get(int32, pressedDuration) const;

		/// <summary>
		/// キーが指すデバイスを示します。
		/// </summary>
		Property_Get(KeyDeviceType, device) const
		{
			return m_deviceType;
		}

		/// <summary>
		/// 仮想キーコードを示します。
		/// </summary>
		Property_Get(uint8, code) const
		{
			return m_code;
		}

		/// <summary>
		/// ユーザーインデックスを示します。
		/// </summary>
		Property_Get(uint8, userIndex) const
		{
			return m_userIndex;
		}
	};

	/// <summary>
	/// 2 つのキーが同じキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが同じキーを示している場合 true, それ以外の場合は false
	/// </returns>
	inline bool operator == (const Key& key1, const Key& key2)
	{
		return key1.device == key2.device
			&& key1.code == key2.code
			&& key1.userIndex == key2.userIndex;
	}

	/// <summary>
	/// 2 つのキーが異なるキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが異なるキーを示している場合 true, それ以外の場合は false
	/// </returns>
	inline bool operator != (const Key& key1, const Key& key2)
	{
		return !(key1 == key2);
	}

	/// <summary>
	/// キーの組み合わせ（プラス）
	/// </summary>
	/// <remarks>
	/// 1 つ目のキーが押されている状態のとき 2 つ目のキー入力を調べます。
	/// </remarks>
	class PlusCombinedKeys
	{
	private:

		Key m_key1, m_key2;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		PlusCombinedKeys() = default;

		/// <summary>
		/// キーの組み合わせを設定します。
		/// </summary>
		/// <param name="key1">
		/// 1 つ目のキー
		/// </param>
		/// <param name="key2">
		/// 2 つ目のキー
		/// </param>
		constexpr PlusCombinedKeys(Key key1, Key key2)
			: m_key1(key1)
			, m_key2(key2) {}

		/// <summary>
		/// 1 つ目のキーが押されているときに、2 つ目のキーがクリックされたことを示します。
		/// </summary>
		Property_Get(bool, clicked) const
		{
			return m_key1.pressed && m_key2.clicked;
		}

		/// <summary>
		/// 1 つ目のキーが押されているときに、2 つ目のキーが押されていることを示します。
		/// </summary>
		Property_Get(bool, pressed) const
		{
			const auto t1 = m_key1.pressedDuration, t2 = m_key2.pressedDuration;

			if (t1 < t2)
			{
				return false;
			}

			return m_key1.pressed && m_key2.pressed;
		}

		/// <summary>
		/// 1 つ目のキーが押されているときに、2 つ目のキーが離されたことを示します。
		/// </summary>
		Property_Get(bool, released) const
		{
			return m_key1.pressed && m_key2.released;
		}

		Property_Get(int32, pressedDuration) const
		{
			const auto t1 = m_key1.pressedDuration, t2 = m_key2.pressedDuration;
			const bool pr = m_key1.pressed && m_key2.pressed;

			if (!pr || t1 < t2)
			{
				return 0;
			}

			return t2;
		}

		Property_Get(Key, key1) const
		{
			return m_key1;
		}

		Property_Get(Key, key2) const
		{
			return m_key2;
		}
	};

	/// <summary>
	/// キーの組み合わせ（プラス）を設定します。
	/// </summary>
	/// <param name="key1">
	/// 1 つ目のキー
	/// </param>
	/// <param name="key2">
	/// 2 つ目のキー
	/// </param>
	/// <returns>
	/// キーの組み合わせ（プラス）
	/// </returns>
	inline constexpr PlusCombinedKeys operator + (Key key1, Key key2)
	{
		return{ key1, key2 };
	}

	/// <summary>
	/// 2 つのキーが同じキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが同じキーを示している場合 true, それ以外の場合は false
	/// </returns>
	inline bool operator == (const PlusCombinedKeys& key1, const PlusCombinedKeys& key2)
	{
		return key1.key1 == key2.key1 && key1.key2 == key2.key2;
	}

	/// <summary>
	/// 2 つのキーが異なるキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが異なるキーを示している場合 true, それ以外の場合は false
	/// </returns>
	inline bool operator != (const PlusCombinedKeys& key1, const PlusCombinedKeys& key2)
	{
		return !(key1 == key2);
	}

	class KeyCombination
	{
	private:

		Array<Key> m_keys;

		Array<PlusCombinedKeys> m_pkeys;

		template <class Type, class ... Args>
		void append(const Type& key, const Args& ... args)
		{
			append(key);
			append(args...);
		}

		void append();

		void append(Key key);

		void append(PlusCombinedKeys key);

		void append(const KeyCombination& vkey);

	public:

		template <class ... Args>
		explicit KeyCombination(const Args& ... args)
		{
			append(args...);
		}

		template <class Type>
		KeyCombination& operator |= (const Type& key)
		{
			append(key);
			return *this;
		}

		/// <summary>
		/// キーがクリックされたことを示します。
		/// </summary>
		Property_Get(bool, clicked) const;

		/// <summary>
		/// キーが押されていることを示します。
		/// </summary>
		Property_Get(bool, pressed) const;

		/// <summary>
		/// キーが離されたことを示します。
		/// </summary>
		Property_Get(bool, released) const;

		Property_Get(int32, num_pressed) const;

		Property_Get(int32, pressedDuration) const;

		Property_Get(const Array<Key>&, keys) const
		{
			return m_keys;
		}

		Property_Get(const Array<PlusCombinedKeys>&, plusCombinedKeys) const
		{
			return m_pkeys;
		}
	};

	inline KeyCombination operator | (Key key1, Key key2)
	{
		return KeyCombination(key1, key2);
	}

	inline KeyCombination operator | (Key key1, const PlusCombinedKeys& key2)
	{
		return KeyCombination(key1, key2);
	}

	inline KeyCombination operator | (Key key1, const KeyCombination& key2)
	{
		return KeyCombination(key1, key2);
	}


	inline KeyCombination operator | (const PlusCombinedKeys& key1, Key key2)
	{
		return KeyCombination(key1, key2);
	}

	inline KeyCombination operator | (const PlusCombinedKeys& key1, const PlusCombinedKeys& key2)
	{
		return KeyCombination(key1, key2);
	}

	inline KeyCombination operator | (const PlusCombinedKeys& key1, const KeyCombination& key2)
	{
		return KeyCombination(key1, key2);
	}


	inline KeyCombination operator | (const KeyCombination& key1, Key key2)
	{
		return KeyCombination(key1, key2);
	}

	inline KeyCombination operator | (const KeyCombination& key1, const PlusCombinedKeys& key2)
	{
		return KeyCombination(key1, key2);
	}

	inline KeyCombination operator | (const KeyCombination& key1, const KeyCombination& key2)
	{
		return KeyCombination(key1, key2);
	}

	bool operator == (const KeyCombination& key1, const KeyCombination& key2);

	inline bool operator != (const KeyCombination& key1, const KeyCombination& key2)
	{
		return !(key1 == key2);
	}

	/// <summary>
	/// 入力
	/// </summary>
	/// <remarks>
	/// ユーザの入力に関する機能を提供します。
	/// </remarks>
	namespace Input
	{
		/// <summary>
		/// マウス左ボタン
		/// </summary>
		constexpr Key MouseL{0x01, Key::VirtualKeyCode{}};

		/// <summary>
		/// マウス右ボタン
		/// </summary>
		constexpr Key MouseR{0x02, Key::VirtualKeyCode{}};

		/// <summary>
		/// マウス中央ボタン
		/// </summary>
		constexpr Key MouseM{0x04, Key::VirtualKeyCode{}};

		/// <summary>
		/// マウス X1 ボタン
		/// </summary>
		constexpr Key MouseX1{0x05, Key::VirtualKeyCode{}};

		/// <summary>
		/// マウス X2 ボタン
		/// </summary>
		constexpr Key MouseX2{0x06, Key::VirtualKeyCode{}};

		/// <summary>
		/// Ctrl + break キー
		/// </summary>
		constexpr Key KeyCancel{0x03, Key::VirtualKeyCode{}};

		/// <summary>
		/// Backspace キー
		/// </summary>
		constexpr Key KeyBackspace{0x08, Key::VirtualKeyCode{}};

		/// <summary>
		/// Tab キー
		/// </summary>
		constexpr Key KeyTab{0x09, Key::VirtualKeyCode{}};

		/// <summary>
		/// Clear(NumLock を外した状態のテンキー5) キー
		/// </summary>
		constexpr Key KeyClear{0x0C, Key::VirtualKeyCode{}};

		/// <summary>
		/// Enter キー
		/// </summary>
		constexpr Key KeyEnter{0x0D, Key::VirtualKeyCode{}};

		/// <summary>
		/// Shift キー
		/// </summary>
		constexpr Key KeyShift{0x10, Key::VirtualKeyCode{}};

		/// <summary>
		/// Ctrl キー
		/// </summary>
		constexpr Key KeyControl{0x11, Key::VirtualKeyCode{}};

		/// <summary>
		/// Alt キー
		/// </summary>
		constexpr Key KeyAlt{0x12, Key::VirtualKeyCode{}};

		/// <summary>
		/// Pause キー
		/// </summary>
		constexpr Key KeyPause{0x13, Key::VirtualKeyCode{}};

		/// <summary>
		/// Escape キー
		/// </summary>
		constexpr Key KeyEscape{0x1B, Key::VirtualKeyCode{}};

		/// <summary>
		/// スペースキー
		/// </summary>
		constexpr Key KeySpace{0x20, Key::VirtualKeyCode{}};

		/// <summary>
		/// PageUp キー
		/// </summary>
		constexpr Key KeyPageUp{0x21, Key::VirtualKeyCode{}};

		/// <summary>
		/// PageDown キー
		/// </summary>
		constexpr Key KeyPageDown{0x22, Key::VirtualKeyCode{}};

		/// <summary>
		/// End キー
		/// </summary>
		constexpr Key KeyEnd{0x23, Key::VirtualKeyCode{}};

		/// <summary>
		/// Home キー
		/// </summary>
		constexpr Key KeyHome{0x24, Key::VirtualKeyCode{}};

		/// <summary>
		/// ← キー
		/// </summary>
		constexpr Key KeyLeft{0x25, Key::VirtualKeyCode{}};

		/// <summary>
		/// ↑ キー
		/// </summary>
		constexpr Key KeyUp{0x26, Key::VirtualKeyCode{}};

		/// <summary>
		/// → キー
		/// </summary>
		constexpr Key KeyRight{0x27, Key::VirtualKeyCode{}};

		/// <summary>
		/// ↓ キー
		/// </summary>
		constexpr Key KeyDown{0x28, Key::VirtualKeyCode{}};

		/// <summary>
		/// PrintScreen キー
		/// </summary>
		constexpr Key KeyPrintScreen{0x2C, Key::VirtualKeyCode{}};

		/// <summary>
		/// Insert キー
		/// </summary>
		constexpr Key KeyInsert{0x2D, Key::VirtualKeyCode{}};

		/// <summary>
		/// Delete キー
		/// </summary>
		constexpr Key KeyDelete{0x2E, Key::VirtualKeyCode{}};

		/// <summary>
		/// 左 Shift キー
		/// </summary>
		constexpr Key KeyLShift{0xA0, Key::VirtualKeyCode{}};

		/// <summary>
		/// 右 Shift キー
		/// </summary>
		constexpr Key KeyRShift{0xA1, Key::VirtualKeyCode{}};

		/// <summary>
		/// 左 Ctrl キー
		/// </summary>
		constexpr Key KeyLControl{0xA2, Key::VirtualKeyCode{}};

		/// <summary>
		/// 右 Ctrl キー
		/// </summary>
		constexpr Key KeyRControl{0xA3, Key::VirtualKeyCode{}};

		/// <summary>
		/// 左 Alt キー
		/// </summary>
		constexpr Key KeyLAlt{0xA4, Key::VirtualKeyCode{}};

		/// <summary>
		/// 右 Alt キー
		/// </summary>
		constexpr Key KeyRAlt{0xA5, Key::VirtualKeyCode{}};

		/// <summary>
		/// 0 キー
		/// </summary>
		constexpr Key Key0{0x30, Key::VirtualKeyCode{}};

		/// <summary>
		/// 1 キー
		/// </summary>
		constexpr Key Key1{0x31, Key::VirtualKeyCode{}};

		/// <summary>
		/// 2 キー
		/// </summary>
		constexpr Key Key2{0x32, Key::VirtualKeyCode{}};

		/// <summary>
		/// 3 キー
		/// </summary>
		constexpr Key Key3{0x33, Key::VirtualKeyCode{}};

		/// <summary>
		/// 4 キー
		/// </summary>
		constexpr Key Key4{0x34, Key::VirtualKeyCode{}};

		/// <summary>
		/// 5 キー
		/// </summary>
		constexpr Key Key5{0x35, Key::VirtualKeyCode{}};

		/// <summary>
		/// 6 キー
		/// </summary>
		constexpr Key Key6{0x36, Key::VirtualKeyCode{}};

		/// <summary>
		/// 7 キー
		/// </summary>
		constexpr Key Key7{0x37, Key::VirtualKeyCode{}};

		/// <summary>
		/// 8 キー
		/// </summary>
		constexpr Key Key8{0x38, Key::VirtualKeyCode{}};

		/// <summary>
		/// 9 キー
		/// </summary>
		constexpr Key Key9{0x39, Key::VirtualKeyCode{}};

		/// <summary>
		/// A キー
		/// </summary>
		constexpr Key KeyA{0x41, Key::VirtualKeyCode{}};

		/// <summary>
		/// B キー
		/// </summary>
		constexpr Key KeyB{0x42, Key::VirtualKeyCode{}};

		/// <summary>
		/// C キー
		/// </summary>
		constexpr Key KeyC{0x43, Key::VirtualKeyCode{}};

		/// <summary>
		/// D キー
		/// </summary>
		constexpr Key KeyD{0x44, Key::VirtualKeyCode{}};

		/// <summary>
		/// E キー
		/// </summary>
		constexpr Key KeyE{0x45, Key::VirtualKeyCode{}};

		/// <summary>
		/// F キー
		/// </summary>
		constexpr Key KeyF{0x46, Key::VirtualKeyCode{}};

		/// <summary>
		/// G キー
		/// </summary>
		constexpr Key KeyG{0x47, Key::VirtualKeyCode{}};

		/// <summary>
		/// H キー
		/// </summary>
		constexpr Key KeyH{0x48, Key::VirtualKeyCode{}};

		/// <summary>
		/// I キー
		/// </summary>
		constexpr Key KeyI{0x49, Key::VirtualKeyCode{}};

		/// <summary>
		/// J キー
		/// </summary>
		constexpr Key KeyJ{0x4A, Key::VirtualKeyCode{}};

		/// <summary>
		/// K キー
		/// </summary>
		constexpr Key KeyK{0x4B, Key::VirtualKeyCode{}};

		/// <summary>
		/// L キー
		/// </summary>
		constexpr Key KeyL{0x4C, Key::VirtualKeyCode{}};

		/// <summary>
		/// M キー
		/// </summary>
		constexpr Key KeyM{0x4D, Key::VirtualKeyCode{}};

		/// <summary>
		/// N キー
		/// </summary>
		constexpr Key KeyN{0x4E, Key::VirtualKeyCode{}};

		/// <summary>
		/// O キー
		/// </summary>
		constexpr Key KeyO{0x4F, Key::VirtualKeyCode{}};

		/// <summary>
		/// P キー
		/// </summary>
		constexpr Key KeyP{0x50, Key::VirtualKeyCode{}};

		/// <summary>
		/// Q キー
		/// </summary>
		constexpr Key KeyQ{0x51, Key::VirtualKeyCode{}};

		/// <summary>
		/// R キー
		/// </summary>
		constexpr Key KeyR{0x52, Key::VirtualKeyCode{}};

		/// <summary>
		/// S キー
		/// </summary>
		constexpr Key KeyS{0x53, Key::VirtualKeyCode{}};

		/// <summary>
		/// T キー
		/// </summary>
		constexpr Key KeyT{0x54, Key::VirtualKeyCode{}};

		/// <summary>
		/// U キー
		/// </summary>
		constexpr Key KeyU{0x55, Key::VirtualKeyCode{}};

		/// <summary>
		/// V キー
		/// </summary>
		constexpr Key KeyV{0x56, Key::VirtualKeyCode{}};

		/// <summary>
		/// W キー
		/// </summary>
		constexpr Key KeyW{0x57, Key::VirtualKeyCode{}};

		/// <summary>
		/// X キー
		/// </summary>
		constexpr Key KeyX{0x58, Key::VirtualKeyCode{}};

		/// <summary>
		/// Y キー
		/// </summary>
		constexpr Key KeyY{0x59, Key::VirtualKeyCode{}};

		/// <summary>
		/// Z キー
		/// </summary>
		constexpr Key KeyZ{0x5A, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 0 キー
		/// </summary>
		constexpr Key KeyNum0{0x60, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 1 キー
		/// </summary>
		constexpr Key KeyNum1{0x61, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 2 キー
		/// </summary>
		constexpr Key KeyNum2{0x62, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 3 キー
		/// </summary>
		constexpr Key KeyNum3{0x63, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 4 キー
		/// </summary>
		constexpr Key KeyNum4{0x64, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 5 キー
		/// </summary>
		constexpr Key KeyNum5{0x65, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 6 キー
		/// </summary>
		constexpr Key KeyNum6{0x66, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 7 キー
		/// </summary>
		constexpr Key KeyNum7{0x67, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 8 キー
		/// </summary>
		constexpr Key KeyNum8{0x68, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad 9 キー
		/// </summary>
		constexpr Key KeyNum9{0x69, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad * キー
		/// </summary>
		constexpr Key KeyNumMultiply{0x6A, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad + キー
		/// </summary>
		constexpr Key KeyNumAdd{0x6B, Key::VirtualKeyCode{}};

		/// <summary>
		/// Separator キー
		/// </summary>
		constexpr Key KeyNumSeparator{0x6C, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad - キー
		/// </summary>
		constexpr Key KeyNumSubtract{0x6D, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad . キー
		/// </summary>
		constexpr Key KeyNumDecimal{0x6E, Key::VirtualKeyCode{}};

		/// <summary>
		/// Numpad / キー
		/// </summary>
		constexpr Key KeyNumDivide{0x6F, Key::VirtualKeyCode{}};

		/// <summary>
		/// NumLock キー
		/// </summary>
		constexpr Key KeyNumLock{0x90, Key::VirtualKeyCode{}};

		/// <summary>
		/// F1 キー
		/// </summary>
		constexpr Key KeyF1{0x70, Key::VirtualKeyCode{}};

		/// <summary>
		/// F2 キー
		/// </summary>
		constexpr Key KeyF2{0x71, Key::VirtualKeyCode{}};

		/// <summary>
		/// F3 キー
		/// </summary>
		constexpr Key KeyF3{0x72, Key::VirtualKeyCode{}};

		/// <summary>
		/// F4 キー
		/// </summary>
		constexpr Key KeyF4{0x73, Key::VirtualKeyCode{}};

		/// <summary>
		/// F5 キー
		/// </summary>
		constexpr Key KeyF5{0x74, Key::VirtualKeyCode{}};

		/// <summary>
		/// F6 キー
		/// </summary>
		constexpr Key KeyF6{0x75, Key::VirtualKeyCode{}};

		/// <summary>
		/// F7 キー
		/// </summary>
		constexpr Key KeyF7{0x76, Key::VirtualKeyCode{}};

		/// <summary>
		/// F8 キー
		/// </summary>
		constexpr Key KeyF8{0x77, Key::VirtualKeyCode{}};

		/// <summary>
		/// F9 キー
		/// </summary>
		constexpr Key KeyF9{0x78, Key::VirtualKeyCode{}};

		/// <summary>
		/// F10 キー
		/// </summary>
		constexpr Key KeyF10{0x79, Key::VirtualKeyCode{}};

		/// <summary>
		/// F11 キー
		/// </summary>
		constexpr Key KeyF11{0x7A, Key::VirtualKeyCode{}};

		/// <summary>
		/// F12 キー
		/// </summary>
		constexpr Key KeyF12{0x7B, Key::VirtualKeyCode{}};

		/// <summary>
		/// : キー
		/// </summary>
		constexpr Key KeyColon{0xBA, Key::VirtualKeyCode{}};

		/// <summary>
		/// ; キー
		/// </summary>
		constexpr Key KeySemicolon{0xBB, Key::VirtualKeyCode{}};

		/// <summary>
		/// , キー
		/// </summary>
		constexpr Key KeyComma{0xBC, Key::VirtualKeyCode{}};

		/// <summary>
		/// - キー
		/// </summary>
		constexpr Key KeyMinus{0xBD, Key::VirtualKeyCode{}};

		/// <summary>
		/// . キー
		/// </summary>
		constexpr Key KeyPeriod{0xBE, Key::VirtualKeyCode{}};

		/// <summary>
		/// / キー
		/// </summary>
		constexpr Key KeySlash{0xBF, Key::VirtualKeyCode{}};

		/// <summary>
		/// @ キー
		/// </summary>
		constexpr Key KeyAt{0xC0, Key::VirtualKeyCode{}};

		/// <summary>
		/// [ キー
		/// </summary>
		constexpr Key KeyLBracket{0xDB, Key::VirtualKeyCode{}};

		/// <summary>
		/// \ キー
		/// </summary>
		/// </summary>
		/// <remarks>
		/// キーボードにより異なります。
		/// </remarks>
		constexpr Key KeyYen{0xDC, Key::VirtualKeyCode{}};

		/// <summary>
		/// ] キー
		/// </summary>
		constexpr Key KeyRBracket{0xDD, Key::VirtualKeyCode{}};

		/// <summary>
		/// ^ キー
		/// </summary>
		constexpr Key KeyCaret{0xDE, Key::VirtualKeyCode{}};

		/// <summary>
		/// バックスラッシュキー
		/// </summary>
		/// <remarks>
		/// キーボードにより異なります。
		/// </remarks>
		constexpr Key KeyBackslash{0xE2, Key::VirtualKeyCode{}};

		/// <summary>
		/// メディア 	Next Track ボタン
		/// </summary>
		constexpr Key KeyNextTrack{0xB0, Key::VirtualKeyCode{}};

		/// <summary>
		/// メディア 	Previous Track ボタン
		/// </summary>
		constexpr Key KeyPreviousTrack{0xB1, Key::VirtualKeyCode{}};

		/// <summary>
		/// メディア Stop ボタン
		/// </summary>
		constexpr Key KeyStopMedia{0xB2, Key::VirtualKeyCode{}};

		/// <summary>
		/// メディア Play / Pause ボタン
		/// </summary>
		constexpr Key KeyPlayPauseMedia{0xB3, Key::VirtualKeyCode{}};
	}
}
