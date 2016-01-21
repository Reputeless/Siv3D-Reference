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
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// アドオン用インタフェースクラス
	/// </summary>
	class IAddon
	{
	public:

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~IAddon() = default;

		/// <summary>
		/// アドオンの名前を返します。
		/// </summary>
		/// <remarks>
		/// 他のアドオンとかぶらない、一意の名前である必要があります。
		/// </remarks>
		/// <returns>
		/// アドオンの名前
		/// </returns>
		virtual String getName() const = 0;

		/// <summary>
		/// アドオン登録時に一度だけ呼ばれる初期化関数です。
		/// </summary>
		/// <remarks>
		/// この関数が false を返した場合、アドオンは登録されません。
		/// </remarks>
		/// <returns>
		/// 初期化に成功した場合 true, それ以外の場合は false
		/// </returns>
		virtual bool init() = 0;

		/// <summary>
		/// 毎フレーム System::Update() 関数内で呼ばれるアップデート関数です。
		/// </summary>
		/// <remarks>
		/// この関数が false を返した場合、System::Update() が false を返し、アプリケーションは終了します。
		/// </remarks>
		/// <returns>
		/// 更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		virtual bool update() = 0;
	};

	/// <summary>
	/// アドオン
	/// </summary>
	namespace Addon
	{
		/// <summary>
		/// アドオンの内部で使用する関数
		/// </summary>
		bool Register(const std::shared_ptr<IAddon>& Addon);

		/// <summary>
		/// アドオンの内部で使用する関数
		/// </summary>
		void Unregister(const String& name);

		/// <summary>
		/// アドオンの内部で使用する関数
		/// </summary>
		bool IsRegistered(const String& name);

		/// <summary>
		/// アドオンの内部で使用する関数
		/// </summary>
		IAddon* GetIAddon(const String& name);

		/// <summary>
		/// アドオンの内部で使用する関数
		/// </summary>
		template <class AddonType>
		AddonType* GetAddon()
		{
			return dynamic_cast<AddonType*>(GetIAddon(AddonType::name()));
		}

		/// <summary>
		/// アドオンを登録する
		/// </summary>
		template <class AddonType>
		bool Register()
		{
			if (Addon::IsRegistered(AddonType::name()))
			{
				return false;
			}

			if (auto p = std::dynamic_pointer_cast<IAddon>(std::make_shared<AddonType>()))
			{
				if (!p->init())
				{
					return false;
				}

				return Addon::Register(p);
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// アドオンの登録を解除する
		/// </summary>
		template <class AddonType>
		void Unregister()
		{
			return Addon::Unregister(AddonType::name());
		}

		/// <summary>
		/// アドオンが登録されているかを調べる
		/// </summary>
		template <class AddonType>
		bool IsRegistered()
		{
			return Addon::IsRegistered(AddonType::name());
		}
	}
}
