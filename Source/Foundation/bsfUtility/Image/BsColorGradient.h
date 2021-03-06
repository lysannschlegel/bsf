//************************************ bs::framework - Copyright 2018 Marko Pintera **************************************//
//*********** Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed. ***********//
#pragma once

#include "Prerequisites/BsPrerequisitesUtil.h"
#include "Image/BsColor.h"
#include "Allocators/BsPoolAlloc.h"

namespace bs 
{
	/** @addtogroup Image
	 *  @{
	 */

	/** Single key in a ColorGradient. */
	struct BS_SCRIPT_EXPORT(m:Image,pl:true) ColorGradientKey
	{
		ColorGradientKey() = default;
		ColorGradientKey(const Color& color, float time)
			:color(color), time(time)
		{ }

		Color color;
		float time = 0.0f;
	};

	/** 
	 * Represents a range of color values over some parameters, similar to a curve. Internally represented as a set of
	 * keys that get interpolated between.
	 */
	class BS_UTILITY_EXPORT BS_SCRIPT_EXPORT(m:Image) ColorGradient
	{
		static constexpr UINT32 MAX_KEYS = 8;
	public:
		BS_SCRIPT_EXPORT()
		ColorGradient() = default;

		BS_SCRIPT_EXPORT()
		ColorGradient(const Color& color);

		BS_SCRIPT_EXPORT()
		ColorGradient(const Vector<ColorGradientKey>& keys);

		/** Evaluates a color at the specified @p t. */
		RGBA evaluate(float t) const;

		/** Set of keys that control the gradient, sorted by time from first to last. */
		BS_SCRIPT_EXPORT()
		void setKeys(const Vector<ColorGradientKey>& keys);

		/** Specify a "gradient" that represents a single color value. */
		BS_SCRIPT_EXPORT()
		void setConstant(const Color& color);

		/** 
		 * Returns the duration over which the gradient values are interpolated over. Corresponds to the time value of the
		 * final keyframe.
		 */
		float getDuration() const { return mDuration; }
	private:
		friend struct RTTIPlainType<ColorGradient>;

		RGBA mColors[MAX_KEYS];
		uint16_t mTimes[MAX_KEYS];
		uint32_t mNumKeys = 0;
		float mDuration = 0.0f;
	};

	/* @} */

	IMPLEMENT_GLOBAL_POOL(ColorGradient, 32)
}
