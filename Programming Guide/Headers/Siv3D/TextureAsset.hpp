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
# include "Texture.hpp"
# include "FileArchive.hpp"
# include "FileMonitor.hpp"

namespace s3d
{
	/// <summary>
	/// Texture アセットデータ
	/// </summary>
	struct TextureAssetData : IAsset
	{
	public:

		static const String& name()
		{
			static const String name = L"Texture";

			return name;
		}

		bool preload() override;

		bool update() override;

		bool release() override;

		const Array<AssetTag>& getTags() const override;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		TextureAssetData() {}

		/// <summary>
		/// Texture アセットデータを作成します。
		/// </summary>
		/// <param name="_path">
		/// 画像ファイルのパス
		/// </param>
		/// <param name="_desc">
		/// テクスチャの設定
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
		TextureAssetData(const FilePath& _path, TextureDesc _desc = TextureDesc::Unmipped, const Array<AssetTag>& _tags = {}, int _flag = AssetFlag::Default, std::function<bool(TextureAssetData&)> _onPreload = nullptr, std::function<bool(TextureAssetData&)> _onUpdate = nullptr, std::function<bool(TextureAssetData&)> _onRelease = nullptr);

		static TextureAssetData FromFileArchive(const FilePath& archiveFile, const FilePath& fileName, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default)
		{
			return FromFileArchive(archiveFile, fileName, TextureDesc::Unmipped, tags, flag);
		}

		static TextureAssetData FromFileArchive(const FilePath& archiveFile, const FilePath& fileName, TextureDesc desc, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default)
		{
			TextureAssetData asset;
			asset.tags = tags;
			asset.flag = flag;
			asset.onPreload = [=](TextureAssetData& d)
			{
				d.texture = Texture(FileArchive(archiveFile).load(fileName), desc);
				return !d.texture.isEmpty();
			};

			return asset;
		}

		FilePath path;

		TextureDesc desc = TextureDesc::Unmipped;

		FileMonitor monitor;

		Texture texture;

		Array<AssetTag> tags;

		int32 flag;

		std::function<bool(TextureAssetData&)> onPreload;

		std::function<bool(TextureAssetData&)> onUpdate;

		std::function<bool(TextureAssetData&)> onRelease;
	};

	/// <summary>
	/// Texture アセット
	/// </summary>
	class TextureAsset : public Texture
	{
	public:

		/// <summary>
		/// Texture アセットにアクセスします。
		/// </summary>
		/// <param name="name">
		/// Texture アセット名
		/// </param>
		TextureAsset(const AssetName& name);

		/// <summary>
		/// Texture アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Texture アセット名
		/// </param>
		/// <param name="_path">
		/// 画像ファイルのパス
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
		static bool Register(const AssetName& name, const FilePath& path, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default);

		/// <summary>
		/// Texture アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Texture アセット名
		/// </param>
		/// <param name="_path">
		/// 画像ファイルのパス
		/// </param>
		/// <param name="_desc">
		/// テクスチャの設定
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
		static bool Register(const AssetName& name, const FilePath& path, TextureDesc desc, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default);

		/// <summary>
		/// Texture アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Texture アセット名
		/// </param>
		/// <param name="data">
		/// Texture アセットデータ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const TextureAssetData& data);

		/// <summary>
		/// 指定した名前の Texture アセットがすでに登録されているかを調べます。
		/// </summary>
		/// <param name="name">
		/// 検索する名前
		/// </param>
		/// <returns>
		/// 指定した名前の Texture アセットがすでに登録されている場合 true, それ以外の場合は false
		/// </returns>
		static bool IsRegistered(const AssetName& name);

		/// <summary>
		/// Texture アセットをプリロードします。
		/// </summary>
		/// <param name="name">
		/// プリロードする Texture アセットの名前
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Preload(const AssetName& name);

		/// <summary>
		/// Texture アセットをプリロードします。
		/// </summary>
		/// <param name="tag">
		/// プリロードする Texture アセットのタグ
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadByTag(const AssetTag& tag);

		/// <summary>
		/// 登録しているすべての Texture アセットをプリロードします。
		/// </summary>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadAll();

		/// <summary>
		/// Texture アセットをリリースします。
		/// </summary>
		/// <param name="name">
		/// リリースする Texture アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Release(const AssetName& name);

		/// <summary>
		/// Texture アセットをリリースします。
		/// </summary>
		/// <param name="tag">
		/// リリースする Texture アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseByTag(const AssetTag& tag);

		/// <summary>
		/// すべての Texture アセットをリリースします。
		/// </summary>
		/// <remarks>
		/// アセットはリリースされても登録は解除されません。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseAll();

		/// <summary>
		/// Texture アセットを登録解除します。
		/// </summary>
		/// <param name="name">
		/// 登録解除する Texture アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Unregister(const AssetName& name);

		/// <summary>
		/// Texture アセットを登録解除します。
		/// </summary>
		/// <param name="tag">
		/// 登録解除する Texture アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterByTag(const AssetTag& tag);

		/// <summary>
		/// すべての Texture アセットを登録解除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterAll();
	};
}
