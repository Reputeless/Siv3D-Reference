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
# include "Uncopyable.hpp"
# include "PropertyMacro.hpp"

namespace s3d
{
	struct IEffect : private Uncopyable
	{
		virtual ~IEffect() = default;

		virtual bool update(double timeSec) = 0;
	};

	class Effect
	{
	private:

		class Handle{};

		using EffectHandle = Siv3DHandle<Handle>;

		std::shared_ptr<EffectHandle> m_handle;

	public:

		Effect();

		~Effect();

		bool hasEffects() const
		{
			return num_effects > 0;
		}

		Property_Get(size_t, num_effects) const;

		bool operator == (const Effect& effect) const;

		bool operator != (const Effect& effect) const;

		bool isPaused() const;

		void add(std::unique_ptr<IEffect>&& effect) const;
		
		template <class Emitter, class... Args>
		void add(Args&&... args)
		{
			add(std::make_unique<Emitter>(std::forward<Args>(args)...));
		}

		void pause() const;

		void resume() const;

		void setSpeed(double speed) const;

		double getSpeed() const;

		void update() const;

		void clear() const;
	};
}
