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
# include "String.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 手書き文字認識の候補
	/// </summary>
	struct HandwritingCharacter
	{
		String character;

		double score;
	};

	class HandwritingRecognizer
	{
	private:

		class CHandwritingRecognizer;

		std::shared_ptr<CHandwritingRecognizer> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		HandwritingRecognizer();

		/// <summary>
		/// 手書き文字認識学習データを開きます。
		/// </summary>
		/// <param name="modelFile">
		/// 学習データファイルのパス
		/// </param>
		/// <remarks>
		/// モデルファイルは HandwritingTrainer や
		/// https://github.com/taku910/zinnia
		/// http://sourceforge.net/projects/tomoe/
		/// を用いて作成してください。
		/// サンプルとして Hiragana.model が Example フォルダに同梱されています。
		/// </remarks>
		explicit HandwritingRecognizer(const FilePath& modelFile);

		~HandwritingRecognizer();

		bool open(const FilePath& modelFile);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		Array<HandwritingCharacter> recognize(const Size& areaSize, const Array<Array<Point>>& strokes, uint32 num_candidates = 5) const;
	};
}
