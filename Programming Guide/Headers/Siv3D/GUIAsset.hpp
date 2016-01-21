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
# include "Asset.hpp"
# include "GUI.hpp"

namespace s3d
{
	/// <summary>
	/// GUI アセットデータ
	/// </summary>
	struct GUIAssetData : IAsset
	{
	public:

		static const String& name()
		{
			static const String name = L"GUI";

			return name;
		}

		bool preload() override;

		bool update() override;

		bool release() override;

		const Array<AssetTag>& getTags() const override;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		GUIAssetData() = default;

		/// <summary>
		/// GUI アセットデータを作成します。
		/// </summary>
		/// <param name="_style">
		/// GUI スタイル
		/// </param>
		/// <param name="_tags">
		/// アセットのタグ
		/// </param>
		/// <param name="_flag">
		/// アセット作成フラグ
		/// </param>
		/// <param name="_onPreload">
		/// アセットのプリロード時に実行するカスタムコールバック
		/// </param>
		/// <param name="_onUpdate">
		/// アセットの更新時に実行するカスタムコールバック
		/// </param>
		/// <param name="_onRelease">
		/// アセットのリリース時に実行するカスタムコールバック
		/// </param>
		GUIAssetData(const GUIStyle& _style, const Array<AssetTag>& _tags = {}, int32 _flag = AssetFlag::Default, std::function<bool(GUIAssetData&)> _onPreload = nullptr, std::function<bool(GUIAssetData&)> _onUpdate = nullptr, std::function<bool(GUIAssetData&)> _onRelease = nullptr);

		GUIStyle style = GUIStyle::Default;

		GUI gui;

		Array<AssetTag> tags;

		int32 flag;

		std::function<bool(GUIAssetData&)> onPreload;

		std::function<bool(GUIAssetData&)> onUpdate;

		std::function<bool(GUIAssetData&)> onRelease;
	};

	/// <summary>
	/// GUI アセット
	/// </summary>
	class GUIAsset : public GUI
	{
	public:

		/// <summary>
		/// GUI アセットにアクセスします。
		/// </summary>
		/// <param name="name">
		/// GUI アセット名
		/// </param>
		GUIAsset(const AssetName& name);

		/// <summary>
		/// GUI アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// GUI アセット名
		/// </param>
		/// <param name="style">
		/// GUI のスタイル
		/// </param>
		/// <param name="tags">
		/// アセットのタグ
		/// </param>
		/// <param name="flag">
		/// アセット作成フラグ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const GUIStyle& style, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default);

		/// <summary>
		/// GUI アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// GUI アセット名
		/// </param>
		/// <param name="data">
		/// GUI アセットデータ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const GUIAssetData& data);

		/// <summary>
		/// 指定した名前の GUI アセットがすでに登録されているかを調べます。
		/// </summary>
		/// <param name="name">
		/// 検索する名前
		/// </param>
		/// <returns>
		/// 指定した名前の GUI アセットがすでに登録されている場合 true, それ以外の場合は false
		/// </returns>
		static bool IsRegistered(const AssetName& name);

		/// <summary>
		/// GUI アセットをプリロードします。
		/// </summary>
		/// <param name="name">
		/// プリロードする GUI アセットの名前
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Preload(const AssetName& name);

		/// <summary>
		/// GUI アセットをプリロードします。
		/// </summary>
		/// <param name="tag">
		/// プリロードする GUI アセットのタグ
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadByTag(const AssetTag& tag);

		/// <summary>
		/// 登録しているすべての GUI アセットをプリロードします。
		/// </summary>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadAll();

		/// <summary>
		/// GUI アセットをリリースします。
		/// </summary>
		/// <param name="name">
		/// リリースする GUI アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Release(const AssetName& name);

		/// <summary>
		/// GUI アセットをリリースします。
		/// </summary>
		/// <param name="tag">
		/// リリースする GUI アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseByTag(const AssetTag& tag);

		/// <summary>
		/// すべての GUI アセットをリリースします。
		/// </summary>
		/// <remarks>
		/// アセットはリリースされても登録は解除されません。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseAll();

		/// <summary>
		/// GUI アセットを登録解除します。
		/// </summary>
		/// <param name="name">
		/// 登録解除する GUI アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Unregister(const AssetName& name);

		/// <summary>
		/// GUI アセットを登録解除します。
		/// </summary>
		/// <param name="tag">
		/// 登録解除する GUI アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterByTag(const AssetTag& tag);

		/// <summary>
		/// すべての GUI アセットを登録解除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterAll();
	};
}
