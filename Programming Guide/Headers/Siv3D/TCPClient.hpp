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
# include "Network.hpp"

namespace s3d
{
	class TCPClient
	{
	private:

		class CTCPClient;

		std::shared_ptr<CTCPClient> pImpl;

	public:

		TCPClient();

		bool connect(const IPv4& ip, uint16 port);

		void cancelConnect();

		bool isConnected() const;

		void disconnect();

		uint16 port() const;

		bool hasError() const;

		NetworkErrorCode getError() const;

		size_t available() const;

		bool skip(size_t size);

		bool lookahead(_Out_writes_bytes_all_(size) void* dst, size_t size) const;

		template <class Type>
		bool lookahead(Type& to) const
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return lookahead(std::addressof(to), sizeof(Type));
		}

		bool read(_Out_writes_bytes_all_(size) void* dst, size_t size);

		template <class Type>
		bool read(Type& to)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return read(std::addressof(to), sizeof(Type));
		}

		bool send(_In_reads_bytes_(size) const void* data, size_t size);

		template <class Type>
		bool send(const Type& data)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return send(&data, sizeof(Type));
		}
	};
}
