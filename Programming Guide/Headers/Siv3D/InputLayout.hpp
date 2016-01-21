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
# include "Handle.hpp"
# include "String.hpp"
# include "TextureFormat.hpp"

namespace s3d
{
	enum class InputClassification
	{
		PerVertex = 0,

		PerInstance = 1,
	};

	struct InputElementDesc
	{
		InputElementDesc(
			const std::string& _semanticName = "",
			uint32 _semanticIndex = 0,
			TextureFormat _format = TextureFormat::Unknown,
			uint32 _inputSlot = 0,
			uint32 _alignedByteOffset = 0,
			InputClassification _inputSlotClass = InputClassification::PerVertex,
			uint32 _instanceDataStepRate = 0
			)
			: semanticName(_semanticName)
			, semanticIndex(_semanticIndex)
			, format(_format)
			, inputSlot(_inputSlot)
			, alignedByteOffset(_alignedByteOffset)
			, inputSlotClass(_inputSlotClass)
			, instanceDataStepRate(_instanceDataStepRate) {}

		std::string semanticName;
		
		uint32 semanticIndex;
		
		TextureFormat format;
		
		uint32 inputSlot;
		
		uint32 alignedByteOffset;
		
		InputClassification inputSlotClass;
		
		uint32 instanceDataStepRate;
	};

	class InputLayout
	{
	private:

		class Handle{};

		using InputLayoutHandle = Siv3DHandle<Handle>;

		std::shared_ptr<InputLayoutHandle> m_handle;

	public:

		InputLayout();

		InputLayout(const Array<InputElementDesc>& inputElementDesc, const VertexShader& vertexShader);

		~InputLayout();

		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const InputLayout& inputLayout) const;

		bool operator != (const InputLayout& inputLayout) const;
	};
}
