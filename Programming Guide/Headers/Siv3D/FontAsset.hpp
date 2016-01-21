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
# include "Font.hpp"

namespace s3d
{
	/// <summary>
	/// Font アセットデータ
	/// </summary>
	struct FontAssetData : IAsset
	{
	public:

		static const String& name()
		{
			static const String name = L"Font";

			return name;
		}

		bool preload() override;

		bool update() override;

		bool release() override;

		const Array<AssetTag>& getTags() const override;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		FontAssetData() {}

		/// <summary>
		/// Font アセットデータを作成します。
		/// </summary>
		/// <param name="_size">
		/// フォントのサイズ
		/// </param>
		/// <param name="_fontName">
		/// フォント名
		/// </param>
		/// <param name="_style">
		/// フォントのスタイル
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
		FontAssetData(int32 _size, const String& _fontName = Typeface::Default, FontStyle _style = FontStyle::Regular, const Array<AssetTag>& _tags = {}, int _flag = AssetFlag::Default, std::function<bool(FontAssetData&)> _onPreload = nullptr, std::function<bool(FontAssetData&)> _onUpdate = nullptr, std::function<bool(FontAssetData&)> _onRelease = nullptr);

		int32 size = 12;

		String fontName;

		FontStyle style = FontStyle::Regular;

		Font font;

		Array<AssetTag> tags;

		int32 flag;

		std::function<bool(FontAssetData&)> onPreload;

		std::function<bool(FontAssetData&)> onUpdate;

		std::function<bool(FontAssetData&)> onRelease;
	};

	/// <summary>
	/// Font アセット
	/// </summary>
	class FontAsset : public Font
	{
	public:

		/// <summary>
		/// Font アセットにアクセスします。
		/// </summary>
		/// <param name="name">
		/// Font アセット名
		/// </param>
		FontAsset(const AssetName& name);

		/// <summary>
		/// Font アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Font アセット名
		/// </param>
		/// <param name="size">
		/// フォントのサイズ
		/// </param>
		/// <param name="fontName">
		/// フォント名
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
		static bool Register(const AssetName& name, int32 size, const String& fontName, const Array<AssetTag>& tags = {}, int flag = AssetFlag::Default);

		/// <summary>
		/// Font アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Font アセット名
		/// </param>
		/// <param name="size">
		/// フォントのサイズ
		/// </param>
		/// <param name="fontName">
		/// フォント名
		/// </param>
		/// <param name="style">
		/// フォントのスタイル
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
		static bool Register(const AssetName& name, int32 size, const String& fontName, FontStyle style, const Array<AssetTag>& tags = {}, int flag = AssetFlag::Default);

		/// <summary>
		/// Font アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Font アセット名
		/// </param>
		/// <param name="data">
		/// Font アセットデータ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const FontAssetData& data);

		/// <summary>
		/// 指定した名前の Font アセットがすでに登録されているかを調べます。
		/// </summary>
		/// <param name="name">
		/// 検索する名前
		/// </param>
		/// <returns>
		/// 指定した名前の Font アセットがすでに登録されている場合 true, それ以外の場合は false
		/// </returns>
		static bool IsRegistered(const AssetName& name);

		/// <summary>
		/// Font アセットをプリロードします。
		/// </summary>
		/// <param name="name">
		/// プリロードする Font アセットの名前
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Preload(const AssetName& name);

		/// <summary>
		/// Font アセットをプリロードします。
		/// </summary>
		/// <param name="tag">
		/// プリロードする Font アセットのタグ
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadByTag(const AssetTag& tag);

		/// <summary>
		/// 登録しているすべての Font アセットをプリロードします。
		/// </summary>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadAll();

		/// <summary>
		/// Font アセットをリリースします。
		/// </summary>
		/// <param name="name">
		/// リリースする Font アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Release(const AssetName& name);

		/// <summary>
		/// Font アセットをリリースします。
		/// </summary>
		/// <param name="tag">
		/// リリースする Font アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseByTag(const AssetTag& tag);

		/// <summary>
		/// すべての Font アセットをリリースします。
		/// </summary>
		/// <remarks>
		/// アセットはリリースされても登録は解除されません。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseAll();

		/// <summary>
		/// Font アセットを登録解除します。
		/// </summary>
		/// <param name="name">
		/// 登録解除する Font アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Unregister(const AssetName& name);

		/// <summary>
		/// Font アセットを登録解除します。
		/// </summary>
		/// <param name="tag">
		/// 登録解除する Font アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterByTag(const AssetTag& tag);

		/// <summary>
		/// すべての Font アセットを登録解除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterAll();
	};
}
