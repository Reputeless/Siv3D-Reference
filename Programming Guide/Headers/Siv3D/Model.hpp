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
# include <unordered_map>
# include "Handle.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "Mesh.hpp"

namespace s3d
{
	/// <summary>
	/// マテリアル
	/// </summary>
	struct Material
	{
		ColorF ambient;

		ColorF diffuse;

		ColorF specular;

		ColorF transmittance;

		ColorF emission;

		float shininess;

		float ior;
		
		float dissolve;

		int32 illum;

		String name;

		String ambientTextureName;

		String diffuseTextureName;

		String specularTextureName;

		String normalTextureName;
	};

	/// <summary>
	/// モデルノード
	/// </summary>
	struct ModelNode
	{
		ModelNode() = default;

		ModelNode(const String& _name, const Mesh& _mesh, const Material& _material)
			: name(_name)
			, mesh(_mesh)
			, material(_material) {}

		String name;

		Mesh mesh;

		Material material;
	};

	/// <summary>
	/// モデル
	/// </summary>
	class Model
	{
	protected:

		class Handle{};

		using ModelHandle = Siv3DHandle<Handle>;

		std::shared_ptr<ModelHandle> m_handle;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Model();

		/// <summary>
		/// 3D モデルファイルからモデルをロードします。
		/// </summary>
		/// <param name="path">
		/// 3D モデルファイルのパス
		/// </param>
		/// <remarks>
		/// Wavefront OBJ 形式のみサポートしています。
		/// </remarks>
		explicit Model(const FilePath& path);

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Model();

		/// <summary>
		/// モデルをリリースします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const Model& model) const;

		bool operator != (const Model& model) const;

		/// <summary>
		/// モデルノードの一覧を取得します。
		/// </summary>
		/// <returns>
		/// モデルノードの一覧
		/// </returns>
		const Array<ModelNode>& nodes() const;
	};
}
